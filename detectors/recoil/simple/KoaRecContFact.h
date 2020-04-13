/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECCONTFACT_H
#define KOARECCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class KoaRecContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    KoaRecContFact();
    ~KoaRecContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( KoaRecContFact,1) // Factory for all KoaRec parameter containers
};

#endif
