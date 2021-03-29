/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecNoisePar.h"

#include "FairParamList.h"

ClassImp(KoaRecNoisePar)

KoaRecNoisePar ::KoaRecNoisePar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fMean(0),
    fSigma(0)
{
}

KoaRecNoisePar::~KoaRecNoisePar(void)
{
}

void KoaRecNoisePar::clear(void)
{
}

void KoaRecNoisePar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("Mean", fMean);
  l->add("Sigma", fSigma);
}

Bool_t KoaRecNoisePar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("Mean", &fMean) ) { return kFALSE; }
  if ( ! l->fill("Sigma", &fSigma) ) { return kFALSE; }

  return kTRUE;
}
