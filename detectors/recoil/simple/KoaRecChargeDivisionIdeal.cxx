/********************************************************************************
 *  Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH      *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRecChargeDivisionIdeal.h"
#include "KoaGeoHandler.h"
#include "TClonesArray.h"
#include "KoaRecDigi.h"
#include "KoaRecPoint.h"
#include "FairRootManager.h"
#include "FairLogger.h"
#include "TVirtualMC.h"

// ---- Default constructor -------------------------------------------
KoaRecChargeDivisionIdeal::KoaRecChargeDivisionIdeal()
  :FairTask("KoaRecChargeDivisionIdeal"),
   fGeoHandler(nullptr),
   fSaveOutput(true)
{
  LOG(debug) << "Defaul Constructor of KoaRecChargeDivisionIdeal";
}

// ---- Destructor ----------------------------------------------------
KoaRecChargeDivisionIdeal::~KoaRecChargeDivisionIdeal()
{
  LOG(debug) << "Destructor of KoaRecChargeDivisionIdeal";

  if ( fDigis ) {
    fDigis->Delete();
    delete fDigis;
  }

  delete fGeoHandler;
}

// ----  Initialisation  ----------------------------------------------
void KoaRecChargeDivisionIdeal::SetParContainers()
{
  LOG(debug) << "SetParContainers of KoaRecChargeDivisionIdeal";
  // Load all necessary parameter containers from the runtime data base
  /*
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  <KoaRecDigitizationIdealDataMember> = (<ClassPointer>*)
    (rtdb->getContainer("<ContainerName>"));
  */
}

// ---- Init ----------------------------------------------------------
InitStatus KoaRecChargeDivisionIdeal::Init()
{
  LOG(debug) << "Initilization of KoaRecChargeDivisionIdeal";

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
  if (fOutputName.empty()) LOG(fatal) << "No output branch name set";
  fDigis = new TClonesArray("KoaRecDigi");
  ioman->Register(fOutputName.data(),"KoaRec",fDigis,fSaveOutput);
  // ioman->RegisterAny(fOutputName.data(),fDigis,fSaveOutput);
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
InitStatus KoaRecChargeDivisionIdeal::ReInit()
{
  LOG(debug) << "Initilization of KoaRecChargeDivisionIdeal";

  Reset();

  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void KoaRecChargeDivisionIdeal::Exec(Option_t* /*option*/)// in keV
{
  LOG(debug) << "Exec of KoaRecChargeDivisionIdeal";// in keV

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
void KoaRecChargeDivisionIdeal::Finish()
{
  LOG(debug) << "Finish of KoaRecChargeDivisionIdeal";

  Reset();
}

// ---- Reset --------------------------------------------------------
void KoaRecChargeDivisionIdeal::Reset()
{
  LOG(debug) << "Reset of KoaRecChargeDivisionIdeal";

  fDigis->Clear();
  fFiredStrips.clear();
}

// ---- GetFiredStrips --------------------------------------------------------
// Even charge distribution along the track
void KoaRecChargeDivisionIdeal::FillFiredStrips(KoaRecPoint* McPoint)
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
  chID_in = fGeoHandler->RecLocalPositionToDetCh(local_in, detID);

  fGeoHandler->GlobalToLocal(global_out, local_out, detID);
  chID_out = fGeoHandler->RecLocalPositionToDetCh(local_out, detID);


  Double_t eLoss = 1e6*McPoint->GetEnergyLoss();// in keV
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
    
    if (step > 64) {
      LOG(info) << "KoaRecChargeDivisionIdeal: Unexpected large step " << step << " in Sensor " << detID
                 << "\t chID_in: " << chID_in << "/" << global_in[2] << "/" << local_in[2]
                 << "\t chID_out: " << chID_out << "/" << global_out[2] << "/" << local_out[2];
      return;
    }

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

void KoaRecChargeDivisionIdeal::FillFiredStrip(Int_t DetID, Double_t Timestamp, Double_t Charge)
{
  auto search = fFiredStrips.find(DetID);
  if(search != fFiredStrips.end()){
    if(Timestamp < search->second.fTimestamp){
      search->second.fTimestamp = Timestamp;
    }
    search->second.fCharge+=Charge;
  }
  else{
    fFiredStrips.emplace(std::piecewise_construct,
                         std::forward_as_tuple(DetID),
                         std::forward_as_tuple(Timestamp, Charge));
  }
}

// ---- AddDigis --------------------------------------------------------
void KoaRecChargeDivisionIdeal::AddDigis()
{
  Int_t index =0;
  for(auto strip = fFiredStrips.begin(); strip != fFiredStrips.end(); strip++){
    KoaRecDigi* digi = new ((*fDigis)[index++]) KoaRecDigi();
    digi->SetDetectorID(strip->first);
    digi->SetCharge(strip->second.fCharge);
    digi->SetTimeStamp(strip->second.fTimestamp);
  }
}

ClassImp(KoaRecChargeDivisionIdeal)
