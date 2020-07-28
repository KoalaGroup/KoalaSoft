#include "PndSdsDigi.h"

PndSdsDigi::PndSdsDigi() :
		fIndex(),
		fDetID(-1),
		fSensorID(-1),
		fFE(-1),
		fCharge(-1.)
{
}

PndSdsDigi::PndSdsDigi(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Double_t charge, Double_t timestamp):
FairTimeStamp(timestamp), fIndex(), fDetID(detID), fSensorID(sensorID), fFE(fe), fCharge(charge)
{ 
	AddIndex(index);
}

PndSdsDigi::PndSdsDigi(Int_t index, Int_t detID, Int_t sensorID, Int_t fe, Double_t charge, Double_t timestamp):
FairTimeStamp(timestamp), fIndex(), fDetID(detID), fSensorID(sensorID), fFE(fe), fCharge(charge)
{
	AddIndex(index);
}

ClassImp(PndSdsDigi);
