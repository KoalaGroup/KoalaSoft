// -------------------------------------------------------------------------
// -----             FairEvtFilterParams header file                 -----
// -------------------------------------------------------------------------


/** FairEvtFilterParams.h

 Authors: Martin Galuska, Katja Kleeberg
 Martin dot J dot Galuska at physik dot uni minus giessen dot de

 Helper class for writing settings and statistics of the event filter to the sim root file

 **/

/** Added by Yong Zhou
    This file is copied from PandaRoot feb17p1
**/
/** TODO:
    1. use FairLogger for information output
 **/


#ifndef FAIREVTFILTERPARAMS_H_
#define FAIREVTFILTERPARAMS_H_

#include "TObject.h"

class FairEvtFilterParams : public TObject
{

public:

	// Default constructor.
	FairEvtFilterParams();

	// constructor with parameters
	FairEvtFilterParams(Long_t FailedFilterEvents, Long_t GeneratedEvents, Long_t FilterMaxTries);

	// Destructor.
	virtual ~FairEvtFilterParams();

	// number of failed attempts to find an event that satisfies all event filters
	// events are generated by the registered event generators
	// a value other than 0 indicates that there is something wrong!
	Long_t fFailedFilterEvents;

	// total number of generated events (accepted + rejected)
	Long_t fGeneratedEvents;

	// limiting number for the attempts to find an event that suits all event filters
	// set this to a very high number
	// this number is only used to avoid infinite loops in case no event can be found
	Long_t fFilterMaxTries;

	ClassDef(FairEvtFilterParams,1)
};


#endif /* FAIREVTFILTERPARAMS_H_ */
