/*
 * PndLmdContFact.h
 *
 *  Created on: May 29, 2009
 *      Author: huagen
 */

#ifndef PNDLMDCONTFACT_H_
#define PNDLMDCONTFACT_H_

#include "FairContFact.h"

class FairContainer;

class PndLmdContFact : public FairContFact {
public:
	PndLmdContFact();
	~PndLmdContFact();
	FairParSet* createContainer(FairContainer* c);
	TList* GetDigiParNames() {return fDigiParNames;};
	TList* GetAlignParNames() {return fAlignParNames;};
private:
	void setAllContainers();
	TList* fDigiParNames;
	TList* fAlignParNames;
	ClassDef(PndLmdContFact,3)
};

#endif /* PNDLMDCONTFACT_H_ */
