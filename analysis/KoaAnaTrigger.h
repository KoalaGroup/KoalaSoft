/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_ANATRIGGER_H
#define KOA_ANATRIGGER_H

#include "FairTask.h"
#include "KoaTextUtility.h"
#include <map>
#include <vector>
#include <string>

class TClonesArray;
class KoaRawEvent;
class KoaMapEncoder;

using namespace KoaUtility;

class KoaAnaTrigger : public FairTask
{
 public:

  /** Default constructor **/
  KoaAnaTrigger();

  /** Destructor **/
  ~KoaAnaTrigger();


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
  void SetThresholdFile(const char* name) {
    fThreshFile = name;
  }

 public:
  struct TimeStruct {
    Long_t Second;
    Long_t Usecond;
  };

 private:
  KoaAnaTrigger(const KoaAnaTrigger&);
  KoaAnaTrigger operator=(const KoaAnaTrigger&);

 private:
  KoaMapEncoder *fEncoder;

  const KoaRawEvent *fRawEvent = nullptr;
  TClonesArray* fRecDigis = nullptr;
  TClonesArray* fRearDigis = nullptr;
  TClonesArray* fFwdDigis = nullptr;

  TimeStruct* fTimestamp;
  std::vector<Int_t> *fTriggerIDs;
  std::map<Int_t, Long_t> *fTriggerCounts;

  std::string fThreshFile = "";
  ValueContainer<double> fThreshold;

  ClassDef(KoaAnaTrigger,1);
};

#endif
