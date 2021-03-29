/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "TClonesArray.h"
#include "TMath.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "KoaRecDigi.h"
#include "KoaRecCluster.h"
#include "KoaRecClusterSizeFilter.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterSizeFilter::KoaRecClusterSizeFilter()
    :FairTask("KoaRecClusterSizeFilter")
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterSizeFilter";
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterSizeFilter::~KoaRecClusterSizeFilter()
{
  LOG(debug) << "Destructor of KoaRecClusterSizeFilter";

  if ( fOutputClusters ) {
    fOutputClusters->Delete();
    delete fOutputClusters;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterSizeFilter::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterSizeFilter";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterSizeFilter::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterSizeFilter";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  if (fInputName.empty()) LOG(fatal) << "No input branch name set";
  fInputClusters = static_cast<TClonesArray*>(ioman->GetObject(fInputName.data()));
  if ( ! fInputClusters ) {
    LOG(error) << "No input branch " << fInputName;
    return kERROR;
  }

  // Create the TClonesArray for the output data and register it in the IO manager
  if (fOutputName.empty()) LOG(fatal) << "No output branch name set";
  fOutputClusters = new TClonesArray("KoaRecCluster", 32);
  ioman->Register(fOutputName.data(),"KoaRec",fOutputClusters,fSaveOutput);

  // read size parameter file
  if (!fSizeParaFile.empty()) {
    auto params = readParameterList<int>(fSizeParaFile);
    auto it = findValueContainer(params, "Size");
    if ( it == params.end()) {
      LOG(error) << "No \'Size\' parameter found in the cluster size file";
      return kERROR;
    }
    fSizeThresholds = it->second;
  }
  else{
    auto encoder = KoaMapEncoder::Instance();
    auto ids = encoder->GetRecChIDs();
    for(auto& id : ids) {
      fSizeThresholds.emplace(id, fThresh);
    }
  }

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterSizeFilter::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterSizeFilter";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterSizeFilter::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterSizeFilter";

  Reset();

  // collect adjacent strips into a cluster
  Int_t index=0;
  Int_t fNrClusters = fInputClusters->GetEntriesFast();
  for(Int_t iNrCluster =0; iNrCluster<fNrClusters; iNrCluster++){
    auto curCluster = (KoaRecCluster*)fInputClusters->At(iNrCluster);

    auto fNrDigits = curCluster->NumberOfDigis();
    auto id = curCluster->GetFirstChId();

    if (fNrDigits > fSizeThresholds[id]) {
      continue;
    }

    // fill in output array
    auto det_id = curCluster->GetDetId();
    auto id_ptr = curCluster->GetIds();
    auto energy_ptr = curCluster->GetEnergies();
    auto timestamp_ptr = curCluster->GetTimestamps();

    auto out_cluster = new ((*fOutputClusters)[index++]) KoaRecCluster(det_id);
    for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++){
      auto digi = new KoaRecDigi();
      digi->SetDetectorID(id_ptr[iNrDigi]);
      digi->SetCharge(energy_ptr[iNrDigi]);
      digi->SetTimeStamp(timestamp_ptr[iNrDigi]);

      out_cluster->AddDigi(digi);
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecClusterSizeFilter::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterSizeFilter";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterSizeFilter::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterSizeFilter";

  fOutputClusters->Clear();
}

ClassImp(KoaRecClusterSizeFilter)
