// -------------------------------------------------------------------------
// -----                    FairEvtFilter header file                   -----
// -------------------------------------------------------------------------


/** FairEvtFilter.h

Authors: Martin Galuska, Katja Kleeberg

abstract base class for event filters
used to reject generated events which should not be fed into the transport.
Each concrete filter class derived from this one must implement the abstract
method EventMatches, in which the particular filter criteria are realized.

 **/

/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/

#ifndef FAIREVTFILTER_H
#define FAIREVTFILTER_H

#include "TNamed.h"                     // for TNamed
#include "Rtypes.h"                     // for Bool_t, etc
#include "TClonesArray.h"
#include "TParticle.h"
#include <iostream>
#include <set>
#include "TDatabasePDG.h"


std::ostream& operator <<(std::ostream& os, const std::set<Int_t> & set);



class FairEvtFilter : public TNamed
{

public:

	enum ChargeState { kNeutral=0, kPlus, kMinus, kCharged, kAll, kChargeLastElement };
	enum MomState { kMomTotal=0, kMomTrans, kMomZ, kMomLastElement};
	enum GeomState {kTheta=0, kPhi, kVertexZ, kVertexRho, kVertexRadius, kGeomLastElement};
	enum LogicOp { kAnd=0, kOr, kLogicOpLastElement };

	/** Default constructor. **/
	FairEvtFilter();


	/** Constructor with name and title **/
	FairEvtFilter(const char* name, const char* title="FairEvtFilter");


	/** Destructor. **/
	virtual ~FairEvtFilter();


	//contains the list of particles that should be checked in the EventMatches method
	Bool_t SetListOfParticles(TClonesArray* ParticleList){fParticleList=ParticleList; return kTRUE;};

	// prints all TParticle in event
	void PrintAllTParticleInEvent();


	//Initialize the filter if needed
	Bool_t Init() { return kTRUE;}


	void SetVerbose(Int_t verbose=12){
		if ( verbose >= 0 ){
			fVerbose = verbose;
			std::cout << "FairEvtFilter: fVerbose is now set to " << verbose << "\n";
		} else {
			std::cout << "\n\n\n  -WARNING from FairEvtFilter: verbose must be a positive number! Check your SetVerbose call!\n\n\n";
		}
	}


	void ShowAcceptedEventNumbers(){
		// for QA
		// shows fAcceptedEventNumbers that is filled after running a simulation
		std::cout << "\n fAcceptedEventNumbers" << " = " << fAcceptedEventNumbers;
	}


	void ShowEvtNrsToAccept(){
		// for QA
		//shows fEvtNrsToAccept that has to be set if you want to run your simulation in test mode
		std::cout << "\n fEvtNrsToAccept" << " = " << fEvtNrsToAccept;
	}


	void SetTestMode(Int_t* arrayPtr, Int_t nEntries){
		//turns on the test mode with the declared fEvtNrsToAccept
		fTestMode=kTRUE;
		std::set<Int_t> evtNrsToAccept (arrayPtr,arrayPtr+nEntries);
		fEvtNrsToAccept=evtNrsToAccept;
	}


	Bool_t TestPassed(){
		if(kFALSE==fTestMode){
			std::cout << "\n\n\n WARNING from FairEvtFilter: Test mode not set.\n\n\n";
			return kFALSE;
		}
		if(fAcceptedEventNumbers==fEvtNrsToAccept){
			//std::cout << "\n\n\n FairEvtFilter: Test passed.\n\n\n";
			return kTRUE;
		}else{
			//std::cout << "\n\n\n FairEvtFilter: Test failed. Check your SetTestMode calls. \n\n\n";
			return kFALSE;
		}
	}


	// returning kTRUE indicates that the event satisfies the filter conditions,
	// kFALSE otherwise.
	virtual Bool_t EventMatches(Int_t evtNr)=0;

	virtual Bool_t FilterActive()=0;

	// returns kTRUE if successful
	// pdgCodeCharge will contain the charge of the particle with pdg code inPdgCode
	Bool_t GetCharge ( Int_t inPdgCode, Double_t *pdgCodeCharge );


protected:
	TDatabasePDG* fdbPdg;
	// constant holding a double number which is not a valid charge
	// this serves to indicate that the value has not been specified by the user
	static const Double_t kNoChargeSpecified;

	TClonesArray* fParticleList; // list of particles in the event which was generated
	Int_t fVerbose; // level of commenting output for your filter, between 0 and 12
	Bool_t fTestMode; // is kTRUE if the filter should run in QA test mode
	std::set<Int_t> fAcceptedEventNumbers; // set of event numbers which were accepted by the filter
	std::set<Int_t> fEvtNrsToAccept; // event numbers that SHOULD be accepted by the filter (QA test mode)
	Int_t fEventNr; // current event number

private:
	FairEvtFilter(const FairEvtFilter& G);
	FairEvtFilter& operator= (const FairEvtFilter&) {return *this;}



	ClassDef(FairEvtFilter,1);
};

#endif


