#ifndef KOA_EVENT_DATA_H
#define KOA_EVENT_DATA_H

#include "ems_interface.h"
#include "KoaBufferTemplate.h"
#include "KoaMxdc32Data.h"

struct KoaEventData
{
  using Mxdc32Data = KoaBufferItem<KoaMxdc32Data>;

  KoaEventData() { Initialize(); }
  ~KoaEventData() {}

  void Initialize() {
    mask = 0;
    modules.clear();
  }
  void Recycle() {
    for( auto module : modules ) {
      module->second->Recycle();
    }
  }

  ems_u32 mask; // whether corresponding module has data in this event
  std::map<ems_u32, Mxdc32Data*> modules;
};

template class KoaBufferItem<KoaEventData>;
using KoaEventDataItem = KoaBufferItem<KoaEventData>;

template class KoaBuffer<KoaEventData>;
using KoaEventBuffer = KoaBuffer<KoaEventData>;

template class KoaBufferManager<KoaEventData>;
using KoaEventBufferManager = KoaBufferManager<KoaEventData>;

#endif
