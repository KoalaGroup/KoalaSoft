#ifndef KOA_DETECTOR_DATA_H
#define KOA_DETECTOR_DATA_H

#include "ems_interface.h"
#include "KoaBufferTemplate.h"
#include "KoaMxdc32Data.h"

struct KoaDetectorData
{
  using Mxdc32Data = KoaBufferItem<KoaMxdc32Data>;

  KoaDetectorData() { Initialize(); }
  ~KoaDetectorData() {}

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

template class KoaBufferItem<KoaDetectorData>;
using KoaDetectorDataItem = KoaBufferItem<KoaDetectorData>;

template class KoaBuffer<KoaDetectorData>;
using KoaDetectorBuffer = KoaBuffer<KoaDetectorData>;

template class KoaBufferManager<KoaDetectorData>;
using KoaDetectorBufferManager = KoaBufferManager<KoaDetectorData>;

#endif
