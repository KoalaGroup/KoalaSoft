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
#include "KoaRecCluster.h"
#include "KoaRecClusterCollect.h"
#include "KoaMapEncoder.h"

// ---- Default constructor -------------------------------------------
KoaRecClusterCollect::KoaRecClusterCollect()
    :FairTask("KoaRecClusterCollect")
{
  LOG(debug) << "Defaul Constructor of KoaRecClusterCollect";

  fEncoder = KoaMapEncoder::Instance();
}

// ---- Destructor ----------------------------------------------------
KoaRecClusterCollect::~KoaRecClusterCollect()
{
  LOG(debug) << "Destructor of KoaRecClusterCollect";

  if ( fOutputClusters ) {
    fOutputClusters->Delete();
    delete fOutputClusters;
  }
}

// ----  Initialisation  ----------------------------------------------
void KoaRecClusterCollect::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecClusterCollect";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecClusterCollect::Init()
{
  LOG(debug) << "Initilization of KoaRecClusterCollect";

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
  fOutputClusters = new TClonesArray("KoaRecCluster", 32);
  ioman->Register(fOutputName.data(),"KoaRec",fOutputClusters,fSaveOutput);

  // Do whatever else is needed at the initilization stage

  // test
  // LOG(info) << "check ADC parameters";
  // printValueContainer(fP0,"Adc P0 Parameters:");
  // printValueContainer(fP1,"Adc P1 Parameters:");
  // printValueList(params,"test.txt");

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecClusterCollect::ReInit()
{
  LOG(debug) << "Initilization of KoaRecClusterCollect";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecClusterCollect::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecClusterCollect";

  Reset();

  // collect adjacent strips into a cluster
  Int_t couter=0;
  Int_t det_id, ch_id, id;
  KoaRecCluster* curCluster = nullptr;

  Int_t fNrDigits = fInputDigis->GetEntriesFast();
  if ( fNrDigits > 0 ) {
    auto* theDigi = static_cast<KoaRecDigi*>(fInputDigis->At(0));
    ch_id = fEncoder->DecodeChannelID(theDigi->GetDetID(), det_id);
    curCluster = new ((*fOutputClusters)[couter++]) KoaRecCluster(det_id);
    curCluster->AddDigi(theDigi);

    for ( int index=1; index<fNrDigits; ++index) {
      theDigi = static_cast<KoaRecDigi*>(fInputDigis->At(index));
      if( !curCluster->isInCluster(theDigi) ) {
        ch_id = fEncoder->DecodeChannelID(theDigi->GetDetID(), det_id);
        curCluster = new ((*fOutputClusters)[couter++]) KoaRecCluster(det_id);
      }
      curCluster->AddDigi(theDigi);
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaRecClusterCollect::Finish()
{
  LOG(debug) << "Finish of KoaRecClusterCollect";

}

// ---- Reset --------------------------------------------------------
void KoaRecClusterCollect::Reset()
{
  LOG(debug) << "Reset of KoaRecClusterCollect";

  fOutputClusters->Clear();
}

ClassImp(KoaRecClusterCollect)
