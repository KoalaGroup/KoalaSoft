// -------------------------------------------------------------------------
// -----                     FairEvtFilter source file                 -----
// -------------------------------------------------------------------------

/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/


#include "FairEvtFilter.h"

const Double_t FairEvtFilter::kNoChargeSpecified = -999.9;

// -----   Default constructor   -------------------------------------------
FairEvtFilter::FairEvtFilter()
: TNamed(), fParticleList(NULL), fVerbose(0), fTestMode(0), fAcceptedEventNumbers(), fEvtNrsToAccept(), fEventNr(0)
{
	fAcceptedEventNumbers.clear();
	fdbPdg = TDatabasePDG::Instance();
}
// -------------------------------------------------------------------------



// -----   Constructor with name and title   -------------------------------
FairEvtFilter::FairEvtFilter(const char* name, const char* title)
: TNamed(name, title), fParticleList(NULL), fVerbose(0), fTestMode(0), fAcceptedEventNumbers(), fEvtNrsToAccept(), fEventNr(0)
{
	fAcceptedEventNumbers.clear();
	fParticleList = 0;
	fdbPdg = TDatabasePDG::Instance();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairEvtFilter::~FairEvtFilter() { }
// -------------------------------------------------------------------------


std::ostream& operator <<(std::ostream& os, const std::set<Int_t> & set)
{
	std::set<Int_t>::iterator iter;
	os << "{";
	for(iter=set.begin(); iter!=set.end(); ++iter){
		os << *iter;
		if(iter!=--set.end()){os << ",";}
	}
	os << "}\n";

	return os;
}


void FairEvtFilter::PrintAllTParticleInEvent(){
	// sanity checks
	if (0==fParticleList){ return; }
	for (Int_t iPart=0; iPart<fParticleList->GetEntries(); ++iPart) {
		TParticle *particle = (TParticle*)fParticleList->At(iPart);
		particle->Print();
	}
}


Bool_t FairEvtFilter::GetCharge ( Int_t inPdgCode, Double_t *pdgCodeCharge )
{
	// Try to find the pdg code
	TParticlePDG *ptrToPdg = fdbPdg->GetParticle(inPdgCode);
	if ( 0 == ptrToPdg) {
		// ignore particles with unknown charges
		std::cout << "WARNING from FairEvtFilter::GetCharge Charge of pdgCode " << inPdgCode << " is unknown and will be ignored!\n";
		*pdgCodeCharge = kNoChargeSpecified;
		return kFALSE;
	}
	*pdgCodeCharge = ptrToPdg->Charge()/3.; // TParticlePDG contains charge in units of |e|/3
	if ( fVerbose > 1 ) std::cout << "Found pdgCodeCharge = " << *pdgCodeCharge << " for inPdgCode " << inPdgCode << '\n';
	return kTRUE;
}

ClassImp(FairEvtFilter)
