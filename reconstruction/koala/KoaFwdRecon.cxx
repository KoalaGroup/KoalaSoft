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
#include "KoaFwdDigi.h"
#include "KoaFwdRecon.h"

// ---- Default constructor -------------------------------------------
KoaFwdRecon::KoaFwdRecon()
    :FairTask("KoaFwdRecon")
{
  LOG(debug) << "Defaul Constructor of KoaFwdRecon";
}

// ---- Destructor ----------------------------------------------------
KoaFwdRecon::~KoaFwdRecon()
{
  LOG(debug) << "Destructor of KoaFwdRecon";
}

// ----  Initialisation  ----------------------------------------------
void KoaFwdRecon::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaFwdRecon";
  // Load all necessary parameter containers from the runtime data base
}

// ---- Init ----------------------------------------------------------
InitStatus KoaFwdRecon::Init()
{
  LOG(debug) << "Initilization of KoaFwdRecon";

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
  ioman->Register(fOutputName.data(),"KoaFwd",fInputDigis,true);

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaFwdRecon::ReInit()
{
  LOG(debug) << "Initilization of KoaFwdRecon";

  //
  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaFwdRecon::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaFwdRecon";
}

// ---- Finish --------------------------------------------------------
void KoaFwdRecon::Finish()
{
  LOG(debug) << "Finish of KoaFwdRecon";

}

// ---- Reset --------------------------------------------------------
void KoaFwdRecon::Reset()
{
  LOG(debug) << "Reset of KoaFwdRecon";
}

ClassImp(KoaFwdRecon)
