/*
 * PndSdsTimeWalkCorr.h
 *
 * Description:
 *
 *  Created on: Aug 26, 2010
 *      Author: Simone Esch
 *      Abstract Base Class to calculate the TimeWalkCorrection from the TOT time
 */

#include "TObject.h"

#ifndef PNDSDSTIMEWALKCORR_H_
#define PNDSDSTIMEWALKCORR_H_

class PndSdsTimeWalkCorr: public TObject {
public:

	PndSdsTimeWalkCorr();

	virtual ~PndSdsTimeWalkCorr();
	virtual Double_t CorrectionTimeWalk(Double_t tot)=0 ;
	virtual Double_t GetCharge()=0;

private:

ClassDef(PndSdsTimeWalkCorr, 1);
};

#endif /* PNDSDSTIMEWALKCORR_H_ */
