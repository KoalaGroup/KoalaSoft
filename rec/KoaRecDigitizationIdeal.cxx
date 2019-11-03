/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecDigitizationIdeal.h"
#include "KoaGeoHandler.h"
#include "TClonesArray.h"
#include "KoaRecDigi.h"
#include "KoaRecPoint.h"
#include "FairRootManager.h"
#include "FairLogger.h"
#include "TVirtualMC.h"

// ---- Default constructor -------------------------------------------
KoaRecDigitizationIdeal::KoaRecDigitizationIdeal()
  :FairTask("KoaRecDigitizationIdeal"),
   fGeoHandler(nullptr)
{
  LOG(debug) << "Defaul Constructor of KoaRecDigitizationIdeal";
}

// ---- Destructor ----------------------------------------------------
KoaRecDigitizationIdeal::~KoaRecDigitizationIdeal()
{
  LOG(debug) << "Destructor of KoaRecDigitizationIdeal";

  if ( fDigis ) {
    fDigis->Delete();
    delete fDigis;
  }

  delete fGeoHandler;
}

// ----  Initialisation  ----------------------------------------------
void KoaRecDigitizationIdeal::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecDigitizationIdeal";
  // Load all necessary parameter containers from the runtime data base
  /*
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  <KoaRecDigitizationIdealDataMember> = (<ClassPointer>*)
    (rtdb->getContainer("<ContainerName>"));
  */
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecDigitizationIdeal::Init()
{
  LOG(debug) << "Initilization of KoaRecDigitizationIdeal";

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) LOG(fatal) << "No FairRootManager";

  fPoints = static_cast<TClonesArray*>(ioman->GetObject("KoaRecPoint"));
  if ( ! fPoints ) {
    LOG(error) << "No input KoaRecPoint array";
    return kERROR;
  }
  // Create the TClonesArray for the output data and register
  // it in the IO manager
  
  fDigis = new TClonesArray("KoaRecDigi", 100);
  ioman->Register("KoaRecDigi","KoaRec",fDigis,kTRUE);
  // if(!gMC->IsMT()){
  //   ioman->Register("KoaRecDigi","KoaRec",fDigis,kTRUE);
  // }
  // else{
  //   ioman->RegisterAny("KoaRecDigi",fDigis,kTRUE);
  // }

  // Do whatever else is needed at the initilization stage
  // Create histograms to be filled
  // initialize variables

  // KoaGeoHandler uses gGeoManager internally, so it must be constructed after parameter input
  // gGeoManager is only available after parameter reading from BaseParSet
  fGeoHandler = new KoaGeoHandler(kFALSE);

  return kSUCCESS;

}

// ---- ReInit  -------------------------------------------------------
InitStatus KoaRecDigitizationIdeal::ReInit()
{
  LOG(debug) << "Initilization of KoaRecDigitizationIdeal";

  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecDigitizationIdeal::Exec(Option_t* /*option*/)
{
  LOG(debug) << "Exec of KoaRecDigitizationIdeal";

  Reset();

  //
  Int_t fNrPoints = fPoints->GetEntriesFast();
  for(Int_t iPoint =0; iPoint<fNrPoints; iPoint++){
    KoaRecPoint* curPoint = (KoaRecPoint*)fPoints->At(iPoint);

    FillFiredStrips(curPoint);
  }
  AddDigis();
}

// ---- Finish --------------------------------------------------------
void KoaRecDigitizationIdeal::Finish()
{
  LOG(debug) << "Finish of KoaRecDigitizationIdeal";

}

// ---- Reset --------------------------------------------------------
void KoaRecDigitizationIdeal::Reset()
{
  LOG(debug) << "Reset of KoaRecDigitizationIdeal";

  fDigis->Clear();
  fFiredStrips.clear();
}

// ---- GetFiredStrips --------------------------------------------------------
// Even charge distribution along the track
void KoaRecDigitizationIdeal::FillFiredStrips(KoaRecPoint* McPoint)
{
  //
  Double_t global_in[3], global_out[3];
  Double_t local_in[3], local_out[3];
  Int_t detID = McPoint->GetDetectorID();

  global_in[0]=McPoint->GetX();
  global_in[1]=McPoint->GetY();
  global_in[2]=McPoint->GetZ();

  global_out[0]=McPoint->GetXEnd();
  global_out[1]=McPoint->GetYEnd();
  global_out[2]=McPoint->GetZEnd();

  Int_t chID_in, chID_out;
  fGeoHandler->GlobalToLocal(global_in, local_in, detID);
  chID_in = fGeoHandler->RecPositionToDetCh(local_in, detID);

  fGeoHandler->GlobalToLocal(global_out, local_out, detID);
  chID_out = fGeoHandler->RecPositionToDetCh(local_out, detID);


  Double_t eLoss = McPoint->GetEnergyLoss();
  Double_t timestamp = McPoint->GetTime();
  if(chID_out == chID_in){
    FillFiredStrip(chID_in, timestamp, eLoss);
  }
  else{
    Int_t start = chID_in;
    Int_t stop = chID_out;
    Double_t point_start = local_in[2];
    Double_t point_stop  = local_out[2];
    if(chID_out < chID_in){
      start = chID_out;
      stop = chID_in;
      point_start = local_out[2];
      point_stop  = local_in[2];
    }
    //
    Double_t track_len = point_stop - point_start;
    Int_t step = stop - start;
    Double_t point_low,point_high,point_temp;
    
    point_low = point_start;
    for(int segid=0;segid<step;segid++){
      fGeoHandler->RecDetChToPosition(start+segid, point_temp, point_high);
      FillFiredStrip(start+segid, timestamp, (point_high-point_low)/track_len*eLoss);

      point_low = point_high;
    }

    // last segmentation
    FillFiredStrip(stop, timestamp, (point_stop-point_low)/track_len*eLoss);
  }
}

void KoaRecDigitizationIdeal::FillFiredStrip(Int_t DetID, Double_t Timestamp, Double_t Charge)
{
  auto search = fFiredStrips.find(DetID);
  if(search != fFiredStrips.end()){
    if(Timestamp < search->second.fTimestamp){
      search->second.fTimestamp = Timestamp;
    }
    search->second.fCharge+=Charge;
  }
  else{
    KoaRecStrip strip;
    strip.fTimestamp = Timestamp;
    strip.fCharge = Charge;
    fFiredStrips.insert(std::make_pair(DetID, strip));
  }
}

// ---- AddDigis --------------------------------------------------------
void KoaRecDigitizationIdeal::AddDigis()
{
  Int_t index =0;
  for(auto strip = fFiredStrips.begin(); strip != fFiredStrips.end(); strip++){
    KoaRecDigi* digi = new ((*fDigis)[index++]) KoaRecDigi();
    digi->SetDetectorID(strip->first);
    digi->SetCharge(strip->second.fCharge);
    digi->SetTimeStamp(strip->second.fTimestamp);
  }
}

ClassImp(KoaRecDigitizationIdeal)
