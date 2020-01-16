void run_sim_filtered(Int_t nEvents = 100, Int_t pdgid=0, const char* outdir="./", TString mcEngine = "TGeant4")
{
  FairLogger *logger = FairLogger::GetLogger();
  //  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
  //  logger->SetLogToFile(kTRUE);
  //  logger->SetLogVerbosityLevel("HIGH");
  //  logger->SetLogFileLevel("DEBUG4");
  // logger->SetLogScreenLevel("WARNING");
  logger->SetLogScreenLevel("INFO");

  // Set the random seed
  gRandom->SetSeed(98989);
    
  TString dir = getenv("VMCWORKDIR");
  // Output file name
  // TString outFile ="test_filtered.root";
  TString outFile =Form("%s/filtered_solidAngle_pdg%d_%d.root", outdir, pdgid, nEvents);
    
  // Parameter file name
  TString parFile=Form("%s/filtered_solidAngle_param_pdg%d_%d.root",outdir, pdgid, nEvents);
  
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
  // ------------------------------------------------------------------------

  // -----   Create simulation run   ----------------------------------------
  FairRunSim* run = new FairRunSim();

  // The name of FairRunSim should be TGeant4, TGeant3 or TFluka
  // TFluka is deprecated, I think.
  // Based on the name of FairRunSim, different MC configuration and engine will be selected
  run->SetName(mcEngine);              // Transport engine

  // the output root where simulation result (hits and digits) are saved
  // run->SetOutputFile(outFile);          // Output file
  run->SetSink(new FairRootFileSink(outFile));
  FairRuntimeDb* rtdb = run->GetRuntimeDb();
  // ------------------------------------------------------------------------
  
  // -----   Create media   -------------------------------------------------
  // Important: the materials used by all detector modules in the simultation is
  // defined in a single file and imported here.
  run->SetMaterials("media.geo");       // Materials
  // ------------------------------------------------------------------------
  
  // -----   Create geometry   ----------------------------------------------

  FairModule* cave= new KoaCave("CAVE");
  cave->SetGeometryFileName("cave.geo");
  run->AddModule(cave);

  // KoaPipe* pipe = new KoaPipe("Pipe");
  // run->AddModule(pipe);
    
  KoaRec* rec_det = new KoaRec("KoaRec", kTRUE);
  rec_det->SetGeometryFileName("rec.root");
  rec_det->SetModifyGeometry(kTRUE);
  run->AddModule(rec_det);

  KoaFwd* fwd_det = new KoaFwd("KoaFwd", kTRUE);
  fwd_det->SetGeometryFileName("fwd.root");
  fwd_det->SetModifyGeometry(kTRUE);
  run->AddModule(fwd_det);
 // ------------------------------------------------------------------------

  // -----   Create PrimaryGenerator   --------------------------------------
  FairFilteredPrimaryGenerator* primGen = new FairFilteredPrimaryGenerator();
  
    // Add a box generator also to the run
    FairBoxGenerator* boxGen = new FairBoxGenerator(pdgid, 1); //0 = rootino/geantino, 2212 = proton; 1 = multipl.
    boxGen->SetPRange(3.4,3.4); // GeV/c
    boxGen->SetPhiRange(0., 360.); // Azimuth angle range [degree]
    boxGen->SetThetaRange(0., 180.); // Polar angle in lab system range [degree]
    boxGen->SetXYZ(0., 0., 0.); // cm
    primGen->AddGenerator(boxGen);

    // // Particle Gun
    // FairParticleGenerator* parGen = new FairParticleGenerator(13, 1, 20,0.5,0);
    // primGen->AddGenerator(parGen);

    // P-P elastic generator
    // KoaPpelasticGenerator* ppGen = new KoaPpelasticGenerator("Background-micro.root");
    // KoaPpelasticGenerator* ppGen = new KoaPpelasticGenerator("PPelast.root");
  
    // KoaPpelasticGenerator* ppGen = new KoaPpelasticGenerator(2.8);
    // primGen->AddGenerator(ppGen);

    // Add filter
    KoaEvtFilterOnGeometry* evtFilter = new KoaEvtFilterOnGeometry("evtFilter");
    evtFilter->SetX(-90.432);
    evtFilter->SetZRange(-3,30);
    evtFilter->SetYRange(-10,10);
    primGen->AndFilter(evtFilter);
    // primGen->AndNotFilter(evtFilter);

  run->SetGenerator(primGen);
// ------------------------------------------------------------------------
 
  //---Store the visualiztion info of the tracks, this make the output file very large!!
  //--- Use it only to display but not for production!
  // run->SetStoreTraj(kTRUE);

  // -----   Runtime database   ---------------------------------------------

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open(parFile.Data());
  rtdb->setOutput(parOut);

  FairParAsciiFileIo* parIn = new FairParAsciiFileIo();
  parIn->open(parFileList, "in");
  rtdb->setFirstInput(parIn);
  // ------------------------------------------------------------------------
    
  // -----   Initialize simulation run   ------------------------------------
  run->Init();
  // ------------------------------------------------------------------------
   
  // -----   Start run   ----------------------------------------------------
   run->Run(nEvents);
    
   rtdb->saveOutput();
   rtdb->print();

  //You can export your ROOT geometry ot a separate file
  run->CreateGeometryFile("geofile_full.root");
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


