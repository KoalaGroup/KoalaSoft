/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "TClonesArray.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "KoaRecDigi.h"
#include "KoaRecNoiseFilter.h"

// ---- Default constructor -------------------------------------------
KoaRecNoiseFilter::KoaRecNoiseFilter()
    :FairTask("KoaRecNoiseFilter")
{
  LOG(debug) << "Defaul Constructor of KoaRecNoiseFilter";
}

// ---- Destructor ----------------------------------------------------
KoaRecNoiseFilter::~KoaRecNoiseFilter()
{
  LOG(debug) << "Destructor of KoaRecNoiseFilter";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecNoiseFilter::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecNoiseFilter";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecNoiseFilter::Init()
{
  LOG(debug) << "Initilization of KoaRecNoiseFilter";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  if (fInputName.empty()) LOG(fatal) << "No input branch name set";
  fInputDigis = static_cast<TClonesArray*>(ioman->GetObject(fInputName.data()));
  if ( ! fInputDigis ) {
    LOG(error) << "No input branch " << fInputName;
    return kERROR;
  }

  // Create the TClonesArray for the output data and register it in the IO manager
  if (fOutputName.empty()) LOG(fatal) << "No output branch name set";
  fOutputDigis = new TClonesArray("KoaRecDigi", 200);
  ioman->Register(fOutputName.data(),"KoaRec",fOutputDigis,fSaveOutput);

  // Do whatever else is needed at the initilization stage
  if (fPedestalFileName.empty()) LOG(fatal) << "No pedestal parameters found";
  auto params = readParameterList<double>(fPedestalFileName);

  auto it = findValueContainer(params, "Mean");
  if ( it == params.end()) {
    LOG(error) << "No \'Mean\' parameter found in the pedestal file";
    return kERROR;
  }
  auto& means = it->second;

  it = findValueContainer(params, "Sigma");
  if ( it == params.end()) {
    LOG(error) << "No \'Sigma\' parameter found in the pedestal file";
    return kERROR;
  }
  auto& sigmas = it->second;

  //
  // auto& outthresh = addValueContainer(params,"Threshold");
  for(const auto& mean: means) {
    auto& id = mean.first;
    auto& mean_value = mean.second;
    auto& sigma_value = sigmas[id];
    fPedThresh.emplace(id, mean_value + fThresh*sigma_value);
    // outthresh.emplace(id, mean_value + fThresh*sigma_value);
  }

  // test
  // LOG(info) << "check threshold";
  // printValueContainer(fPedThresh,"Thresholds:");
  // printValueList(params,"test.txt");

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecNoiseFilter::ReInit()
{
  LOG(debug) << "Initilization of KoaRecNoiseFilter";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecNoiseFilter::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecNoiseFilter";

  Reset();

  // filter out noise digis
  Int_t couter=0;
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge();

    if ( charge > fPedThresh[id] ) {
      KoaRecDigi* outDigi = new ((*fOutputDigis)[couter++]) KoaRecDigi();
      outDigi->SetDetectorID(id);
      outDigi->SetTimeStamp(curDigi->GetTimeStamp());
      outDigi->SetCharge(charge);
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecNoiseFilter::Finish()
{
  LOG(debug) << "Finish of KoaRecNoiseFilter";

}

// ---- Reset --------------------------------------------------------
void KoaRecNoiseFilter::Reset()
{
  LOG(debug) << "Reset of KoaRecNoiseFilter";

  fOutputDigis->Clear();
}

ClassImp(KoaRecNoiseFilter)
