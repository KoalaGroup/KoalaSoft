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
  fFwdPath = "/cave_1/FwdArm_0/FwdArm_Vacuum_1/FwdArm_Detectors_1/";

  Init();
}

// Init fDetMatrix, fRecDetDimension, fRecDetPosition, fRecChIdToStripRange
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
      NavigateTo(fDetPath[detId]);
      fDetMatrix[detId] = static_cast<TGeoHMatrix*>(gGeoManager->GetCurrentMatrix()->MakeClone());
      TGeoBBox* actBox = static_cast<TGeoBBox*>(gGeoManager->GetCurrentVolume()->GetShape());
      fRecDetDimension[detId] = actBox->GetDZ(); 

      fDetMatrix[detId]->LocalToMaster(centor_local, centor_global);
      fRecDetPosition[detId] = centor_global[2];
    }
    
    // for fwd detector
    // WARNING: only sc1 and sc2 are recorded
    fMapEncoder->GetFwdDetIDRange(low,high);
    for(int detId=low;detId <= low+1;detId++){
      NavigateTo(fDetPath[detId]);
      fDetMatrix[detId] = static_cast<TGeoHMatrix*>(gGeoManager->GetCurrentMatrix()->MakeClone());
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
  }
  return 1;
}

// init: fRecStripIdToChId, fDetPath
Int_t KoaGeoHandler::Init()
{
  //--------------------------------//
  Int_t SumWidth, low, high;
  Int_t detId, detChId, detStripId;
  StripRange range;

  //--------------------------------//
  // Init fRecStripIdToChId
  //--------------------------------//
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
  // Init fDetPath
  //----------------------------------//
  TString volName;

  // for recoil detector
  fMapEncoder->GetRecDetIDRange(low,high);
  for(int id=low;id <= high;id++){
    volName = fMapEncoder->DetectorIDToVolName(id);
    fDetPath[id]= fRecPath + volName +"_1";
  }
  
  // for fwd detector
  // WARNING: only sc1 and sc2 are recorded
  fMapEncoder->GetFwdDetIDRange(low,high);
  for(int id=low;id <= low+1;id++){
    volName = fMapEncoder->DetectorIDToVolName(id);
    fDetPath[id]= fFwdPath + volName +"_1";
  }

  //----------------------------------//
  InitMatrix();
}

Int_t KoaGeoHandler::GetDetIdByName(const char* volName)
{
  return fMapEncoder->VolNameToDetectorID(volName);
}

TString KoaGeoHandler::GetDetNameById(Int_t detId)
{
  return fMapEncoder->DetectorIDToVolName(detId);
}

TString KoaGeoHandler::GetDetPathById(Int_t detId)
{
  return fDetPath[detId];
}

TString KoaGeoHandler::GetDetPathByName(const char* volName)
{
  Int_t id = GetDetIdByName(volName);
  return fDetPath[id];
}

void KoaGeoHandler::LocalToGlobal(Double_t* local, Double_t* global, Int_t detID)
{
  TGeoHMatrix* matrix = fDetMatrix[detID];
  matrix->LocalToMaster(local, global);
}

void KoaGeoHandler::GlobalToLocal(Double_t* global, Double_t* local, Int_t detID)
{
  TGeoHMatrix* matrix = fDetMatrix[detID];
  matrix->MasterToLocal(global,local);
}

Int_t KoaGeoHandler::RecPositionToDetCh(Double_t* hitPos, Int_t detID)
{
  Int_t strip_ch = (hitPos[2] + fRecDetDimension[detID])/STRIPWIDTH;
  strip_ch = fMapEncoder->EncodeChannelID(detID,strip_ch);
  auto search = fRecStripIdToChId.find(strip_ch);
  if(search == fRecStripIdToChId.end())
    strip_ch--;
  return fRecStripIdToChId[strip_ch];
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
  if (!fIsSimulation) {
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
  fDetPath   = rhs.fDetPath;
  fDetMatrix = rhs.fDetMatrix;
  fRecDetPosition = rhs.fRecDetPosition;
  fRecDetDimension = rhs.fRecDetDimension;
  fRecStripIdToChId = rhs.fRecStripIdToChId;
  fRecChIdToStripRange = rhs.fRecChIdToStripRange;
}

ClassImp(KoaGeoHandler)
