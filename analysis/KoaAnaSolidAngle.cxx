/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaAnaSolidAngle.h"
#include "FairRootManager.h"
#include "TClonesArray.h"
#include "TMath.h"
#include "FairLogger.h"

// ---- Default constructor -------------------------------------------
KoaAnaSolidAngle::KoaAnaSolidAngle()
  :FairTask("KoaAnaSolidAngle"),
   fMCEntryNo(0),
   fOutputFile(),
   fFileName("NrOfHitsDistribution.txt")
{
  LOG(debug) << "Defaul Constructor of KoaAnaSolidAngle";
  for(int i=0;i<48;i++){
    if(fSi1NrHit[i])
      LOG(fatal) << "Array not initialized to zero in KoaAnaSolidAngle";
  }
}

// ---- Destructor ----------------------------------------------------
KoaAnaSolidAngle::~KoaAnaSolidAngle()
{
  LOG(debug) << "Destructor of KoaAnaSolidAngle";
}

// ----  Initialisation  ----------------------------------------------
void KoaAnaSolidAngle::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaAnaSolidAngle";
  // Load all necessary parameter containers from the runtime data base
  /*
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  <KoaAnaSolidAngleDataMember> = (<ClassPointer>*)
    (rtdb->getContainer("<ContainerName>"));
  */
}

// ---- Init ----------------------------------------------------------
InitStatus KoaAnaSolidAngle::Init()
{
  LOG(debug) << "Initilization of KoaAnaSolidAngle";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  // Get a pointer to the previous already existing data level
  fPoints = static_cast<TClonesArray*>(ioman->GetObject("KoaRecPoint"));
  if ( ! fPoints ) {
    LOG(warn) << "No input KoaRecPoint array";
      // return kERROR;
  }

  // Create the TClonesArray for the output data and register
  // it in the IO manager
  /*
    <OutputDataLevel> = new TClonesArray("OutputDataLevelName", 100);
    ioman->Register("OutputDataLevelName","OutputDataLevelName",<OutputDataLevel>,kTRUE);
  */

  // Do whatever else is needed at the initilization stage
  // Create histograms to be filled
  // initialize variables
  fOutputFile.open(fFileName.Data(),std::fstream::out);

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaAnaSolidAngle::ReInit()
{
  LOG(debug) << "Initilization of KoaAnaSolidAngle";
  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaAnaSolidAngle::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaAnaSolidAngle";

  fMCEntryNo++;
}

// ---- Finish --------------------------------------------------------
void KoaAnaSolidAngle::Finish()
{
  LOG(debug) << "Finish of KoaAnaSolidAngle";

  Write();
  fOutputFile.close();
}

// ---- SetOutFileName --------------------------------------------------------
void KoaAnaSolidAngle::SetOutFileName(const char* filename)
{
  fFileName = filename;
}

// ---- SaveToFile --------------------------------------------------------
void KoaAnaSolidAngle::Write()
{
  const Double_t pi=TMath::Pi();
  Int_t ch_id=0;

  fOutputFile << "Si1 (solid angle of each channel):" << std::endl;
  for(Long_t nr : fSi1NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " <<  pi*nr/fMCEntryNo << std::endl;
  }

  fOutputFile << "Si2 (solid angle of each channel):" << std::endl;
  ch_id=0;
  for(Long_t nr : fSi2NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " << pi*nr/fMCEntryNo << std::endl;
  }

  fOutputFile << "Ge1 (solid angle of each channel):" << std::endl;
  ch_id=0;
  for(Long_t nr : fGe1NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " << pi*nr/fMCEntryNo << std::endl;
  }

  fOutputFile << "Ge2 (solid angle of each channel):" << std::endl;
  ch_id=0;
  for(Long_t nr : fGe2NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " << pi*nr/fMCEntryNo << std::endl;
  }
}

ClassImp(KoaAnaSolidAngle)
