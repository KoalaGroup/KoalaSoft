/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaGeoHandler source file                  -----
// -----                 Created 31/05/2019 by Y.ZHOU               -----
// -------------------------------------------------------------------------

#include "KoaGeoHandler.h"
#include "KoaMapEncoder.h"

#include "FairLogger.h"                 // for FairLogger, etc

#include "TGeoBBox.h"                   // for TGeoBBox
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TGeoNode.h"                   // for TGeoNode
#include "TGeoVolume.h"                 // for TGeoVolume
#include "TVirtualMC.h"                 // for TVirtualMC
#include "FairLogger.h"

#include <string.h>                     // for NULL, strlen, strncpy
#include <utility>                      // for pair

#define STRIPWIDTH 0.12                 // [cm]

using std::map;
using std::pair;

KoaGeoHandler::KoaGeoHandler(Bool_t isSimulation)
  : TObject(),
    fIsSimulation(isSimulation)
{
  fMapEncoder = KoaMapEncoder::Instance();
  fRecPath = "/cave_1/RecArm_0/RecArm_Vacuum_1/RecArm_Detectors_1/";
  fFwdPath = "TO BE DONE";

  Init();
}

Int_t KoaGeoHandler::InitMatrix()
{
  if(!fIsSimulation){
    Int_t low,high;
    TString volName;
    Double_t centor_local[3]={0,0,0};
    Double_t centor_global[3];

    // for recoil detector
    fMapEncoder->GetRecDetIDRange(low,high);
    for(int detId=low;detId <= high;detId++){
      volName = fMapEncoder->DetectorIDToVolName(detId);
      fRecDetPath[detId]= fRecPath + volName +"_1";
      NavigateTo(fRecDetPath[detId]);
      fRecDetMatrix[detId] = static_cast<TGeoHMatrix*>(gGeoManager->GetCurrentMatrix()->MakeClone());
      TGeoBBox* actBox = static_cast<TGeoBBox*>(gGeoManager->GetCurrentVolume()->GetShape());
      fRecDetDimension[detId] = actBox->GetDZ(); 

      RecLocalToGlobal(centor_local,centor_global,detId);
      fRecDetPosition[detId] = centor_global[2];
    }
    
    //--------------------------------//
    Int_t SumWidth;
    Int_t detId, detChId, detStripId;
    StripRange range;

    // Si1: 2-in-1 for the first 32 channels (16 ch)
    //      1-in-1 for the last 32 channels
    SumWidth = 0;
    detId = fMapEncoder->VolNameToDetectorID("SensorSi1");
    for(int ch=0;ch<16;ch++){
      low = SumWidth;
      SumWidth += 2;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    for(int ch=16;ch<48;ch++){
      low = SumWidth;
      SumWidth += 1;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    // Si2: 1-in-1 for all 64 channels
    SumWidth = 0;
    detId = fMapEncoder->VolNameToDetectorID("SensorSi2");
    for(int ch=0;ch<64;ch++){
      low = SumWidth;
      SumWidth += 1;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }

    // Ge1: 1-in-1 for the first 9 channels
    //      2-in-1 for next 12 channels (6 ch)
    //      3-in-1 for next 36 channels (12 ch)
    //      2-in-1 for next 10 channels (5 ch)
    SumWidth = 0;
    detId = fMapEncoder->VolNameToDetectorID("SensorGe1");
    for(int ch=0;ch<9;ch++){
      low = SumWidth;
      SumWidth += 1;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    for(int ch=9;ch<15;ch++){
      low = SumWidth;
      SumWidth += 2;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    for(int ch=15;ch<27;ch++){
      low = SumWidth;
      SumWidth += 3;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    for(int ch=27;ch<32;ch++){
      low = SumWidth;
      SumWidth += 2;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
  
    // Ge2: 2-in-1 for the first 60 channels (30 ch)
    //      3-in-1 for next 3 channels (1 ch)
    //      4-in-1for next 4 channels (1 ch)
    SumWidth = 0;
    detId = fMapEncoder->VolNameToDetectorID("SensorGe2");
    for(int ch=0;ch<30;ch++){
      low = SumWidth;
      SumWidth += 2;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    for(int ch=30;ch<31;ch++){
      low = SumWidth;
      SumWidth += 3;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    for(int ch=31;ch<32;ch++){
      low = SumWidth;
      SumWidth += 4;
      high = SumWidth;
      detChId = fMapEncoder->EncodeChannelID(detId, ch);

      range.lower = low*STRIPWIDTH - fRecDetDimension[detId];
      range.higher = high*STRIPWIDTH - fRecDetDimension[detId];
      range.center = (range.lower + range.higher)/2;
      fRecChIdToStripRange[detChId] = range;
    }
    // for fwd detector: TODO
  }
  return 1;
}

Int_t KoaGeoHandler::Init()
{
  //--------------------------------//
  Int_t SumWidth, low, high;
  Int_t detId, detChId, detStripId;
  StripRange range;

  // Si1: 2-in-1 for the first 32 channels (16 ch)
  //      1-in-1 for the last 32 channels
  SumWidth = 0;
  detId = fMapEncoder->VolNameToDetectorID("SensorSi1");
  for(int ch=0;ch<16;ch++){
    low = SumWidth;
    SumWidth += 2;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  for(int ch=16;ch<48;ch++){
    low = SumWidth;
    SumWidth += 1;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  // Si2: 1-in-1 for all 64 channels
  SumWidth = 0;
  detId = fMapEncoder->VolNameToDetectorID("SensorSi2");
  for(int ch=0;ch<64;ch++){
    low = SumWidth;
    SumWidth += 1;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }

  // Ge1: 1-in-1 for the first 9 channels
  //      2-in-1 for next 12 channels (6 ch)
  //      3-in-1 for next 36 channels (12 ch)
  //      2-in-1 for next 10 channels (5 ch)
  SumWidth = 0;
  detId = fMapEncoder->VolNameToDetectorID("SensorGe1");
  for(int ch=0;ch<9;ch++){
    low = SumWidth;
    SumWidth += 1;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  for(int ch=9;ch<15;ch++){
    low = SumWidth;
    SumWidth += 2;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  for(int ch=15;ch<27;ch++){
    low = SumWidth;
    SumWidth += 3;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  for(int ch=27;ch<32;ch++){
    low = SumWidth;
    SumWidth += 2;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  
  // Ge2: 2-in-1 for the first 60 channels (30 ch)
  //      3-in-1 for next 3 channels (1 ch)
  //      4-in-1for next 4 channels (1 ch)
  SumWidth = 0;
  detId = fMapEncoder->VolNameToDetectorID("SensorGe2");
  for(int ch=0;ch<30;ch++){
    low = SumWidth;
    SumWidth += 2;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  for(int ch=30;ch<31;ch++){
    low = SumWidth;
    SumWidth += 3;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }
  for(int ch=31;ch<32;ch++){
    low = SumWidth;
    SumWidth += 4;
    high = SumWidth;
    detChId = fMapEncoder->EncodeChannelID(detId, ch);

    for(int strip=low; strip<high;strip++){
      detStripId = fMapEncoder->EncodeChannelID(detId, strip);
      fRecStripIdToChId[detStripId] = detChId;
    }
  }

  //----------------------------------//
  InitMatrix();
}

Int_t KoaGeoHandler::GetRecDetId(const char* volName)
{
  return fMapEncoder->VolNameToDetectorID(volName);
}

TString KoaGeoHandler::GetRecDetName(Int_t detId)
{
  return fMapEncoder->DetectorIDToVolName(detId);
}

TString KoaGeoHandler::GetRecDetPath(Int_t detId)
{
  TString path;
  if(!fIsSimulation){
    path = fRecDetPath[detId];
  }
  else{
    LOG(fatal) << "This method is only available in simulation task. Set fIsSimulation to kFALSE to use this method";
  }
  return path;
}

void KoaGeoHandler::RecLocalToGlobal(Double_t* local, Double_t* global, Int_t detID)
{
  TGeoHMatrix* matrix = fRecDetMatrix[detID];
  matrix->LocalToMaster(local, global);
}

void KoaGeoHandler::RecGlobalToLocal(Double_t* global, Double_t* local, Int_t detID)
{
  TGeoHMatrix* matrix = fRecDetMatrix[detID];
  matrix->MasterToLocal(global,local);
}

Int_t KoaGeoHandler::RecPositionToDetCh(Double_t* hitPos, Int_t detID)
{
  Int_t strip_ch = (hitPos[2] + fRecDetDimension[detID])/STRIPWIDTH;
  return fRecStripIdToChId[fMapEncoder->EncodeChannelID(detID,strip_ch)];
}

Double_t KoaGeoHandler::RecDetChToPosition(Int_t detChId, Double_t& lower, Double_t& higher)
{
  StripRange range = fRecChIdToStripRange[detChId];
  lower = range.lower;
  higher = range.higher;
  return range.center;
}


void KoaGeoHandler::NavigateTo(TString volName)
{
  if (fIsSimulation) {
    LOG(fatal)<<"This methode is not supported in simulation mode";
  } else {
    if(!gGeoManager->cd(volName.Data()))
      LOG(fatal)<<"Node do not exists: "<<volName.Data();
  }
}

KoaGeoHandler::KoaGeoHandler(const KoaGeoHandler& rhs) :
  TObject(rhs)
{
  fMapEncoder = rhs.fMapEncoder;
  fRecPath = rhs.fRecPath;
  fFwdPath = rhs.fFwdPath;

  fIsSimulation = rhs.fIsSimulation;
  fRecDetPath   = rhs.fRecDetPath;
  fRecDetMatrix = rhs.fRecDetMatrix;
  fRecDetPosition = rhs.fRecDetPosition;
  fRecDetDimension = rhs.fRecDetDimension;
  fRecStripIdToChId = rhs.fRecStripIdToChId;
  fRecChIdToStripRange = rhs.fRecChIdToStripRange;
}

ClassImp(KoaGeoHandler)
