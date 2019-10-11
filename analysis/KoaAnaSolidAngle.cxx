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
#include "KoaGeoHandler.h"
#include "KoaMapEncoder.h"
#include "KoaRecPoint.h"
// #include "FairEvtFilterParams.h"

// ---- Default constructor -------------------------------------------
KoaAnaSolidAngle::KoaAnaSolidAngle()
  :FairTask("KoaAnaSolidAngle"),
   fMCEntryNo(0),
   fMCEntryFromExternal(kFALSE),
   fOutputFile(),
   fFileName("NrOfHitsDistribution.txt"),
   fSi1NrHit{0},
   fSi2NrHit{0},
   fGe1NrHit{0},
   fGe2NrHit{0},
   fGeoHandler(nullptr)
{
  LOG(debug) << "Defaul Constructor of KoaAnaSolidAngle";
  for(int i=0;i<48;i++){
    if(fSi1NrHit[i])
      LOG(fatal) << "Array not initialized to zero in KoaAnaSolidAngle" << fSi1NrHit[i];
  }
  for(int i=0;i<64;i++){
    if(fSi2NrHit[i])
      LOG(fatal) << "Array not initialized to zero in KoaAnaSolidAngle" << fSi1NrHit[i];
  }
  for(int i=0;i<32;i++){
    if(fGe1NrHit[i] || fGe2NrHit[i])
      LOG(fatal) << "Array not initialized to zero in KoaAnaSolidAngle" << fSi1NrHit[i];
  }
}

// ---- Destructor ----------------------------------------------------
KoaAnaSolidAngle::~KoaAnaSolidAngle()
{
  delete fGeoHandler;
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
      return kERROR;
  }

  // read no event based object ??
  // FairEvtFilterParams* filterStats = static_cast<FairEvtFilterParams*>(ioman->GetObject("FairEvtFilter"));
  // if(!filterStats){
  //   LOG(fatal) << "Can't get filterStats using standard method";
  // }
  // else{
  //   LOG(info) << "Events generated: " << filterStats->fGeneratedEvents ;
  // }

  // Do whatever else is needed at the initilization stage
  // Create histograms to be filled
  // initialize variables
  fOutputFile.open(fFileName.Data(),std::fstream::out);

  fNrHit.clear();

  // KoaGeoHandler uses gGeoManager internally, so it must be constructed after parameter input
  // gGeoManager is only available after parameter reading from BaseParSet
  fGeoHandler = new KoaGeoHandler(kFALSE);

  return kSUCCESS;
}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaAnaSolidAngle::ReInit()
{
  LOG(debug) << "Initilization of KoaAnaSolidAngle";

  fNrHit.clear();
  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaAnaSolidAngle::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaAnaSolidAngle";
  //
  if(!fMCEntryFromExternal)
    fMCEntryNo++;
  //
  std::map<Int_t, Int_t> mulithit;
  fNrPoints = fPoints->GetEntriesFast();
  if(fNrPoints>1) LOG(warning) << "More than 1 hit point!";

  Double_t global[3], local[3];
  for(Int_t iPoint =0; iPoint<fNrPoints; iPoint++){
    KoaRecPoint* curPoint = (KoaRecPoint*)fPoints->At(iPoint);
    Int_t detID = curPoint->GetDetectorID();
    global[0]=curPoint->GetX();
    global[1]=curPoint->GetY();
    global[2]=curPoint->GetZ();
    fGeoHandler->RecGlobalToLocal(global,local,detID);

    Int_t chID = fGeoHandler->RecPositionToDetCh(local,detID);

    auto it = mulithit.find(chID);
    if(it != mulithit.end()){
      LOG(warning) << "mulithit  in the same strip exists!";
    }
    else{
      mulithit[chID] = 1;
    }

    auto search = fNrHit.find(chID);
    if(search == fNrHit.end()){
      fNrHit[chID] = 1;
    }
    else{
      search->second++;
    }
  }
}

// ---- Finish --------------------------------------------------------
void KoaAnaSolidAngle::Finish()
{
  LOG(debug) << "Finish of KoaAnaSolidAngle";

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  Int_t detID, chID;
  for(auto& ch: fNrHit){
    chID = encoder->DecodeChannelID(ch.first, detID);
    switch(detID){
    case 0:
      {
        fSi1NrHit[chID] = ch.second;
        break;
      }
    case 1:
      {
        fSi2NrHit[chID] = ch.second;
        break;
      }
    case 2:
      {
        fGe1NrHit[chID] = ch.second;
        break;
      }
    case 3:
      {
        fGe2NrHit[chID] = ch.second;
        break;
      }
    default:
      break;
    }
  }

  //
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
    fOutputFile << ch_id << ", " <<  4*pi*nr/fMCEntryNo \
                << ", " << nr << ", " << fMCEntryNo << std::endl;
  }

  fOutputFile << "Si2 (solid angle of each channel):" << std::endl;
  ch_id=0;
  for(Long_t nr : fSi2NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " << 4*pi*nr/fMCEntryNo \
                << ", " << nr << ", " << fMCEntryNo << std::endl;
  }

  fOutputFile << "Ge1 (solid angle of each channel):" << std::endl;
  ch_id=0;
  for(Long_t nr : fGe1NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " << 4*pi*nr/fMCEntryNo \
                << ", " << nr << ", " << fMCEntryNo << std::endl;
  }

  fOutputFile << "Ge2 (solid angle of each channel):" << std::endl;
  ch_id=0;
  for(Long_t nr : fGe2NrHit){
    ch_id++;
    fOutputFile << ch_id << ", " << 4*pi*nr/fMCEntryNo \
                << ", " << nr << ", " << fMCEntryNo << std::endl;
  }
}

void KoaAnaSolidAngle::SetMCEntryNo(Long_t entryNr)
{
  fMCEntryFromExternal = kTRUE;
  fMCEntryNo = entryNr;
}

ClassImp(KoaAnaSolidAngle)
