#ifndef KOA_MXDC32_DATA_H
#define KOA_MXDC32_DATA_H

#include "ems_interface.h"
#include "KoaBufferTemplate.h"
#include "KoaEmsEventData.h"

/* This class is a data class holding an unpacked event data from a mesytec mxdc32 module.
 * It should be used together with tempalte class 'KoaBufferItem' as an template argument.
 * And it will be filled up by unpacker 'KoaMxdc32Unpack'.
 *
 * Totally, there are 34 channels in each module, including 2 trigger channels.
 * Channel data, header and footer are extracted but not decoded.
 * Decoding of these data words are postponed to 'KoaAnalyzer' or later stage by dedicated KoalaSoft task.
 * Timestamp words are extracted and decoded, it is used by 'KoaAssembler' to construct a full KOALA event.
 * Event number is this class tracks the events recorded by this specific Mxdc32 module.
 * It's can be different from the full KOALA event number.
 */

struct KoaMxdc32Data
{
  KoaMxdc32Data() { Initialize(); }
  ~KoaMxdc32Data() {}

  void Initialize() {
    std::memset(this, 0, sizeof *this);
    ems_event = nullptr;
  }
  void Recycle() {
    ems_event->fData.ref--;
    ems_event = nullptr;
  }

  ems_u32 data[34];// channel data words including trigger channel, the index is ch_id, 33,34 is trigger input
  ems_u32 header; // header word
  ems_u32 footer; // end of event word

  uint64_t event_nr;// event number recorded in this module, couted by parse_mxdc32
  int length; // number of following words in this event

  int64_t  timestamp; // timestamp of this event (extracted and with ext_stamp)
  uint64_t ext_stamp; // extended timestamp (extracted)
  bool ext_stamp_valid; // whether extended timestamp is found

  KoaEmsEventDataItem* ems_event; // pointer to associated ems event, no ownership
};

template class KoaBufferItem<KoaMxdc32Data>;
using KoaMxdc32DataItem = KoaBufferItem<KoaMxdc32Data>;

template class KoaBuffer<KoaMxdc32Data>;
using KoaMxdc32Buffer = KoaBuffer<KoaMxdc32Data>;

template class KoaBufferManager<KoaMxdc32Data>;
using KoaMxdc32BufferManager = KoaBufferManager<KoaMxdc32Data>;

#endif
