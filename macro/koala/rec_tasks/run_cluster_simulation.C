/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * Clustering of simulation data with a full chain of digitization (energy value):
 * Specifically, electronic noises are added to each channel.
 * Thus, in this case, a clustering chain from NoiseFilter is needed.
 * However, the pedestal noise parameter file should be energy-equivalent noise
 * file. Because it's energy digis, not ADC digits are generated in simulation.
 */

void run_cluster_simulation(const char* data,
                            const char* para,
                            const char* suffix = "_digi.root",
                            const char* ped_file = "adc_pedestal_20190902_003449_energy.txt",
                            const char* ped_adcfile = "adc_pedestal_20190902_003449.txt",
                            const char* adcpara_file = "adc_calib_energy.txt"
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

  // Parameter file
  TString paraFile(para);

  // Output file
  TString outFile = inFile;
  outFile.ReplaceAll(suffix, "_cluster.root");


  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Parameter Directories   --------------------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";
  TString pedestal_file = param_dir + ped_file;
  TString pedestal_adcfile = param_dir + ped_adcfile;
  TString adcparaFile = param_dir + adcpara_file;

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

  // 1. filter out digis below noise level
  KoaRecNoiseFilter* noiseFilter = new KoaRecNoiseFilter();
  noiseFilter->SetInputDigiName("KoaRecDigi");
  noiseFilter->SetOutputDigiName("RecDigi_NoiseFilter");
  // noiseFilter->SaveOutputDigi(true);
  noiseFilter->SetPedestalFile(pedestal_file.Data());
  noiseFilter->SetThreshold(2);
  fRun->AddTask(noiseFilter);

  // 2. filter out clusters where there is no seed digi, output is array of remaining digis
  KoaRecClusterSeedFilter* seedFilter = new KoaRecClusterSeedFilter();
  seedFilter->SetInputDigiName("RecDigi_NoiseFilter");
  seedFilter->SetOutputDigiName("RecDigi_ClusterSeedFilter");
  seedFilter->SaveOutputDigi(true);
  seedFilter->SetMode(ClusterSeedMode::Pedestal);
  seedFilter->SetPedestalFile(pedestal_file.Data());
  seedFilter->SetThreshold(5);
  fRun->AddTask(seedFilter);

  // 3. clustering based on adjacency
  KoaRecClusterCollect* clusterCollect = new KoaRecClusterCollect();
  clusterCollect->SetInputDigiName("RecDigi_ClusterSeedFilter");
  clusterCollect->SetOutputClusterName("KoaRecCluster_SeedFilter");
  clusterCollect->SaveOutputCluster(true);
  fRun->AddTask(clusterCollect);

  // 4. filter out clusters where the total energy is below noise threshold (combination of composing digis)
  KoaRecClusterThresholdFilter* clusterThresholdFilter = new KoaRecClusterThresholdFilter();
  clusterThresholdFilter->SetInputClusterName("KoaRecCluster_SeedFilter");
  clusterThresholdFilter->SetOutputClusterName("KoaRecCluster_ThresholdFilter");
  clusterThresholdFilter->SaveOutputCluster(true);
  clusterThresholdFilter->SetAdcParaFile(adcparaFile.Data());
  clusterThresholdFilter->SetPedestalFile(pedestal_adcfile.Data());
  clusterThresholdFilter->SetThreshold(5);
  fRun->AddTask(clusterThresholdFilter);

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
