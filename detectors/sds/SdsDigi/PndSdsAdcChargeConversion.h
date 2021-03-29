#ifndef PNDSDSADCCHARGECONVERSION_H
#define PNDSDSADCCHARGECONVERSION_H

#include <iostream>
#include <cmath>
#include "PndSdsChargeConversion.h"

//! Class to calculate the deposited charge in one digi <-> digital channel number
//! and vice versa
/** @authors R.Schnell & R. Kliemt (Uni Bonn)
 *
 * This class calculates the ADC channel number for a given resolution
 * 
 * Open issues: Introduce a possible nonlinear behavior/calibration
 *
 */


class PndSdsAdcChargeConversion : public PndSdsChargeConversion
{
public:
  
	/// constructor
  PndSdsAdcChargeConversion(Int_t threshold=0, Int_t adcstep=1, Int_t resolution=8, Int_t VerboseLevel=0);
  
	///Destructor
  ~PndSdsAdcChargeConversion(){};
  
  
	virtual Double_t ChargeToDigiValue(Double_t charge);
	virtual Double_t DigiValueToCharge(Double_t digivalue);
	virtual Double_t GetRelativeError(Double_t Charge);
  virtual Int_t GetTimeStamp(Double_t time);
  virtual Double_t GetTimeStamp(Double_t tof, Double_t charge, Double_t MCEventTime);
  
  
//private:
  Int_t fVerboseLevel;
  Int_t fThreshold;		//[e]
  Int_t fAdcStep;     //[e]
  Int_t fResolution;  //[bit]
  Int_t fMaxADC;      //
  Double_t fTimeStep;     //[ns]
  Double_t DigitizeTime(Double_t time);
  
  ClassDef(PndSdsAdcChargeConversion, 1);
};

#endif /* PndSdsAdcChargeConversion_H */
