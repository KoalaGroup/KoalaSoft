/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "TClonesArray.h"
#include "KoaRawEvent.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "KoaRecDigi.h"
#include "KoaFwdDigi.h"
#include "KoaAnaTrigger.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaAnaTrigger::KoaAnaTrigger()
    :FairTask("KoaAnaTrigger")
{
  LOG(debug) << "Defaul Constructor of KoaAnaTrigger";

  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaAnaTrigger::~KoaAnaTrigger()
{
  delete fTimestamp;
  delete fTriggerIDs, fTriggerCounts;

  LOG(debug) << "Destructor of KoaAnaTrigger";
}

// ----  Initialisation  ----------------------------------------------
void KoaAnaTrigger::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaAnaTrigger";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaAnaTrigger::Init()
{
  LOG(debug) << "Initilization of KoaAnaTrigger";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  fRawEvent = ioman->InitObjectAs<const KoaRawEvent*>("KoaRawEvent");
  if ( ! fRawEvent ) {
    LOG(error) << "No input branch KoaRawEvent";
    return kERROR;
  }

  fRecDigis = static_cast<TClonesArray*>(ioman->GetObject("KoaRecDigi"));
  if ( ! fRecDigis ) {
    LOG(error) << "No input branch KoaRecDigi";
    return kERROR;
  }

  fRearDigis = static_cast<TClonesArray*>(ioman->GetObject("KoaRecRearDigi"));
  if ( ! fRearDigis ) {
    LOG(error) << "No input branch KoaRecRearDigi";
    return kERROR;
  }

  fFwdDigis = static_cast<TClonesArray*>(ioman->GetObject("KoaFwdDigi"));
  if ( ! fFwdDigis ) {
    LOG(error) << "No input branch KoaFwdDigi";
    return kERROR;
  }

  // Register the the output data in the IO manager
  fTriggerIDs = new std::vector<Int_t>();
  ioman->RegisterAny("TriggerID", fTriggerIDs, kTRUE);
  fTriggerCounts = new std::map<Int_t, Long_t>();
  ioman->RegisterAny("TriggerCount", fTriggerCounts, kTRUE);

  fTimestamp = new TimeStruct();
  ioman->RegisterAny("Timestamp", fTimestamp, kTRUE);

  // Read in parameters from threshold file in the file exists
  if(!fThreshFile.empty()){
    LOG(info) << "Threshold setting from " << fThreshFile;

    auto thresh_params = readParameterList<double>(fThreshFile);
    auto it = findValueContainer(thresh_params, "Threshold");
    if ( it == thresh_params.end()) {
      LOG(error) << "No \'Threshold\' parameter found in the threshold parameter file";
      return kERROR;
    }
    fThreshold = it->second;
  }
  else{
    LOG(fatal) << "Threshold file not set";
  }

  //
  auto rec_ids = fEncoder->GetRecChIDs();
  for(auto id: rec_ids) {
    fTriggerCounts->emplace(id, 0);
  }

  auto rear_ids = fEncoder->GetRecRearChIDs();
  for(auto id: rear_ids) {
    fTriggerCounts->emplace(id, 0);
  }

  auto fwd_ids = fEncoder->GetFwdChIDs();
  for(auto id: fwd_ids) {
    fTriggerCounts->emplace(id, 0);
  }

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaAnaTrigger::ReInit()
{
  LOG(debug) << "Initilization of KoaAnaTrigger";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaAnaTrigger::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaAnaTrigger";

  Reset();

  fTimestamp->Second = fRawEvent->Second;
  fTimestamp->Usecond = fRawEvent->Usecond;

  // 
  Int_t rec_nr = fRecDigis->GetEntriesFast();
  for ( int index=0; index<rec_nr; ++index) {
    KoaRecDigi* theDigi = static_cast<KoaRecDigi*>(fRecDigis->At(index));
    auto id = theDigi->GetDetID();
    auto charge = theDigi->GetCharge();
    if(charge > fThreshold[id]){
      fTriggerIDs->emplace_back(id);
      ( *fTriggerCounts )[id]++;
    }
  }

  // 
  Int_t rear_nr = fRearDigis->GetEntriesFast();
  for ( int index=0; index<rear_nr; ++index) {
    KoaRecDigi* theDigi = static_cast<KoaRecDigi*>(fRearDigis->At(index));
    auto id = theDigi->GetDetID();
    auto charge = theDigi->GetCharge();
    if(charge > fThreshold[id]){
      fTriggerIDs->emplace_back(id);
      ( *fTriggerCounts )[id]++;
    }
  }

  //
  Int_t fwd_nr = fFwdDigis->GetEntriesFast();
  for ( int index=0; index<fwd_nr; ++index) {
    KoaFwdDigi* theDigi = static_cast<KoaFwdDigi*>(fFwdDigis->At(index));
    auto id = theDigi->GetDetID();

    auto search = fThreshold.find(id);
    if(search == fThreshold.end()) continue;

    auto charge = theDigi->GetCharge();
    if(charge > fThreshold[id]){
      fTriggerIDs->emplace_back(id);
      ( *fTriggerCounts )[id]++;
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaAnaTrigger::Finish()
{
  LOG(debug) << "Finish of KoaAnaTrigger";
}

// ---- Reset --------------------------------------------------------
void KoaAnaTrigger::Reset()
{
  LOG(debug) << "Reset of KoaAnaTrigger";

  fTriggerIDs->clear();
}

ClassImp(KoaAnaTrigger)
