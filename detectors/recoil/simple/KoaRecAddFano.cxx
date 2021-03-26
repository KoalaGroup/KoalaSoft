/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "KoaRecDigi.h"
#include "KoaRecAddFano.h"
#include "KoaRecFanoPar.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecAddFano::KoaRecAddFano()
    :FairTask("KoaRecAddFano"),
     fSaveOutput(true),
     fFanoPar(nullptr),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecAddFano";
  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaRecAddFano::~KoaRecAddFano()
{
  LOG(debug) << "Destructor of KoaRecAddFano";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecAddFano::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecAddFano";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fFanoPar = static_cast<KoaRecFanoPar*>(rtdb->getContainer("KoaRecFanoPar"));
  fFanoPar->printParams();
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecAddFano::Init()
{
  LOG(debug) << "Initilization of KoaRecAddFano";

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
  fFanoFactors = fFanoPar->GetFanoFactors();
  fFanoPar->printParams();

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecAddFano::ReInit()
{
  LOG(debug) << "Initilization of KoaRecAddFano";

  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fFanoPar = static_cast<KoaRecFanoPar*>(rtdb->getContainer("KoaRecFanoPar"));

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecAddFano::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecAddFano";

  Reset();

  //
  AddFano();
}

// ---- Finish --------------------------------------------------------
void KoaRecAddFano::Finish()
{
  LOG(debug) << "Finish of KoaRecAddFano";

}

// ---- Reset --------------------------------------------------------
void KoaRecAddFano::Reset()
{
  LOG(debug) << "Reset of KoaRecAddFano";

  fOutputDigis->Clear();
}

// ---- AddFano --------------------------------------------------------
void KoaRecAddFano::AddFano()
{
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto ts = curDigi->GetTimeStamp();
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge();

    //
    Int_t det_id;
    fEncoder->DecodeChannelID(id, det_id);
    auto sigma = TMath::Sqrt(fFanoFactors[det_id]*charge);

    KoaRecDigi* outDigi = new ((*fOutputDigis)[iNrDigit]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(ts);
    outDigi->SetCharge(fRndEngine.Gaus(charge, sigma));
  }
}

ClassImp(KoaRecAddFano)
