// A simple clusterfinder for pixel detectors
#include "KoaSimplePixelClusterFinder.h"
#include "PndSdsIdealChargeConversion.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsTotDigiPar.h"

KoaSimplePixelClusterFinder::KoaSimplePixelClusterFinder(Int_t verbose)
    : PndSdsSimplePixelClusterFinder() {
  fVerbose = verbose;
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb = ana->GetRuntimeDb();
  PndSdsPixelDigiPar* fDigiPar =
      (PndSdsPixelDigiPar*)(rtdb->getContainer("KOAPixelDigiPar"));
  PndSdsTotDigiPar* fTotDigiPar =
      (PndSdsTotDigiPar*)(rtdb->getContainer("SDSPixelTotDigiPar"));
  if (fDigiPar->GetChargeConvMethod() == 0) {
    if (fVerbose > 0)
      std::cout
          << "Info in <KoaSimplePixelClusterFinder>: ideal charge conversion"
          << std::endl;
    fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
  } else if (fDigiPar->GetChargeConvMethod() == 1) {
    if (fVerbose > 0)
      std::cout
          << "Info in <KoaSimplePixelClusterFinder>: TOT charge conversion"
          << std::endl;
    fChargeConverter = new PndSdsTotChargeConversion(
        fTotDigiPar->GetChargingTime(), fTotDigiPar->GetConstCurrent(),
        fDigiPar->GetThreshold(), fTotDigiPar->GetClockFrequency(), fVerbose);
  } else {
    std::cout << "Error in <KoaSimplePixelClusterFinder>: charge conversion "
                 "method not defined, use ideal converter..."
              << std::endl;
    fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
  }
  fcols = fDigiPar->GetFECols();
  frows = fDigiPar->GetFERows();
  fradius = fDigiPar->GetClustRadius();
};
