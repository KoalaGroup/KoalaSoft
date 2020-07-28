/*
 * PndSdsDigiPixelSorterTask.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include <PndSdsDigiPixelSorterTask.h>

#include "PndSdsDigiPixel.h"
#include "PndSdsDigiPixelRingSorter.h"

#include "TClonesArray.h"

ClassImp(PndSdsDigiPixelSorterTask);

PndSdsDigiPixelSorterTask::PndSdsDigiPixelSorterTask() {
	// TODO Auto-generated constructor stub

}

PndSdsDigiPixelSorterTask::~PndSdsDigiPixelSorterTask() {
	// TODO Auto-generated destructor stub
}


void PndSdsDigiPixelSorterTask::AddNewDataToTClonesArray(FairTimeStamp* data)
{
	 FairRootManager* ioman = FairRootManager::Instance();
	 TClonesArray* myArray = ioman->GetTClonesArray(fOutputBranch);
	 if (fVerbose > 1){
		 std::cout << "-I- PndSdsDigiPixelSorterTask::AddNewDataToTClonesArray Data: " ;
		 std::cout <<  *(PndSdsDigiPixel*)(data) << std::endl;
	 }
	 new ((*myArray)[myArray->GetEntries()]) PndSdsDigiPixel(*(PndSdsDigiPixel*)(data));
}

FairRingSorter* PndSdsDigiPixelSorterTask::InitSorter(Int_t numberOfCells, Double_t widthOfCells) const{
	return new PndSdsDigiPixelRingSorter(numberOfCells, widthOfCells);
}
