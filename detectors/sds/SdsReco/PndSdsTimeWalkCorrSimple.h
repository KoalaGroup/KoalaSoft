/*
 * PndSdsTimeWalkCorrSimple.h
 *
 *  Created on: Aug 26, 2010
 *      Author: esch
 *
 *      This class calculates the TimeWalkCorrection from TOT time
 *      using a triangular model of the signal
 *      (see PndSdsTotChargeConversion)
 *                                           _____________________________________________
 *       			t_r*m-Q_thr-t_tot*m      | / t_r*m-Q_thr-t_tot*m \ 2                 |
 *      Q(tot) = - --------------------- + \ ||  -------------------  |  + t_r*Q_thr*m
 *                          2				\| \           2         /
 *                 Q_thr
 *      t_tw(Q) = -------- * t_r
 *                 Q(tot)
 *
 *
 *     Params from Parameter Database:
 *     ------------------------------
 *     t_r = rising time of the signal
 *     Q_thr = threshold charge
 *     m = constatnt current to unload the capacitor
 *
 */

#ifndef PNDSDSTIMEWALKCORRSIMPLE_H_
#define PNDSDSTIMEWALKCORRSIMPLE_H_

#include "PndSdsTimeWalkCorr.h"
#include <iostream>
#include <cmath>

class PndSdsTimeWalkCorrSimple: public PndSdsTimeWalkCorr {
public:
	PndSdsTimeWalkCorrSimple();

	PndSdsTimeWalkCorrSimple(Double_t risingtime, Double_t constcurrent, Double_t thr, Double_t frequency, Int_t verblevel);

	virtual ~PndSdsTimeWalkCorrSimple();

	virtual Double_t CorrectionTimeWalk(Double_t tot);
	virtual Double_t GetCharge() {return fCharge;};



private:
	Double_t fRisingTime;                 // ns
	Double_t fConstantCurrent;            // e/ns
	Double_t fTimeOverThreshold;          // ns
	Double_t fThreshold;                  // e
	Double_t fFrequency;				  // MHz
	Int_t fVerboseLevel;
	Double_t fCharge;					  // e
	Double_t fTimeWalk;                   // ns
	Double_t CalculateCharge(Double_t);
	Double_t CalculateTimeWalk(Double_t);

ClassDef(PndSdsTimeWalkCorrSimple, 1);
};

#endif /* PNDSDSTIMEWALKCORRSIMPLE_H_ */
