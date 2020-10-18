#ifndef KOA_EMS_EVENT_DATA_H
#define KOA_EMS_EVENT_DATA_H

#include "ems_interface.h"
#include "KoaBufferTemplate.h"
#include <sys/time.h> // for timeval struct
#include <cstring> // for memset

struct KoaEmsEventData
{
  KoaEmsEventData() { Initialize(); }
  ~KoaEmsEventData() {}

  void Initialize() {
    std::memset(this, 0, sizeof *this);
  }
  void Recycle() { ref = 0; }

  // ems event number, totally different from experiment event
  ems_u32 event_nr;
  bool evnr_valid;

  // From Timestamp IS (from OS time system)
  // can be used to calculate the hit rates and event rates
  struct timeval time;
  bool time_valid;

  // From Scalor IS
  ems_u32 scalor[32];
  bool scalor_valid;

  // reference counter
  int ref;
};

template class KoaBufferItem<KoaEmsEventData>;
using KoaEmsEventDataItem = KoaBufferItem<KoaEmsEventData>;

template class KoaBuffer<KoaEmsEventData>;
using KoaEmsEventBuffer = KoaBuffer<KoaEmsEventData>;

template class KoaBufferManager<KoaEmsEventData>;
using KoaEmsEventBufferManager = KoaBufferManager<KoaEmsEventData>;

#endif
