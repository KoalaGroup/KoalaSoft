/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_cluster_purification_AbsoluteMode(const char* data,
                                           const char* para,
                                           const char* branch = "KoaRecCluster_ThresholdFilter",
                                           int threshold = 400,
                                           std::string thresh_file = "",
                                           const char* suffix = "_cluster_purification_absolute.root"
                                           )
{
  // ----    Debug option   -------------------------------------------------
  gDebug = 0;

  FairLogger *logger = FairLogger::GetLogger();
  logger->SetLogToScreen(kTRUE);
  // logger->SetLogScreenLevel("DEBUG");
  logger->SetLogScreenLevel("WARNING");

  // Input file (MC events)
  TString inFile(data);

  // Parameter file
  TString paraFile(para);

  // Output file
  bool useThreshFile = true;
  TString outFile = inFile;
  outFile.ReplaceAll(".root", suffix);
  if (thresh_file.empty()) {
      outFile.ReplaceAll(".root", Form("_%dkeV.root", threshold));
      useThreshFile = false;
  }

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Parameter Directories   --------------------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";

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

  KoaRecClusterPurification* clusterPurification = new KoaRecClusterPurification();
  clusterPurification->SetInputClusterName(branch);
  clusterPurification->SetOutputClusterName("KoaRecCluster_Purification");
  clusterPurification->SaveOutputCluster(kTRUE);

  clusterPurification->SetMode(ClusterPurificationMode::Absolute);
  if(useThreshFile)
    clusterPurification->SetThresholdFile(thresh_file.data());
  else
    clusterPurification->SetThreshold(threshold);
  fRun->AddTask(clusterPurification);

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
