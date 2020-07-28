// A basic clusterfinder for pixel detectors
#include "PndSdsSimplePixelClusterFinder.h"
#include "TMath.h"
#include "FairLogger.h"

std::vector< std::vector<Int_t> > PndSdsSimplePixelClusterFinder::GetClusters(std::vector<PndSdsDigiPixel> hits)
{
	fHits = hits;
//	if (fVerbose > 1) Print();
	std::vector<Int_t> posHits;
	for (UInt_t i = 0; i < fHits.size(); i++) posHits.push_back(i);
	std::vector< std::vector< Int_t> > result;
	Int_t sizeTempHits = posHits.size();
	//Int_t actHit = 0;
	while (sizeTempHits != 0){
		std::vector<Int_t> tempInt;
		if (fChargeConverter->DigiValueToCharge(fHits[posHits[0]]) == 0){
			MoveHit(&posHits,0);
			sizeTempHits = posHits.size();
		}
		else {
			tempInt.push_back(MoveHit(&posHits,0));
			result.push_back(tempInt);
			Int_t sizeResultI = (result.end()-1)->size(); // size of last vector in array
			for (Int_t i = 0; i < sizeResultI; i++){
				sizeTempHits = posHits.size();
				for (Int_t j = 0; j < sizeTempHits; j++){
					if (fChargeConverter->DigiValueToCharge(fHits[posHits[j]]) == 0){
								MoveHit(&posHits,j);
//								if (fVerbose > 1)
//									std::cout << "Charge too low!" << std::endl;
								j--;
					}
					else{
						if (fHits[(*(result.end()-1))[i]].GetSensorID() == fHits[posHits[j]].GetSensorID()){
							if (IsInRange(fHits[(*(result.end()-1))[i]], fHits[posHits[j]])) {
									(result.end()-1)->push_back(MoveHit(&posHits,j));
									j--;
//									if (fVerbose > 1)
//										std::cout << "Hit added to cluster: " << result.size()-1 << std::endl;
							}
						}

					}
					sizeTempHits = posHits.size();
				}
				sizeResultI = (result.end()-1)->size();
			}
		}
	}
	if (fVerbose > 1) PrintResult(result);
	return result;
}

Int_t PndSdsSimplePixelClusterFinder::MoveHit(std::vector<Int_t>* hitVector, Int_t index) const
{
	Int_t result = -1;
	if (index < (Int_t)hitVector->size()){
		result = (*hitVector)[index];
		hitVector->erase(hitVector->begin()+index);
	}
	return result;
}

bool PndSdsSimplePixelClusterFinder::IsInRange(PndSdsDigiPixel hit1, PndSdsDigiPixel hit2) const
{
	Double_t result1, result2;
	Int_t col1 = hit1.GetPixelColumn() + (Int_t)((hit1.GetFE()%10) * fcols);
	Int_t col2 = hit2.GetPixelColumn() + (Int_t)((hit2.GetFE()%10) * fcols);
	Int_t row1 = hit1.GetPixelRow()    + (Int_t)((hit1.GetFE()/10) * frows);
	Int_t row2 = hit2.GetPixelRow()    + (Int_t)((hit2.GetFE()/10) * frows);
	if (fVerbose > 2){
    std::cout <<" -I- PndSdsSimplePixelClusterFinder::IsInRange():"<<std::endl;
		std::cout << "Hit1: ";
		hit1.Print();
		std::cout << "Hit2: ";
		hit2.Print();
		std::cout << "col1: " << col1 << " col2: " << col2 << " row1: " << row1 << " row2: " << row2 << std::endl;
		std::cout << "col1 - col2: " << (col1-col2) << " row1 - row2 " << (row1-row2) << std::endl;
	}
	result1 = (col1-col2);
	result1 *= result1;
	result2 = (row1-row2);
	result2 *= result2;
	result1 += result2;
	if (fVerbose > 2)
		std::cout << "IsInRange result: " << TMath::Sqrt(result1) << std::endl;
	return (TMath::Sqrt(result1) < fradius);
}
