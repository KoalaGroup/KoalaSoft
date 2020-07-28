#ifndef PNDSDSTOTCHARGECONVERSION_H
#define PNDSDSTOTCHARGECONVERSION_H

#include "TRandom2.h"
#include <iostream>
#include <cmath>
#include "PndSdsChargeConversion.h"

//! Class to calculate the deposited charge in one digi <-> time over threshold
//! and vice versa
/** @author D.-L.Pohl <d.pohl@fz-juelich.de>
 *
 * This class calculates the time over threshold by using the charge
 * of a pixel/strip. To calculate the TOT a simple capacitor model (integrator) is used.
 * The charge time tr [ns] is assumed to be constant. This leads to a rising straight line.
 * A constant current unloads the capacitor with a ratio of: a [e/ns].
 * The distance between the points of intersection between the resulting triangle
 * and the threshold line is the TOT.
 *
 * q
 * |
 * |     /\     a
 * |    /     \
 * |---/----------\--------------- threshold
 * |  /               \
 * ------------------------------- q = 0 (charge)
 *    | tr|                    t[ns]
 *      <-  TOT ->
 */


class PndSdsTotChargeConversion : public PndSdsChargeConversion
{
public:
	///Default constructor
	PndSdsTotChargeConversion(Int_t VerboseLevel = 0);
  
	///Main constructor
	PndSdsTotChargeConversion(Double_t tr, Double_t a, Double_t threshold, Double_t clockfrequency = 0, Int_t VerboseLevel = 0);
  
	///Destructor
	~PndSdsTotChargeConversion(){};
  
	void StartExecute();
  
	virtual Double_t ChargeToDigiValue(Double_t charge);
	virtual Double_t DigiValueToCharge(Double_t digivalue);
	virtual Double_t GetPileUpTime(Double_t charge);		///<returns the time the capacitor is loaded and therefore the time this MVD pixel/strip is blind for other events
	virtual Double_t GetRelativeError(Double_t Charge);
 // virtual Int_t GetTimeStamp(Double_t time);
  virtual Double_t GetTimeStamp(Double_t tof, Double_t charge, Double_t MCEventTime);
  virtual Double_t GetTimeWalk(Double_t Charge);
  virtual Double_t GetTimeStampErrorAfterCorrection(){
  	return ftimestep/sqrt(12);
  }

  virtual Double_t GetTimeStep(){return ftimestep;}


  
  
private:
  Double_t fthreshold;		//[e]
  Double_t Qt;				//threshold charge [e]
  Double_t t1e, t2e;			//exact time point when signal is over threshold/under threshold again [ns]
  Double_t ftimestep;			//one time step of the clock [ns]
  Double_t fstarttime;		//absolute point when TOT begins [ns]
  Double_t fstoptime;			//absolute point when TOT ends [ns]
  Double_t ftimeoffset;		//difference between rising clock edge and when detector gets hit [ns]
  Double_t ftimewalk;        //exact time point when signal is over threshold
  Int_t fVerboseLevel;
  Double_t GetTotWC();		//assumes a clock which results in a quantized TOT
  Double_t DigitizeTime(Double_t time);	///< returns the time in [ns] but binned to clock units
  TRandom2 fRand;
  
  ClassDef(PndSdsTotChargeConversion, 1);
};

#endif /* PNDSDSTOTCHARGECONVERSION_H */
