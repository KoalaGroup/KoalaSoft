/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ChargeCollectionPar_H
#define KOA_REC_ChargeCollectionPar_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"
#include "Rtypes.h"                     // for ClassDef
#include "TArrayD.h"                    // for TArrayD
#include "KoaMapEncoder.h"

class FairParamList;

class KoaRecChargeCollectionPar : public FairParGenericSet
{
  public:

    KoaRecChargeCollectionPar(const char* name="KoaRecChargeCollectionPar",
                              const char* title="Charge collection parameters for KOALA recoil detector digitization",
                              const char* context="TestDefaultContext");
    ~KoaRecChargeCollectionPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetEfficiency() {return fEfficiency;}
    TArrayD GetDispersion() {return fDispersion;}

  void  printParams() {
    LOG(info) << "Charge Collection parameters : ";

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    Int_t low, high;
    encoder->GetRecDetIDRange(low,high);
    for(int detId=low;detId <= high;detId++){
      LOG(info) << encoder->DetectorIDToVolName(detId) << ": " << fEfficiency[detId-low] << ", " << fDispersion[detId-low] << "keV";
    }
  }

  private:
    TArrayD fEfficiency; // Array to the efficiency of each sensor
    TArrayD fDispersion; // Array to hold the dispersion sigma of each sensor

    KoaRecChargeCollectionPar(const KoaRecChargeCollectionPar&);
    KoaRecChargeCollectionPar& operator=(const KoaRecChargeCollectionPar&);

    ClassDef(KoaRecChargeCollectionPar,1)
};

#endif
