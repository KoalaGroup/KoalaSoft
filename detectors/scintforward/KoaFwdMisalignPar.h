/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWD_MISALIGNPAR_H
#define KOAFWD_MISALIGNPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaFwdMisalignPar : public FairParGenericSet
{
  public:

    KoaFwdMisalignPar(const char* name="KoaFwdMisalignPar",
                                const char* title="Missalignment parameter for Koala Fwd Detector Module",
                                const char* context="TestDefaultContext");
    ~KoaFwdMisalignPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Int_t GetNrOfSensors() {return fNrOfSensors;}
    TArrayD GetSensorShiftX() {return fSensorShiftX;}
    TArrayD GetSensorShiftY() {return fSensorShiftY;}
    TArrayD GetSensorShiftZ() {return fSensorShiftZ;}
    TArrayD GetSensorRotPhi() {return fSensorRotPhi;}
    TArrayD GetSensorRotTheta() {return fSensorRotTheta;}
    TArrayD GetSensorRotPsi() {return fSensorRotPsi;}

  private:
    // Individual Sensor's misalignment
    Int_t fNrOfSensors;
    TArrayD fSensorShiftX; // Array to hold the misalignment in x-direction
    TArrayD fSensorShiftY; // Array to hold the misalignment in y-direction
    TArrayD fSensorShiftZ; // Array to hold the misalignment in z-direction
    TArrayD fSensorRotPhi; // Array to hold the rotation in x-direction
    TArrayD fSensorRotTheta; // Array to hold the rotation in y-direction
    TArrayD fSensorRotPsi; // Array to hold the rotation in z-direction

    KoaFwdMisalignPar(const KoaFwdMisalignPar&);
    KoaFwdMisalignPar& operator=(const KoaFwdMisalignPar&);

    ClassDef(KoaFwdMisalignPar,1)
};

#endif
