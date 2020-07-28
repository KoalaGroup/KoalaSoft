int KoaPixel0SimDPMDirect(
    const int nEvents = 10,
    const int startEvent = 0,
    const double mom = 3.2,
    TString storePath = "tmpOutput",
    const int verboseLevel = 0,
    const int seed = 177013)
{
  gRandom->SetSeed(seed);
  TStopwatch timer;
  timer.Start();
  gDebug = 0;

  TString simOutput = storePath + "/Koala_MC_";
  simOutput += startEvent;
  simOutput += ".root";
  TString parOutput = storePath + "/Koala_Params_";
  parOutput += startEvent;
  parOutput += ".root";
  FairRunSim *fRun = new FairRunSim();

  fRun->SetName("TGeant4");
  fRun->SetOutputFile(simOutput);
  fRun->SetMaterials("media_pnd.geo");

  FairModule *Cave = new KoaCave("CAVE");
  Cave->SetGeometryFileName("pndcaveVAC.geo");
  fRun->AddModule(Cave);

  Koaladetector *Koala = new Koaladetector("KOALA", kTRUE);
  Koala->SetGeometryFileName("../geometry/scripts/Koala-Detector.root");
  Koala->SetVerboseLevel(verboseLevel);
  fRun->AddModule(Koala);

  PndLmdDetector *Lum = new PndLmdDetector("LUM", kTRUE);
  Lum->SetGeometryFileName("../geometry/scripts/LumiDetector.root");
  Lum->SetVerboseLevel(verboseLevel);
  fRun->AddModule(Lum);

  FairPrimaryGenerator *primGen = new FairPrimaryGenerator();
  fRun->SetGenerator(primGen);

  FairBoxGenerator *fBox = new FairBoxGenerator(2212, 1);
  fBox->SetPRange(mom, mom);
  fBox->SetThetaRange(0.13, 0.65); // 2... 11 mrad 0.13 and 0.65
  fBox->SetPhiRange(0, 360.);
  primGen->AddGenerator(fBox);

  fRun->SetBeamMom(mom);

  if (nEvents < 201)
    fRun->SetStoreTraj(kTRUE); // toggle this for use with EVE
  else
    fRun->SetStoreTraj(kFALSE);

  fRun->Init();

  FairRuntimeDb *rtdb = fRun->GetRuntimeDb();
  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo *output = new FairParRootFileIo(kParameterMerged);
  output->open(parOutput.Data(), "RECREATE");
  rtdb->setOutput(output);

  fRun->Run(nEvents);

  rtdb->saveOutput();
  rtdb->print();

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  printf("RealTime=%f seconds, CpuTime=%f seconds\n", rtime, ctime);
  return 0;
}
