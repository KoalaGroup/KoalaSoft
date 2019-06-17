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
#include <map>

class TClonesArray;
class KoaGeoHandler;

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

    void SetMCEntryNo(Long_t entryNo);

 public:
    void SetOutFileName(const char* filename);

 private:
    KoaAnaSolidAngle(const KoaAnaSolidAngle&);
    KoaAnaSolidAngle operator=(const KoaAnaSolidAngle&);

    void Write();

 private:
    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;
    KoaGeoHandler* fGeoHandler;

    Long_t fSi1NrHit[48];
    Long_t fSi2NrHit[64];
    Long_t fGe1NrHit[32];
    Long_t fGe2NrHit[32];
    std::map<Int_t,Long_t> fNrHit;
    Bool_t fMCEntryFromExternal;
    Long_t fMCEntryNo;
    Long_t fNrPoints;

    TString fFileName;
    std::ofstream fOutputFile;

    ClassDef(KoaAnaSolidAngle,1);
};

#endif
