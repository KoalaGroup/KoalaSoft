/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAANASOLIDANGLE_H
#define KOAANASOLIDANGLE_H

#include "FairTask.h"
#include <fstream>

class TClonesArray;

class KoaAnaSolidAngle : public FairTask
{
  public:

    /** Default constructor **/
    KoaAnaSolidAngle();

    /** Constructor with parameters (Optional) **/
    //  KoaAnaSolidAngle(Int_t verbose);


    /** Destructor **/
    ~KoaAnaSolidAngle();


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

 public:
    void SetOutFileName(const char* filename);

 private:
    KoaAnaSolidAngle(const KoaAnaSolidAngle&);
    KoaAnaSolidAngle operator=(const KoaAnaSolidAngle&);

    void Write();

 private:
    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;

    Long_t fSi1NrHit[48];
    Long_t fSi2NrHit[64];
    Long_t fGe1NrHit[32];
    Long_t fGe2NrHit[32];
    Long_t fMCEntryNo;

    TString fFileName;
    std::ofstream fOutputFile;

    ClassDef(KoaAnaSolidAngle,1);
};

#endif
