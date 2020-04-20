/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_NOISEPAR_H
#define KOA_REC_NOISEPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecNoisePar : public FairParGenericSet
{
  public:

    KoaRecNoisePar(const char* name="KoaRecNoisePar",
                                const char* title="Noise parameter for KOALA recoil detector digitization",
                                const char* context="TestDefaultContext");
    ~KoaRecNoisePar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetMean() {return fMean;}
    Double_t GetSigma() {return fSigma;}
    // TArrayD GetSensorRotPsi() {return fSensorRotPsi;}

  void  printParams() {
    LOG(info) << "Mean: " << fMean << ", Sigma: " << fSigma;
  }

  private:
    Double_t fMean; // Mean of noise, in keV
    Double_t fSigma; // Sigma of noise, in keV
    // TArrayD fSensorRotPsi; // Array to hold the rotation in z-direction

    KoaRecNoisePar(const KoaRecNoisePar&);
    KoaRecNoisePar& operator=(const KoaRecNoisePar&);

    ClassDef(KoaRecNoisePar,1)
};

#endif
