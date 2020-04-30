void run_sim_pythia(Double_t beamMom = 2.6, Int_t nEvents = 100, const char* outdir = "./",  TString mcEngine = "TGeant4")
{
  FairLogger *logger = FairLogger::GetLogger();
  logger->SetLogToScreen(kTRUE);
  logger->SetLogScreenLevel("WARNING");
  // logger->SetLogScreenLevel("INFO");

  TString dir = getenv("VMCWORKDIR");
  // Output file name
  TString outFile =Form("%s/pythia_%d.root", outdir, nEvents);
    
  // Parameter file name
  TString parFile=Form("%s/param_pythia_%d.root",outdir, nEvents);
  
  TList *parFileList = new TList();
  TString paramDir = dir + "/parameters/";

  TString paramfile_rec = paramDir + "rec.par";
  TObjString* paramFile_rec = new TObjString(paramfile_rec);
  parFileList->Add(paramFile_rec);

  TString paramfile_fwd = paramDir + "fwd.par";
  TObjString* paramFile_fwd = new TObjString(paramfile_fwd);
  parFileList->Add(paramFile_fwd);

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();

  // -----   Create simulation run   ----------------------------------------
  FairRunSim* run = new FairRunSim();
  run->SetName(mcEngine);              // Transport engine

  run->SetSink(new FairRootFileSink(outFile));
  FairRuntimeDb* rtdb = run->GetRuntimeDb();

  // -----   Create media   -------------------------------------------------
  run->SetMaterials("media.geo");       // Materials
  
  // -----   Create geometry   ----------------------------------------------
  FairModule* cave= new KoaCave("CAVE");
  cave->SetGeometryFileName("cave.geo");
  run->AddModule(cave);

  KoaPipe* pipe = new KoaPipe("Pipe");
  pipe->SetGeometryFileName("pipe.root");
  run->AddModule(pipe);

  KoaRec* rec_det = new KoaRec("KoaRec", kTRUE);
  // rec_det->SetGeometryFileName("rec.root");
  rec_det->SetGeometryFileName("rec_withChamber_withColdPlate.root");
  rec_det->SetModifyGeometry(kTRUE);
  run->AddModule(rec_det);

  KoaFwd* fwd_det = new KoaFwd("KoaFwd", kTRUE);
  // fwd_det->SetGeometryFileName("fwd.root");
  fwd_det->SetGeometryFileName("fwd_withChamber_withExtra.root");
  fwd_det->SetModifyGeometry(kTRUE);
  run->AddModule(fwd_det);

 // ------------------------------------------------------------------------

  // -----   Create PrimaryGenerator   --------------------------------------
  FairFilteredPrimaryGenerator* primGen = new FairFilteredPrimaryGenerator();
  // FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  
    // Add a pythia generator also to the run
    KoaPythia8Generator *pythiaGen = new KoaPythia8Generator();
    pythiaGen->SetId(2212);
    pythiaGen->SetMom(beamMom);
    // pythiaGen->SetParameters("Main:numberOfEvents = 100");
    // pythiaGen->SetParameters("Main:numberToList = 3");
    // pythiaGen->SetParameters("Main:timesAllowErrors = 3");
    // pythiaGen->SetParameters("Init:showChangedSettings = on");
    // pythiaGen->SetParameters("Init:showChangedParticleData = off");
    pythiaGen->SetParameters("SoftQCD:all = on");
    // pythiaGen->Print();
    primGen->AddGenerator(pythiaGen);

    // Add filter
    KoaEvtFilterOnGeometry* evtFilter = new KoaEvtFilterOnGeometry("evtFilter");
    evtFilter->SetX(-90.432);
    evtFilter->SetZRange(-3,30);
    evtFilter->SetYRange(-10,10);
    primGen->AndFilter(evtFilter);

  run->SetGenerator(primGen);

  // -----   Runtime database   ---------------------------------------------

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open(parFile.Data());
  rtdb->setOutput(parOut);

  FairParAsciiFileIo* parIn = new FairParAsciiFileIo();
  parIn->open(parFileList, "in");
  rtdb->setFirstInput(parIn);
    
  // -----   Initialize simulation run   ------------------------------------
  run->Init();
   
  // -----   Start run   ----------------------------------------------------
   run->Run(nEvents);
    
   rtdb->saveOutput();
   rtdb->print();

  //You can export your ROOT geometry ot a separate file
  // run->CreateGeometryFile("geofile_full.root");
  // ------------------------------------------------------------------------

  delete run;
  
  // -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file is "    << outFile << endl;
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime 
       << "s" << endl << endl;
  // ------------------------------------------------------------------------
}

