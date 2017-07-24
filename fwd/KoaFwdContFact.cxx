/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaFwdContFact.h"

#include "KoaFwdGeoPar.h"

#include "FairRuntimeDb.h"

#include <iostream>

ClassImp(KoaFwdContFact)

static KoaFwdContFact gKoaFwdContFact;

KoaFwdContFact::KoaFwdContFact()
  : FairContFact()
{
  /** Constructor (called when the library is loaded) */
  fName="KoaFwdContFact";
  fTitle="Factory for parameter containers in libKoaFwd";
  setAllContainers();
  FairRuntimeDb::instance()->addContFactory(this);
}

void KoaFwdContFact::setAllContainers()
{
  /** Creates the Container objects with all accepted
      contexts and adds them to
      the list of containers for the KoaFwd library.
  */

  FairContainer* p= new FairContainer("KoaFwdGeoPar",
                                      "KoaFwd Geometry Parameters",
                                      "TestDefaultContext");
  p->addContext("TestNonDefaultContext");

  containers->Add(p);
}

FairParSet* KoaFwdContFact::createContainer(FairContainer* c)
{
  /** Calls the constructor of the corresponding parameter container.
      For an actual context, which is not an empty string and not
      the default context
      of this container, the name is concatinated with the context.
  */
  const char* name=c->GetName();
  FairParSet* p=NULL;
  if (strcmp(name,"KoaFwdGeoPar")==0) {
    p=new KoaFwdGeoPar(c->getConcatName().Data(),
                            c->GetTitle(),c->getContext());
  }
  return p;
}
