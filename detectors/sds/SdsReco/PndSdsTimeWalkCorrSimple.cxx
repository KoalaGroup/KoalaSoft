/*
 * PndSdsTimeWalkCorrSimple.cpp
 *
 *  Created on: Aug 26, 2010
 *      Author: esch
 */

#include "PndSdsTimeWalkCorrSimple.h"


ClassImp(PndSdsTimeWalkCorrSimple);

//----- Default Constructor

PndSdsTimeWalkCorrSimple::PndSdsTimeWalkCorrSimple() 
:	fRisingTime(0.),
  fConstantCurrent(0.),
  fTimeOverThreshold(0.),
  fThreshold(0.),
  fFrequency(0.),
  fVerboseLevel(0),
  fCharge(0.),
  fTimeWalk(0.)
{
}
//----- Main Constructor

PndSdsTimeWalkCorrSimple::PndSdsTimeWalkCorrSimple(Double_t risingtime, Double_t constcurrent, Double_t thr, Double_t frequency, Int_t verblevel)
:	fRisingTime(risingtime),
  fConstantCurrent(constcurrent),
  fTimeOverThreshold(0.),
  fThreshold(thr),
  fFrequency(frequency),
  fVerboseLevel(verblevel),
  fCharge(0.),
  fTimeWalk(0.)
{
}

PndSdsTimeWalkCorrSimple::~PndSdsTimeWalkCorrSimple() {

}

Double_t PndSdsTimeWalkCorrSimple::CorrectionTimeWalk(Double_t tot)
{
fCharge = CalculateCharge(tot);
fTimeWalk = CalculateTimeWalk(fCharge);


return fTimeWalk;
}

Double_t PndSdsTimeWalkCorrSimple::CalculateCharge(Double_t tot) {
Double_t charge = -(fRisingTime*fConstantCurrent-fThreshold-tot*fConstantCurrent)/2.+sqrt(fRisingTime*fThreshold*fConstantCurrent+pow((fRisingTime*fConstantCurrent-fThreshold-tot*fConstantCurrent)/2.,2));

return charge;
}

Double_t PndSdsTimeWalkCorrSimple::CalculateTimeWalk(Double_t charge)
{
return fRisingTime*fThreshold/charge;

}


