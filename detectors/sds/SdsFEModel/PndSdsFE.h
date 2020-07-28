/*
 * SdsFEAmpModel.h
 *
 *  Created on: Apr 4, 2011
 *      Author: esch
 *
 *      Class to calculate ToT, TimeWalk, TimeStamp and Time till the signal is back to baseline from a TF1 amplifier model.
 *
 *
 */

#ifndef PndSdsFE_H_
#define PndSdsFE_H_
#include "TObject.h"
#include "PndSdsFEAmpModelSimple.h"
#include "TMath.h"
#include "TF1.h"
#include "TRandom2.h"
#include "Math/Interpolator.h"
#include "Math/InterpolationTypes.h"
#include "PndSdsTotChargeConversion.h"
#include "TVectorT.h"

class PndSdsFE: public TObject {
public:
	PndSdsFE(): fFrontEndModel(0), fNumberOfSupportPoints(0), fNumberOfMaxElectons(0), fFunction(0), fMaximumAmplitude(0),fThreshold(0), fBaselineEpsilon(1), fToF(0), fEventTime(0),	fTimeOffSet(0), fTimeStep(0),fFunctionRange(0), fRand(0), i(0), stepsize(0), fCharge_list(0), fTot_list(0), inter(0) 
	{
		CalcTimeOffSet();
	};
  
  PndSdsFE(PndSdsFE& other):TObject(other),
      fFrontEndModel(other.fFrontEndModel),
      fNumberOfSupportPoints(other.fNumberOfSupportPoints),
      fNumberOfMaxElectons(other.fNumberOfMaxElectons),
      fFunction(other.fFunction),
      fMaximumAmplitude(other.fMaximumAmplitude),
      fThreshold(other.fThreshold),
      fBaselineEpsilon(other.fBaselineEpsilon),
      fToF(other.fToF),
      fEventTime(other.fEventTime),
  	  fTimeOffSet(other.fTimeOffSet),
      fTimeStep(other.fTimeStep),
      fFunctionRange(other.fFunctionRange),
      fRand(other.fRand),
      i(other.i),
      stepsize(other.stepsize),
      fCharge_list(other.fCharge_list),
      fTot_list(other.fTot_list),
      inter(other.inter)
  {};
//	PndSdsFE(double charingtime, double constcurrent, double threshold, double frequency, int verbose);
	virtual ~PndSdsFE();

	virtual double GetTotFromCharge(Double_t charge);			// Calculates the ToT value from the charge
	virtual double GetChargeFromTot(double tot);				// Calculates the charge from the tot value
	virtual double GetTimeWalkFromCharge(double charge);		// Calculates the TimeWalk from the charge
	virtual double GetTimeWalkFromTot(double tot);				// Calculates the TimeWalk from the TOT value
	virtual double GetTimeBackToBaseline(double charge);		// Calculates the time from start of the signal till the signal is fBaselineEpsilon close to baseline
	virtual double GetTimeStamp(double eventtime, double tof, double charge);  // Calculates the TimeStamp of the signal
	virtual double GetTimeStep(){return fTimeStep;}
	virtual void SetParameter(TString parName, double parValue);
	virtual void SetThreshold(double threshold){fThreshold = threshold;}

  PndSdsFE& operator=(PndSdsFE& other)
  {
    if (this != &other) // protect against invalid self-assignment
    {   
      fFrontEndModel=other.fFrontEndModel;
      fNumberOfSupportPoints=other.fNumberOfSupportPoints;
      fNumberOfMaxElectons=other.fNumberOfMaxElectons;
      fFunction=other.fFunction;
      fMaximumAmplitude=other.fMaximumAmplitude;
      fThreshold=other.fThreshold;
      fBaselineEpsilon=other.fBaselineEpsilon;
      fToF=other.fToF;
      fEventTime=other.fEventTime;
  	  fTimeOffSet=other.fTimeOffSet;
      fTimeStep=other.fTimeStep;
      fFunctionRange=other.fFunctionRange;
      fRand=other.fRand;
      i=other.i;
      stepsize=other.stepsize;
      fCharge_list=other.fCharge_list;
      fTot_list=other.fTot_list;
      inter=other.inter;
    }
    return *this;
  };
protected:

  double DigitizeTime(double time);
	void CalcTimeOffSet();
  void CreateInterpolatorList();  // Creates the Interpolatorlist for GetTotFromCharge calculation
	void SaveInterpolatorList(std::vector<double> charge, std::vector<double> tot);
	void LoadInterpolatorList();
	void GetInterpolatorList();


	PndSdsFEAmpModelSimple *fFrontEndModel;

	int fNumberOfSupportPoints;
	int fNumberOfMaxElectons ;

	TF1 *fFunction;
	double fMaximumAmplitude;      // Saves position of the maximum amplitude of the signal
	double fThreshold;				// Threshold for Signal from Parameter database
	double fBaselineEpsilon;		//
	double fToF;					// Time of Flight from MC
	double fEventTime;				// EventTime from MC
	double fTimeOffSet;				// Random offset
	double fTimeStep;
	double fFunctionRange; 			//Range of the function. max 100 fC => 624 150.9 e => max.tot 10503 ns (with thr.= 1100 e)
	TRandom2 fRand;
	int i;
	double stepsize;

	std::vector<double> fCharge_list;
	std::vector<double> fTot_list;
	ROOT::Math::Interpolator *inter;

private:




	ClassDef(PndSdsFE,1);
};

#endif /* PndSdsFE_H_ */
