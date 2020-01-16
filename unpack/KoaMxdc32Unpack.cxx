#include "KoaMxdc32Unpack.h"

Bool_t KoaMxdc32Unpack::Init()
{
  // 1. Get module table config
  auto emsConfig = KoaEmsConfig::Instance();
  if (!emsConfig) {
    LOG(fatal) << "KoaMxdc32Unpack::Init : no valid EMS configuration information exists,"
               << "instantiate an instance of KoaEmsConfig first!";
    return false;
  }
  fModuleTable = emsConfig->GetModuleTable();

  // 2. Init module buffers
  auto bufferManager = KoaMxdc32BufferManager::Instance();
  for ( auto module : fModuleTable ) {
    auto module_id = module.first;
    auto module_info = module.second;

    auto module_buffer = bufferManager->GetBuffer(module_info.name);
    fModuleBuffer.emplace(module_id, module_buffer);
  }

  return true;
}

Int_t KoaMxdc32Unpack::DoUnpack(ems_u32* buf, Int_t size)
{
  KoaMxdc32Buffer *priv = nullptr;
  KoaMxdc32DataItem *event = nullptr;
  ModuleInfo module;

  for (int i=0; i<size; i++) {
    uint32_t d=buf[i];

    switch ((d>>30)&3) {
    case 0x1:
      { /* header */
        int id = (d>>16)&0xff;
        auto search = fModuleBuffer.find(id);
        if ( search == fModuleBuffer.end() ) {
          LOG(ERROR) <<"KoaMxdc32Unpack::DoUnpack : can't find module buffer with id = " << id;
          return 0;
        }
        priv = search->second;
        event = priv->PrepareNewItem();
        module = fModuleTable[id];

        //
        event->fData.header = d;
        event->fData.length = d&0xfff;
        
        // TODO statist
        // priv->statist.events++;
        // priv->statist.words+=event->len;
        // event->evnr=priv->statist.events;
        
        break;
      }
    case 0x0: /* data, ext. timestamp or dummy */
      {
        switch ((d>>22)&0xff) {
        case 0x00: /* dummy */
          /* do nothing */
          break;
        case 0x10:
          { /* data */
            if ( !event ) {
              LOG(ERROR) << "KoaMxdc32Unpack::DoUnpack : no corresponding header found in this event";
              return -1;
            }
          
            if ( (module.type == MesytecType::MTDC32) || (module.type == MesytecType::MQDC32) ) {
              int chan = (d>>16)&0x3f;
              if ( event->fData.data[chan] ) {
                LOG(WARNING) << "KoaMxdc32Unpack::Unpack : duplicated data in module "<< module.name << " , channel " << chan;
              } else if( chan>33 ){
                LOG(ERROR) << "KoaMxdc32Unpack::Unpack : invalid channel index " << chan;
                return -1;
              }else {
                event->fData.data[chan] = d;
              }
            } else {
              int chan = (d>>16)&0x3f;
              if ( chan>33 ) {
                LOG(ERROR) << "KoaMxdc32Unpack::Unpack : invalid channel index " << chan;
                return -1;
              }
              event->fData.data[chan] = d;
            }

            break;
          }
        case 0x12:
          { /* extended timestamp */
            if ( !event ) {
              LOG(ERROR) << "KoaMxdc32Unpack::DoUnpack : no corresponding header found in this event";
              return -1;
            }
            
            event->fData.ext_stamp = d&0xffff;
            event->fData.ext_stamp_valid = true;
            break;
          }
        default: /* does not exist */
          LOG(WARNING) << "KoaMxdc32Unpack::Unpack : illegal data word " << std::hex << d << std::dec;
          break;
        }
      }
    case 0x3:
      { /* footer */
        if ( !event ) {
          LOG(ERROR) << "KoaMxdc32Unpack::DoUnpack : no corresponding header && body found in this event";
          return -1;
        }
        event->fData.footer = d;

        int64_t stamp = d&0x3fffffff;
        event->fData.timestamp = stamp;
        if ( event->fData.ext_stamp_valid )
          event->fData.timestamp |= event->fData.ext_stamp<<30;

        //
        priv->StoreNewItem();
        event = nullptr;

        break;
      }
    default: /* does not exist */
      LOG(WARNING) << "KoaMxdc32Unpack::Unpack : illegal data word " << std::hex << d << std::dec;
      break;
    }
  }

  return 0;
}

void KoaMxdc32Unpack::Reset()
{
  fModuleTable.clear();
  fModuleBuffer.clear();
}
