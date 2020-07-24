/* Just used to simulate nEvents empty events.
 * It's used as a prerequiste for noise generator
 */

// pdg_id :
//   proton : 2212
//   pion   : 211
//   muon   : 13
void run_sim_mip(Int_t nEvents = 100, const char* outdir="./",
                 Int_t pdg_id = 2212,
                 TString mcEngine = "TGeant4")
{
  FairLogger *logger = FairLogger::GetLogger();
  //  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
  //  logger->SetLogToFile(kTRUE);
  //  logger->SetLogVerbosityLevel("HIGH");
  //  logger->SetLogFileLevel("DEBUG4");
  logger->SetLogScreenLevel("WARNING");
  // logger->SetLogScreenLevel("INFO");

  TString dir = getenv("VMCWORKDIR");
  // Output file name
  TString outFile =Form("%s/mip_%d_%d.root", outdir, pdg_id, nEvents);
    
  // Parameter file name
  TString parFile=Form("%s/param_mip_%d_%d.root",outdir, pdg_id, nEvents);
  
  TList *parFileList = new TList();
  TString paramDir = dir + "/parameters/";

  TString paramfile_rec = paramDir + "rec.par";
  TObjString* paramFile_rec = new TObjString(paramfile_rec);
  parFileList->Add(paramFile_rec);

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

  KoaRec* rec_det = new KoaRec("KoaRec", kTRUE);
  rec_det->SetGeometryFileName("rec.root");
  rec_det->SetModifyGeometry(kTRUE);
  run->AddModule(rec_det);

  KoaFwd* fwd_det = new KoaFwd("KoaFwd", kTRUE);
  fwd_det->SetGeometryFileName("fwd.root");
  run->AddModule(fwd_det);
 // ------------------------------------------------------------------------

  // -----   Create PrimaryGenerator   --------------------------------------
  FairFilteredPrimaryGenerator* primGen = new FairFilteredPrimaryGenerator();

    // Add a box generator also to the run
    FairBoxGenerator* boxGen = new FairBoxGenerator(pdg_id, 1); //0 = rootino/geantino, 2212 = proton; 1 = multipl.
    boxGen->SetEkinRange(2, 4);// set kinematic energy range in GeV
    boxGen->SetPhiRange(0., 360.); // Azimuth angle range [degree]
    boxGen->SetThetaRange(0., 180.); // Polar angle in lab system range [degree]
    boxGen->SetXYZ(0., 0., 0.); // cm
    primGen->AddGenerator(boxGen);

    // Add filter
    KoaEvtFilterOnGeometry* evtFilter = new KoaEvtFilterOnGeometry("evtFilter");
    evtFilter->SetX(-90.432);
    evtFilter->SetZRange(-3,30);
    evtFilter->SetYRange(-10,10);
    primGen->AndFilter(evtFilter);

  run->SetGenerator(primGen);
// ------------------------------------------------------------------------
 
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


