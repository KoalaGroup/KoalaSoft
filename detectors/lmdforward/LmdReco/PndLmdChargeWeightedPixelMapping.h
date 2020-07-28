#ifndef PNDLMDCHARGEWEIGHTEDPIXELMAPPING_H
#define PNDLMDCHARGEWEIGHTEDPIXELMAPPING_H

#include "PndSdsChargeWeightedPixelMapping.h"

//! PndMvdChargeWeightedPixelMapping.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief PndSdsChargedWeightedPixelMapping: Gets a vector of DigiHits and
//! calculates the cluster center weighted with the charge

class PndLmdChargeWeightedPixelMapping
    : public PndSdsChargeWeightedPixelMapping {
 public:
  PndLmdChargeWeightedPixelMapping(Int_t verbose = 0);
  PndLmdChargeWeightedPixelMapping(PndGeoHandling* geo, Int_t verbose = 0);
};

#endif
