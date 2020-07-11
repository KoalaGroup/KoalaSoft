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
#include "TGeoTrd1.h"
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

      std::vector<Int_t> stripIds;
      for(int strip=low; strip<high;strip++){
        detStripId = fMapEncoder->EncodeChannelID(detId, strip);
        fStripIds.emplace_back(detStripId);

        range.lower = strip*STRIPWIDTH - fRecDetDimension[detId];
        range.higher = (strip+1)*STRIPWIDTH - fRecDetDimension[detId];
        range.center = (range.lower + range.higher)/2;
        fRecStripIdToStripRange[detStripId] = range;

        stripIds.emplace_back(detStripId);
      }
      fChIdToStripIds[detChId] = stripIds;
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

Double_t KoaGeoHandler::GetDetPositionById(Int_t detId)
{
  Int_t low, high;
  fMapEncoder->GetRecDetIDRange(low, high);

  NavigateTo(fDetPath[detId]);
  Double_t local_pos[3] = {0};
  Double_t global_pos[3] = {0};
  Double_t position;

  if ( detId > high ) { // for fwd
    TGeoTrd1* actBox = static_cast<TGeoTrd1*>(gGeoManager->GetCurrentVolume()->GetShape());
    local_pos[1] = -actBox->GetDy(); 
    LocalToGlobal(local_pos, global_pos, detId);
    position = global_pos[2];
  }
  else { // for recoil
    TGeoBBox* actBox = static_cast<TGeoBBox*>(gGeoManager->GetCurrentVolume()->GetShape());
    local_pos[0] = -actBox->GetDX(); 
    LocalToGlobal(local_pos, global_pos, detId);
    position = global_pos[0];
  }

  return position;
}

Double_t KoaGeoHandler::GetDetPositionByName(const char* volName)
{
  Int_t detId = GetDetIdByName(volName);
  return GetDetPositionById(detId);
}

void KoaGeoHandler::GetDetBoundaryById(Int_t detId, Double_t& lower, Double_t& higher)
{
  Int_t id_low, id_high;
  fMapEncoder->GetRecDetIDRange(id_low, id_high);

  NavigateTo(fDetPath[detId]);
  Double_t local_pos[3] = {0};
  Double_t global_pos[3] = {0};

  if ( detId > id_high ) { // for fwd
    TGeoTrd1* actBox = static_cast<TGeoTrd1*>(gGeoManager->GetCurrentVolume()->GetShape());

    local_pos[2] = -actBox->GetDz(); 
    LocalToGlobal(local_pos, global_pos, detId);
    lower = global_pos[0];

    local_pos[2] = actBox->GetDz(); 
    LocalToGlobal(local_pos, global_pos, detId);
    higher = global_pos[0];
  }
  else { // for recoil
    TGeoBBox* actBox = static_cast<TGeoBBox*>(gGeoManager->GetCurrentVolume()->GetShape());

    local_pos[2] = -actBox->GetDZ(); 
    LocalToGlobal(local_pos, global_pos, detId);
    lower = global_pos[2];

    local_pos[2] = actBox->GetDZ(); 
    LocalToGlobal(local_pos, global_pos, detId);
    higher = global_pos[2];
  }
}

void KoaGeoHandler::GetDetBoundaryByName(const char* volName, Double_t& lower, Double_t& higher)
{
  Int_t detId = GetDetIdByName(volName);
  GetDetBoundaryById(detId, lower, higher);
}

std::vector<TVector3> KoaGeoHandler::GetDetBoundaryPointsById(Int_t detId)
{
  Int_t id_low, id_high;
  fMapEncoder->GetRecDetIDRange(id_low, id_high);

  //
  NavigateTo(fDetPath[detId]);
  Double_t local_pos[3] = {0};
  Double_t global_pos[3] = {0};

  std::vector<TVector3> boundaryPoints;
  if ( detId > id_high ) { // for fwd
    TGeoTrd1* actBox = static_cast<TGeoTrd1*>(gGeoManager->GetCurrentVolume()->GetShape());
    Double_t dxlow = actBox->GetDx1();
    Double_t dxhigh = actBox->GetDx2();
    Double_t dy = actBox->GetDy();
    Double_t dz = actBox->GetDz();

    // point 1:
    local_pos[0] = dxlow;
    local_pos[1] = -dy;
    local_pos[2] = -dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);

    // point 2:
    local_pos[0] = dxhigh;
    local_pos[1] = -dy;
    local_pos[2] = dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);

    // point 3:
    local_pos[0] = -dxhigh;
    local_pos[1] = -dy;
    local_pos[2] = dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);

    // point 4:
    local_pos[0] = -dxlow;
    local_pos[1] = -dy;
    local_pos[2] = -dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);
  }
  else {
    TGeoBBox* actBox = static_cast<TGeoBBox*>(gGeoManager->GetCurrentVolume()->GetShape());
    Double_t dx = actBox->GetDX();
    Double_t dy = actBox->GetDY();
    Double_t dz = actBox->GetDZ();

    // point 1:
    local_pos[0] = -dx;
    local_pos[1] = -dy;
    local_pos[2] = -dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);

    // point 2:
    local_pos[0] = -dx;
    local_pos[1] = -dy;
    local_pos[2] = dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);

    // point 3:
    local_pos[0] = -dx;
    local_pos[1] = dy;
    local_pos[2] = dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);

    // point 4:
    local_pos[0] = -dx;
    local_pos[1] = dy;
    local_pos[2] = -dz; 
    LocalToGlobal(local_pos, global_pos, detId);
    boundaryPoints.emplace_back(global_pos);
  }

  return boundaryPoints;
}

std::vector<TVector3> KoaGeoHandler::GetDetBoundaryPointsByName(const char* volName)
{
  Int_t detId = GetDetIdByName(volName);
  return GetDetBoundaryPointsById(detId);
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

Int_t KoaGeoHandler::RecLocalPositionToDetCh(Double_t* hitPos, Int_t detID)
{
  Int_t strip_ch = (hitPos[2] + fRecDetDimension[detID])/STRIPWIDTH;
  strip_ch = fMapEncoder->EncodeChannelID(detID,strip_ch);
  auto search = fRecStripIdToChId.find(strip_ch);
  if(search == fRecStripIdToChId.end())
    strip_ch--;

  return fRecStripIdToChId[strip_ch];
}

Int_t KoaGeoHandler::RecGlobalPositionToDetCh(Double_t* hitPos, Int_t detID)
{
  Double_t local_pos[3];
  GlobalToLocal(hitPos, local_pos, detID);

  return RecLocalPositionToDetCh(local_pos, detID);
}

Double_t KoaGeoHandler::RecDetChToPosition(Int_t detChId, Double_t& lower, Double_t& higher)
{
  StripRange range = fRecChIdToStripRange[detChId];
  lower = range.lower;
  higher = range.higher;
  return range.center;
}

Double_t KoaGeoHandler::RecDetStripToPosition(Int_t stripId, Double_t& lower, Double_t& higher)
{
  StripRange range = fRecStripIdToStripRange[stripId];
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
