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
#include "KoaRecEnergyRecon.h"
#include "KoaGeoHandler.h"
#include "TGeoManager.h"
#include "KoaMapEncoder.h"
#include "TFile.h"

// ---- Default constructor -------------------------------------------
KoaRecEnergyRecon::KoaRecEnergyRecon()
    :FairTask("KoaRecEnergyRecon")
{
  LOG(debug) << "Defaul Constructor of KoaRecEnergyRecon";
}

// ---- Destructor ----------------------------------------------------
KoaRecEnergyRecon::~KoaRecEnergyRecon()
{
  LOG(debug) << "Destructor of KoaRecEnergyRecon";

  if ( fOutputDigis ) {
    fOutputDigis->Delete();
    delete fOutputDigis;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecEnergyRecon::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecEnergyRecon";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecEnergyRecon::Init()
{
  LOG(debug) << "Initilization of KoaRecEnergyRecon";

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
  if (fAdcParaFile.empty()) LOG(fatal) << "No ADC parameters found";
  auto params = readParameterList<double>( fAdcParaFile);

  auto it = findValueContainer(params, "AdcToE_p0");
  if ( it == params.end()) {
    LOG(error) << "No \'AdcToE_p0\' parameter found in the ADC parameter file";
    return kERROR;
  }
  fP0 = it->second;

  it = findValueContainer(params, "AdcToE_p1");
  if ( it == params.end()) {
    LOG(error) << "No \'AdcToE_p1\' parameter found in the ADC parameter file";
    return kERROR;
  }
  fP1 = it->second;

  // Read alphas from geometry file
  if (fGeometryFile.empty()) LOG(fatal) << "No Geometry model file is configured";
  auto fgeo = TFile::Open(fGeometryFile.data());
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  auto geoHandler = new KoaGeoHandler(kFALSE);
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<int> ChIDs = encoder->GetRecChIDs();

  Double_t pos_low, pos_high, pos_center;
  Double_t global_pos[3] = {0};
  Double_t local_pos[3] = {0};
  Double_t sensor_thickness[4] = {0.1/2, 0.1/2, 0.5/2, 1.1/2}; // half thickness in cm
  Double_t yoffset[4] = {0};

  Int_t ch_id, det_id;
  double pi = TMath::Pi();

  for(auto id : ChIDs) {
    ch_id = encoder->DecodeChannelID(id, det_id);

    pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);

    local_pos[0] = -sensor_thickness[det_id];
    local_pos[2] = pos_center;
    geoHandler->LocalToGlobal(local_pos, global_pos, det_id);

    global_pos[2] += fZOffset[det_id];
    global_pos[1] += yoffset[det_id];
    TVector3 vec(global_pos);
    fAlpha.emplace(id, 90 - vec.Theta()/pi*180);
  }

  delete geoHandler;
  delete fgeo;

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecEnergyRecon::ReInit()
{
  LOG(debug) << "Initilization of KoaRecEnergyRecon";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecEnergyRecon::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecEnergyRecon";

  Reset();

  // calibration of energy and get rid of low energy hits
  Int_t couter=0;
  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  for(Int_t iNrDigit =0; iNrDigit<fNrDigits; iNrDigit++){
    KoaRecDigi* curDigi = (KoaRecDigi*)fInputDigis->At(iNrDigit);
    auto id = curDigi->GetDetID();
    auto energy = fP0[id] + fP1[id]*curDigi->GetCharge();

    if ( energy > fThreshold ) {
      KoaRecDigi* outDigi = new ((*fOutputDigis)[couter++]) KoaRecDigi();
      outDigi->SetDetectorID(id);
      outDigi->SetTimeStamp(curDigi->GetTimeStamp());
      outDigi->SetCharge(energy);
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecEnergyRecon::Finish()
{
  LOG(debug) << "Finish of KoaRecEnergyRecon";

}

// ---- Reset --------------------------------------------------------
void KoaRecEnergyRecon::Reset()
{
  LOG(debug) << "Reset of KoaRecEnergyRecon";

  fOutputDigis->Clear();
}

ClassImp(KoaRecEnergyRecon)
