/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOARECDIGITIZATIONIDEAL_H
#define KOARECDIGITIZATIONIDEAL_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaGeoHandler;
class KoaRecPoint;

class KoaRecDigitizationIdeal : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecDigitizationIdeal();

    /** Constructor with parameters (Optional) **/
    //  KoaRecDigitizationIdeal(Int_t verbose);


    /** Destructor **/
    ~KoaRecDigitizationIdeal();


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

 public:
  struct KoaRecStrip{
    Double_t fTimestamp;
    Double_t fCharge;
  };
  using KoaRecStrips = std::map<Int_t, KoaRecStrip>;

 private:
    void FillFiredStrips(KoaRecPoint* McPoint);
    void FillFiredStrip(Int_t DetID, Double_t Timestamp, Double_t Charge);

    void AddDigis();

  private:
    /** Geometry Handler **/
    KoaGeoHandler* fGeoHandler;

    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    /** Output array to  new data level**/
    TClonesArray* fDigis;

    KoaRecStrips fFiredStrips;

    KoaRecDigitizationIdeal(const KoaRecDigitizationIdeal&);
    KoaRecDigitizationIdeal operator=(const KoaRecDigitizationIdeal&);

    ClassDef(KoaRecDigitizationIdeal,1);
};

#endif
