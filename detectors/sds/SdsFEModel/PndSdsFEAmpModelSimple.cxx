/*
 * SdsFEAmpModelSimple.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 */

#include "PndSdsFEAmpModelSimple.h"
#include "TMath.h"

PndSdsFEAmpModelSimple::PndSdsFEAmpModelSimple(): fModelNumber(1) {
}

PndSdsFEAmpModelSimple::~PndSdsFEAmpModelSimple() {
}

double PndSdsFEAmpModelSimple::Definition(double * x, double *params)  {

	// params[0] = charge time [ns]
	// params[1] = constant current to discharge the capacitor of the amplifier [e/ns]
 	// params[2] = charge [e]

	if( *x <= 0 )
	  {
	    return 0;
	  }
	 else if (*x <= params[0])
	   {
	     return *x * params[2] / params[0];
	   }
	 else
	   {
	     return TMath::Max( params[2]- ((*x- params[0])* params[1]),0.0);
	   }
}

int PndSdsFEAmpModelSimple::GetModelNumber(){

	return fModelNumber;
}


