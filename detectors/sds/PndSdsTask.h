/*
 * PndSdsTask.h
 *
 *  Created on: Jul 7, 2010
 *      Author: stockman
 */

#ifndef PNDSDSTASK_H_
#define PNDSDSTASK_H_
#include <PndPersistencyTask.h>
#include "FairRootManager.h"

#include <iostream>

class PndSdsTask: public PndPersistencyTask {
public:
	PndSdsTask();

	PndSdsTask(const char* name, Int_t iVerbose = 1) : 
  PndPersistencyTask(name, iVerbose),
  fInBranchName(""),
	fOutBranchName(""),
	fFolderName(""),
	fInBranchId(-1),
	fOutBranchId(-1)
  {};
	virtual ~PndSdsTask();

	virtual void SetBranchNames()= 0;
	virtual void SetInBranchId(){
		FairRootManager *ioman = FairRootManager::Instance();
		fInBranchId = ioman->GetBranchId(fInBranchName);
		fOutBranchId = ioman->GetBranchId(fOutBranchName);
		std::cout << "InBranchId: " << fInBranchId << " for Branch: " << fInBranchName.Data() << std::endl;
		std::cout << "OutBranchId: " << fOutBranchId << " for Branch: " << fOutBranchName.Data() << std::endl;
	}

protected:
	TString fInBranchName;
	TString fOutBranchName;
	TString fFolderName;

	Int_t fInBranchId;
	Int_t fOutBranchId;

	ClassDef(PndSdsTask,1);
};

#endif /* PNDSDSTASK_H_ */
