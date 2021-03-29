/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_CHARGEDIVISIONIDEAL_H
#define KOA_REC_CHARGEDIVISIONIDEAL_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaGeoHandler;
class KoaRecPoint;


class KoaRecChargeDivisionIdeal : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecChargeDivisionIdeal();

    /** Constructor with parameters (Optional) **/
    //  KoaRecChargeDivisionIdeal(Int_t verbose);


    /** Destructor **/
    ~KoaRecChargeDivisionIdeal();


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

    KoaRecStrip(): fTimestamp(-1), fCharge(0) {}
    KoaRecStrip(double ts, double charge) : fTimestamp(ts), fCharge(charge) {}
    ~KoaRecStrip() {}
  };

  using KoaRecStrips = std::map<Int_t, KoaRecStrip>;

  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void FillFiredStrips(KoaRecPoint* McPoint);
    void FillFiredStrip(Int_t DetID, Double_t Timestamp, Double_t Charge);

    void AddDigis();

  private:
    /** Geometry Handler **/
    KoaGeoHandler* fGeoHandler;

  // Output digit branch name
  std::string fOutputName;
  // Flag indicate save output branch to file or in memory
  bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    /** Output array to  new data level**/
    TClonesArray* fDigis; // fCharge in keV

    KoaRecStrips fFiredStrips;

    KoaRecChargeDivisionIdeal(const KoaRecChargeDivisionIdeal&);
    KoaRecChargeDivisionIdeal operator=(const KoaRecChargeDivisionIdeal&);

    ClassDef(KoaRecChargeDivisionIdeal,1);
};

#endif
