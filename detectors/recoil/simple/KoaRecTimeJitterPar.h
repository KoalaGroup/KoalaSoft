/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_TIMEJITTERPAR_H
#define KOA_REC_TIMEJITTERPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecTimeJitterPar : public FairParGenericSet
{
  public:

    KoaRecTimeJitterPar(const char* name="KoaRecTimeJitterPar",
                        const char* title="Time-jitter parameters for recoil detector",
                        const char* context="TestDefaultContext");
    ~KoaRecTimeJitterPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetSigma() {return fSigma;}

  void  printParams() {
    LOG(info) << "Sigma: " << fSigma;
  }

  private:
    Double_t fSigma; // Jitter sigma, in ns

    KoaRecTimeJitterPar(const KoaRecTimeJitterPar&);
    KoaRecTimeJitterPar& operator=(const KoaRecTimeJitterPar&);

    ClassDef(KoaRecTimeJitterPar,1)
};

#endif
