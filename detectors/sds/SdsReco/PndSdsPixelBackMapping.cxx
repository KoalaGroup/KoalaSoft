#include "PndSdsPixelBackMapping.h"
#include "FairLogger.h"

PndSdsPixelBackMapping::PndSdsPixelBackMapping() :
    fDigiArray(),
    fGeoH(PndGeoHandling::Instance()),
    fVerbose(0)
{
  //fGeoH = PndGeoHandling::Instance();
}
      
PndSdsPixelBackMapping::PndSdsPixelBackMapping(PndGeoHandling* geo) :
    fDigiArray(),
    fGeoH(geo),
    fVerbose(0)
{
}

PndSdsPixelBackMapping::~PndSdsPixelBackMapping()
{
}
            

