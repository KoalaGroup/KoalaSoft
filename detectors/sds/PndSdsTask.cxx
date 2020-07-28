/*
 * PndSdsTask.cxx
 *
 *  Created on: May 18, 2010
 *      Author: stockman
 */

#include "PndSdsTask.h"

PndSdsTask::PndSdsTask() :
  PndPersistencyTask("SdsTask", 0),
  fInBranchName(""),
	fOutBranchName(""),
	fFolderName(""),
	fInBranchId(-1),
	fOutBranchId(-1)
  {
	// TODO Auto-generated constructor stub

}

PndSdsTask::~PndSdsTask() {
	// TODO Auto-generated destructor stub
}

ClassImp(PndSdsTask);
