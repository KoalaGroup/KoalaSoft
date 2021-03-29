/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_rec_clusternoise(const char* data,
                          const char* out_directory = "./",
                          const char* suffix = "_calib.root",
                          const char* ped_file = "adc_pedestal_20190902_003449.txt",
                          const char* adcpara_file = "adc_calib_energy.txt",
                          const char* tdcpara_file = "tdc_calib_shift.txt",
                          const char* clustersize_file = "cluster_size.txt"
                          )
{
  // ----    Debug option   -------------------------------------------------
  gDebug = 0;

  FairLogger *logger = FairLogger::GetLogger();
  logger->SetLogToScreen(kTRUE);
  // logger->SetLogScreenLevel("DEBUG");
  logger->SetLogScreenLevel("INFO");

  // Input file (MC events)
  TString inFile(data);
  TString baseName = gSystem->BaseName(inFile.Data());

  // Parameter file
  TString paraFile(data);
  paraFile.ReplaceAll(".root", "_param.root");

  // Output file
  TString outDir = gSystem->ExpandPathName(out_directory);
  TString outFile = gSystem->ConcatFileName(outDir.Data(), baseName.Data());
  outFile.ReplaceAll(".root", suffix);


  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Parameter Directories   --------------------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";
  TString pedestal_file = param_dir + ped_file;
  TString adcparaFile = param_dir + adcpara_file;
  TString tdcparaFile = param_dir + tdcpara_file;
  TString clusterSizeFile = param_dir + clustersize_file;

  // -----   Run   --------------------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  FairFileSource *fFileSource = new FairFileSource(inFile);
  fRun->SetSource(fFileSource);
  fRun->SetSink(new FairRootFileSink(outFile));

  // parameter container
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(paraFile.Data());
  // rtdb->setOutput(parInput1);

  // 1. filter out digis with ADC counts below noise level
  KoaRecNoiseFilter* noiseFilter = new KoaRecNoiseFilter();
  noiseFilter->SetInputDigiName("KoaRecDigi");
  noiseFilter->SetOutputDigiName("RecDigi_NoiseFilter");
  // noiseFilter->SaveOutputDigi(true);
  noiseFilter->SetPedestalFile(pedestal_file.Data());
  noiseFilter->SetThreshold(2);
  fRun->AddTask(noiseFilter);

  // 2. clustering based on adjacency
  KoaRecClusterCollect* clusterCollectDigi = new KoaRecClusterCollect();
  clusterCollectDigi->SetInputDigiName("RecDigi_NoiseFilter");
  clusterCollectDigi->SetOutputClusterName("RecCluster_Digis");
  clusterCollectDigi->SaveOutputCluster(false);
  fRun->AddTask(clusterCollectDigi);

  // 3. filter out noise clusters
  KoaRecClusterNoiseFilter* clusterNoiseFilter = new KoaRecNoiseFilter();
  clusterNoiseFilter->SetInputClusterName("RecCluster_Digis");
  clusterNoiseFilter->SetOutputDigiName("RecDigi_ClusterNoiseFilter")

  // 4. filter out clusters where there is no seed digi, output is array of remaining digis
  KoaRecClusterSeedFilter* seedFilter = new KoaRecClusterSeedFilter();
  seedFilter->SetInputDigiName("RecDigi_ClusterNoiseFilter");
  seedFilter->SetOutputDigiName("RecDigi_ClusterSeedFilter");
  seedFilter->SetPedestalFile(pedestal_file.Data());
  seedFilter->SetThreshold(3);
  fRun->AddTask(seedFilter);

  // 5. correct recoil front channels' time offset for digis with valid timestamp
  KoaRecTimeShiftCorrect* timeshiftCorrect = new KoaRecTimeShiftCorrect();
  timeshiftCorrect->SetInputDigiName("RecDigi_ClusterSeedFilter");
  timeshiftCorrect->SetOutputDigiName("RecDigi_TimeShift");
  // timeshiftCorrect->SaveOutputDigi(true);
  timeshiftCorrect->SetTdcParaFile(tdcparaFile.Data());
  timeshiftCorrect->SetTdcParaName("Mean");
  fRun->AddTask(timeshiftCorrect);

  // 6. reconstructed recoil front strip energy to keV
  //    and filter out digis with energy below threshold (optional)
  KoaRecEnergyRecon* energyRecon = new KoaRecEnergyRecon();
  energyRecon->SetInputDigiName("RecDigi_TimeShift");
  energyRecon->SetOutputDigiName("KoaRecCalib");
  energyRecon->SaveOutputDigi(true);
  energyRecon->SetAdcParaFile(adcparaFile.Data());
  energyRecon->SetThreshold(0);
  fRun->AddTask(energyRecon);

  // 7. dumy recoil rear side reconstruction, just copy the raw digis
  KoaRecRearRecon* rearRecon = new KoaRecRearRecon();
  // rearRecon->SetInputDigiName("KoaRecRearDigi");
  // rearRecon->SetOutputDigiName("KoaRecRearDigi");
  fRun->AddTask(rearRecon);

  // 8. clustering based on adjacency
  KoaRecClusterCollect* clusterCollect = new KoaRecClusterCollect();
  clusterCollect->SetInputDigiName("KoaRecCalib");
  clusterCollect->SetOutputClusterName("KoaRecCluster_SeedFilter");
  clusterCollect->SaveOutputCluster(true);
  fRun->AddTask(clusterCollect);

  // 8. filter out clusters where the total energy is below noise threshold (combination of composing digis)
  KoaRecClusterThresholdFilter* clusterThresholdFilter = new KoaRecClusterThresholdFilter();
  clusterThresholdFilter->SetInputClusterName("KoaRecCluster_SeedFilter");
  clusterThresholdFilter->SetOutputClusterName("KoaRecCluster_ThresholdFilter");
  clusterThresholdFilter->SaveOutputCluster(kTRUE);
  clusterThresholdFilter->SetAdcParaFile(adcparaFile.Data());
  clusterThresholdFilter->SetPedestalFile(pedestal_file.Data());
  clusterThresholdFilter->SetThreshold(5);
  fRun->AddTask(clusterThresholdFilter);

  // 9. filter out clusters with number of digis larger than a threshold
  KoaRecClusterSizeFilter* clusterSizeFilter = new KoaRecClusterSizeFilter();
  clusterSizeFilter->SetInputClusterName("KoaRecCluster_ThresholdFilter");
  clusterSizeFilter->SetOutputClusterName("KoaRecCluster_SizeFilter");
  clusterSizeFilter->SaveOutputCluster(kTRUE);
  clusterSizeFilter->SetSizeParaFile(clusterSizeFile.Data());
  // clusterSizeFilter->SetSizeParameter(5);
  fRun->AddTask(clusterSizeFilter);

  // 10. dumy fwd reconstruction, just copy the raw digis
  KoaFwdRecon* fwdRecon = new KoaFwdRecon();
  // fwdRecon->SetInputDigiName("KoaFwdDigi");
  // fwdRecon->SetOutputDigiName("KoaFwdDigi");
  fRun->AddTask(fwdRecon);

  fRun->Init();

  timer.Start();
  fRun->Run();

  // rtdb->saveOutput();
  rtdb->print();

  // -----   Finish   -------------------------------------------------------
  delete fRun;

  cout << endl << endl;

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Float_t maxMemory=sysInfo.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  Float_t cpuUsage=ctime/rtime;
  cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
  cout << cpuUsage;
  cout << "</DartMeasurement>" << endl;

  cout << endl << endl;
  cout << "Output file is "    << outFile << endl;
  cout << "Parameter file is " << paraFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}
