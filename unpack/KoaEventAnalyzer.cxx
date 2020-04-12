#include "FairRootManager.h"
#include "KoaEventAnalyzer.h"

const Float_t KoaEventAnalyzer::fTimeUnit[9] = {-1,1./256,2./256,4./256,8./256,16./256,32./256,64./256,128./256}; //! unit: ns

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

TFile* KoaEventAnalyzer::InitOutputFile()
{
  FairRootManager* ioMan = FairRootManager::Instance();
  auto sink = ioMan->GetSink();
  if(!sink) {
    LOG(fatal) << "KoaEventAnalyzer::InitOutputFile : no sink available, setup sink first";
  }

  TString fileName = sink->GetFileName();
  fileName.ReplaceAll(".root","_RawModuleBased.root");
  return new TFile(fileName, "recreate");
}

void KoaEventAnalyzer::InitInputBuffer()
{
  auto bufferManager = KoaEventBufferManager::Instance();
  fBuffer = bufferManager->GetBuffer("KOALA");
}

void KoaEventAnalyzer::InitChannelMap()
{
  // 1 get the ems configuration first
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaEventAnalyzer::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
  }

  fModuleTable = emsConfig->GetModuleTable();
  fAmplitudeChannelMap = emsConfig->GetAmplitudeChMap();
  fTimeChannelMap = emsConfig->GetTimeChMap();

}

void KoaEventAnalyzer::InitOutputBuffer()
{
  // 1. init the storage space
  Int_t nr_mesymodules = fModuleTable.size();

  fModuleId = new UChar_t[nr_mesymodules];
  fResolution = new Char_t[nr_mesymodules];
  fNrWords  =  new Short_t[nr_mesymodules];
  fTimestamp = new Long64_t[nr_mesymodules];
  fData      = new Int_t[nr_mesymodules][34];

  // 2. index map
  Int_t indexnum = 0;
  for ( auto module : fModuleTable ) {
    fIndexMap[module.first] = indexnum++;
  }

  // 3. value map
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

  // 4. register fRawEvent to RootManager in memory
  // 4.1 register output object
  FairRootManager* ioMan = FairRootManager::Instance();
  if (!ioMan)
    LOG(fatal) << "No FairRootManager";

  fRawEvent = new KoaRawEvent();
  // ioMan->Register("KoaRawEvent", "Raw", fRawEvent, kTRUE);
  ioMan->RegisterAny("KoaRawEvent", fRawEvent, kTRUE);

  // 4.2 get the value map and check whether data available
  fAmplitudeValueMapOutput = fRawEvent->GetAmplitudeValueMap();
  fTimeValueMapOutput = fRawEvent->GetTimeValueMap();
}

void KoaEventAnalyzer::InitOutputTree()
{
  // check persistency flag, init TTree accordingly
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

bool KoaEventAnalyzer::NextEvent()
{
  fCurrentEvent = fBuffer->PopTopItem();

  if ( !fCurrentEvent )
    return false;

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

void KoaEventAnalyzer::FillTree()
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
}
