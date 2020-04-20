/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_REC_ADDNOISE_H
#define KOA_REC_ADDNOISE_H

#include "FairTask.h"
#include "TRandom3.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class KoaRecNoisePar;

class KoaRecAddNoise : public FairTask
{
  public:

    /** Default constructor **/
    KoaRecAddNoise();

    /** Destructor **/
    ~KoaRecAddNoise();


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
  void SetInputDigiName(const char* name) {
    fInputName = name;
  }
  void SetOutputDigiName(const char* name) {
    fOutputName = name;
  }
  void SaveOutputDigi(bool flag = true) {
    fSaveOutput = flag;
  }

 private:
    void AddNoise();

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;
    // Flag indicate save output branch to file or in memory
    bool fSaveOutput;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;
    /** Output array to  new data level**/
    TClonesArray* fOutputDigis;

    // Noise parameter
  TRandom3 fRndEngine;
  KoaRecNoisePar* fNoisePar;
  Double_t fNoiseMean;
  Double_t fNoiseSigma;

    KoaRecAddNoise(const KoaRecAddNoise&);
    KoaRecAddNoise operator=(const KoaRecAddNoise&);

    ClassDef(KoaRecAddNoise,1);
};

#endif
