#ifndef PNDSDSSIMPLEPIXELCLUSTERFINDER_H
#define PNDSDSSIMPLEPIXELCLUSTERFINDER_H

#include "PndSdsPixelClusterFinder.h"
/// PndSdsSimplePixelClusterFinder.h
/// Simple cluster finder for pixel detectors.
///
/// It takes the first hit in the DigiArray and moves it into a new cluster.
/// Then it looks through the remaining hits in the DigiArray if there are hits which are in the area around the first hit and moves them into the cluster.
/// The radius is given by the first parameter.
/// Then it takes the new hits in the cluster and looks if there are other hits which are in the range of these hits and moves them into the cluster, too.
/// This process is repeated until no hits around the cluster are found
/// The the first hit of the remaining DigiHits is taken to create a new hit and the cluster search process is started again.
///
/// params: Number of columns in a front-end
/// 		Number of rows in a front-end
/// 		Range as Int_t at which a pixel belongs to a cluster or not
/// params are taken from parameter database


class PndSdsSimplePixelClusterFinder : public PndSdsPixelClusterFinder
  {
    public :
    PndSdsSimplePixelClusterFinder():PndSdsPixelClusterFinder(), fcols(0), frows(0), fradius(-1.0){};
    //PndSdsSimplePixelClusterFinder(std::vector<PndSdsDigiPixel> hits):
    //	PndSdsPixelClusterFinder(hits){
    //	if(fVerbose>0)std::cout << "Hits in array: " << fHits.size() << std::endl;
    //};
    virtual ~PndSdsSimplePixelClusterFinder(){};
    
    ///Main method which searches for the clusters.
    ///It returns a matrix of ints where a column corresponds to a cluster and an integer to a hit in the DigiArray
    std::vector< std::vector< Int_t> > GetClusters(std::vector<PndSdsDigiPixel> hits);
    
    virtual void SetMaxCols(Int_t col){ fcols = col; }
    virtual void SetMaxRows(Int_t row){ frows = row; }
    virtual void SetRadius(Double_t rad) { fradius = rad; }

    protected :
    Int_t fcols;
    Int_t frows;
    Double_t fradius;
    
    private :
    //PndSdsDigiPixel MoveHit(std::vector<PndSdsDigiPixel>* hitVector, Int_t index);
    Int_t MoveHit(std::vector<Int_t>* hitVector, Int_t index) const;
    bool IsInRange(PndSdsDigiPixel hit1, PndSdsDigiPixel hit2) const;
    
  };
#endif
