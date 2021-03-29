#ifndef PNDSDSPIXELCLUSTERFINDER_H
#define PNDSDSPIXELCLUSTERFINDER_H

#include <vector>
#include "PndSdsDigiPixel.h"
#include "PndSdsChargeConversion.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

//! Base class for cluster finding algorithms
/** @author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 * As input it gets all digis to be analyzed and a set of parameters vector<Double_t>
 * The output is a vector< vector <Int_t> > which contains the position of the hits in the TClonesArray containing the Digis
 */

class PndSdsPixelClusterFinder
  {
    public :
    PndSdsPixelClusterFinder()
    : fHits(),
      fVerbose(0),
      fChargeConverter(NULL)
    {};
    PndSdsPixelClusterFinder(PndSdsPixelClusterFinder& other)
    : fHits(other.fHits),
      fVerbose(other.fVerbose),
      fChargeConverter(other.fChargeConverter)
    {};
    PndSdsPixelClusterFinder& operator=(PndSdsPixelClusterFinder& other)
    {
      fHits=other.fHits;
      fVerbose=other.fVerbose;
      fChargeConverter=other.fChargeConverter;
    return *this;
    };
    virtual ~PndSdsPixelClusterFinder(){};
    virtual std::vector< std::vector < Int_t > > GetClusters(std::vector<PndSdsDigiPixel> hits) = 0;
    void Print();
    void Print(std::vector<PndSdsDigiPixel> hits);
    void PrintResult(std::vector<std::vector< Int_t> > clusters);
    void SetVerbose(Int_t level){fVerbose = level;};
    
    std::vector<PndSdsDigiPixel> fHits;
    Int_t fVerbose;
    
    PndSdsChargeConversion* fChargeConverter;
    
    ClassDef(PndSdsPixelClusterFinder, 2);
  };

#endif


