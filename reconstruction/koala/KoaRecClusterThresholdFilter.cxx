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
#include "KoaRecClusterThresholdFilter.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterThresholdFilter::KoaRecClusterThresholdFilter()
    :FairTask("KoaRecClusterThresholdFilter")
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterThresholdFilter";
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterThresholdFilter::~KoaRecClusterThresholdFilter()
{
  LOG(debug) << "Destructor of KoaRecClusterThresholdFilter";

  if ( fOutputClusters ) {
    fOutputClusters->Delete();
    delete fOutputClusters;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterThresholdFilter::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterThresholdFilter";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterThresholdFilter::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterThresholdFilter";

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

  // read pedestal parameters
  if (fPedestalFileName.empty()) LOG(fatal) << "No pedestal parameters found";
  auto params = readParameterList<double>(fPedestalFileName);

  auto it = findValueContainer(params, "Sigma");
  if ( it == params.end()) {
    LOG(error) << "No \'Sigma\' parameter found in the pedestal file";
    return kERROR;
  }
  auto& sigmas = it->second;

  // read adc calib parameters
  if (fAdcParaFile.empty()) LOG(fatal) << "No ADC parameters found";
  auto adc_params = readParameterList<double>( fAdcParaFile);

  it = findValueContainer(adc_params, "AdcToE_p1");
  if ( it == params.end()) {
    LOG(error) << "No \'AdcToE_p1\' parameter found in the ADC parameter file";
    return kERROR;
  }
  auto& p1s = it->second;

  // compute noise sigmas
  for(auto item: sigmas) {
    auto id = item.first;
    auto sigma = item.second;
    auto p1 = p1s[id];
    fNoiseThresh.emplace(id, p1*p1*sigma*sigma);
  }

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterThresholdFilter::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterThresholdFilter";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterThresholdFilter::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterThresholdFilter";

  Reset();

  // collect adjacent strips into a cluster
  Int_t index=0;
  Int_t fNrClusters = fInputClusters->GetEntriesFast();
  for(Int_t iNrCluster =0; iNrCluster<fNrClusters; iNrCluster++){
    auto curCluster = (KoaRecCluster*)fInputClusters->At(iNrCluster);

    auto det_id = curCluster->GetDetId();
    auto fNrDigits = curCluster->NumberOfDigis();
    auto id_ptr = curCluster->GetIds();
    auto energy_ptr = curCluster->GetEnergies();
    auto timestamp_ptr = curCluster->GetTimestamps();

    // compute threshold
    double threshold = 0;
    for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++){
      threshold += fNoiseThresh[id_ptr[iNrDigi]];
    }
    threshold = fThresh*TMath::Sqrt(threshold);

    // ignore clusters under threshold
    if (curCluster->EnergyTotal() < threshold ) {
      continue;
    }

    // fill in output array
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
void KoaRecClusterThresholdFilter::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterThresholdFilter";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterThresholdFilter::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterThresholdFilter";

  fOutputClusters->Clear();
}

ClassImp(KoaRecClusterThresholdFilter)
