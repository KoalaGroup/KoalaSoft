/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_sim_createMatrices(Double_t beamMom = 2.6, Int_t nEvents = 100, const char* outdir="./", TString mcEngine = "TGeant4")
{
  // ----    Debug option   -------------------------------------------------
  gDebug = 0;

  FairLogger *logger = FairLogger::GetLogger();
  //  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
  //  logger->SetLogToFile(kTRUE);
  //  logger->SetLogVerbosityLevel("HIGH");
  //  logger->SetLogFileLevel("DEBUG4");
  logger->SetLogScreenLevel("WARNING");
    
  TString dir = getenv("VMCWORKDIR");

  // Output file name
  TString outFile =Form("%s/elastic_ideal_%.1fGeV_%d.root", outdir, beamMom, nEvents);
    
  // output Parameter file name
  TString parFile=Form("%s/elastic_ideal_param_%.1f_%d.root", outdir, beamMom, nEvents);
  
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
  
    KoaPPElasticIdealGenerator* idealGen = new KoaPPElasticIdealGenerator(beamMom);
    idealGen->SetAlphaRange(0,20);
    primGen->AddGenerator(idealGen);

  // Add filter
  KoaEvtFilterOnGeometry* evtFilter = new KoaEvtFilterOnGeometry("evtFilter");
  evtFilter->SetX(-90.432);
  evtFilter->SetZRange(-3,30);
  evtFilter->SetYRange(-10,10);
  primGen->AndFilter(evtFilter);

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
  

  //sadly, the align parameters are only available AFTER we called fRun->Init()

  // We fill a std::map<std::string, TGeoHMatrix> map with all misalignment matrices
  // how you get those in your geometry is up to you

  auto matrices = rec_det->getMisalignmentMatrices();

  ofstream myfile;
  myfile.open ("misalignmentMatrices.txt");

  double *rot;
  double *trans;

  // this can probably be done more elegantly
  for(auto &mat : matrices){
    myfile << mat.first << "\n";
    rot = mat.second.GetRotationMatrix();
    trans = mat.second.GetTranslation();
    for(int i=0; i<9; i++)  myfile << rot[i] << "\n";
    for(int i=0; i<3; i++)  myfile << trans[i] << "\n";
  }

  matrices = fwd_det->getMisalignmentMatrices();
  for(auto &mat : matrices){
    myfile << mat.first << "\n";
    rot = mat.second.GetRotationMatrix();
    trans = mat.second.GetTranslation();
    for(int i=0; i<9; i++)  myfile << rot[i] << "\n";
    for(int i=0; i<3; i++)  myfile << trans[i] << "\n";
  }
  myfile.close();

  LOG(info) << "AlignHandler: all matrices added!";

  LOG(info) << "SUCCESS! All matrices created and saved!";

  return;
}


