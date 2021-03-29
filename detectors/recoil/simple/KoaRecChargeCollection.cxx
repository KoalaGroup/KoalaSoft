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
#include "KoaRecChargeCollection.h"
#include "KoaRecChargeCollectionPar.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecChargeCollection::KoaRecChargeCollection()
    :FairTask("KoaRecChargeCollection"),
     fSaveOutput(true),
     fCollectionPar(nullptr),
     fRndEngine(0)
{
  LOG(debug) << "Defaul Constructor of KoaRecChargeCollection";
  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaRecChargeCollection::~KoaRecChargeCollection()
{
  LOG(debug) << "Destructor of KoaRecChargeCollection";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecChargeCollection::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecChargeCollection";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fCollectionPar = static_cast<KoaRecChargeCollectionPar*>(rtdb->getContainer("KoaRecChargeCollectionPar"));
  fCollectionPar->printParams();
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecChargeCollection::Init()
{
  LOG(debug) << "Initilization of KoaRecChargeCollection";

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
  fCollectionEfficiency = fCollectionPar->GetEfficiency();
  fCollectionDispersion = fCollectionPar->GetDispersion();
  fCollectionPar->printParams();

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecChargeCollection::ReInit()
{
  LOG(debug) << "Initilization of KoaRecChargeCollection";

  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fCollectionPar = static_cast<KoaRecChargeCollectionPar*>(rtdb->getContainer("KoaRecChargeCollectionPar"));

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecChargeCollection::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecChargeCollection";

  Reset();

  //
  ChargeCollection();
}

// ---- Finish --------------------------------------------------------
void KoaRecChargeCollection::Finish()
{
  LOG(debug) << "Finish of KoaRecChargeCollection";

}

// ---- Reset --------------------------------------------------------
void KoaRecChargeCollection::Reset()
{
  LOG(debug) << "Reset of KoaRecChargeCollection";

  fOutputDigis->Clear();
}

// ---- ChargeCollection --------------------------------------------------------
void KoaRecChargeCollection::ChargeCollection()
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
    auto sigma = fCollectionDispersion[det_id];
    auto mean = fCollectionEfficiency[det_id]*charge;

    KoaRecDigi* outDigi = new ((*fOutputDigis)[iNrDigit]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(ts);
    outDigi->SetCharge(fRndEngine.Gaus(mean, sigma));
  }
}

ClassImp(KoaRecChargeCollection)
