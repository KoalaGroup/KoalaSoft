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
#include "KoaRecClusterPurification.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterPurification::KoaRecClusterPurification()
    :FairTask("KoaRecClusterPurification")
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterPurification";
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterPurification::~KoaRecClusterPurification()
{
  LOG(debug) << "Destructor of KoaRecClusterPurification";

  if ( fOutputClusters ) {
    fOutputClusters->Delete();
    delete fOutputClusters;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterPurification::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterPurification";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterPurification::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterPurification";

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

  // initialize pedestal noise parameters

  // 1. read ADC calibration paramters
  if (fAdcParaFile.empty()) LOG(fatal) << "No ADC parameters found";
  auto adc_params = readParameterList<double>( fAdcParaFile);

  auto it = findValueContainer(adc_params, "AdcToE_p0");
  if ( it == adc_params.end()) {
    LOG(error) << "No \'AdcToE_p0\' parameter found in the ADC parameter file";
    return kERROR;
  }
  auto fP0 = it->second;

  it = findValueContainer(adc_params, "AdcToE_p1");
  if ( it == adc_params.end()) {
    LOG(error) << "No \'AdcToE_p1\' parameter found in the ADC parameter file";
    return kERROR;
  }
  auto fP1 = it->second;

  // 2. read pedestal parameters in ADC counts
  if (fPedestalFileName.empty()) LOG(fatal) << "No Pedestal noises paramters found";
  auto noise_params = readParameterList<double>(fPedestalFileName);
  it = findValueContainer(noise_params, "Mean");
  if ( it == noise_params.end()) {
    LOG(error) << "No \'Mean\' parameter found in the pedestal file";
    return kERROR;
  }
  auto fNoiseMeans = it->second;

  it = findValueContainer(noise_params, "Sigma");
  if ( it == noise_params.end()) {
    LOG(error) << "No \'Sigma\' parameter found in the pedestal file";
    return kERROR;
  }
  auto fNoiseSigmas = it->second;

  // 3. convert noise paramters from ADC value to Energy (keV)
  for(auto& item: fNoiseMeans) {
    auto& id = item.first;
    auto& mean = item.second;
    auto sigma = fNoiseSigmas[id];

    auto p0 = fP0[id];
    auto p1 = fP1[id];

    fNoiseThreshold.emplace(id, p0+p1*(mean+fThresh*sigma)); // in keV
  }

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterPurification::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterPurification";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterPurification::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterPurification";

  Reset();

  // get rid of noise digis at the head and tail of the cluster
  Int_t index=0;
  Int_t fNrClusters = fInputClusters->GetEntriesFast();
  for(Int_t iNrCluster =0; iNrCluster<fNrClusters; iNrCluster++){
    auto curCluster = (KoaRecCluster*)fInputClusters->At(iNrCluster);

    auto fNrDigits = curCluster->NumberOfDigis();
    auto id_ptr = curCluster->GetIds();
    auto energy_ptr = curCluster->GetEnergies();
    auto timestamp_ptr = curCluster->GetTimestamps();

    //
    int head;
    int tail;
    for( head = 0; head < fNrDigits; head++){
      if( energy_ptr[head] > fNoiseThreshold[id_ptr[head]] )
        break;
    }

    if (head == fNrDigits) {
      continue;
    }

    for( tail = (fNrDigits-1); tail > head; tail-- ){
      if( energy_ptr[tail] > fNoiseThreshold[id_ptr[tail]])
        break;
    }

    // fill in output array
    auto det_id = curCluster->GetDetId();
    auto out_cluster = new ((*fOutputClusters)[index++]) KoaRecCluster(det_id);
    for(int i=head; i <= tail; i++){
      auto digi = new KoaRecDigi();
      digi->SetDetectorID(id_ptr[i]);
      digi->SetCharge(energy_ptr[i]);
      digi->SetTimeStamp(timestamp_ptr[i]);
      out_cluster->AddDigi(digi);
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecClusterPurification::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterPurification";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterPurification::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterPurification";

  fOutputClusters->Clear();
}

ClassImp(KoaRecClusterPurification)
