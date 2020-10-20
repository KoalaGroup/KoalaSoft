#include "KoaEventLgtAsm.h"

bool KoaEventLgtAsm::NextEvent()
{
  while ( IsFull() ){
    // 1. get the list of timestamps
    CollectTS();

    // 2. get the list of min timestamps
    fMinTSs.clear();
    auto tmin = fTSs.begin()->second;
    for( auto item : fTSs ) {
      auto t = item.second;
      switch (IsSameTS(tmin, t)) {
        case TSType::Equal : {
          fMinTSs.emplace_back(item.first);
          break;
        }
        case TSType::Greater : {
          tmin = t;
          fMinTSs.clear();
          fMinTSs.emplace_back(item.first);
        }
        default:
          break;
      }
    }

    // 3. return if all items synchronized,
    //    otherwise pop out the list of min timestamp and continue
    if ( fMinTSs.size() == fModuleNr ) {
      return true;
    }
    else {
      for ( auto module_id : fMinTSs ) {
        auto buffer = fModuleBuffer[module_id];
        auto item = buffer->PopTopItem();
        item->Recycle();
        fModuleStat[module_id]->discarded++;
      }
    }
  }

  return false;
}
