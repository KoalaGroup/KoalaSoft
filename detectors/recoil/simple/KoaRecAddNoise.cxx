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
#include "KoaRecAddNoise.h"
#include "KoaRecNoisePar.h"
#include "TRandom3.h"

// ---- Default constructor -------------------------------------------
KoaRecAddNoise::KoaRecAddNoise()
    :FairTask("KoaRecAddNoise"),
     fSaveOutput(true),
     fNoisePar(nullptr),
     fNoiseMean(0),
     fNoiseSigma(0),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecAddNoise";
}

// ---- Destructor ----------------------------------------------------
KoaRecAddNoise::~KoaRecAddNoise()
{
  LOG(debug) << "Destructor of KoaRecAddNoise";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecAddNoise::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecAddNoise";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fNoisePar = static_cast<KoaRecNoisePar*>(rtdb->getContainer("KoaRecNoisePar"));
  fNoisePar->printParams();
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecAddNoise::Init()
{
  LOG(debug) << "Initilization of KoaRecAddNoise";

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
  // Create histograms to be filled
  // initialize variables
  fNoiseMean = fNoisePar->GetMean();
  fNoiseSigma = fNoisePar->GetSigma();
  fNoisePar->printParams();

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecAddNoise::ReInit()
{
  LOG(debug) << "Initilization of KoaRecAddNoise";

  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fNoisePar = static_cast<KoaRecNoisePar*>(rtdb->getContainer("KoaRecNoisePar"));

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecAddNoise::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecAddNoise";

  Reset();

  //
  AddNoise();
}

// ---- Finish --------------------------------------------------------
void KoaRecAddNoise::Finish()
{
  LOG(debug) << "Finish of KoaRecAddNoise";

}

// ---- Reset --------------------------------------------------------
void KoaRecAddNoise::Reset()
{
  LOG(debug) << "Reset of KoaRecAddNoise";

  fOutputDigis->Clear();
}

// ---- AddNoise --------------------------------------------------------
void KoaRecAddNoise::AddNoise()
{
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto ts = curDigi->GetTimeStamp();
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge();

    KoaRecDigi* outDigi = new ((*fOutputDigis)[iNrDigit]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(ts);
    outDigi->SetCharge(charge + fRndEngine.Gaus(fNoiseMean, fNoiseSigma));
  }
}

ClassImp(KoaRecAddNoise)
