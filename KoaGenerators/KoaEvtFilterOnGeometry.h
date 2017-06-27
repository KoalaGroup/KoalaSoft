// -------------------------------------------------------------------------
// -----                 KoaEvtFilterOnGeometry header file                  -----
// -----               Created 27/06/17  by Y.Zhou                 -----
// -------------------------------------------------------------------------

/** KoaEvtFilterOnGeometry.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 *
 The KoaEvtFilterOnGeometry will reject the event from transportation in simlation engine
 based on whether the generated tracks will hit the detector.
**/

#ifndef Koa_EvtFilterOnGeometry
#define Koa_EvtFilterOnGeometry

#include "FairEvtFilter.h"

class KoaEvtFilterOnGeometry : public FairEvtFilter
{
 public:
  KoaEvtFilterOnGeometry() {}
  KoaEvtFilterOnGeometry(const char* name, const char* title="KoaEvtFilterOnGeometry") {}
  virtual ~KoaEvtFilterOnGeometry() {}

  virtual Bool_t EventMatches(Int_t evtNr);
  virtual Bool_t FilterActive() {return kTRUE;}

  ClassDef(KoaEvtFilterOnGeometry, 1);
};

#endif
