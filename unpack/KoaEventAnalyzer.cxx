#include "KoaEventAnalyzer.h"
#include "KoaEmsConfig.h"
#include "KoaEventData.h"

KoaEventAnalyzer::~KoaEventAnalyzer()
{
  if(fModuleId)   delete [] fModuleId;
  if(fResolution) delete [] fResolution;
  if(fNrWords)    delete [] fNrWords;
  if(fTimestamp)  delete [] fTimestamp;
  if(fData)       delete [] fData;

  if(fRawEvent) delete fRawEvent;

  if ( fPersistence ) {
    for ( auto module : fModuleTable ) {
      if (fTreeMap[module.first])
        delete fTreeMap[module.first];
    }
  }
}

void KoaEventAnalyzer::Init()
{
  // 1. get the event buffer
  auto bufferManager = KoaEventBufferManager::Instance();
  // the default buffer name for koala event is 'KOALA'
  fBuffer = bufferManager->GetBuffer("KOALA");

  // 2. book the memory for decoded data, and the object for output
  // 2.1 get the ems configuration first
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaEventAnalyzer::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
  }

  fModuleTable = emsConfig->GetModuleTable();
  fAmplitudeChannelMap = emsConfig->GetAmplitudeChMapInfo();
  fTimeChannelMap = emsConfig->GetTimeChMapInfo();

  // 2.2 init the storage space
  Int_t nr_mesymodules = fModuleTable.size();

  Int_t index = 0;
  for ( auto module : fModuleTable ) {
    fIndexMap[module.first] = index++;
  }

  fModuleId = new UChar_t[nr_mesymodules];
  fResolution = new Char_t[nr_mesymodules];
  fNrWords  =  new Short_t[nr_mesymodules];
  fTimestamp = new Long64_t[nr_mesymodules];
  fData      = new Int_t[nr_mesymodules][34];

  // 3. register fRawEvent to RootManager in memory
  FairRootManager* ioMan = FairRootManager::Instance();
  fRawEvent = new KoaRawEvent();
  ioMan->RegisterAny("KoaRawEvent", fRawEvent, kFALSE);

  // 3. check persistency flag, init TTree accordingly
  if ( fPersistence ) {
    fRootFile->cd();

    // tree definition
    for( auto module : fModuleTable ) {
      fTreeMap.emplace(module.first, new TTree(module.second.name.c_str(), module.second.name.c_str()));

      auto tree = fTreeMap[module.first];
      Int_t mod = fIndexMap[module.first];

      tree->Branch("ModuleId",fModuleId+mod,"ModuleId/b");
      tree->Branch("NrWords",fNrWords+mod,"NrWords/S");
      tree->Branch("Timestamp",fTimestamp+mod,"Timestamp/L");
      tree->Branch("Data",fData+mod,"Data[34]/I");
      if ( module.second.type != MesytecType::MQDC32 ) {
        tree->Branch("Resolution",fResolution+mod,"Resolution/B");
      }
    }
  }
}

bool KoaEventAnalyzer::Analyze()
{
  // 1. check whether there is koala event available
  fCurrentEvent = fBuffer->PopTopItem();

  if ( !fCurrentEvent )
    return false;

  // 2 analyze this event
  Decode();

  // 3 fill into tree
  Fill();

  // 4 recycle this event
  Recycle();
  
  return true;
}

void KoaEventAnalyzer::Decode()
{
  KoaMxdc32DataItem *event;

  for( auto module : fModuleTable ){
    j
    event = koala->modules[mod];
    //
    fTimestamp[mod] = event->timestamp;
    fModuleId[mod]= (event->header>>16)&0xff;
    fNrWords[mod] = event->header&0xfff;
    switch(mesymodules[mod].mesytype)
      {
      case mesytec_madc32:
        {
          fResolution[mod] = (event->header>>12)&0x7;
          for(int ch=0;ch<32;ch++){
            if(event->data[ch]){
              if((event->data[ch]>>14)&0x1){
                fData[mod][ch] = ADC_OVERFLOW;
              }
              else{
                switch(fResolution[mod])
                  {
                  case 0:
                    fData[mod][ch] = (event->data[ch])&0x7ff;
                    break;
                  case 1:
                  case 2:
                    fData[mod][ch] = (event->data[ch])&0xfff;
                    break;
                  case 3:
                  case 4:
                    fData[mod][ch] = (event->data[ch])&0x1fff;
                    break;
                  default:
                    printf("Unknown resolution (KoaRawSimple::Decode)\n");
                  }
              }
            }
            else{
              fData[mod][ch] = UNDER_THRESHOLD;
            }
          }
          break;
        }
      case mesytec_mqdc32:
        {
          for(int ch=0;ch<32;ch++){
            if(event->data[ch]){
              if((event->data[ch]>>15)&0x1){
                fData[mod][ch] = QDC_OVERFLOW;
              }
              else{
                fData[mod][ch] = (event->data[ch])&0xfff;
              }
            }
            else{
              fData[mod][ch] = UNDER_THRESHOLD;
            }
          }
          break;
        }
      case mesytec_mtdc32:
        {
          fResolution[mod] = (event->header>>12)&0xf;
          for(int ch=0;ch<34;ch++){
            if(event->data[ch]){
              fData[mod][ch] = (event->data[ch])&0xffff;
            }
            else{
              fData[mod][ch] = UNDER_THRESHOLD;
            }
          }
          break;
        }
      default:
        break;
      }
  }
}
