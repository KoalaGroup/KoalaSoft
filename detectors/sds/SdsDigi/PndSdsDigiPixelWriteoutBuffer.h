/*
 * PndSdsDigiPixelWriteoutBuffer.h
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#ifndef PNDSDSDIGIPIXELWRITEOUTBUFFER_H_
#define PNDSDSDIGIPIXELWRITEOUTBUFFER_H_

#include "FairWriteoutBuffer.h"
#include "PndSdsDigiPixel.h"

class FairTimeStamp;

class PndSdsDigiPixelWriteoutBuffer : public FairWriteoutBuffer{

public:
	PndSdsDigiPixelWriteoutBuffer();
	PndSdsDigiPixelWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);
	void AddNewDataToTClonesArray(FairTimeStamp*);

	virtual ~PndSdsDigiPixelWriteoutBuffer();

	virtual std::vector<std::pair<double, FairTimeStamp*> > Modify(std::pair<double, FairTimeStamp*> oldData, std::pair<double, FairTimeStamp*> newData);
        
	virtual double FindTimeForData(FairTimeStamp* data) ;
	virtual void FillDataMap(FairTimeStamp* data, double activeTime) ;
	virtual void EraseDataFromDataMap(FairTimeStamp* data);
protected:	

	std::map<PndSdsDigiPixel, double> fData_map;
	
	ClassDef(PndSdsDigiPixelWriteoutBuffer, 1);
};

#endif /* PNDSDSDIGIPIXELWRITEOUTBUFFER_H_ */
