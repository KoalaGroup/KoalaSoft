/////////////////////////////////////////////////////////////
//
//  PndLmdContFact
//
//  Factory for the parameter containers in libPndLmd
//
/////////////////////////////////////////////////////////////

#include "PndLmdContFact.h"
#include "FairRuntimeDb.h"
//#include "PndMvdGeoPar.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotDigiPar.h"
#include "PndLmdAlignPar.h"
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "TList.h"
#include "TObjString.h"
#include <iostream>
#include <iomanip>

ClassImp(PndLmdContFact);

static PndLmdContFact gPndLmdContFact;

PndLmdContFact::PndLmdContFact() {
  // Constructor (called when the library is loaded)
  fName="PndLmdContFact";
  fTitle="Factory for parameter containers in libPndLmd";
  fDigiParNames = new TList();
  fAlignParNames = new TList();
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}
PndLmdContFact::~PndLmdContFact(){
  if(0!=fDigiParNames) 
  {
    fDigiParNames->Delete(); 
    delete fDigiParNames;
  }
  if(0!=fAlignParNames) 
  {
    fAlignParNames->Delete(); 
    delete fAlignParNames;
  }

}


void PndLmdContFact::setAllContainers() {
  /** Creates the Container objects with all accepted contexts and adds them to
   *  the list of containers for the MVD library.*/
//  FairContainer* p= new FairContainer("PndMvdGeoPar","PndMvd Geometry Parameters","TestDefaultContext");
//  p->addContext("TestNonDefaultContext");
//  fDigiParNames->Add(new TObjString(p->GetName()));
//  containers->Add(p);
  
  FairContainer* p2 = new FairContainer("KOAPixelDigiPar", "KOASds Pixel Digitization Parameters", "TestDefaultContext");
  p2->addContext("TestNonDefaultContext");
  fDigiParNames->Add(new TObjString(p2->GetName()));
  containers->Add(p2);
  
  FairContainer* p3 = new FairContainer("SDSStripDigiParRect", "PndSds Strip Digitization Parameters (rectangular sensors)", "TestDefaultContext");
  p3->addContext("TestNonDefaultContext");
  fDigiParNames->Add(new TObjString(p3->GetName()));
  containers->Add(p3);
  
  FairContainer* p4 = new FairContainer("SDSStripDigiParTrap", "PndSds Strip Digitization Parameters (trapezoid sensors)", "TestDefaultContext");
  p4->addContext("TestNonDefaultContext");
  fDigiParNames->Add(new TObjString(p4->GetName()));
  containers->Add(p4);

  FairContainer* p5 = new FairContainer("LMDAlignPar", "PndLmd Alignment Parameters", "TestDefaultContext");
  p5->addContext("TestNonDefaultContext");
  fAlignParNames->Add(new TObjString(p5->GetName()));
  containers->Add(p5);

FairContainer* p6 = new FairContainer("LMDPixelDigiPar", "LMDSds Pixel Digitization Parameters", "TestDefaultContext");
  p6->addContext("TestNonDefaultContext");
  fDigiParNames->Add(new TObjString(p6->GetName()));
  containers->Add(p6);
}

FairParSet* PndLmdContFact::createContainer(FairContainer* c) {
  /** Calls the constructor of the corresponding parameter container.
   * For an actual context, which is not an empty string and not the default context
   * of this container, the name is concatinated with the context. */
  const char* name=c->GetName();
  FairParSet* p=NULL;
//  if (strcmp(name,"PndMvdGeoPar")==0) {
//    p=new PndMvdGeoPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
//  }

  if (strcmp(name,"KOAPixelDigiPar")==0) {
	p=new PndSdsPixelDigiPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }

  if (strcmp(name,"LMDAlignPar")==0) {
    p=new PndLmdAlignPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }
 if (strcmp(name,"LMDPixelDigiPar")==0) {
	p=new PndSdsPixelDigiPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
  }
  return p;
}

