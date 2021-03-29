// -------------------------------------------------------------------------
// -----                      PndSdsMCPoint source file                  -----
// -------------------------------------------------------------------------


#include <iostream>
#include "PndSdsMCPoint.h"
#include "FairRun.h"
#include "FairEventHeader.h"


// -----   Default constructor   -------------------------------------------
PndSdsMCPoint::PndSdsMCPoint() : FairMCPoint(), 
 		        fXfOut(0.), fYfOut(0.), fZfOut(0.), 
 		        fPxfOut(0.), fPyfOut(0.), fPzfOut(0), fSensorID(-1)
 		
{} 
	// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PndSdsMCPoint::PndSdsMCPoint(Int_t trackID, Int_t detID, Int_t sensorID,
			 TVector3 posIn, TVector3 posOut,
			 TVector3 momIn, TVector3 momOut,
			 Double_t tof, Double_t length, Double_t eLoss) :
  FairMCPoint(trackID, detID, posIn, momIn, tof, length, eLoss) ,
  fXfOut(posOut.X()),
  fYfOut(posOut.Y()),
  fZfOut(posOut.Z()),
  fPxfOut(momOut.Px()),
  fPyfOut(momOut.Py()),
  fPzfOut(momOut.Pz()),
  fSensorID(sensorID)
{
  //FIXME: Do we really need the header request?
  //FairEventHeader* evtHeader = FairRun::Instance()->GetEventHeader();
  SetLink(FairLink("MCTrack", trackID));
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndSdsMCPoint::~PndSdsMCPoint() { }
// -------------------------------------------------------------------------




// -----   Public method Print   -------------------------------------------
void PndSdsMCPoint::Print(const Option_t* opt) const {
	std::cout << *this << "opt="<<opt<<std::endl;
}
// -------------------------------------------------------------------------



ClassImp(PndSdsMCPoint);
