/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecFanoPar.h"
#include "FairParamList.h"

ClassImp(KoaRecFanoPar)

KoaRecFanoPar ::KoaRecFanoPar(const char* name,
                              const char* title,
                              const char* context)
: FairParGenericSet(name,title,context),
  fFanoFactors(4)
{
  for(int i=0;i<4;i++){
    fFanoFactors[i] = 1;
  }
}

KoaRecFanoPar::~KoaRecFanoPar(void)
{
}

void KoaRecFanoPar::clear(void)
{
}

void KoaRecFanoPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("FanoFactors", fFanoFactors);
}

Bool_t KoaRecFanoPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("FanoFactors", &fFanoFactors) ) { return kFALSE; }

  return kTRUE;
}
