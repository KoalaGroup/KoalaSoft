#include "FairRootManager.h"
#include "KoaEventAnalyzer.h"
#include "KoaMxdc32Data.h"

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

  // 2. book the memory for decoded data
  // 2.1 get the ems configuration first
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaEventAnalyzer::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
  }

  fModuleTable = emsConfig->GetModuleTable();
  fAmplitudeChannelMap = emsConfig->GetAmplitudeChMap();
  fTimeChannelMap = emsConfig->GetTimeChMap();

  // 2.2 init the storage space
  Int_t nr_mesymodules = fModuleTable.size();

  Int_t indexnum = 0;
  for ( auto module : fModuleTable ) {
    fIndexMap[module.first] = indexnum++;
  }

  fModuleId = new UChar_t[nr_mesymodules];
  fResolution = new Char_t[nr_mesymodules];
  fNrWords  =  new Short_t[nr_mesymodules];
  fTimestamp = new Long64_t[nr_mesymodules];
  fData      = new Int_t[nr_mesymodules][34];

  // 2.3 get the value map
  for( auto channel : fAmplitudeChannelMap ) {
    auto detector_encoded_id = channel.first;
    auto module_id = channel.second.first;
    auto module_ch = channel.second.second;
    auto index = fIndexMap[module_id];

    fAmplitudeValueMapInput.emplace(detector_encoded_id, *(fData+index)+module_ch);
  }
  for( auto channel : fTimeChannelMap ) {
    auto detector_encoded_id = channel.first;
    auto module_id = channel.second.first;
    auto module_ch = channel.second.second;
    auto index = fIndexMap[module_id];

    fTimeValueMapInput.emplace(detector_encoded_id, *(fData+index)+module_ch);
    fTimeResolutionMap.emplace(detector_encoded_id, fResolution+index);
  }

  // 3. register fRawEvent to RootManager in memory
  // 3.1 register output object
  FairRootManager* ioMan = FairRootManager::Instance();
  fRawEvent = new KoaRawEvent();
  ioMan->RegisterAny("KoaRawEvent", fRawEvent, kFALSE);

  // 3.2 get the value map and check whether data available
  fAmplitudeValueMapOutput = fRawEvent->GetAmplitudeValueMap();
  fTimeValueMapOutput = fRawEvent->GetTimeValueMap();

  // 4. check persistency flag, init TTree accordingly
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

  // 4. init histograms
  InitHist();
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
    // get next module data
    auto id = module.first;
    auto mod = fIndexMap[id];
    event = fCurrentEvent->fData.modules[id];

    //
    fTimestamp[mod] = event->fData.timestamp;
    fModuleId[mod] = (event->fData.header>>16)&0xff;
    fNrWords[mod] = event->fData.header&0xfff;

    switch(module.second.type) {
    case MesytecType::MADC32 :
      {
        fResolution[mod] = (event->fData.header>>12)&0x7;
        for(int ch=0;ch<32;ch++){
          if(event->fData.data[ch]){
            if((event->fData.data[ch]>>14)&0x1){
              fData[mod][ch] = ADC_OVERFLOW;
            }
            else{
              switch(fResolution[mod])
                {
                case 0:
                  fData[mod][ch] = (event->fData.data[ch])&0x7ff;
                  break;
                case 1:
                case 2:
                  fData[mod][ch] = (event->fData.data[ch])&0xfff;
                  break;
                case 3:
                case 4:
                  fData[mod][ch] = (event->fData.data[ch])&0x1fff;
                  break;
                default:
                  LOG(WARN) << "KoaEventAnalyzer::Decode : unknown Madc32 resolution";
                }
            }
          }
          else{
            fData[mod][ch] = UNDER_THRESHOLD;
          }
        }
        break;
      }
    case MesytecType::MQDC32 :
      {
        for(int ch=0;ch<32;ch++){
          if(event->fData.data[ch]){
            if((event->fData.data[ch]>>15)&0x1){
              fData[mod][ch] = QDC_OVERFLOW;
            }
            else{
              fData[mod][ch] = (event->fData.data[ch])&0xfff;
            }
          }
          else{
            fData[mod][ch] = UNDER_THRESHOLD;
          }
        }
        break;
      }
    case MesytecType::MTDC32 :
      {
        fResolution[mod] = (event->fData.header>>12)&0xf;
        for(int ch=0;ch<34;ch++){
          if(event->fData.data[ch]){
            fData[mod][ch] = (event->fData.data[ch])&0xffff;
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

void KoaEventAnalyzer::Fill()
{
  // 1. fill the raw event object
  for( auto value_map : fAmplitudeValueMapOutput ) {
    auto encoded_id = value_map.first;
    auto output = value_map.second;

    auto search = fAmplitudeValueMapInput.find(encoded_id);
    if (search == fAmplitudeValueMapInput.end() ) {
      (*output) = UNDER_THRESHOLD;
    }
    else{
      auto input = fAmplitudeValueMapInput[encoded_id];
      (*output) = (*input);
    }
  }

  for( auto value_map : fTimeValueMapOutput ) {
    auto encoded_id = value_map.first;
    auto output = value_map.second;

    auto search = fTimeValueMapInput.find(encoded_id);
    if (search == fTimeValueMapInput.end() ) {
      (*output) = UNDER_THRESHOLD;
    }
    else{
      auto input = fTimeValueMapInput[encoded_id];
      auto unit = fTimeUnit[(*fTimeResolutionMap[encoded_id])-1];
      (*output) = (*input)*unit;
    }
  }

  // 2. fill the output tree if persistence is set
  if (fPersistence) {
    for( auto module : fModuleTable ) {
      fTreeMap[module.first]->Fill();
    }
  }

  // 3. fill histograms if any
  FillHist();
}
