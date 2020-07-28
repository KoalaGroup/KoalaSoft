#ifndef PNDSDSCHARGEWEIGHTEDPIXELMAPPING_H
#define PNDSDSCHARGEWEIGHTEDPIXELMAPPING_H

#include "PndSdsPixelBackMapping.h"
#include "PndSdsChargeConversion.h"
#include "TGeoMatrix.h"
#include "TVector3.h"
//! PndSdsChargeWeightedPixelMapping.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief PndSdsChargedWeightedPixelMapping: Gets a vector of DigiHits and calculates the cluster center weighted with the charge
//! params: Number of columns in FE, Number of rows in FE, Pixel dimension in x, Pixel dimension in y
//! params are taken from parameter database

class PndSdsChargeWeightedPixelMapping : public PndSdsPixelBackMapping
  {
    public :
    PndSdsChargeWeightedPixelMapping();
    PndSdsChargeWeightedPixelMapping(const PndSdsChargeWeightedPixelMapping& other) :
      PndSdsPixelBackMapping(other),
      fChargeConverter(other.fChargeConverter),
      flx(other.flx),
      fly(other.fly),
      fcols(other.fcols),
      frows(other.frows)
    {};
    PndSdsChargeWeightedPixelMapping(PndGeoHandling* geo);
    virtual ~PndSdsChargeWeightedPixelMapping(){};
    PndSdsChargeWeightedPixelMapping& operator=(PndSdsChargeWeightedPixelMapping& other)
    {
      fChargeConverter=other.fChargeConverter;
      flx=other.flx;
      fly=other.fly;
      fcols=other.fcols;
      frows=other.frows;
     return *this;
   };
    PndSdsHit GetCluster(std::vector<PndSdsDigiPixel> pixelArray); ///< Main function of class to calculate the PndSdsHit out of the given PndSdsDigis
    
    protected :
    PndSdsChargeConversion* fChargeConverter;
    Double_t flx;
    Double_t fly;
    Int_t fcols;
    Int_t frows;
    
    private :
    TGeoHMatrix GetTransformation(Int_t sensorID);
    TVector3 GetSensorDimensions(Int_t sensorID);
  };

#endif
