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
#include "KoaRecTimeShiftCorrect.h"
#include <iterator>

// ---- Default constructor -------------------------------------------
KoaRecTimeShiftCorrect::KoaRecTimeShiftCorrect()
    :FairTask("KoaRecTimeShiftCorrect")
{
  LOG(debug) << "Defaul Constructor of KoaRecTimeShiftCorrect";
}

// ---- Destructor ----------------------------------------------------
KoaRecTimeShiftCorrect::~KoaRecTimeShiftCorrect()
{
  LOG(debug) << "Destructor of KoaRecTimeShiftCorrect";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecTimeShiftCorrect::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecTimeShiftCorrect";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecTimeShiftCorrect::Init()
{
  LOG(debug) << "Initilization of KoaRecTimeShiftCorrect";

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
  fMean = it->second;

  CalcTimeShift();

  // test
  // LOG(info) << "check TDC parameters";
  // printValueContainer(fTimeShift,"Tdc Time Shift Parameters:");
  // printValueList(params,"test.txt");

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecTimeShiftCorrect::ReInit()
{
  LOG(debug) << "Initilization of KoaRecTimeShiftCorrect";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecTimeShiftCorrect::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecTimeShiftCorrect";

  Reset();

  // calibration of energy and get rid of low energy hits
  Int_t couter=0;
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto id = curDigi->GetDetID();
    auto charge = curDigi->GetCharge();
    auto timestamp = curDigi->GetTimeStamp();
    if ( timestamp > 0 )
      timestamp -= fTimeShift[id];

    KoaRecDigi* outDigi = new ((*fOutputDigis)[couter++]) KoaRecDigi();
    outDigi->SetDetectorID(id);
    outDigi->SetTimeStamp(timestamp);
    outDigi->SetCharge(charge);
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecTimeShiftCorrect::Finish()
{
  LOG(debug) << "Finish of KoaRecTimeShiftCorrect";

}

// ---- Reset --------------------------------------------------------
void KoaRecTimeShiftCorrect::Reset()
{
  LOG(debug) << "Reset of KoaRecTimeShiftCorrect";

  fOutputDigis->Clear();
}

// Calculate the time shift between channels using first as a reference
void KoaRecTimeShiftCorrect::CalcTimeShift(int ref_ch)
{
  auto it = std::next(fMean.begin(), ref_ch);
  auto tdc_ref = it->second;
  for ( auto& ch : fMean ) {
    auto& id = ch.first;
    auto& mean = ch.second;
    fTimeShift.emplace(id, mean-tdc_ref);
  }
}

ClassImp(KoaRecTimeShiftCorrect)
