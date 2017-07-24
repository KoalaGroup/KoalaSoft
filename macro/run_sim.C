void run_sim(Int_t nEvents = 100, TString mcEngine = "TGeant4")
{
    
  // Output file name
  TString outFile ="test.root";
    
  // Parameter file name
  TString parFile="params.root";
  
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

  FairModule* pipe = new KoaPipe("Pipe");
  /* if not geometry file is specified, the default one will be used.
   */
  // pipe->SetGeometryFileName("pipe_simple.root");
  run->AddModule(pipe);
    
  FairDetector* rec_det = new KoaRec("KoaRec", kTRUE);
  rec_det->SetGeometryFileName("rec.root");
  // rec_det->SetGeometryFileName("rec_geomanager.root");
  // rec_det->SetGeometryFileName("rec.geo");
  run->AddModule(rec_det);

  FairDetector* fwd_det = new KoaFwd("KoaFwd", kTRUE);
  fwd_det->SetGeometryFileName("fwd.root");
  // fwd_det->SetGeometryFileName("fwd.geo");
  run->AddModule(fwd_det);

// ------------------------------------------------------------------------


    // // -----   Magnetic field   -------------------------------------------
    // // Constant Field
    // KoaConstField  *fMagField = new KoaConstField();
    // fMagField->SetField(0., 20. ,0. ); // values are in kG
    // fMagField->SetFieldRegion(-200, 200,-200, 200, -200, 200); // values are in cm
    //                       //  (xmin,xmax,ymin,ymax,zmin,zmax)
    // run->SetField(fMagField);
    // // --------------------------------------------------------------------

    
    
  // -----   Create PrimaryGenerator   --------------------------------------
  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  
    // // Add a box generator also to the run
    // FairBoxGenerator* boxGen = new FairBoxGenerator(13, 1); // 13 = muon; 1 = multipl.
    // boxGen->SetPRange(20,20); // GeV/c
    // boxGen->SetPhiRange(1., 5.); // Azimuth angle range [degree]
    // boxGen->SetThetaRange(89., 90.); // Polar angle in lab system range [degree]
    // boxGen->SetXYZ(0., 0., 0.); // cm
    // primGen->AddGenerator(boxGen);

    // // Particle Gun
    // FairParticleGenerator* parGen = new FairParticleGenerator(13, 1, 20,0.5,0);
    // primGen->AddGenerator(parGen);

    // P-P elastic generator
    KoaPpelasticGenerator* ppGen = new KoaPpelasticGenerator("PPelast.root");
  // KoaPpelasticGenerator* ppGen = new KoaPpelasticGenerator(5);
    primGen->AddGenerator(ppGen);

    run->SetGenerator(primGen);
// ------------------------------------------------------------------------
 
  //---Store the visualiztion info of the tracks, this make the output file very large!!
  //--- Use it only to display but not for production!
  run->SetStoreTraj(kTRUE);

    
    
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


