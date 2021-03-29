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
#include "KoaTransformToArray.h"
#include "KoaRecNoisePar.h"
#include "KoaMapEncoder.h"
#include "TFile.h"
#include "TTree.h"

// ---- Default constructor -------------------------------------------
KoaTransformToArray::KoaTransformToArray()
    :FairTask("KoaTransformToArray"),
     fOutputFile(nullptr)
{
  LOG(debug) << "Defaul Constructor of KoaTransformToArray";
}

// ---- Destructor ----------------------------------------------------
KoaTransformToArray::~KoaTransformToArray()
{
  LOG(debug) << "Destructor of KoaTransformToArray";

  if(fOutputFile) delete fOutputFile;
}

// ----  Initialisation  ----------------------------------------------
void KoaTransformToArray::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaTransformToArray";
}

// ---- Init ----------------------------------------------------------
InitStatus KoaTransformToArray::Init()
{
  LOG(debug) << "Initilization of KoaTransformToArray";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  if (fInputName.empty()) LOG(fatal) << "No input tree name set";
  fInputDigis = static_cast<TClonesArray*>(ioman->GetObject(fInputName.data()));
  if ( ! fInputDigis ) {
    LOG(error) << "No input branch " << fInputName;
    return kERROR;
  }

  // Create the TClonesArray for the output data and register it in the IO manager
  if (!fOutputFile) LOG(fatal) << "No output file name set";
  fOutputFile->cd();
  if (fOutputName.empty()) LOG(fatal) << "No output tree name set";
  fTree = new TTree(fOutputName.data(), fOutputName.data());
  fTree->Branch("Si1",fSi1,"Si1[48]/D");
  fTree->Branch("Si2",fSi2,"Si2[64]/D");
  fTree->Branch("Ge1",fGe1,"Ge1[32]/D");
  fTree->Branch("Ge2",fGe2,"Ge2[32]/D");

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaTransformToArray::ReInit()
{
  LOG(debug) << "Initilization of KoaTransformToArray";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaTransformToArray::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaTransformToArray";

  Reset();

  //
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  Int_t digis=fInputDigis->GetEntriesFast();
  for(int i=0;i<digis;i++){
    // rec digis
    KoaRecDigi* digi=(KoaRecDigi*)fInputDigis->At(i);
    Int_t id = digi->GetDetID();
    Int_t ch_id, det_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    auto charge = digi->GetCharge(); // keV
    switch (det_id) {
      case 0: {
        fSi1[ch_id] = charge;
        break;
      }
      case 1: {
        fSi2[ch_id] = charge;
        break;
      }
      case 2: {
        fGe1[ch_id] = charge;
        break;
      }
      case 3: {
        fGe2[ch_id] = charge;
        break;
      }
      default:
        break;
    }
  }

  fTree->Fill();
}

// ---- Finish --------------------------------------------------------
void KoaTransformToArray::Finish()
{
  LOG(debug) << "Finish of KoaTransformToArray";

  fTree->Write();
}

// ---- Reset --------------------------------------------------------
void KoaTransformToArray::Reset()
{
  LOG(debug) << "Reset of KoaTransformToArray";

  for(int i=0;i<48;i++){
    fSi1[i]=0;
  }
  for(int i=0;i<64;i++){
    fSi2[i]=0;
  }
  for(int i=0;i<32;i++){
    fGe1[i]=0;
  }
  for(int i=0;i<32;i++){
    fGe2[i]=0;
  }
}

ClassImp(KoaTransformToArray)
