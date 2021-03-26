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
#include "KoaRecAddTimeWalk.h"
#include "KoaRecTimeWalkPar.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecAddTimeWalk::KoaRecAddTimeWalk()
    :FairTask("KoaRecAddTimeWalk"),
     fSaveOutput(true),
     fTimeWalkPar(nullptr)
{
  LOG(debug) << "Defaul Constructor of KoaRecAddTimeWalk";
}

// ---- Destructor ----------------------------------------------------
KoaRecAddTimeWalk::~KoaRecAddTimeWalk()
{
  LOG(debug) << "Destructor of KoaRecAddTimeWalk";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecAddTimeWalk::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecAddTimeWalk";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fTimeWalkPar = static_cast<KoaRecTimeWalkPar*>(rtdb->getContainer("KoaRecTimeWalkPar"));
  fTimeWalkPar->printParams();
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecAddTimeWalk::Init()
{
  LOG(debug) << "Initilization of KoaRecAddTimeWalk";

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
  fThreshold = fTimeWalkPar->GetThreshold();
  fWidth = fTimeWalkPar->GetWidth();

  fTimeWalkPar->printParams();

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecAddTimeWalk::ReInit()
{
  LOG(debug) << "Initilization of KoaRecAddTimeWalk";

  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fTimeWalkPar = static_cast<KoaRecTimeWalkPar*>(rtdb->getContainer("KoaRecTimeWalkPar"));

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecAddTimeWalk::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecAddTimeWalk";

  Reset();

  //
  AddTimeWalk();
}

// ---- Finish --------------------------------------------------------
void KoaRecAddTimeWalk::Finish()
{
  LOG(debug) << "Finish of KoaRecAddTimeWalk";

}

// ---- Reset --------------------------------------------------------
void KoaRecAddTimeWalk::Reset()
{
  LOG(debug) << "Reset of KoaRecAddTimeWalk";

  fOutputDigis->Clear();
}

// ---- AddTimeWalk --------------------------------------------------------
void KoaRecAddTimeWalk::AddTimeWalk()
{
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto ts = curDigi->GetTimeStamp(); // in ns
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge(); // in keV

    //
    ts += fWidth*fThreshold/charge;

    KoaRecDigi* outDigi = new ((*fOutputDigis)[iNrDigit]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(ts);
    outDigi->SetCharge(charge);
  }
}

ClassImp(KoaRecAddTimeWalk)
