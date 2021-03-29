/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_digi_noise(const char* data,
                    const char* para,
                    const char* ped_file = "adc_pedestal_20190902_003449.txt",
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
  TString parFile(para);

  // Output file
  TString outFile(data);
  outFile.ReplaceAll(".root","_noise.root");


  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;

  // -----   Reconstruction run   -------------------------------------------
  TString dir = getenv("VMCWORKDIR");

  TString param_dir = dir+"/parameters/";
  TString pedestal_file = param_dir + ped_file;
  TString adcparaFile = param_dir + adcpara_file;

  FairRunAna *fRun= new FairRunAna();
  FairFileSource *fFileSource = new FairFileSource(inFile);
  fRun->SetSource(fFileSource);
  fRun->SetSink(new FairRootFileSink(outFile));

  // parameter container
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(parFile.Data(), "UPDATE");
  rtdb->setFirstInput(parInput1);

  FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
  TList *parFileList = new TList();
  TString paramDir = dir + "/parameters/";
  TString paramfile_fwd = paramDir + "fwd.par";
  TObjString *paramFile_fwd = new TObjString(paramfile_fwd);
  parFileList->Add(paramFile_fwd);
  TString paramfile_rec = paramDir + "rec.par";
  TObjString *paramFile_rec = new TObjString(paramfile_rec);
  parFileList->Add(paramFile_rec);
  parInput2->open(parFileList,"in");
  rtdb->setSecondInput(parInput2);

  // rtdb->setOutput(parInput1);

  //
  KoaRecAddNoise* recAddNoise = new KoaRecAddNoise();
  recAddNoise->SetInputDigiName("RecDigi_ChargeCollection");
  // recAddNoise->SetInputDigiName("KoaRecDigi");
  recAddNoise->SetOutputDigiName("RecDigi_AddNoise");
  recAddNoise->SaveOutputDigi(true);
  recAddNoise->SetPedestalFile(pedestal_file.Data());
  recAddNoise->SetAdcParaFile(adcparaFile.Data());
  fRun->AddTask(recAddNoise);

  // KoaFwdDigitization* fwdDigiTask = new KoaFwdDigitization();
  // fRun->AddTask(fwdDigiTask);

  fRun->Init();

  timer.Start();
  fRun->Run();

  // rtdb->saveOutput();
  rtdb->print();
  // -----   Finish   -------------------------------------------------------

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
