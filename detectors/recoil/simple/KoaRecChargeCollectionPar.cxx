/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecChargeCollectionPar.h"
#include "FairParamList.h"

ClassImp(KoaRecChargeCollectionPar)

KoaRecChargeCollectionPar ::KoaRecChargeCollectionPar(const char* name,
                                                      const char* title,
                                                      const char* context)
: FairParGenericSet(name,title,context),
  fEfficiency(4),
  fDispersion(4)
{
  for(int i=0;i<4;i++){
    fEfficiency[i] = 1;
    fDispersion[i] = 0;
  }
}

KoaRecChargeCollectionPar::~KoaRecChargeCollectionPar(void)
{
}

void KoaRecChargeCollectionPar::clear(void)
{
}

void KoaRecChargeCollectionPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("CollectionEfficiency", fEfficiency);
  l->add("CollectionDispersion", fDispersion);
}

Bool_t KoaRecChargeCollectionPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("CollectionEfficiency", &fEfficiency) ) { return kFALSE; }
  if ( ! l->fill("CollectionDispersion", &fDispersion) ) { return kFALSE; }

  return kTRUE;
}
