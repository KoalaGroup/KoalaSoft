/*
 * PndSdsRadDamHit.h
 *
 *  Created on: Dec 16, 2008
 *      Author: stockman
 */

#ifndef PNDSDSRADDAMHIT_H_
#define PNDSDSRADDAMHIT_H_

#include "TObject.h"
#include "TVector3.h"
class PndSdsRadDamHit : public TObject
{
public:
	PndSdsRadDamHit();
	PndSdsRadDamHit(Int_t trackID, Int_t hitID, TString detName, Int_t pdgCode, Double_t energy,
	  	    TVector3 pos, TVector3 mom, Double_t radDam);
	virtual ~PndSdsRadDamHit(){};

	void SetRadDam(Double_t radDam){fRadDam = radDam;};
	Double_t GetRadDam(){return fRadDam;};

private:
  Int_t fTrackID;
	Int_t fHitID;
	TString fDetName;
	Int_t fPdgCode;
	Double_t fEnergy;
	TVector3 fPos;
	TVector3 fMom;
  Double_t fRadDam;


	ClassDef(PndSdsRadDamHit,2);
};


#endif /* PNDSDSRADDAMHIT_H_ */
