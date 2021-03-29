/////////////////////////////////////////////////////////////
//
//  PndSensorNameContFact
//
//  Factory for the parameter containers in libPndMvd
//
/////////////////////////////////////////////////////////////

#include "PndSensorNameContFact.h"
#include "FairRuntimeDb.h"
#include "PndSensorNamePar.h"
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "TList.h"
#include "TObjString.h"
#include <iostream>
#include <iomanip>

ClassImp(PndSensorNameContFact);

static PndSensorNameContFact gPndSensorNameContFact;

PndSensorNameContFact::PndSensorNameContFact(): fSensorParNames(), fContainerNames() {
  // Constructor (called when the library is loaded)
  fName="PndSensorNameContFact";
  fTitle="Factory for parameter containers of the PndGeoHandler";
  fSensorParNames = new TList();
  fContainerNames.push_back("PndSensorNamePar");
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}
PndSensorNameContFact::~PndSensorNameContFact(){
  if(0!=fSensorParNames)
  {
    fSensorParNames->Delete();
    delete fSensorParNames;
  }
}


void PndSensorNameContFact::setAllContainers() {
  /** Creates the Container objects with all accepted contexts and adds them to
   *  the list of containers for the MVD library.*/
	for (unsigned int i = 0; i < fContainerNames.size(); i++){
		std::string description = "Match between GeoManager path and SensorId";
		FairContainer* p = new FairContainer(fContainerNames[i].c_str(), description.c_str(), "TestDefaultContext");
		fSensorParNames->Add(new TObjString(p->getConcatName()));
		containers->Add(p);
	}
}

FairParSet* PndSensorNameContFact::createContainer(FairContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */
  const char* name=c->GetName();
  FairParSet* p=NULL;

  for (unsigned int i = 0; i < fContainerNames.size(); i++){
	  if (strcmp(name,fContainerNames[i].c_str())==0) {
		  p=new PndSensorNamePar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
		  return p;
	  }
  }
  return p;
}
