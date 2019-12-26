void  KoaRunDecode::SetGeomFile(const char* GeoFileName)
{
  if (fIsInitialized) {
    LOG(fatal) << "Geometry file has to be set before Run::Init !";
    exit(-1);
  } else {

    TFile* CurrentFile=gFile;
    fInputGeoFile= TFile::Open(GeoFileName);
    if (fInputGeoFile->IsZombie()) {
      LOG(error) << "Error opening Geometry Input file";
      fInputGeoFile=0;
    }
    LOG(info) << "Opening Geometry input file: " << GeoFileName;
    fLoadGeo=kTRUE;
    gFile=CurrentFile;
  }
}

void KoaRunDecode::Init()
{
  // 1) Check if it's a legal Init(), one initilization in a session is allowed
  if (fIsInitialized) {
    LOG(fatal) << "Error Init is already called before!";
    exit(-1);
  } else {
    fIsInitialized=kTRUE;
  }

  if (kONLINE != fRootManager->GetSource()->GetSourceType()) {
    LOG(fatal) << "Error Source should be ONLINE type";
    exit(-1);
  }

  // 2) Init Source and Sink
  fRootManager->InitSource();
  fRootManager->InitSink();

  /* TODO Get geometry from source file, needed or not */
  // if (fLoadGeo) {
  //   if (fInputGeoFile!=0) { //First check if the user has a separate Geo file!
  //     TIter next(fInputGeoFile->GetListOfKeys());
  //     TKey* key;
  //     while ((key =dynamic_cast< TKey*>(next()))) {
  //       if (strcmp(key->GetClassName(),"TGeoManager") != 0) {
  //         continue;
  //       }
  //       gGeoManager = dynamic_cast<TGeoManager*>(key->ReadObj());
  //       break;
  //     }
  //   }
  // }

  // 3) Instancize FairEventHeader and register it for output
  GetEventHeader();
  fEvtHeader->Register(kTRUE);

  // 4) Generate a new Run ID on the fly and pass it to all related objects
  FairRunIdGenerator genid;
  fRunId = genid.generateId();

  fEvtHeader->SetRunId(fRunId);
  fRootManager->GetSource()->SetRunId(fRunId);
  fRtdb->addRun(fRunId);
  fFileHeader->SetRunId(fRunId);

  // 4) Parameters
  // 4.1 Prepare the common parameters BaseSet and GeoSet for output
  FairBaseParSet* par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
  FairGeoParSet* geopar = dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));

  TList* containerList = fRtdb->getListOfContainers();
  TIter next(containerList);
  FairParSet* cont;
  TObjArray* ContList= new TObjArray();
  while ((cont=dynamic_cast<FairParSet*>(next()))) {
    ContList->Add(new TObjString(cont->GetName()));
  }
  if (par) {
    par->SetContListStr(ContList);
    par->setChanged();
    par->setInputVersion(fRunId,1);
  }
  if (geopar) {
    geopar->SetGeometry(gGeoManager);
    geopar->setChanged();
    geopar->setInputVersion(fRunId,1);
  }

  // 4.2 Fetch all the parameters used in tasks
  fTask->SetParTask(); 

  // 4.3 Fetch all the parameters used in unpackers
  fRootManager->GetSource()->SetParUnpackers();

  // 4.4 Initilization (where the real reading from the file take place)
  fRtdb->initContainers(fRunId);

  // 5) Init Unpackers for decoding
  fRootManager->GetSource()->InitUnpackers();

  // 6) Init all other tasks
  gROOT->GetListOfBrowsables()->Add(fTask);
  fTask->InitTask();

  /* TODO Align geometry */
  // if(fLoadGeo) {
  //   AlignGeometry();
  // }

  // 7) Write Folder and FileHeader
  fRootManager->WriteFolder();
  fRootManager->WriteFileHeader(fFileHeader);

  return;
}
