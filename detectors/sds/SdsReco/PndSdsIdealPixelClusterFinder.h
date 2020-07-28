#ifndef PNDSDSIDEALPIXELCLUSTERFINDER_H
#define PNDSDSIDEALPIXELCLUSTERFINDER_H

#include "PndSdsPixelClusterFinder.h"
#include "PndSdsDigiPixel.h"
#include "TClonesArray.h"
#include <vector>
/// PndSdsIdealPixelClusterFinder.h
/// Ideal cluster finder using MCtruth information.

class PndSdsIdealPixelClusterFinder : public PndSdsPixelClusterFinder
  {
    public : 	PndSdsIdealPixelClusterFinder():PndSdsPixelClusterFinder(){};
    //		PndSdsIdealPixelClusterFinder(std::vector<PndSdsDigiPixel> hits):
    //			PndSdsPixelClusterFinder(hits){
    //			if(fVerbose>0) std::cout << "Hits in array: " << fHits.size() << std::endl;
    //		};
    virtual ~PndSdsIdealPixelClusterFinder(){};
    std::vector< std::vector< Int_t> > GetClusters(std::vector<PndSdsDigiPixel> hits);
    Int_t MoveHit(std::vector<Int_t>* hitVector, Int_t index) const;
    bool IsInRange(PndSdsDigiPixel hit1, PndSdsDigiPixel hit2) const;
    
  };
#endif
