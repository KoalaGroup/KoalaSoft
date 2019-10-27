/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaFwdDigitizationPar.h"

#include "FairParamList.h"

ClassImp(KoaFwdDigitizationPar)

KoaFwdDigitizationPar ::KoaFwdDigitizationPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
  fTimeSigma(0),
  fEnergySigma(0),
  fEnergyNoise(0),
  fEnergyNoiseSigma(0)
{
}

KoaFwdDigitizationPar::~KoaFwdDigitizationPar(void)
{
}

void KoaFwdDigitizationPar::clear(void)
{
}

void KoaFwdDigitizationPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("TimeSigma", fTimeSigma);
  l->add("EnergySigma", fEnergySigma);
  l->add("EnergyNoise", fEnergyNoise);
  l->add("EnergyNoiseSigma", fEnergyNoiseSigma);

}

Bool_t KoaFwdDigitizationPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("TimeSigma", &fTimeSigma) ) { return kFALSE; }
  if ( ! l->fill("EnergySigma", &fEnergySigma) ) { return kFALSE; }
  if ( ! l->fill("EnergyNoise", &fEnergyNoise) ) { return kFALSE; }
  if ( ! l->fill("EnergyNoiseSigma", &fEnergyNoiseSigma) ) { return kFALSE; }

  return kTRUE;
}
