#include "PndSdsPixelClusterFinder.h"
#include "PndSdsIdealChargeConversion.h"
#include "PndSdsTotChargeConversion.h"

ClassImp(PndSdsPixelClusterFinder);

//PndSdsPixelClusterFinder::PndSdsPixelClusterFinder(std::vector<PndSdsDigiPixel> hits){
//     fHits   = hits;
//      fVerbose = 0;
//}

void PndSdsPixelClusterFinder::Print(std::vector<PndSdsDigiPixel> hits)
{
	std::cout << "--------------" << std::endl;
	for (UInt_t i = 0; i < hits.size(); i++){
		std::cout << hits[i] << std::endl;
	}
}

void PndSdsPixelClusterFinder::Print()
{
	Print(fHits);
}

void PndSdsPixelClusterFinder::PrintResult(std::vector<std::vector< Int_t> > clusters)
{
	for (UInt_t i = 0; i < clusters.size(); i++){
		std::cout << "PndSdsPixelClusterFinder::PrintResult(): Cluster " << i << ": " << std::endl;
		for (UInt_t j = 0; j < clusters[i].size();j++)
			fHits[clusters[i][j]].Print();
	}
}
