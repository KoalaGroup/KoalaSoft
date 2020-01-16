/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_unpack(const char* data)
{
  // Input file (MC events)
  TString inFile(data);

  // Output file
  TString outFile(data);
  outFile.ReplaceAll(".cl",".root");

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Decoding run   -------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  KoaRunOnline *fRun = new KoaRunOnline();

  // Setup ems configuration
  KoaEmsConfig* emsConfig = new KoaEmsConfig();

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
    KoaEmsAssembler *assembler = new KoaEmsAssembler();
    fFileSource->SetAssembler(assembler);
  
    // Config analyzer
    KoaEventAnalyzer* koalaAnalyzer = new KoaEventAnalyzer();
    fFileSource->SetKoaEventAnalyzer(koalaAnalyzer);
    KoaEmsEventAnalyzer* emsAnalyzer = new KoaEmsEventAnalyzer();
    fFileSource->SetEmsEventAnalyzer(emsAnalyzer);

  fRun->SetSource(fFileSource);

  // Setup sink
  FairRootFileSink *fFileSink = new FairRootFileSink(outFile);
  fRun->SetSink(fFileSink);

  // -----   Parameters   --------------------------------------------------------

  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  // FairParRootFileIo* parInput1 = new FairParRootFileIo();
  // parInput1->open(parFile.Data(), "UPDATE");
  // rtdb->setFirstInput(parInput1);

  // FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
  // TList *parFileList = new TList();
  // TString paramDir = dir + "/parameters/";
  // TString paramfile_fwd = paramDir + "fwd.par";
  // TObjString *paramFile_fwd = new TObjString(paramfile_fwd);
  // parFileList->Add(paramFile_fwd);
  // TString paramfile_rec = paramDir + "rec.par";
  // TObjString *paramFile_rec = new TObjString(paramfile_rec);
  // parFileList->Add(paramFile_rec);
  // parInput2->open(parFileList,"in");
  // rtdb->setSecondInput(parInput2);

  // rtdb->setOutput(parInput1);

  // -----   Tasks   --------------------------------------------------------

  // Transform to simulation data format, i.e. TClonesArray based
  KoaRawEventTransform *evtTransTask = new KoaRawEventTransform();

  // -----   Init   --------------------------------------------------------
  fRun->Init();

  // -----   Run   --------------------------------------------------------
  timer.Start();
  fRun->Run();

  rtdb->saveOutput();
  rtdb->print();

  // -----   Finish   --------------------------------------------------------
  delete emsConfig;

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
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}
