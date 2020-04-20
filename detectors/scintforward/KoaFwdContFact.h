/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDCONTFACT_H
#define KOAFWDCONTFACT_H

#include "FairContFact.h"

class FairContainer;

class KoaFwdContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    KoaFwdContFact();
    ~KoaFwdContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( KoaFwdContFact,1) // Factory for all KoaRec parameter containers
};

#endif
