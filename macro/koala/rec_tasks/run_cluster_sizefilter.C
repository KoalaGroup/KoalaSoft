/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_cluster_sizefilter(const char* data,
                            const char* param_file,
                            const char* branchName = "KoaRecCluster_ThresholdFilter",
                            const char* out_directory = "./",
                            const char* suffix = "_sizefilter.root",
                            int size = 2
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
  TString paraFile(param_file);

  // Output file
  TString outDir = gSystem->ExpandPathName(out_directory);
  TString outFile = gSystem->ConcatFileName(outDir.Data(), baseName.Data());
  outFile.ReplaceAll(".root", suffix);


  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Parameter Directories   --------------------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";
  // TString clusterSizeFile = param_dir + clustersize_file;

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

  // 8. filter out clusters with number of digis larger than a threshold
  KoaRecClusterSizeFilter* clusterSizeFilter = new KoaRecClusterSizeFilter();
  clusterSizeFilter->SetInputClusterName(branchName);
  clusterSizeFilter->SetOutputClusterName("KoaRecCluster_SizeFilter");
  clusterSizeFilter->SaveOutputCluster(kTRUE);
  // clusterSizeFilter->SetSizeParaFile(clusterSizeFile.Data());
  clusterSizeFilter->SetSizeParameter(size);
  fRun->AddTask(clusterSizeFilter);

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
