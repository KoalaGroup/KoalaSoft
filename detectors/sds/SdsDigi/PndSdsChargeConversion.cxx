#include "PndSdsChargeConversion.h"

Double_t PndSdsChargeConversion::DigiValueToCharge	(PndSdsDigi &digi){
	return DigiValueToCharge(digi.GetCharge());
}

ClassImp(PndSdsChargeConversion);
