#ifndef KOA_EVENT_ASSEMBLER_H
#define KOA_EVENT_ASSEMBLER_H

/* This class will assemble tha koala event from each module into a synchronized event based timestamp
 *
 */

#include "TObject.h"
#include "KoaMxdc32Data.h"
#include "KoaEventData.h"
#include "KoaEmsConfig.h"
#include <map>

constexpr int64_t TS_RANGE = 0x40000000;

class KoaEventAssembler : public TObject
{
public:
  KoaEventAssembler() : fQdcTimeDiff(3), fMaxTimeDiff(4)
  {}
  ~KoaEventAssembler() {}

  virtual void Init();
  virtual void Assemble();
  virtual void Finish() {}
  virtual void PrintStatistics() {}
  

  void SetQdcTimeDiff(int diff){
    fQdcTimeDiff=diff;
  }
  void SetMaxTimeDiff(int diff){
    fMaxTimeDiff = diff;
  }

private:
  // whether two timestamp are synchronized
  Bool_t IsSameTS(int64_t first, int64_t second)
  {
    int64_t delta_t = first - second;

    if ( delta_t > TS_RANGE/2 ) delta_t -= TS_RANGE;
    if ( delta_t < -TS_RANGE/2 ) delta_t += TS_RANGE;

    if ( delta_t > fMaxTimeDiff || delta_t < -fMaxTimeDiff ) {
      LOG(INFO) << "Unsynchronized timestamp: " << first << " != " << second;
      return false;
    }

    return true;
  }

  // whether all of the module have at least one event data available
  Bool_t IsFull()
  {
    for ( auto buffer : fModuleBuffer ) {
      if ( buffer.second.IsEmpty() )
        return false;
    }
    return true;
  }

private:
  std::map<ModuleId, KoaMxdc32Buffer*> fModuleBuffer;
  ModuleTable fModuleTable;
  KoaEventBuffer* fKoalaBuffer;

  Int_t   fQdcTimeDiff; // correction of QDC timestamp, the width of QDC gate in 62.5ns
  Int_t   fMaxTimeDiff; // the maximum difference of timestamps between module

  ClassDef(KoaEventAssembler, 1)
};
#endif
