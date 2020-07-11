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
#include "KoaRecTimeWalkCorrect.h"

// ---- Default constructor -------------------------------------------
KoaRecTimeWalkCorrect::KoaRecTimeWalkCorrect()
    :FairTask("KoaRecTimeWalkCorrect")
{
  LOG(debug) << "Defaul Constructor of KoaRecTimeWalkCorrect";
}

// ---- Destructor ----------------------------------------------------
KoaRecTimeWalkCorrect::~KoaRecTimeWalkCorrect()
{
  LOG(debug) << "Destructor of KoaRecTimeWalkCorrect";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecTimeWalkCorrect::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecTimeWalkCorrect";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecTimeWalkCorrect::Init()
{
  LOG(debug) << "Initilization of KoaRecTimeWalkCorrect";

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
  if (fTdcParaFile.empty()) LOG(fatal) << "No TDC parameters found";
  auto params = readParameterList<double>( fTdcParaFile);

  auto it = findValueContainer(params, fTdcParaName);
  if ( it == params.end()) {
    LOG(error) << "No parameter found in the TDC parameter file: " << fTdcParaName;
    return kERROR;
  }
  fP0 = it->second;

  // test
  // LOG(info) << "check TDC parameters";
  // printValueContainer(fTimeShift,"Tdc Time Shift Parameters:");
  // printValueList(params,"test.txt");

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecTimeWalkCorrect::ReInit()
{
  LOG(debug) << "Initilization of KoaRecTimeWalkCorrect";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecTimeWalkCorrect::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecTimeWalkCorrect";

  Reset();

  // calibration of energy and get rid of low energy hits
  Int_t couter=0;
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge();
    auto timestamp = curDigi->GetTimeStamp();
    if ( timestamp > 0 ) {
      timestamp -= fP0[id]/charge;
    }

    KoaRecDigi* outDigi = new ((*fOutputDigis)[couter++]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(timestamp);
    outDigi->SetCharge(charge);
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecTimeWalkCorrect::Finish()
{
  LOG(debug) << "Finish of KoaRecTimeWalkCorrect";

}

// ---- Reset --------------------------------------------------------
void KoaRecTimeWalkCorrect::Reset()
{
  LOG(debug) << "Reset of KoaRecTimeWalkCorrect";

  fOutputDigis->Clear();
}

ClassImp(KoaRecTimeWalkCorrect)
