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
#include "KoaRecNoiseGenerator.h"

// ---- Default constructor -------------------------------------------
KoaRecNoiseGenerator::KoaRecNoiseGenerator()
    :FairTask("KoaRecNoiseGenerator"),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecNoiseGenerator";
}

// ---- Destructor ----------------------------------------------------
KoaRecNoiseGenerator::~KoaRecNoiseGenerator()
{
  LOG(debug) << "Destructor of KoaRecNoiseGenerator";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecNoiseGenerator::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecNoiseGenerator";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecNoiseGenerator::Init()
{
  LOG(debug) << "Initilization of KoaRecNoiseGenerator";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  // Create the TClonesArray for the output data and register it in the IO manager
  if (fOutputName.empty()) LOG(fatal) << "No output branch name set";
  fOutputDigis = new TClonesArray("KoaRecDigi", 300);
  ioman->Register(fOutputName.data(),"KoaRec",fOutputDigis, true);

  // Do whatever else is needed at the initilization stage
  if (fPedestalFileName.empty()) LOG(fatal) << "No pedestal parameters found";
  auto params = readParameterList<double>(fPedestalFileName);

  auto it = findValueContainer(params, "Mean");
  if ( it == params.end()) {
    LOG(error) << "No \'Mean\' parameter found in the pedestal file";
    return kERROR;
  }
  fMeans = it->second;

  it = findValueContainer(params, "Sigma");
  if ( it == params.end()) {
    LOG(error) << "No \'Sigma\' parameter found in the pedestal file";
    return kERROR;
  }
  fSigmas = it->second;

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecNoiseGenerator::ReInit()
{
  LOG(debug) << "Initilization of KoaRecNoiseGenerator";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecNoiseGenerator::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecNoiseGenerator";

  Reset();

  Int_t couter=0;
  for(auto& item: fMeans){
    auto id = item.first;
    auto mean = item.second;
    auto sigma = fSigmas[id];

    KoaRecDigi* outDigi = new ((*fOutputDigis)[couter++]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(-5);
    outDigi->SetCharge(fRndEngine.Gaus(mean, sigma));
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecNoiseGenerator::Finish()
{
  LOG(debug) << "Finish of KoaRecNoiseGenerator";

}

// ---- Reset --------------------------------------------------------
void KoaRecNoiseGenerator::Reset()
{
  LOG(debug) << "Reset of KoaRecNoiseGenerator";

  fOutputDigis->Clear();
}

ClassImp(KoaRecNoiseGenerator)
