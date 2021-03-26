/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWD_DIGITIZATIONPAR_H
#define KOAFWD_DIGITIZATIONPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaFwdDigitizationPar : public FairParGenericSet
{
  public:

    KoaFwdDigitizationPar(const char* name="KoaFwdDigitizationPar",
                                const char* title="Fwd Digitization Parameters",
                                const char* context="TestDefaultContext");
    ~KoaFwdDigitizationPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetTimeSigma() {return fTimeSigma;}
    Double_t GetEnergySigma() {return fEnergySigma;}
    Double_t GetEnergyNoise() {return fEnergyNoise;}
    Double_t GetEnergyNoiseSigma() {return fEnergyNoiseSigma;}

  private:
  Double_t fTimeSigma; // in ns
  Double_t fEnergySigma; // in keV
  Double_t fEnergyNoise; //in keV
  Double_t fEnergyNoiseSigma; // in keV

    KoaFwdDigitizationPar(const KoaFwdDigitizationPar&);
    KoaFwdDigitizationPar& operator=(const KoaFwdDigitizationPar&);

    ClassDef(KoaFwdDigitizationPar,1)
};

#endif
