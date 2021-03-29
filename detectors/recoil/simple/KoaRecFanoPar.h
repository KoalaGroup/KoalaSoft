/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_FANOPAR_H
#define KOA_REC_FANOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"
#include "Rtypes.h"                     // for ClassDef
#include "TArrayD.h"                    // for TArrayD
#include "KoaMapEncoder.h"

class FairParamList;

class KoaRecFanoPar : public FairParGenericSet
{
  public:

    KoaRecFanoPar(const char* name="KoaRecFanoPar",
                  const char* title="Fano factor for KOALA recoil detector digitization",
                  const char* context="TestDefaultContext");
    ~KoaRecFanoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetFanoFactors() {return fFanoFactors;}

  void  printParams() {
    LOG(info) << "Fano factors : ";

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    Int_t low, high;
    encoder->GetRecDetIDRange(low,high);
    for(int detId=low;detId <= high;detId++){
      LOG(info) << encoder->DetectorIDToVolName(detId) << ": " << fFanoFactors[detId-low];
    }
  }

  private:
    TArrayD fFanoFactors; // Array to hold the rotation in z-direction

    KoaRecFanoPar(const KoaRecFanoPar&);
    KoaRecFanoPar& operator=(const KoaRecFanoPar&);

    ClassDef(KoaRecFanoPar,1)
};

#endif
