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
#include "KoaRecRearRecon.h"

// ---- Default constructor -------------------------------------------
KoaRecRearRecon::KoaRecRearRecon()
    :FairTask("KoaRecRearRecon")
{
  LOG(debug) << "Defaul Constructor of KoaRecRearRecon";
}

// ---- Destructor ----------------------------------------------------
KoaRecRearRecon::~KoaRecRearRecon()
{
  LOG(debug) << "Destructor of KoaRecRearRecon";
}

// ----  Initialisation  ----------------------------------------------
void KoaRecRearRecon::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecRearRecon";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecRearRecon::Init()
{
  LOG(debug) << "Initilization of KoaRecRearRecon";

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
  ioman->Register(fOutputName.data(),"KoaRec",fInputDigis,true);

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecRearRecon::ReInit()
{
  LOG(debug) << "Initilization of KoaRecRearRecon";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecRearRecon::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecRearRecon";
}

// ---- Finish --------------------------------------------------------
void KoaRecRearRecon::Finish()
{
  LOG(debug) << "Finish of KoaRecRearRecon";

}

// ---- Reset --------------------------------------------------------
void KoaRecRearRecon::Reset()
{
  LOG(debug) << "Reset of KoaRecRearRecon";
}

ClassImp(KoaRecRearRecon)
