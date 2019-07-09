/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/


#include "FairFilteredPrimaryGenerator.h"
#include "FairLogger.h"

#include "FairGenerator.h"              // for FairGenerator
#include "FairGenericStack.h"           // for FairGenericStack
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairMCEventHeader.h"          // for FairMCEventHeader

#include "TDatabasePDG.h"               // for TDatabasePDG
#include "TIterator.h"                  // for TIterator
#include "TObject.h"                    // for TObject
#include "TString.h"                    // for TString

#include <stddef.h>                     // for NULL
#include <iostream>                     // for operator<<, basic_ostream, etc

using std::cout;
using std::cerr;
using std::endl;


// -----   Default constructor   -------------------------------------------
FairFilteredPrimaryGenerator::FairFilteredPrimaryGenerator()
: FairPrimaryGenerator(),

  fVetoFilterList(new TObjArray()),
  fVetoFilterIter(fVetoFilterList->MakeIterator()),
  fFilterList(new TObjArray()),
  fFilterIter(fFilterList->MakeIterator()),
  fEvtFilterStat(FairEvtFilterParams()),
  fVerbose(3),
  fEventVetoFilterActive(kFALSE),
  fEventFilterActive(kFALSE),
  filterAcceptEvent(),fLogicalFilterOperation(),fFilterNegation(),
  fEventNrFiltered(0)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with title and name   -------------------------------
FairFilteredPrimaryGenerator::FairFilteredPrimaryGenerator(const char* name, const char* title)
: FairPrimaryGenerator(name,title),

  fVetoFilterList(new TObjArray()),
  fVetoFilterIter(fVetoFilterList->MakeIterator()),
  fFilterList(new TObjArray()),
  fFilterIter(fFilterList->MakeIterator()),
  fEvtFilterStat(FairEvtFilterParams()),
  fVerbose(3),
  fEventVetoFilterActive(kFALSE),
  fEventFilterActive(kFALSE),
  filterAcceptEvent(),fLogicalFilterOperation(),fFilterNegation(),
  fEventNrFiltered(0)
{
}
// -------------------------------------------------------------------------

Bool_t FairFilteredPrimaryGenerator::Init()
{
	FairPrimaryGenerator::Init();
	// Initialize list of veto filters
	for(Int_t k=0; k<fVetoFilterList->GetEntries(); ++k ) {
		FairEvtFilter* vetoFilter= (FairEvtFilter*) fVetoFilterList->At(k);
		if(vetoFilter) { vetoFilter->Init(); }
	}
	// Initialize list of event filters
	for(Int_t k=0; k<fFilterList->GetEntries(); ++k ) {
		FairEvtFilter* filter= (FairEvtFilter*) fFilterList->At(k);
		if(filter) { filter->Init(); }
	}
	return kTRUE;
}


// -----   Destructor   ----------------------------------------------------
FairFilteredPrimaryGenerator::~FairFilteredPrimaryGenerator()
{
	fVetoFilterList->Delete();
	delete fVetoFilterList;
	delete fVetoFilterIter;

	fFilterList->Delete();
	delete fFilterList;
	delete fFilterIter;

	//cout<<" Leave Destructor of FairFilteredPrimaryGenerator"<<endl;
}
// -------------------------------------------------------------------------



// -----   Public method GenerateEvent   -----------------------------------
Bool_t FairFilteredPrimaryGenerator::GenerateEvent(FairGenericStack* pStack)
{
	Int_t iTry=0; // number of attempts to find the next event that suits your filter
	Bool_t acceptEvent = kFALSE; // is kTRUE if the event is finally accepted

	if(kTRUE == fEventFilterActive){
		// sanity check settings for logical combinations of event filters
		if((int)fFilterNegation.size()!=fFilterList->GetEntriesFast()){
			std::cout << "\n\n\n  -WARNING from FairFilteredPrimaryGenerator: size of the negation vector has to be equal to the number of added filters. Check your FilterNegation call!\n\n\n";
			return kFALSE;
		}
		if((int)fLogicalFilterOperation.size()!=fFilterList->GetEntriesFast()-1){
			std::cout << "\n\n\n  -WARNING from FairFilteredPrimaryGenerator: size of the operation vector has to be equal to the number of added filters minus one. Check your LogicalFilterOperation call!\n\n\n";
			return kFALSE;
		}
	}

	do{
		++iTry; // count how often we run the generators before we accept an event
		++fEvtFilterStat.fGeneratedEvents; // total number of generated events
		Bool_t vetoed = kFALSE; // is kTRUE if event matches any of the veto filters (we will skip such events)



		pStack->Reset(); // Clean the stack
		FairPrimaryGenerator::GenerateEvent(pStack); // fill the stack
		fEventNr = fEventNrFiltered; // Fix event numbering in FairPrimaryGenerator (otherwise fRun will stop too early...)


		if(kTRUE == fEventVetoFilterActive){// skip veto filter checking if no veto filters are set
			// check veto filters. skip event if the event satisfies any of the veto filters' conditions
			// Call the FilterAccept methods for all veto filters
			fVetoFilterIter->Reset();
			TObject* vetoFilterObject = 0;
			FairEvtFilter* vetoFilter = 0;
			while( (vetoFilterObject = fVetoFilterIter->Next()) ) {
				vetoFilter = dynamic_cast<FairEvtFilter*> (vetoFilterObject);
				if ( ! vetoFilter ) { // this should never happen
					cout << " \n\n\n  -FATAL ERROR from FairFilteredPrimaryGenerator: Veto filter cast did not work!\n\n\n" << endl;
					return kFALSE;
				}
				if( !( vetoFilter->FilterActive() ) ){
					cout << " \n\n\n  -WARNING from FairFilteredPrimaryGenerator: There are no filter settings for filter " << vetoFilter->GetName() << " : " << vetoFilter->GetTitle() << ". Execution is halted!\n\n\n" << endl;
					return kFALSE;
				}
				Bool_t setParticlesOk = vetoFilter->SetListOfParticles(pStack->GetListOfParticles());//committing the list of particles to be checked
				if( ! setParticlesOk ) {
					cout << " \n\n\n  -WARNING from FairFilteredPrimaryGenerator: Particles were not pushed correctly to veto filter.\n\n\n" << endl;
					return kFALSE;
				}
				if ( vetoFilter->EventMatches(fEvtFilterStat.fGeneratedEvents) ) {
					// if event matches veto filter, skip event
					if( 3 < fVerbose ){
						cout << "\n Event is NOT accepted because it matches a veto filter \n";
					}
					vetoed = kTRUE;
					break; // no need to check other veto filters as event will be skipped anyway
				}
			} // end while
		} // if veto filtering

		if ( vetoed ) { continue; }; // skip event if it matches at least one veto filter

		if ( kFALSE == fEventFilterActive ){ // skip event filtering (i.e. accept all events) if filtering is not requested
			acceptEvent = kTRUE;
			if( 3 < fVerbose ){
				cout << "\n Event is accepted because event filtering is not requested.\n\n";
			}
		} else { // do the event filtering (i.e. decide whether to accept or not accept the generated events) if filtering is requested
			Int_t iCheckFilter=0;
			// Call the FilterAccept methods for all registered (non-veto) filters
			fFilterIter->Reset();
			TObject* eventFilterObject = 0;
			FairEvtFilter* eventFilter = 0;
			filterAcceptEvent.clear();
			while( (eventFilterObject = fFilterIter->Next()) ) {
				eventFilter = dynamic_cast<FairEvtFilter*> (eventFilterObject);
				if ( ! eventFilter ) {
					return kFALSE; } // this should never happen
				if( !( eventFilter->FilterActive() ) ){
					cout << " \n\n\n  -WARNING from FairFilteredPrimaryGenerator: There are no filter settings for filter " << eventFilter->GetName() << " : " << eventFilter->GetTitle() << ". Execution is halted!\n\n\n" << endl;
					return kFALSE;
				}
				Bool_t setParticlesOk = eventFilter->SetListOfParticles(pStack->GetListOfParticles());//committing the list of particles to be checked
				if( ! setParticlesOk ) {
					return kFALSE;
				}
				filterAcceptEvent.push_back(eventFilter->EventMatches(fEvtFilterStat.fGeneratedEvents));
				// check whether the simulated event matches the individual event filter
				iCheckFilter++;
			}

			//----------FilterNegation
			// negate output from the event filters which should be negated
			for(UInt_t iFil=0; iFil<fFilterNegation.size(); iFil++){
				if(kTRUE == fFilterNegation[iFil]){
					filterAcceptEvent[iFil]=(!filterAcceptEvent[iFil]);
				}
			}


			//----------LogicalFilterOperation
			// combine (possibly negated) outputs from individual event filters using the logical connections stored in fLogicalFilterOperation
			// in order to check whether the event is accepted
			acceptEvent=filterAcceptEvent[0];
			for(UInt_t iOper=0; iOper<fLogicalFilterOperation.size();iOper++){
				if(fLogicalFilterOperation[iOper]==FairEvtFilter::kAnd){
					acceptEvent=acceptEvent && filterAcceptEvent[iOper+1];
				}else{
					if(fLogicalFilterOperation[iOper]==FairEvtFilter::kOr){
						acceptEvent=acceptEvent || filterAcceptEvent[iOper+1];
					}else{
						std::cout << "\n\n\n  -WARNING from FairFilteredPrimaryGenerator: the entries of the operation vector have to be kAnd or kOr. Check your LogicalFilterOperation call!\n\n\n";
						return kFALSE;
					}
				}
			}
			if( !acceptEvent && 3 < fVerbose ){
				cout << "\n Event is NOT accepted after combining the event filters.\n";
			}
		} // if (non-veto) event filtering
	}while(! acceptEvent && iTry < fEvtFilterStat.fFilterMaxTries);


	// Set the event number ALWAYS when filtering
	++fEventNrFiltered;
	fEvent->SetEventID(fEventNrFiltered);

	if ( !acceptEvent && ( fEventFilterActive||fEventVetoFilterActive ) ){
		++fEvtFilterStat.fFailedFilterEvents;
		cout << "\n -E FairFilteredPrimaryGenerator: No event was found within " << iTry << " tries which satisfies your event filter.\n ";
		cout << "I accept a random event as evtNr " << fEventNrFiltered << " to avoid infinite loops. \n";
		cout <<  "Try increasing the max. number of tries or change your filter\n\n";
		if (fVerbose > 3 ){
			if(fFilterList->GetEntriesFast() > 0){cout << "\n Event is accepted after combining the appointed filters.\n";}
			cout << iTry << " events simulated until I found a good one.\n";
			cout << fEvtFilterStat.fGeneratedEvents << " events generated for finding " << fEventNr << " accepted events.\n";
			cout << fEvtFilterStat.fFailedFilterEvents << " unsuccessful attempts in total to find an event that suits your filters\n\n";
		}
	}

	if (0 < fVerbose) cout << fEventNrFiltered << " of " << fEvtFilterStat.fGeneratedEvents << " generated events accepted.\n";

	return kTRUE;
}
// -------------------------------------------------------------------------



ClassImp(FairFilteredPrimaryGenerator)
