#ifndef PNDSDSPIXELBACKMAPPING_H
#define PNDSDSPIXELBACKMAPPING_H

#include "PndSdsDigiPixel.h"
#include "PndSdsHit.h"
#include "PndGeoHandling.h"
#include <vector>

class PndSdsPixelBackMapping
{
  public :  
  PndSdsPixelBackMapping();
  PndSdsPixelBackMapping(PndGeoHandling* geo);
  PndSdsPixelBackMapping(const PndSdsPixelBackMapping& other) :
    fDigiArray(other.fDigiArray),
    fGeoH(other.fGeoH),
    fVerbose(other.fVerbose)
  {};
  PndSdsPixelBackMapping& operator=(PndSdsPixelBackMapping& other)
  {
    fDigiArray=other.fDigiArray;
    fGeoH=other.fGeoH;
    fVerbose=other.fVerbose;
     return *this;
 };
  virtual ~PndSdsPixelBackMapping();

  void SetVerbose (Int_t level) {fVerbose = level;};
  virtual PndSdsHit GetCluster(std::vector<PndSdsDigiPixel> pixelArray) = 0;
      
  std::vector<PndSdsDigiPixel> fDigiArray;
  PndGeoHandling* fGeoH;
  Int_t fVerbose;

};

#endif

