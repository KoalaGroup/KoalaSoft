/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaFwdDigitization.h"
#include "KoaFwdDigitizationPar.h"
#include "KoaMapEncoder.h"
#include "TClonesArray.h"
#include "KoaFwdDigi.h"
#include "KoaFwdPoint.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "TRandom.h"

// ---- Default constructor -------------------------------------------
KoaFwdDigitization::KoaFwdDigitization()
  :FairTask("KoaFwdDigitization"),
   fDigitizationPar(nullptr),
   fTimeSigma(0),
   fEnergySigma(0),
   fEnergyNoise(0),
   fEnergyNoiseSigma(0)
{
  fMapEncoder = KoaMapEncoder::Instance();
  LOG(debug) << "Defaul Constructor of KoaFwdDigitization";
}

// ---- Destructor ----------------------------------------------------
KoaFwdDigitization::~KoaFwdDigitization()
{
  LOG(debug) << "Destructor of KoaFwdDigitization";

  if ( fDigis ) {
    fDigis->Delete();
    delete fDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaFwdDigitization::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaFwdDigitization";
  // Load all necessary parameter containers from the runtime data base
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigitizationPar = static_cast<KoaFwdDigitizationPar*>(rtdb->getContainer("KoaFwdDigitizationPar"));
}

// ---- Init ----------------------------------------------------------
InitStatus KoaFwdDigitization::Init()
{
  LOG(debug) << "Initilization of KoaFwdDigitization";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  fPoints = static_cast<TClonesArray*>(ioman->GetObject("KoaFwdPoint"));
  if ( ! fPoints ) {
    LOG(error) << "No input KoaFwdPoint array";
    return kERROR;
  }
  // Create the TClonesArray for the output data and register
  // it in the IO manager
  
  fDigis = new TClonesArray("KoaFwdDigi", 10);
  ioman->Register("KoaFwdDigi","KoaFwd",fDigis,kTRUE);

  // Do whatever else is needed at the initilization stage
  // Create histograms to be filled
  // initialize variables
  fTimeSigma = fDigitizationPar->GetTimeSigma();
  fEnergySigma = fDigitizationPar->GetEnergySigma();
  fEnergyNoise = fDigitizationPar->GetEnergyNoise();
  fEnergyNoiseSigma = fDigitizationPar->GetEnergyNoiseSigma();

  return kSUCCESS;

}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaFwdDigitization::ReInit()
{
  LOG(debug) << "Initilization of KoaFwdDigitization";

  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigitizationPar = static_cast<KoaFwdDigitizationPar*>(rtdb->getContainer("KoaFwdDigitizationPar"));

  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaFwdDigitization::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaFwdDigitization";

  Reset();

  //
  Int_t fNrPoints = fPoints->GetEntriesFast();
  for(Int_t iPoint =0; iPoint<fNrPoints; iPoint++){
    KoaFwdPoint* curPoint = (KoaFwdPoint*)fPoints->At(iPoint);
    FillFiredStrip(curPoint);
  }
  //
  SmearDigis();
  //
  AddDigis();
}

// ---- Finish --------------------------------------------------------
void KoaFwdDigitization::Finish()
{
  LOG(debug) << "Finish of KoaFwdDigitization";

}

// ---- Reset --------------------------------------------------------
void KoaFwdDigitization::Reset()
{
  LOG(debug) << "Reset of KoaFwdDigitization";

  if ( fDigis ) fDigis->Delete();
  fFiredStrips.clear();
}

// ---- Fill Fired Scint digi --------------------------------------------------------
void KoaFwdDigitization::FillFiredStrip(KoaFwdPoint* McPoint)
{
  //
  Int_t detID = McPoint->GetDetectorID();
  Int_t chID = fMapEncoder->EncodeChannelID(detID, 0);
  Double_t eLoss = McPoint->GetEnergyLoss();
  Double_t timestamp = McPoint->GetTime();

  auto search = fFiredStrips.find(chID);
  if(search != fFiredStrips.end()){
    if(timestamp < search->second.fTimestamp){
      search->second.fTimestamp = timestamp;
    }
    search->second.fCharge+=eLoss;
  }
  else{
    KoaFwdStrip strip;
    strip.fTimestamp = timestamp;
    strip.fCharge = eLoss;
    fFiredStrips.insert(std::make_pair(chID, strip));
  }
}

// ---- Smear time and energy --------------------------------------------------------
void KoaFwdDigitization::SmearDigis()
{
  if(fTimeSigma){
    for(auto& strip : fFiredStrips){
      Double_t time = strip.second.fTimestamp;
      strip.second.fTimestamp = gRandom->Gaus(time, fTimeSigma);
    }
  }

  if(fEnergySigma || fEnergyNoise || fEnergyNoiseSigma){
    for(auto& strip : fFiredStrips){
      Double_t energy = strip.second.fCharge;
      Double_t noise = gRandom->Gaus(fEnergyNoise, fEnergyNoiseSigma);
      energy = noise + gRandom->Gaus(energy, fEnergySigma);
      strip.second.fCharge = energy;
    }
  }
}

// ---- AddDigis --------------------------------------------------------
void KoaFwdDigitization::AddDigis()
{
  Int_t index=0;
  for(auto strip = fFiredStrips.begin(); strip != fFiredStrips.end(); strip++){
    KoaFwdDigi* digi = new ((*fDigis)[index++]) KoaFwdDigi();
    digi->SetDetectorID(strip->first);
    digi->SetCharge(strip->second.fCharge);
    digi->SetTimeStamp(strip->second.fTimestamp);
  }
}

ClassImp(KoaFwdDigitization)
