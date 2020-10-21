#include "FairRootManager.h"
#include "KoaEmsEventAnalyzer.h"
#include "KoaEmsConfig.h"
#include "KoaEmsRawEvent.h"
#include "TTree.h"

KoaEmsEventAnalyzer::~KoaEmsEventAnalyzer()
{
  if (fCurrentRawEvent) delete fCurrentRawEvent;
  if (fPreviousRawEvent) delete fPreviousRawEvent;

}

TFile* KoaEmsEventAnalyzer::InitOutputFile()
{
  FairRootManager* ioMan = FairRootManager::Instance();
  auto sink = ioMan->GetSink();
  if(!sink) {
    LOG(fatal) << "KoaEmsEventAnalyzer::InitOutputFile : no sink available, setup sink first";
  }

  TString fileName = sink->GetFileName();
  fileName.ReplaceAll(".root","_EmsRawEvent.root");
  return new TFile(fileName, "recreate");
}

void KoaEmsEventAnalyzer::InitInputBuffer()
{
  auto bufferManager = KoaEmsEventBufferManager::Instance();
  fBuffer = bufferManager->GetBuffer("EMS");
}

void KoaEmsEventAnalyzer::InitChannelMap()
{
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaEmsEventAnalyzer::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
  }
  fScalorChMap = emsConfig->GetScalorChMap();
}

void KoaEmsEventAnalyzer::InitOutputBuffer()
{
  // 1. first entry flag
  fInitialEvent = true;

  // 2. init the storage space
  fCurrentRawEvent = new KoaEmsRawEvent();
  fPreviousRawEvent = new KoaEmsRawEvent();
}

void KoaEmsEventAnalyzer::InitOutputTree()
{
  // check persistence flag, init Tree accordingly
  if ( fPersistence ) {
    fRootFile->cd();

    // raw tree containing scalor array
    fTree = new TTree("Ems","EMS Event Data");
    fTree->Branch("KoaEmsRawEvent", &fCurrentRawEvent);

    // write the scalor mapping
    fRootFile->WriteObjectAny(&fScalorChMap, "std::map<std::string,int>", "ScalorChMap");
  }
}

bool KoaEmsEventAnalyzer::Analyze()
{
  // 1. get the latest event from input buffer
  if (!NextEvent())  return true;

  // 2. decode
  Decode();

  // 3. update
  Update();

  // 4. fill tree
  FillTree();

  // 5. fill histograms
  FillHist();

  // 6. recycle input event buffer
  Recycle();

  // 7. go to next event
  Analyze();
}

bool KoaEmsEventAnalyzer::NextEvent()
{
  // 1. get the next event on roll and whether it's referenced by other objects
  fCurrentEvent = fBuffer->TopItem();
  if (!fCurrentEvent || fCurrentEvent->fData.ref != 0 ) {
    return false;
  }

  // 2. pop out the top item, since it's not referenced by any object
  fCurrentEvent = fBuffer->PopTopItem();
  return true;
}

void KoaEmsEventAnalyzer::Decode()
{
  for ( int i=0; i<32; i++ ) {
    fCurrentRawEvent->Scalor[i] = fCurrentEvent->fData.scalor[i];
  }
  fCurrentRawEvent->Second = fCurrentEvent->fData.time.tv_sec;
  fCurrentRawEvent->Usecond = fCurrentEvent->fData.time.tv_usec;
  fCurrentRawEvent->EventNr = fCurrentEvent->fData.event_nr;
}

void KoaEmsEventAnalyzer::Update()
{
  if ( fInitialEvent ) { // skip the first event
    for ( auto rate : fRates ) {
      rate.second = 0;
    }

    fInitialEvent = false;
  }
  else {
    auto start_t = fPreviousRawEvent->Second;
    auto stop_t = fCurrentRawEvent->Second;
    double delta_t = stop_t - start_t;
    double delta_ut = (fCurrentRawEvent->Usecond - fPreviousRawEvent->Usecond) * 1e-6;

    if ( delta_t > 10 ) {
      int step = delta_t/2;
      for ( int i = 0 ; i < step ; i++ ) {
        fSpareTime.emplace_back(start_t+2);
      }
    }

    for ( auto rate : fRates ) {
      // calculate current rate
      auto ch_name = rate.first;
      auto index = fScalorChMap[ch_name];
      auto current_counts = fCurrentRawEvent->Scalor[index];
      auto previous_counts = fPreviousRawEvent->Scalor[index];

      rate.second = (current_counts - previous_counts) / (delta_t + delta_ut);
    }
  }

  // update current time
  fCurrentTime = fCurrentRawEvent->Second;

  // keep current raw event to previous
  fPreviousRawEvent = fCurrentRawEvent;
}

void KoaEmsEventAnalyzer::FillTree()
{
  //
  if ( fPersistence ) {
    fTree->Fill();
  }
}

void KoaEmsEventAnalyzer::FillHist()
{
  if (fSpareTime.size()) {
    // TODO fill in the null rate

    // clear spare timestamp points
    fSpareTime.clear();
  }

  // TODO fill the current rate
  for ( auto scalor : fScalorChMap ) {
  
  }
}

void KoaEmsEventAnalyzer::Finish()
{
  // clean the remaining items in the buffer
  Analyze();

  // standard finish tasks in base class
  KoaRawEventAnalyzer::Finish();
}
