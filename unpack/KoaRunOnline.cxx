#include "KoaRunOnline.h"
#include "FairRootManager.h"
#include "FairTask.h"
#include "FairEventHeader.h"
#include "FairRuntimeDb.h"
#include "FairRunIdGenerator.h"
#include "FairLogger.h"
#include "FairFileHeader.h"
#include "FairParIo.h"
#include "FairBaseParSet.h"
#include "FairGeoParSet.h"
#include "FairField.h"
#include "FairSource.h"

#include "TFile.h"
#include "THttpServer.h"
#include "TGeoManager.h"
#include "TSystem.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TROOT.h"
#include "TList.h"
#include "TObjArray.h"
#include "TCollection.h"

#include <signal.h>

Bool_t gKOAIsInterrupted;

void KOA_handler_ctrlc(int)
{
  LOG(info) << "*********** CTRL C PRESSED *************";
  gKOAIsInterrupted = kTRUE;
}

KoaRunOnline* KoaRunOnline::fgRinstance = 0;

KoaRunOnline* KoaRunOnline::Instance()
{
  return fgRinstance;
}

KoaRunOnline::KoaRunOnline()
  :FairRun(),
   fRunInfo(),
   fIsInitialized(kFALSE),
   fAutomaticFinish(kTRUE),
   fStaticParamContainer(kFALSE),
   fInputGeoFile(nullptr),
   fLoadGeo(kFALSE),
   fNevents(0),
   fServer(nullptr),
   fServerRefreshRate(0)
{
  fgRinstance = this;
  fAna = kTRUE;
  LOG(info) << "KoaRunOnline constructed at " << this;
}

KoaRunOnline::~KoaRunOnline()
{
  if (gGeoManager) {
    if (gROOT->GetVersionInt() >= 60602) {
      gGeoManager->GetListOfVolumes()->Delete();
      gGeoManager->GetListOfShapes()->Delete();
    }
    delete gGeoManager;
  }

  delete fServer;
}

void KoaRunOnline::Init()
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

  /* 3) Get geometry from user-provided geometry file, if flag is set */
  if (fLoadGeo) {
    if (fInputGeoFile!=0) { //First check if the user has a separate Geo file!
      TIter next(fInputGeoFile->GetListOfKeys());
      TKey* key;
      while ((key =dynamic_cast< TKey*>(next()))) {
        if (strcmp(key->GetClassName(),"TGeoManager") != 0) {
          continue;
        }
        gGeoManager = dynamic_cast<TGeoManager*>(key->ReadObj());
        break;
      }
    }
  }

  // 3) Instancize FairEventHeader and register it for output
  GetEventHeader();
  fEvtHeader->Register(kTRUE);

  // 4) Generate a new Run ID on the fly and pass it to all related objects
  // TODO the source can also be the generator of run id, implement an alternative
  FairRunIdGenerator genid;
  fRunId = genid.generateId();

  fEvtHeader->SetRunId(fRunId);
  fRootManager->GetSource()->SetRunId(fRunId);
  fRtdb->addRun(fRunId);
  fFileHeader->SetRunId(fRunId);

  // 5) Parameters
  // 5.1 Fetch all the parameters used in tasks
  fTask->SetParTask(); 

  // 5.2 Fetch all the parameters used in unpackers
  fRootManager->GetSource()->SetParUnpackers();

  // 5.3 Initilization (where the real reading from the file take place)
  fRtdb->initContainers(fRunId);

  // 5.4 Prepare the common parameters BaseSet and GeoSet for output
  FairBaseParSet* par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
  TList* containerList = fRtdb->getListOfContainers();
  TIter next(containerList);
  FairParSet* cont;
  TObjArray* ContList= new TObjArray();
  while ((cont=dynamic_cast<FairParSet*>(next()))) {
    ContList->Add(new TObjString(cont->GetName()));
  }
  if (par) {
    par->SetContListStr(ContList);
    // par->SetRndSeed(gRandom->GetSeed());
    par->setChanged();
    par->setInputVersion(fRunId,1);
  }

  FairGeoParSet* geopar = dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
  if (geopar) {
    geopar->SetGeometry(gGeoManager);
    geopar->setChanged();
    geopar->setInputVersion(fRunId,1);
  }

  // 6) Init Unpackers for decoding
  fRootManager->GetSource()->InitUnpackers();

  // 7) Init all other tasks
  gROOT->GetListOfBrowsables()->Add(fTask);
  fTask->InitTask();

  // 8) Align geometry
  if(fLoadGeo) {
    AlignGeometry();
  }

  // 9) Write Folder and FileHeader
  fRootManager->WriteFolder();
  fRootManager->WriteFileHeader(fFileHeader);

  return;
}

Int_t KoaRunOnline::EventLoop()
{
  // 0) register ctrl-c behavior
  gSystem->IgnoreInterrupt();
  signal(SIGINT, KOA_handler_ctrlc);

  // 1) Fetch the latest event header information, i.e. run id, event time , entry number
  fRootManager->FillEventHeader(fEvtHeader);

  // 2) Check if it's a new run or not, since the run id may come from the source
  // TODO is it necessary if the run id is generated by KoaRunOnline on the fly
  Int_t tmpId = fEvtHeader->GetRunId();
  if ( tmpId != -1 && tmpId != fRunId ) {
    LOG(info) << "Call Reinit due to changed RunID (from " << fRunId << " to " << tmpId;
    // 2.1) set current run id to new one
    fRunId = tmpId;

    if ( !fStaticParamContainer ) {
      // 2.2) read the parameters with new run id
      Reinit( fRunId );

      // 2.3) since parameters are re-read, unpackers and tasks need re-init as well
      fRootManager->GetSource()->ReInitUnpackers();
      fTask->ReInitTask();
    }
  }

  // 3) Timebased run ??
  fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());

  // 4) Execute all tasks
  fTask->ExecuteTask("");

  // TODO Is it necessary to Fill the Event Header again?
  // fRootManager->FillEventHeader(fEvtHeader);

  // 5) Fill the output tree
  Fill();

  // 6) Clean up at the end of event processing
  fRootManager->DeleteOldWriteoutBufferData();
  fTask->FinishEvent();

  // 7) Save System Run Info if flag is set
  if (fGenerateRunInfo) {
    fRunInfo.StoreInfo();
  }

  // 8) Histogram server maintainence
  fNevents += 1;
  if(fServer && 0 == (fNevents%fServerRefreshRate))
  {
    fServer->ProcessRequests();
  }

  // 9) User interrupted
  if(gKOAIsInterrupted)
  {
    LOG(warn) << "Event loop was interrupted by the user!";
    return 1;
  }

  return 0;
}

//_____________________________________________________________________________
void KoaRunOnline::Run(Int_t Ev_start, Int_t Ev_end)
{
  fNevents = 0;

  gKOAIsInterrupted = kFALSE;
  
  // 1. Checking the max number of events allowed. For ONLINE source, it always return -1
  // TODO remove this checking?
  // Int_t MaxAllowed=fRootManager->CheckMaxEventNo(Ev_end);
  // if ( MaxAllowed != -1 ) {
  //   if (Ev_end==0) {
  //     if (Ev_start==0) {
  //       Ev_end=MaxAllowed;
  //     } else {
  //       Ev_end =  Ev_start;
  //       if ( Ev_end > MaxAllowed ) {
  //         Ev_end = MaxAllowed;
  //       }
  //       Ev_start=0;
  //     }
  //   } else {
  //     if (Ev_end > MaxAllowed) {
  //       cout << "-------------------Warning---------------------------" << endl;
  //       cout << " -W FairRunAna : File has less events than requested!!" << endl;
  //       cout << " File contains : " << MaxAllowed  << " Events" << endl;
  //       cout << " Requested number of events = " <<  Ev_end <<  " Events"<< endl;
  //       cout << " The number of events is set to " << MaxAllowed << " Events"<< endl;
  //       cout << "-----------------------------------------------------" << endl;
  //       Ev_end = MaxAllowed;
  //     }
  //   }
  // }

  // 2) entering the event loop
  Int_t status;
  if(Ev_start < 0) {
    // default is an infinite loop until the end of source file or interrupted by user
    while(kTRUE) {
      // 2.1 read next event from source
      status = fRootManager->ReadEvent();

      if(0 == status) { // a new valid event available, entering main event loop
        status = EventLoop();
      }

      if(1 == status) { // source is not readable anymore or interrupted by user while in main event loop
        break;
      }
      else if(2 == status) { // the current event-reading from source failed, skip to next event
        continue;
      }

      if(gKOAIsInterrupted) // interrupted by the user at this loop
      {
        LOG(warn) << "Event loop was interrupted by the user!";
        break;
      }
    }
  }
  else {
    // alternative, is to read Ev_start valid events from source, then stop or interrupted by user
    for (Int_t entry = 0; entry < Ev_start; entry++) {
      status = fRootManager->ReadEvent();

      if(0 == status) { // a new valid event available, entering main event loop
        status = EventLoop();
      }

      if(1 == status) { // source is not readable anymore or interrupted by user while in main event loop
        break;
      }
      else if (2 == status) { // the current event-reading from source failed, skip to next event
        entry -= 1; // this event does not count
        continue;
      }

      if(gKOAIsInterrupted) // interrupted by the user at this loop
      {
        LOG(warn) << "Event loop was interrupted by the user!";
        break;
      }
    }
  }
 
  // 3) Cleaning job at the end of Run
  fRootManager->StoreAllWriteoutBufferData();
  if (fAutomaticFinish) {
    Finish();
  }
}

void KoaRunOnline::Reinit(UInt_t runId)
{
  // reading the parameters again with new runId
  fRtdb->initContainers( runId );
}

void  KoaRunOnline::SetGeomFile(const char* GeoFileName)
{
  if (fIsInitialized) {
    LOG(fatal) << "Geometry file has to be set before Run::Init !";
    exit(-1);
  }
  else {
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

void KoaRunOnline::SetContainerStatic(Bool_t tempBool)
{
  fStaticParamContainer = tempBool;
  if ( fStaticParamContainer ) {
    LOG(info) << "Parameter Cont. initialisation is static, not changed with run id";
  } else {
    LOG(info) << "Parameter Cont. initialisation is NOT static, reload every time run id changes";
  }
}

void KoaRunOnline::Finish()
{
  // finish tasks
  fTask->FinishTask();

  // write system running information if needed
  if (fGenerateRunInfo) {
    fRunInfo.WriteInfo();
  }

  // write to the output sink
  fRootManager->LastFill();
  fRootManager->Write();

  // close source and sink
  fRootManager->GetSource()->Close();
  fRootManager->CloseSink();
}

/* Copied from KoaRunOnline */
void KoaRunOnline::Fill()
{
  if(fMarkFill) {
    fRootManager->Fill();
  }
  else {
    fMarkFill = kTRUE;
  }
}

void KoaRunOnline::AddObject(TObject* object)
{
  if(object && fServer) {
    TString classname = TString(object->ClassName());
    if(classname.EqualTo("TCanvas")) {
      fServer->Register("CANVAS", object);
    }
    else if(classname.EqualTo("TFolder")) {
      fServer->Register("/", object);
    }
    else if(classname.Contains("TH1") || classname.Contains("TH2")) {
      fServer->Register("HISTO", object);
    }
    else {
      LOG(warn) << "KoaRunOnline::AddObject : unrecognized object type : " << classname;
    }
  }
}

void KoaRunOnline::RegisterHttpCommand(TString name, TString command)
{
  if(fServer) {
    TString path = "/Objects/HISTO";
    fServer->RegisterCommand(name, path + command);
  }
}

void KoaRunOnline::ActivateHttpServer(Int_t refreshRate, Int_t httpServer)
{
  TString serverAddress="http:";
  serverAddress+=httpServer;
  fServer = new THttpServer(serverAddress);
  fServerRefreshRate = refreshRate;
}

ClassImp(KoaRunOnline)
