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
  KoaEvtFilterOnGeometry() : fUnlimitY(false), fUnlimitZ(false) {}
  KoaEvtFilterOnGeometry(const char* name, const char* title="KoaEvtFilterOnGeometry") {}
  virtual ~KoaEvtFilterOnGeometry() {}

  virtual Bool_t EventMatches(Int_t evtNr);
  virtual Bool_t FilterActive() {return kTRUE;}

  void SetX(Double_t range){ fXDistance = range;}
  void SetYRange(Double_t min, Double_t max){
    fYMin = min;
    fYMax = max;
  }
  void SetZRange(Double_t min, Double_t max){
    fZMin = min;
    fZMax = max;
  }
  void SetUnlimitY(Bool_t flag) { fUnlimitY = flag;}
  void SetUnlimitZ(Bool_t flag) { fUnlimitZ = flag;}

 private:
  Double_t fXDistance;
  Double_t fYMin;
  Double_t fYMax;
  Double_t fZMin;
  Double_t fZMax;

  Bool_t   fUnlimitY;
  Bool_t   fUnlimitZ;

  ClassDef(KoaEvtFilterOnGeometry, 1);
};

#endif
