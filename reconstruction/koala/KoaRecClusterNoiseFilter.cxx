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
#include "KoaRecClusterNoiseFilter.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterNoiseFilter::KoaRecClusterNoiseFilter()
    :FairTask("KoaRecClusterNoiseFilter")
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterNoiseFilter";

  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterNoiseFilter::~KoaRecClusterNoiseFilter()
{
  LOG(debug) << "Destructor of KoaRecClusterNoiseFilter";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
  if ( fClusters ) {
    fClusters->Delete();
    delete fClusters;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterNoiseFilter::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterNoiseFilter";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterNoiseFilter::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterNoiseFilter";

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
  fOutputDigis = new TClonesArray("KoaRecDigi", 160);
  ioman->Register(fOutputName.data(),"KoaRec",fOutputDigis,fSaveOutput);

  fClusters = new TClonesArray("KoaRecCluster", 32);

  // read pedestal parameters
  if (fPedestalFileName.empty()) LOG(fatal) << "No pedestal parameters found";
  auto params = readParameterList<double>(fPedestalFileName);

  auto it = findValueContainer(params, "Mean");
  if ( it == params.end()) {
    LOG(error) << "No \'Mean\' parameter found in the pedestal file";
    return kERROR;
  }
  fNoiseMeans = it->second;

  it = findValueContainer(params, "Sigma");
  if ( it == params.end()) {
    LOG(error) << "No \'Sigma\' parameter found in the pedestal file";
    return kERROR;
  }
  auto& sigmas = it->second;

  // compute noise sigmas
  for(auto item: sigmas) {
    auto id = item.first;
    auto sigma = item.second;
    fNoiseSigmas.emplace(id, sigma*sigma);
  }

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterNoiseFilter::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterNoiseFilter";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterNoiseFilter::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterNoiseFilter";

  Reset();

  // collect adjacent strips into a cluster
  Int_t det_id, ch_id, id;
  Int_t couter=0;
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  KoaRecCluster* curCluster = nullptr;
  if ( fNrDigits > 0 ) {
    auto* theDigi = static_cast<KoaRecDigi*>(fInputDigis->At(0));
    ch_id = fEncoder->DecodeChannelID(theDigi->GetDetID(), det_id);
    curCluster = new ((*fClusters)[couter++]) KoaRecCluster(det_id);
    curCluster->AddDigi(theDigi);

    for ( int index=1; index<fNrDigits; ++index) {
      theDigi = static_cast<KoaRecDigi*>(fInputDigis->At(index));
      if( !curCluster->isInCluster(theDigi) ) {
        ch_id = fEncoder->DecodeChannelID(theDigi->GetDetID(), det_id);
        curCluster = new ((*fClusters)[couter++]) KoaRecCluster(det_id);
      }
      curCluster->AddDigi(theDigi);
    }
  }

  // filter out clusters without seed and fill in the output digis collection
  couter = 0;
  Int_t fNrClusters = fClusters->GetEntriesFast();
  for(Int_t iNrCluster =0; iNrCluster<fNrClusters; iNrCluster++){
    curCluster = (KoaRecCluster*)fClusters->At(iNrCluster);

    fNrDigits = curCluster->NumberOfDigis();
    auto id_ptr = curCluster->GetIds();
    auto energy_ptr = curCluster->GetEnergies();
    auto timestamp_ptr = curCluster->GetTimestamps();


    // check whether there is digi above threshold
    bool isValid = false;
    double noise_mean = 0;
    double noise_sigma = 0;
    for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++) {
      noise_mean += fNoiseMeans[id_ptr[iNrDigi]];
      noise_sigma += fNoiseSigmas[id_ptr[iNrDigi]];
    }
    noise_sigma = noise_mean + fThresh*TMath::Sqrt(noise_sigma);

    auto cluster_e = curCluster->EnergyTotal();
    if(cluster_e > noise_sigma)
      isValid = true;

    // fill output array
    if (isValid) {
      for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++) {
        auto digi = new ((*fOutputDigis)[couter++]) KoaRecDigi();
        digi->SetDetectorID(id_ptr[iNrDigi]);
        digi->SetCharge(energy_ptr[iNrDigi]);
        digi->SetTimeStamp(timestamp_ptr[iNrDigi]);
      }
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecClusterNoiseFilter::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterNoiseFilter";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterNoiseFilter::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterNoiseFilter";

  fOutputDigis->Clear();
  fClusters->Clear();
}

ClassImp(KoaRecClusterNoiseFilter)
