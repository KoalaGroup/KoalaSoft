#ifndef KOA_EMS_RAWEVENT_H
#define KOA_EMS_RAWEVENT_H

#include "TObject.h"

/* Ems Raw Event format after decoding
 * It contains the timestamp and scalor counts.
 * Scalors are not named. The channel mapping of the scalor is saved in an std::map<std::string,int> object.
 * 
 */

struct KoaEmsRawEvent
{
  UInt_t Scalor[32];
  Long_t Second;
  Long_t Usecond;
  UInt_t EventNr;

  KoaEmsRawEvent& operator=(const KoaEmsRawEvent& rhs) {
    for ( int i=0; i < 32 ; i++ ) {
      Scalor[i] = rhs.Scalor[i];
    }

    Second = rhs.Second;
    Usecond = rhs.Usecond;
    EventNr = rhs.EventNr;

    return *this;
  }

  ClassDef(KoaEmsRawEvent, 1)
};
#endif
