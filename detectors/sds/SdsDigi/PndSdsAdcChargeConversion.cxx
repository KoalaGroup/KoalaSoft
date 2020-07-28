//
#include "PndSdsAdcChargeConversion.h"


/// constructor
PndSdsAdcChargeConversion::PndSdsAdcChargeConversion(Int_t threshold, Int_t adcstep, Int_t resolution, Int_t VerboseLevel) 
: PndSdsChargeConversion(kADC),
fVerboseLevel(VerboseLevel),
fThreshold(threshold),
fAdcStep(adcstep),
fResolution(resolution),
fMaxADC(0),
fTimeStep(0.)
{
  fMaxADC = (Int_t)pow(2,fResolution);
}


Double_t PndSdsAdcChargeConversion::ChargeToDigiValue(Double_t charge)
{
  if(charge <= fThreshold) return 0.; //underflow
  Int_t ADC = (Int_t)floor(double(charge - fThreshold)/double(fAdcStep))+1;
  if(ADC>fMaxADC) return fMaxADC; //overflow
	return ADC;  
}

Double_t PndSdsAdcChargeConversion::DigiValueToCharge(Double_t ADC)
{ //returns the charge for the given tot value
	if (ADC<0){
		if (fVerboseLevel>0)
      Error("ConvertDigiValueToELoss(Double_t digi)","charge digitization value not calculated properly");
		return -1;
	}
	if(ADC==0) return 0.5*fThreshold;
  return (ADC-0.5)*fAdcStep+fThreshold;
}


Double_t PndSdsAdcChargeConversion::GetRelativeError(Double_t Charge)
{
  // TODO: How is the uncertainty?
  if(fabs(Charge) < 1e-6) return -1;
  return fAdcStep/Charge;
}

Int_t PndSdsAdcChargeConversion::GetTimeStamp(Double_t time)
{
  return (Int_t)time;
  //Int_t temp = (Int_t)(time / ftimestep); // [clockcycles]
  //time = temp*ftimestep + ftimestep; //[ns] to the following clock tick
  //return (Int_t)TMath::Ceil(time); // [ns] with 1 ns number precision, casting cuts trailing digits, like floor()
}


Double_t PndSdsAdcChargeConversion::GetTimeStamp(Double_t time, Double_t Charge,Double_t MCEventTime)
{

	Double_t totaltime = MCEventTime;// [ns]
	totaltime += time; // [ns]
	//ftimewalk=GetTimeWalk(Charge);
  //totaltime += ftimewalk;

	Double_t digitizedtime = DigitizeTime(totaltime);

	  if (fVerboseLevel>2){
	   std::cout<<"  +++charge: "<< Charge <<" "<<std::endl;
	   std::cout<<"  time since event: "<< time <<" "<<std::endl;
	   //std::cout<<"  timewalk: "<< ftimewalk <<std::endl;
	   std::cout<<"  total time: "<< totaltime <<std::endl;
	   std::cout<<"  digitized total time:"<< digitizedtime << "+++"<<std::endl;
	  }
	 return digitizedtime ; //digitalisiert
//	 return totaltime; // nicht digitalisiert
}

Double_t PndSdsAdcChargeConversion::DigitizeTime(Double_t time)
{
  return ceil(time);
	//Int_t temp = (time) / ftimestep;
	//time =  temp *ftimestep + ftimestep;
  //if (fVerboseLevel>2) std::cout << "temp " << temp << " time " << time << std::endl;
	//return time;
}

ClassImp(PndSdsAdcChargeConversion);

