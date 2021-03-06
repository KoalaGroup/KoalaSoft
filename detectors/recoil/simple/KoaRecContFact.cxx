/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecContFact.h"

#include "KoaRecGeoPar.h"
#include "KoaRecMisalignPar.h"
#include "KoaRecNoisePar.h"
#include "KoaRecFanoPar.h"
#include "KoaRecChargeCollectionPar.h"
#include "KoaRecTimeWalkPar.h"
#include "KoaRecTimeJitterPar.h"

#include "FairRuntimeDb.h"

#include <iostream>

ClassImp(KoaRecContFact)

static KoaRecContFact gKoaRecContFact;

KoaRecContFact::KoaRecContFact()
  : FairContFact()
{
  /** Constructor (called when the library is loaded) */
  fName="KoaRecContFact";
  fTitle="Factory for parameter containers in libKoaRec";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void KoaRecContFact::setAllContainers()
{
  /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the KoaRec library.
  */

  FairContainer* p= new FairContainer("KoaRecGeoPar",
                                      "KoaRec Geometry Parameters",
                                      "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);

  //
  FairContainer* p1= new FairContainer("KoaRecMisalignPar",
                                      "KoaRec Geometry Misalignment Matrix Parameters",
                                      "TestDefaultContext");
  p1->addContext("TestNonDefaultContext");

  containers->Add(p1);

  //
  p = new FairContainer("KoaRecNoisePar",
                        "Noise parameter for KOALA recoil detector digitization",
                        "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);

  //
  p = new FairContainer("KoaRecFanoPar",
                        "Fano factor for KOALA recoil detector digitization",
                        "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);

  //
  p = new FairContainer("KoaRecChargeCollectionPar",
                        "Charge collection parameters for KOALA recoil detector digitization",
                        "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);

  //
  p = new FairContainer("KoaRecTimeWalkPar",
                        "Time-walk parameters for recoil detector",
                        "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);

  //
  p = new FairContainer("KoaRecTimeJitterPar",
                        "Time-jitter parameters for recoil detector",
                        "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);
}

FairParSet* KoaRecContFact::createContainer(FairContainer* c)
{
  /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
  const char* name=c->GetName();
  FairParSet* p=NULL;
  if (strcmp(name,"KoaRecGeoPar")==0) {
    p=new KoaRecGeoPar(c->getConcatName().Data(),
                            c->GetTitle(),c->getContext());
  }
  else if(strcmp(name,"KoaRecMisalignPar")==0){
    p=new KoaRecMisalignPar(c->getConcatName().Data(),
                            c->GetTitle(), c->getContext());
  }
  else if(strcmp(name,"KoaRecNoisePar")==0){
    p=new KoaRecNoisePar(c->getConcatName().Data(),
                            c->GetTitle(), c->getContext());
  }
  else if(strcmp(name,"KoaRecFanoPar")==0){
    p=new KoaRecFanoPar(c->getConcatName().Data(),
                         c->GetTitle(), c->getContext());
  }
  else if(strcmp(name,"KoaRecChargeCollectionPar")==0){
    p=new KoaRecChargeCollectionPar(c->getConcatName().Data(),
                                    c->GetTitle(), c->getContext());
  }
  else if(strcmp(name,"KoaRecTimeWalkPar")==0){
    p=new KoaRecTimeWalkPar(c->getConcatName().Data(),
                            c->GetTitle(), c->getContext());
  }
  else if(strcmp(name,"KoaRecTimeJitterPar")==0){
    p=new KoaRecTimeJitterPar(c->getConcatName().Data(),
                              c->GetTitle(), c->getContext());
  }

  return p;
}
