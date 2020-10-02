void run_sim_gaussian_vertex(Double_t beamMom = 2.6, Int_t nEvents = 100, const char* outdir="./", TString mcEngine = "TGeant4")
{
  // ----    Debug option   -------------------------------------------------
  gDebug = 0;

  FairLogger *logger = FairLogger::GetLogger();
  //  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
  //  logger->SetLogToFile(kTRUE);
   // logger->SetLogVerbosityLevel("HIGH");
  //  logger->SetLogFileLevel("DEBUG4");
  logger->SetLogScreenLevel("WARNING");
    
  TString dir = getenv("VMCWORKDIR");

  // Output file name
  TString outFile =Form("%s/pp_%.1fGeV_%d.root", outdir, beamMom, nEvents);
    
  // output Parameter file name
  TString parFile=Form("%s/pp_param_%.1f_%d.root", outdir, beamMom, nEvents);
  
  // input Parameter file name
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
  run->SetSink(new FairRootFileSink(outFile));
  // run->SetOutputFile(outFile);          // Output file
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

    
  // -----   Create PrimaryGenerator   --------------------------------------
  FairFilteredPrimaryGenerator* primGen = new FairFilteredPrimaryGenerator();
  
    // KoaPPElasticIdealGenerator* idealGen = new KoaPPElasticIdealGenerator(beamMom);
    // // idealGen->SetGeantino();
    // idealGen->SetAlphaRange(0,20);
    // primGen->AddGenerator(idealGen);

    KoaPpelasticGenerator* ppGen = new KoaPpelasticGenerator(beamMom);
    primGen->AddGenerator(ppGen);

  // Add filter
  KoaEvtFilterOnGeometry* evtFilter = new KoaEvtFilterOnGeometry("evtFilter");
  evtFilter->SetX(-90.432);
  evtFilter->SetZRange(-3,30); // real: [-2.85,23.95]
  evtFilter->SetYRange(-10,10); // real: [-5.675, 5.675]
  primGen->AndFilter(evtFilter);

  // Smear Interaction Vertex with Gaussian distribution
  primGen->SmearGausVertexZ(kTRUE);
  primGen->SetTarget(0, 3); // residual gas thickness sigma 3 cm
  primGen->SmearGausVertexXY(kTRUE);
  primGen->SetBeam(0, 0, 1., 1.); // beam profile sigma: 10 mm

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


