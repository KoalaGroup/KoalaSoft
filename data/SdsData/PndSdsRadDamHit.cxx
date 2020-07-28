/*
 * PndSdsRadDamHit.cxx
 *
 *  Created on: Dec 16, 2008
 *      Author: stockman
 */

#include "PndSdsRadDamHit.h"

PndSdsRadDamHit::PndSdsRadDamHit() :
  fTrackID(-1),
  fHitID(-1),
  fDetName(""),
  fPdgCode(-1),
  fEnergy(0.),
  fPos(0.,0.,0.),
  fMom(0.,0.,0.),
  fRadDam(0.)
{
}

PndSdsRadDamHit::PndSdsRadDamHit(Int_t trackID, Int_t hitID, TString detName, Int_t pdgCode, Double_t energy,
  	    TVector3 pos, TVector3 mom, Double_t radDam):
	  	    	fTrackID(trackID), fHitID(hitID), fDetName(detName), fPdgCode(pdgCode), fEnergy(energy),
	  	    	fPos(pos), fMom(mom), fRadDam(radDam)
{
}

ClassImp(PndSdsRadDamHit);
