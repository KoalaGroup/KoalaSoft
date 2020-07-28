/*
 * PndSdsDigiPixelSorterTask.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef PNDSDSDIGIPIXELSORTERTASK_H_
#define PNDSDSDIGIPIXELSORTERTASK_H_

#include <FairRingSorterTask.h>
#include <FairRingSorter.h>

class PndSdsDigiPixelSorterTask: public FairRingSorterTask {
public:
	PndSdsDigiPixelSorterTask();
	PndSdsDigiPixelSorterTask(const char* name):FairRingSorterTask(name){};
	PndSdsDigiPixelSorterTask(Int_t numberOfCells, Double_t widthOfCells, TString inputBranch, TString outputBranch, TString folderName):
		FairRingSorterTask(numberOfCells, widthOfCells, inputBranch, outputBranch, folderName){};

	virtual ~PndSdsDigiPixelSorterTask();

	virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
	virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

	ClassDef(PndSdsDigiPixelSorterTask, 1);
};

#endif /* PNDSDSDIGIPIXELSORTERTASK_H_ */
