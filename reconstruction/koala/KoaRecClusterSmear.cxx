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
#include "KoaRecClusterSmear.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterSmear::KoaRecClusterSmear()
    :FairTask("KoaRecClusterSmear"),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterSmear";
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterSmear::~KoaRecClusterSmear()
{
  LOG(debug) << "Destructor of KoaRecClusterSmear";

  if ( fOutputClusters ) {
    fOutputClusters->Delete();
    delete fOutputClusters;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterSmear::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterSmear";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterSmear::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterSmear";

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

  // read adc calib parameters
  if (fAdcParaFile.empty()) LOG(fatal) << "No ADC parameters found";
  auto adc_params = readParameterList<double>( fAdcParaFile);

  auto it = findValueContainer(adc_params, "AdcToE_p1");
  if ( it == adc_params.end()) {
    LOG(error) << "No \'AdcToE_p1\' parameter found in the ADC parameter file";
    return kERROR;
  }
  fBinWidth = it->second;

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterSmear::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterSmear";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterSmear::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterSmear";

  Reset();

  // collect adjacent strips into a cluster
  Int_t index=0;
  auto digi = new KoaRecDigi();

  Int_t fNrClusters = fInputClusters->GetEntriesFast();
  for(Int_t iNrCluster =0; iNrCluster<fNrClusters; iNrCluster++){
    auto curCluster = (KoaRecCluster*)fInputClusters->At(iNrCluster);

    auto det_id = curCluster->GetDetId();
    auto fNrDigits = curCluster->NumberOfDigis();
    auto id_ptr = curCluster->GetIds();
    auto energy_ptr = curCluster->GetEnergies();
    auto timestamp_ptr = curCluster->GetTimestamps();

    // fill in output array
    auto out_cluster = new ((*fOutputClusters)[index++]) KoaRecCluster(det_id);
    for(Int_t iNrDigi = 0; iNrDigi < fNrDigits; iNrDigi++){
      digi->SetDetectorID(id_ptr[iNrDigi]);
      digi->SetTimeStamp(timestamp_ptr[iNrDigi]);

      auto width = fBinWidth[id_ptr[iNrDigi]]/2.;
      auto e_smear = fRndEngine.Uniform(energy_ptr[iNrDigi]-width, energy_ptr[iNrDigi]+width);
      digi->SetCharge(e_smear);

      out_cluster->AddDigi(digi);
    }
  }
  delete digi;
}

// ---- Finish --------------------------------------------------------
void KoaRecClusterSmear::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterSmear";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterSmear::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterSmear";

  fOutputClusters->Clear();
}

ClassImp(KoaRecClusterSmear)
