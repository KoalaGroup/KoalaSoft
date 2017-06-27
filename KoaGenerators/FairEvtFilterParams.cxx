/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/

#include "FairEvtFilterParams.h"

ClassImp(FairEvtFilterParams)
// -----   Default constructor   -------------------------------------------
FairEvtFilterParams::FairEvtFilterParams() : fFailedFilterEvents(0), fGeneratedEvents(0),
fFilterMaxTries(999999){ }
// -------------------------------------------------------------------------

// -----   constructor with parameters   -------------------------------------------
FairEvtFilterParams::FairEvtFilterParams(Int_t FailedFilterEvents, Int_t GeneratedEvents, Int_t FilterMaxTries) {
	fFailedFilterEvents=FailedFilterEvents;
	fGeneratedEvents=GeneratedEvents;
	fFilterMaxTries=FilterMaxTries;
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairEvtFilterParams::~FairEvtFilterParams() { }
// -------------------------------------------------------------------------

