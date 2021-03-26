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
#include "KoaRecAddTimeJitter.h"
#include "KoaRecTimeJitterPar.h"

// ---- Default constructor -------------------------------------------
KoaRecAddTimeJitter::KoaRecAddTimeJitter()
    :FairTask("KoaRecAddTimeJitter"),
     fSaveOutput(true),
     fJitterPar(nullptr),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecAddTimeJitter";
}

// ---- Destructor ----------------------------------------------------
KoaRecAddTimeJitter::~KoaRecAddTimeJitter()
{
  LOG(debug) << "Destructor of KoaRecAddTimeJitter";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecAddTimeJitter::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecAddTimeJitter";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fJitterPar = static_cast<KoaRecTimeJitterPar*>(rtdb->getContainer("KoaRecTimeJitterPar"));
  fJitterPar->printParams();
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecAddTimeJitter::Init()
{
  LOG(debug) << "Initilization of KoaRecAddTimeJitter";

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
  fSigma = fJitterPar->GetSigma();

  fJitterPar->printParams();

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecAddTimeJitter::ReInit()
{
  LOG(debug) << "Initilization of KoaRecAddTimeJitter";

  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fJitterPar = static_cast<KoaRecTimeJitterPar*>(rtdb->getContainer("KoaRecTimeJitterPar"));

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecAddTimeJitter::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecAddTimeJitter";

  Reset();

  //
  AddTimeJitter();
}

// ---- Finish --------------------------------------------------------
void KoaRecAddTimeJitter::Finish()
{
  LOG(debug) << "Finish of KoaRecAddTimeJitter";

}

// ---- Reset --------------------------------------------------------
void KoaRecAddTimeJitter::Reset()
{
  LOG(debug) << "Reset of KoaRecAddTimeJitter";

  fOutputDigis->Clear();
}

// ---- AddTimeJitter --------------------------------------------------------
void KoaRecAddTimeJitter::AddTimeJitter()
{
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto ts = curDigi->GetTimeStamp(); // in ns
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge(); // in keV

    //
    ts = fRndEngine.Gaus(ts, fSigma);

    KoaRecDigi* outDigi = new ((*fOutputDigis)[iNrDigit]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(ts);
    outDigi->SetCharge(charge);
  }
}

ClassImp(KoaRecAddTimeJitter)
