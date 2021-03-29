#ifndef KOACHARGEWEIGHTEDPIXELMAPPING_H
#define KOACHARGEWEIGHTEDPIXELMAPPING_H

#include "PndSdsChargeWeightedPixelMapping.h"

//! PndMvdChargeWeightedPixelMapping.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief PndSdsChargedWeightedPixelMapping: Gets a vector of DigiHits and
//! calculates the cluster center weighted with the charge

class KoaChargeWeightedPixelMapping
    : public PndSdsChargeWeightedPixelMapping {
 public:
  KoaChargeWeightedPixelMapping(Int_t verbose = 0);
  KoaChargeWeightedPixelMapping(PndGeoHandling* geo, Int_t verbose = 0);
};

#endif
