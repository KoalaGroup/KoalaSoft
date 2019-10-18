void run_sim_pythia(Int_t nEvents = 100, TString mcEngine = "TGeant4")
{
    
  // Output file name
  TString outFile =Form("pythia_%d.root",nEvents);
    
  // Parameter file name
  TString parFile=Form("pythia_param_%d.root",nEvents);
  
  // ----    Debug option   -------------------------------------------------
  gDebug = 0;

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
  run->SetOutputFile(outFile);          // Output file
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

  // FairModule* pipe = new KoaPipe("Pipe");
  // if not geometry file is specified, the default one will be used.
  // run->AddModule(pipe);
    
  FairDetector* rec_det = new KoaRec("KoaRec", kTRUE);
  rec_det->SetGeometryFileName("rec.root");
  // rec_det->SetGeometryFileName("rec_withChamber.root");
  run->AddModule(rec_det);

  FairDetector* fwd_det = new KoaFwd("KoaFwd", kTRUE);
  fwd_det->SetGeometryFileName("fwd.root");
  run->AddModule(fwd_det);

    
  // -----   Create PrimaryGenerator   --------------------------------------
  FairFilteredPrimaryGenerator* primGen = new FairFilteredPrimaryGenerator();
  
    Pythia8Generator *pythiaGen = new Pythia8Generator();
    pythiaGen->UseRandom3();
    // pythiaGen->UseRandom1();
    pythiaGen->SetMom(2.8);
    // pythiaGen->SetId(-2212);//anti-proton
    // pythiaGen->SetHNLId(id);
    pythiaGen->SetParameters("SoftQCD:all = on");
    // pythiaGen->SetParameters("SigmaTotal:sigmaTot = 106");
    pythiaGen->SetParameters("PhaseSpace:pTHatMin = 20.");
    primGen->AddGenerator(pythiaGen);

  // Add filter
  KoaEvtFilterOnGeometry* evtFilter = new KoaEvtFilterOnGeometry("evtFilter");
  evtFilter->SetX(-101);
  evtFilter->SetZRange(-5,30);
  evtFilter->SetYRange(-10,10);
  primGen->AndFilter(evtFilter);

  run->SetGenerator(primGen);
// ------------------------------------------------------------------------
 
  //---Store the visualiztion info of the tracks, this make the output file very large!!
  //--- Use it only to display but not for production!
  // run->SetStoreTraj(kTRUE);

    
    
  // -----   Initialize simulation run   ------------------------------------
  run->Init();
  // ------------------------------------------------------------------------

  // -----   Runtime database   ---------------------------------------------

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open(parFile.Data());
  rtdb->setOutput(parOut);
  rtdb->saveOutput();
  rtdb->print();
  // ------------------------------------------------------------------------
   
  // -----   Start run   ----------------------------------------------------
   run->Run(nEvents);
    
  //You can export your ROOT geometry ot a separate file
  run->CreateGeometryFile("geofile_full.root");
  // ------------------------------------------------------------------------
  
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


