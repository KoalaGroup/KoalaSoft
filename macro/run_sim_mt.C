void run_sim_mt(Int_t nEvents = 100, TString mcEngine = "TGeant4", Bool_t isMT=true)
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

  // Based on the name of FairRunSim, different MC configuration and engine will be selected
  run->SetName(mcEngine); // Transport engine
  run->SetIsMT(isMT); // multi-thread or not
  run->SetSink(new FairRootFileSink(outFile)); // Output file
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
  // if no geometry file is specified, the default one will be used.
  //pipe->SetGeometryFileName("pipe_simple.root");
  run->AddModule(pipe);
    
  FairDetector* rec_det = new KoaRec("KoaRec", kTRUE);
  rec_det->SetGeometryFileName("rec.root");
  // rec_det->SetGeometryFileName("rec_withChamber.root");
  // rec_det->SetGeometryFileName("rec.geo");
  run->AddModule(rec_det);

  FairDetector* fwd_det = new KoaFwd("KoaFwd", kTRUE);
  // fwd_det->SetGeometryFileName("fwd.root");
 // fwd_det->SetGeometryFileName("fwd_withMonitor.root");
  // fwd_det->SetGeometryFileName("fwd_withMonitor_withChamber.root");
  fwd_det->SetGeometryFileName("fwd_withMonitor_withChamber_withExtras.root");
  run->AddModule(fwd_det);

  // -----   Create PrimaryGenerator   --------------------------------------
  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  FairBoxGenerator* boxGen = new FairBoxGenerator(13, 1); // 13 = muon; 1 = multipl.
  boxGen->SetPRange(20,20); // GeV/c
  boxGen->SetPhiRange(0., 360.); // Azimuth angle range [degree]
  boxGen->SetThetaRange(0., 180.); // Polar angle in lab system range [degree]
  boxGen->SetXYZ(0., 0., 0.); // cm

  primGen->AddGenerator(boxGen);
  run->SetGenerator(primGen);
 
  //---Store the visualiztion info of the tracks, this make the output file very large!!
  //--- Use it only to display but not for production!
  run->SetStoreTraj(kFALSE);

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


