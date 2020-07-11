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
#include "KoaRecCluster.h"
#include "KoaRecClusterSeedFilter.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterSeedFilter::KoaRecClusterSeedFilter()
    :FairTask("KoaRecClusterSeedFilter")
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterSeedFilter";

  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterSeedFilter::~KoaRecClusterSeedFilter()
{
  LOG(debug) << "Destructor of KoaRecClusterSeedFilter";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterSeedFilter::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterSeedFilter";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterSeedFilter::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterSeedFilter";

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
  for(const auto& mean: means) {
    auto& id = mean.first;
    auto& mean_value = mean.second;
    auto& sigma_value = sigmas[id];
    fPedThresh.emplace(id, mean_value + fThresh*sigma_value);
  }

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterSeedFilter::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterSeedFilter";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterSeedFilter::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterSeedFilter";

  Reset();

  Int_t det_id, ch_id, id;
  Int_t couter=0;
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  KoaRecCluster* curCluster = nullptr;
  auto clusters = new TClonesArray("KoaRecCluster", 32);

  // collect ajacent strips into a cluster
  if ( fNrDigits > 0 ) {
    auto* theDigi = static_cast<KoaRecDigi*>(fInputDigis->At(0));
    ch_id = fEncoder->DecodeChannelID(theDigi->GetDetID(), det_id);
    curCluster = new ((*clusters)[couter++]) KoaRecCluster(det_id);
    curCluster->AddDigi(theDigi);

    for ( int index=1; index<fNrDigits; ++index) {
      theDigi = static_cast<KoaRecDigi*>(fInputDigis->At(index));
      if( !curCluster->isInCluster(theDigi) ) {
        ch_id = fEncoder->DecodeChannelID(theDigi->GetDetID(), det_id);
        curCluster = new ((*clusters)[couter++]) KoaRecCluster(det_id);
      }
      curCluster->AddDigi(theDigi);
    }
  }

  // filter out clusters without seed and fill in the output digis collection
  Int_t fNrClusters = clusters->GetEntriesFast();
  for(Int_t iNrCluster =0; iNrCluster<fNrClusters; iNrCluster++){
    curCluster = (KoaRecCluster*)clusters->At(iNrCluster);

    fNrDigits = curCluster->NumberOfDigis();
    auto id_ptr = curCluster->GetIds();
    auto energy_ptr = curCluster->GetEnergies();
    auto timestamp_ptr = curCluster->GetTimestamps();


    // check whether there is digi above threshold
    bool isValid = false;
    for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++) {
      if( energy_ptr[iNrDigi] > fPedThresh[id_ptr[iNrDigi]] ) {
        isValid = true;
        break;
      }
    }

    // fill output array
    if (isValid) {
      for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++) {
        auto digi = new ((*fOutputDigis)[iNrDigi]) KoaRecDigi();
        digi->SetDetectorID(id_ptr[iNrDigi]);
        digi->SetCharge(energy_ptr[iNrDigi]);
        digi->SetTimeStamp(timestamp_ptr[iNrDigi]);
      }
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecClusterSeedFilter::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterSeedFilter";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterSeedFilter::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterSeedFilter";

  fOutputDigis->Clear();
}

ClassImp(KoaRecClusterSeedFilter)
