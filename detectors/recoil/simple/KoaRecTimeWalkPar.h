/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_TIMEWALKPAR_H
#define KOA_REC_TIMEWALKPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairLogger.h"

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class KoaRecTimeWalkPar : public FairParGenericSet
{
  public:

    KoaRecTimeWalkPar(const char* name="KoaRecTimeWalkPar",
                                const char* title="Time-walk parameters for recoil detector",
                                const char* context="TestDefaultContext");
    ~KoaRecTimeWalkPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    Double_t GetThreshold() {return fThreshold;}
    Double_t GetWidth() {return fWidth;}

  void  printParams() {
    LOG(info) << "Threshold: " << fThreshold << ", Half-Width: " << fWidth;
  }

  private:
    Double_t fThreshold; // Threshold for LED, in keV
    Double_t fWidth; // Half-width of Shaper output, in ns

    KoaRecTimeWalkPar(const KoaRecTimeWalkPar&);
    KoaRecTimeWalkPar& operator=(const KoaRecTimeWalkPar&);

    ClassDef(KoaRecTimeWalkPar,1)
};

#endif
