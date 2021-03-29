/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_TRANSFORMTOARRAY_H
#define KOA_TRANSFORMTOARRAY_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class TFile;
class TTree;

class KoaTransformToArray : public FairTask
{
  public:

    /** Default constructor **/
    KoaTransformToArray();

    /** Destructor **/
    ~KoaTransformToArray();


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
  void SetInputName(const char* name) {
    fInputName = name;
  }
  void SetOutputName(const char* name) {
    fOutputName = name;
  }
  void SetOutputFileName(const char* name) {
    fOutputFile = TFile::Open(name,"update");
  }

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;

  TFile*    fOutputFile;
  TTree*    fTree;
  Double_t     fSi1[48];
  Double_t     fSi2[64];
  Double_t     fGe1[32];
  Double_t     fGe2[32];

    KoaTransformToArray(const KoaTransformToArray&);
    KoaTransformToArray operator=(const KoaTransformToArray&);

    ClassDef(KoaTransformToArray,1);
};

#endif
