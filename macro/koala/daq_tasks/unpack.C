/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// decode raw binary to TClonesArray of digis
void unpack(const char* data)
{
  // ----    Debug option   -------------------------------------------------
  gDebug = 0;

  FairLogger *logger = FairLogger::GetLogger();
  //  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
  //  logger->SetLogToFile(kTRUE);
  // logger->SetLogVerbosityLevel("HIGH");
  //  logger->SetLogFileLevel("DEBUG4");
  // logger->SetLogScreenLevel("DEBUG2");

  // Input file (MC events)
  TString inFile(data);

  // Output file
  TString outFile(data);
  outFile.ReplaceAll(".cl",".root");

  // Output param file
  TString paraFile(data);
  paraFile.ReplaceAll(".cl","_param.root");

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Parameter Directories   --------------------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";
  TString config_module_table = param_dir + "mxdc32.config";
  TString config_amplitude_map = param_dir + "mxdc32_amplitude_map.config";
  TString config_time_map = param_dir + "mxdc32_time_map.config";
  TString config_scalor_map = param_dir + "scalor_map.config";

  // -----   Decoding run   -------------------------------------------
  KoaRunOnline *fRun = new KoaRunOnline();
  // fRun->SetAutoFinish(kFALSE); // auto finish or not,  default is TRUE

  // Setup ems configuration, it's owned by user himself
  KoaEmsConfig* emsConfig = new KoaEmsConfig();
  emsConfig->SetEmsConfigFile(config_module_table.Data());
  emsConfig->SetAmplitudeChannelMap(config_amplitude_map.Data());
  emsConfig->SetTimeChannelMap(config_time_map);
  emsConfig->SetScalorChannelMap(config_scalor_map);

  // Setup ems source
  KoaEmsFileSource *fFileSource = new KoaEmsFileSource(inFile);

    // Config unpackers
    KoaScalorUnpack *scalorUnpack = new KoaScalorUnpack(1);
    fFileSource->AddUnpacker(1, scalorUnpack);
    KoaMxdc32Unpack *mxdc32Unpack = new KoaMxdc32Unpack(10);
    fFileSource->AddUnpacker(10, mxdc32Unpack);
    KoaTimeUnpack *timeUnpack = new KoaTimeUnpack(100);
    fFileSource->AddUnpacker(100, timeUnpack);

    // Config assembler
    // KoaEventAssembler *assembler = new KoaEventAssembler(); // simplest
    KoaEventLgtAsm *assembler = new KoaEventLgtAsm(); // Tobias's method
    // assembler->SetQdcTimeDiff(3);
    // assembler->SetMaxTimeDiff(4);
    fFileSource->SetAssembler(assembler);
  
    // Config analyzer
    KoaEventAnalyzer* koalaAnalyzer = new KoaEventAnalyzer();
    koalaAnalyzer->SaveRawEvent(kTRUE); // save channel-mapped raw data
    fFileSource->SetKoaEventAnalyzer(koalaAnalyzer);

    KoaEmsEventAnalyzer* emsAnalyzer = new KoaEmsEventAnalyzer();
    fFileSource->SetEmsEventAnalyzer(emsAnalyzer);

  fRun->SetSource(fFileSource);

  // Setup sink
  FairRootFileSink *fFileSink = new FairRootFileSink(outFile);
  fRun->SetSink(fFileSink);
  emsAnalyzer->SetPersistence(true);

  // -----   Parameters   --------------------------------------------------------

  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo *parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open(paraFile.Data());
  rtdb->setOutput(parOut);

  // -----   Tasks   --------------------------------------------------------

  // Transform to simulation data format, i.e. TClonesArray based
  KoaRawEventTransform *evtTransTask = new KoaRawEventTransform();
  fRun->AddTask(evtTransTask);

  // -----   Init   --------------------------------------------------------
  fRun->Init();

  // -----   Run   --------------------------------------------------------
  timer.Start();
  fRun->Run();

  rtdb->saveOutput();
  rtdb->print();

  // -----   Finish   --------------------------------------------------------
  // fRun->Finish(); // in case automatic finish is not set

  // KoaEmsConfig is owned and managed by user himself
  delete emsConfig;
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
  cout << "EMS module config table file is " << config_module_table << endl;
  cout << "Amplitude channel map file is" << config_amplitude_map << endl;
  cout << "Time channel map file is" << config_time_map << endl;
  cout << "Scalor channel map file is" << config_scalor_map << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}
