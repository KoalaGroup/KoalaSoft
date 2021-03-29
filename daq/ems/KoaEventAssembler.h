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
  virtual ~KoaEventAssembler() {}

  virtual void Init();
  virtual void Assemble();
  virtual void Finish();
  virtual void PrintStatistics() {}
  

  void SetQdcTimeDiff(int diff){
    fQdcTimeDiff=diff;
  }
  void SetMaxTimeDiff(int diff){
    fMaxTimeDiff = diff;
  }

protected:
  virtual bool NextEvent() { return IsFull(); }

  enum class TSType {Equal, Greater, Less };
  // whether two timestamp are synchronized
  TSType IsSameTS(int64_t first, int64_t second)
  {
    int64_t delta_t = first - second;

    if ( delta_t > TS_RANGE/2 ) delta_t -= TS_RANGE;
    if ( delta_t < -TS_RANGE/2 ) delta_t += TS_RANGE;

    if ( delta_t > fMaxTimeDiff ){
      return TSType::Greater;
    }
    else if ( delta_t < -fMaxTimeDiff ) {
      return TSType::Less;
    }

    return TSType::Equal;
  }

  // whether all of the module have at least one event data available
  Bool_t IsFull()
  {
    for ( auto buffer : fModuleBuffer ) {
      if ( buffer.second->IsEmpty() )
        return false;
    }
    return true;
  }

  // collect the timestamps of current item from all modules
  // in the same time, correct the qdc offset
  void CollectTS()
  {
    for ( auto& module : fModuleTable ) {
      auto module_id = module.first;
      auto ts = fModuleBuffer[module_id]->Current()->fData.timestamp;
      if(module.second.type == MesytecType::MQDC32) {
        ts -= fQdcTimeDiff;
      }
      fTSs[module_id] = ts;
    }
  }

protected:
  int fModuleNr;
  std::map<ModuleId, KoaMxdc32Buffer*> fModuleBuffer;
  std::map<ModuleId, KoaBufferStatistic*> fModuleStat;
  ModuleTable fModuleTable;
  KoaEventBuffer* fKoalaBuffer;
  KoaBufferStatistic* fKoalaStat;

  Int_t   fQdcTimeDiff; // correction of QDC timestamp, the width of QDC gate in 62.5ns
  Int_t   fMaxTimeDiff; // the maximum difference of timestamps between module

  std::map<ModuleId,int64_t> fTSs; // collection of current timestamps

  ClassDef(KoaEventAssembler, 1)
};
#endif
