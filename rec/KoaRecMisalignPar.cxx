/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecMisalignPar.h"

#include "FairParamList.h"

ClassImp(KoaRecMisalignPar)

KoaRecMisalignPar ::KoaRecMisalignPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name,title,context),
    fSensorShiftX(),
    fSensorShiftY(),
    fSensorShiftZ(),
    fSensorRotPhi(),
    fSensorRotTheta(),
    fSensorRotPsi(),
    fNrOfSensors(0)
{
}

KoaRecMisalignPar::~KoaRecMisalignPar(void)
{
}

void KoaRecMisalignPar::clear(void)
{
}

void KoaRecMisalignPar::putParams(FairParamList* l)
{
  if (!l) { return; }

  l->add("NrOfSensors", fNrOfSensors);
  l->add("SensorShiftX", fSensorShiftX);
  l->add("SensorShiftY", fSensorShiftY);
  l->add("SensorShiftZ", fSensorShiftZ);
  l->add("SensorRotationPhi", fSensorRotPhi);
  l->add("SensorRotationTheta", fSensorRotTheta);
  l->add("SensorRotationPsi", fSensorRotPsi);

}

Bool_t KoaRecMisalignPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }

  if ( ! l->fill("NrOfSensors", &fNrOfSensors) ) { return kFALSE; }

  fSensorShiftX.Set(fNrOfSensors);
  if ( ! l->fill("SensorShiftX", &fSensorShiftX )) { return kFALSE; }

  fSensorShiftY.Set(fNrOfSensors);
  if ( ! l->fill("SensorShiftY", &fSensorShiftY )) { return kFALSE; }

  fSensorShiftZ.Set(fNrOfSensors);
  if ( ! l->fill("SensorShiftZ", &fSensorShiftZ )) { return kFALSE; }

  fSensorRotPhi.Set(fNrOfSensors);
  if ( ! l->fill("SensorRotationPhi", &fSensorRotPhi )) { return kFALSE; }

  fSensorRotTheta.Set(fNrOfSensors);
  if ( ! l->fill("SensorRotationTheta", &fSensorRotTheta )) { return kFALSE; }

  fSensorRotPsi.Set(fNrOfSensors);
  if ( ! l->fill("SensorRotationPsi", &fSensorRotPsi )) { return kFALSE; }

  return kTRUE;
}
