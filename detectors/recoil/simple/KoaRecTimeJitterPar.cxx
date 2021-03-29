/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecTimeJitterPar.h"

#include "FairParamList.h"

ClassImp(KoaRecTimeJitterPar)

KoaRecTimeJitterPar ::KoaRecTimeJitterPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fSigma(0)
{
}

KoaRecTimeJitterPar::~KoaRecTimeJitterPar(void)
{
}

void KoaRecTimeJitterPar::clear(void)
{
}

void KoaRecTimeJitterPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("Sigma", fSigma);
}

Bool_t KoaRecTimeJitterPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("Sigma", &fSigma) ) { return kFALSE; }

  return kTRUE;
}
