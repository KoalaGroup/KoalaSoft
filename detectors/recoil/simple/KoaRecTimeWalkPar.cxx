/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecTimeWalkPar.h"

#include "FairParamList.h"

ClassImp(KoaRecTimeWalkPar)

KoaRecTimeWalkPar ::KoaRecTimeWalkPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fThreshold(0),
    fWidth(0)
{
}

KoaRecTimeWalkPar::~KoaRecTimeWalkPar(void)
{
}

void KoaRecTimeWalkPar::clear(void)
{
}

void KoaRecTimeWalkPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("Threshold", fThreshold);
  l->add("Width", fWidth);
}

Bool_t KoaRecTimeWalkPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("Threshold", &fThreshold) ) { return kFALSE; }
  if ( ! l->fill("Width", &fWidth) ) { return kFALSE; }

  return kTRUE;
}
