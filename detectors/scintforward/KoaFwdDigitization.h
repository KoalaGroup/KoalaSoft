/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAFWDDIGITIZATION_H
#define KOAFWDDIGITIZATION_H

#include "FairTask.h"
#include "TRandom3.h"
#include <map>

class TClonesArray;
class KoaMapEncoder;
class KoaFwdPoint;
class KoaFwdDigitizationPar;

struct KoaFwdStrip{
  Double_t fTimestamp;
  Double_t fCharge;
};

using KoaFwdStrips = std::map<Int_t, KoaFwdStrip>;

class KoaFwdDigitization : public FairTask
{
  public:

    /** Default constructor **/
    KoaFwdDigitization();

    /** Constructor with parameters (Optional) **/
    //  KoaFwdDigitization(Int_t verbose);


    /** Destructor **/
    ~KoaFwdDigitization();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();


    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 private:
    void FillFiredStrip(KoaFwdPoint* McPoint);
    void SmearDigis();
    void AddDigis();

  private:
    /** MapEncoder **/
    KoaMapEncoder* fMapEncoder;

    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    /** Output array to  new data level**/
    TClonesArray* fDigis;
    KoaFwdStrips  fFiredStrips;

    /** parameters used for time & energy smearing **/
  TRandom3 fRndEngine;
    KoaFwdDigitizationPar* fDigitizationPar;
    Double_t fTimeSigma;
    Double_t fEnergySigma;
    Double_t fEnergyNoise;
    Double_t fEnergyNoiseSigma;

    KoaFwdDigitization(const KoaFwdDigitization&);
    KoaFwdDigitization operator=(const KoaFwdDigitization&);

    ClassDef(KoaFwdDigitization,1);
};

#endif
