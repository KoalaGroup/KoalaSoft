#include "KoaEmsEventAnalyzer.h"
#include "KoaEmsConfig.h"

KoaEmsEventAnalyzer::~KoaEmsEventAnalyzer()
{
  if (fCurrentRawEvent) delete fCurrentRawEvent;
  if (fPreviousRawEvent) delete fPreviousRawEvent;

}

void KoaEmsEventAnalyzer::Init()
{
  // 1. get the event buffer
  auto bufferManager = KoaEmsEventBufferManager::Instance();
  // the default buffer name for koala event is 'KOALA'
  fBuffer = bufferManager->GetBuffer("EMS");

  // 2. get scalor channel mapping
  fInitialEvent = true;

  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
  LOG(fatal) << "KoaEmsEventAnalyzer::Init : no valid EMS configuration information exists,"
             << "instantiate an instance of KoaEmsConfig first!";
}
  fScalorChMap = emsConfig->GetScalorChMap();

  // 3. book the memory for decoded data
  fCurrentRawEvent = new KoaEmsRawEvent();
  fPreviousRawEvent = new KoaEmsRawEvent();

  // 4. check persistence flag, init Tree accordingly
  if ( fPersistence ) {
    fRootFile->cd();

    // raw tree containing scalor array
    fTree = new TTree("Ems","EMS Event Data");
    fTree->Branch("KoaEmsRawEvent", &fCurrentRawEvent);

    // write the scalor mapping
    fRootFile->WriteObjectAny(fScalorChMap, "std::map<std::string,int>", "ScalorChMap");
  }

  // 5. init histograms if any
  InitHist();
}

bool KoaEmsEventAnalyzer::Analyze()
{
  // 1. check whether there is new ems event available
  fCurrentEvent = fBuffer->PopTopItem();
  if (!fCurrentEvent) {
    return false;
  }

  // 2. Decode
  Decode();

  // 3. Update rate
  UpdateRate();

  // 4. Fill
  Fill();

  // 5. Recycle
  Recycle();
}

void KoaEmsEventAnalyzer::Decode()
{
  for ( int i=0; i<32; i++ ) {
    fCurrentRawEvent->Scalor[i] = fCurrentEvent->scalor[i];
  }
  fCurrentRawEvent->Second = fCurrentEvent->time.tv_sec;
  fCurrentRawEvent->Usecond = fCurrentEvent->time.tv_usec;
  fCurrentRawEvent->EventNr = fCurrentEvent->EventNr;
}

void KoaEmsEventAnalyzer::UpdateRate()
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

void KoaEmsEventAnalyzer::Fill()
{
  //
  if ( fPersistence ) {
    fTree->Fill();
  }

  //
  FillHist();
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
