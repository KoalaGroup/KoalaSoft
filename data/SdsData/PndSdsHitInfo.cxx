/** PndSdsHitInfo source file
 *@author 
 ** Acknowledgements to M. Al-Turany, D. Bertini, G. Gaycken, Michael Deveaux <m.deveaux@gsi.de>
 ** Version beta 0.1 (02.02.2005)
 **/


#include "PndSdsHitInfo.h"


/** Constructor **/
PndSdsHitInfo::PndSdsHitInfo() {
  fFileNumber  = -1;
  fEventNumber = -1;
  fTrackID     = -1;
  fPointID     = -1;
  fNMerged     =  0;
  fIsFake      = kFALSE;
}


/** Constructor with all parameters **/
PndSdsHitInfo::PndSdsHitInfo(Int_t fileNumber, Int_t eventNumber,
			     Int_t trackID, Int_t pointID,
			     Int_t nMerged, Bool_t isFake) {
  fFileNumber  = fileNumber;
  fEventNumber = eventNumber;
  fTrackID     = trackID;
  fPointID     = pointID;
  fNMerged     = nMerged;
  fIsFake      = isFake;
}


/** Destructor **/
PndSdsHitInfo::~PndSdsHitInfo() { }


/** Public method Clear **/
void PndSdsHitInfo::Clear() {
  fFileNumber  = -1;
  fEventNumber = -1;
  fTrackID     = -1;
  fPointID     = -1;
  fNMerged     =  0;
  fIsFake      = kFALSE;
}



ClassImp(PndSdsHitInfo);
