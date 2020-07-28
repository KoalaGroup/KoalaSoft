#include "PndLmdChargeWeightedPixelMapping.h"
#include "PndSdsIdealChargeConversion.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsTotDigiPar.h"

PndLmdChargeWeightedPixelMapping::PndLmdChargeWeightedPixelMapping(
    Int_t verbose)
    : PndSdsChargeWeightedPixelMapping() {
  fVerbose = verbose;
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb = ana->GetRuntimeDb();
  PndSdsPixelDigiPar* fDigiPar =
      (PndSdsPixelDigiPar*)(rtdb->getContainer("LMDPixelDigiPar"));
  PndSdsTotDigiPar* fTotDigiPar =
      (PndSdsTotDigiPar*)(rtdb->getContainer("SDSPixelTotDigiPar"));
  if (fDigiPar->GetChargeConvMethod() == 0) {
    if (fVerbose > 0)
      Info("PndLmdChargeWeightedPixelMapping", "ideal charge conversion");
    fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
  } else if (fDigiPar->GetChargeConvMethod() == 1) {
    if (fVerbose > 0)
      Info("PndLmdChargeWeightedPixelMapping", "use TOT charge conversion");
    fChargeConverter = new PndSdsTotChargeConversion(
        fTotDigiPar->GetChargingTime(), fTotDigiPar->GetConstCurrent(),
        fDigiPar->GetThreshold(), fTotDigiPar->GetClockFrequency(), fVerbose);
  } else {
    Fatal("PndLmdChargeWeightedPixelMapping", "conversion method not defined!");
  }

  flx = fDigiPar->GetXPitch();
  fly = fDigiPar->GetYPitch();
  fcols = fDigiPar->GetFECols();
  frows = fDigiPar->GetFERows();
}

PndLmdChargeWeightedPixelMapping::PndLmdChargeWeightedPixelMapping(
    PndGeoHandling* geo, Int_t verbose)
    : PndSdsChargeWeightedPixelMapping(geo) {
  fVerbose = verbose;
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb = ana->GetRuntimeDb();
  PndSdsPixelDigiPar* fDigiPar =
      (PndSdsPixelDigiPar*)(rtdb->getContainer("LMDPixelDigiPar"));
  PndSdsTotDigiPar* fTotDigiPar =
      (PndSdsTotDigiPar*)(rtdb->getContainer("SDSPixelTotDigiPar"));
  if (fDigiPar->GetChargeConvMethod() == 0) {
    if (fVerbose > 0)
      Info("PndLmdChargeWeightedPixelMapping", "ideal charge conversion");
    fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
  } else if (fDigiPar->GetChargeConvMethod() == 1) {
    if (fVerbose > 0)
      Info("PndLmdChargeWeightedPixelMapping", "use TOT charge conversion");
    fChargeConverter = new PndSdsTotChargeConversion(
        fTotDigiPar->GetChargingTime(), fTotDigiPar->GetConstCurrent(),
        fDigiPar->GetThreshold(), fTotDigiPar->GetClockFrequency(), fVerbose);
  } else {
    Fatal("PndLmdChargeWeightedPixelMapping", "conversion method not defined!");
  }
  flx = fDigiPar->GetXPitch();
  fly = fDigiPar->GetYPitch();
  fcols = fDigiPar->GetFECols();
  frows = fDigiPar->GetFERows();
}
