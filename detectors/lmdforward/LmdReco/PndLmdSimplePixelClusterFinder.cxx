// A simple clusterfinder for pixel detectors
#include "PndLmdSimplePixelClusterFinder.h"
#include "PndSdsIdealChargeConversion.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsTotDigiPar.h"

PndLmdSimplePixelClusterFinder::PndLmdSimplePixelClusterFinder(Int_t verbose)
    : PndSdsSimplePixelClusterFinder() {
  fVerbose = verbose;
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb = ana->GetRuntimeDb();
  PndSdsPixelDigiPar* fDigiPar =
      (PndSdsPixelDigiPar*)(rtdb->getContainer("LMDPixelDigiPar"));
  PndSdsTotDigiPar* fTotDigiPar =
      (PndSdsTotDigiPar*)(rtdb->getContainer("SDSPixelTotDigiPar"));
  if (fDigiPar->GetChargeConvMethod() == 0) {
    if (fVerbose > 0)
      std::cout
          << "Info in <PndLmdSimplePixelClusterFinder>: ideal charge conversion"
          << std::endl;
    fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
  } else if (fDigiPar->GetChargeConvMethod() == 1) {
    if (fVerbose > 0)
      std::cout
          << "Info in <PndLmdSimplePixelClusterFinder>: TOT charge conversion"
          << std::endl;
    fChargeConverter = new PndSdsTotChargeConversion(
        fTotDigiPar->GetChargingTime(), fTotDigiPar->GetConstCurrent(),
        fDigiPar->GetThreshold(), fTotDigiPar->GetClockFrequency(), fVerbose);
  } else {
    std::cout << "Error in <PndLmdSimplePixelClusterFinder>: charge conversion "
                 "method not defined, use ideal converter..."
              << std::endl;
    fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
  }
  fcols = fDigiPar->GetFECols();
  frows = fDigiPar->GetFERows();
  fradius = fDigiPar->GetClustRadius();
};
