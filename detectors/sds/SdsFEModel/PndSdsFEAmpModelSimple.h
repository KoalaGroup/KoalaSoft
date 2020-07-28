/*
 * SdsFEAmpModelSimple.h
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 *
 *      Class for the simple amplifier model definition
 *
 */

#ifndef PNDSDSFEAMPMODELSIMPLE_H_
#define PNDSDSFEAMPMODELSIMPLE_H_


class PndSdsFEAmpModelSimple {
public:
	PndSdsFEAmpModelSimple();
	virtual ~PndSdsFEAmpModelSimple();
	double Definition(double *x, double *params);
	int GetModelNumber();

private:
	const int fModelNumber;    // Holds the number of the model - necessary to save the interpolatorlist in PndSdsFE
};

#endif /* PNDSDSFEAMPMODELSIMPLE_H_ */
