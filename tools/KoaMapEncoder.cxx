/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "KoaMapEncoder.h"
#include "FairLogger.h"

KoaMapEncoder* KoaMapEncoder::fpInstance = nullptr;

KoaMapEncoder::KoaMapEncoder()
{
  Init();
}

KoaMapEncoder::~KoaMapEncoder()
{
  
}

void KoaMapEncoder::Init()
{
  //-------------------------------------//
  fDetectorIDToVolName[0]="SensorSi1";
  fDetectorIDToVolName[1]="SensorSi2";
  fDetectorIDToVolName[2]="SensorGe1";
  fDetectorIDToVolName[3]="SensorGe2";
  fRecDetIDRange[0]=0;
  fRecDetIDRange[1]=3;

  fDetectorIDToVolName[4]="SensorSc1";
  fDetectorIDToVolName[5]="SensorSc2";
  fFwdDetIDRange[0]=4;
  fFwdDetIDRange[1]=5;

  //-------------------------------------//
  fVolNameToDetectorID["SensorSi1"]=0;
  fVolNameToDetectorID["SensorSi2"]=1;
  fVolNameToDetectorID["SensorGe1"]=2;
  fVolNameToDetectorID["SensorGe2"]=3;

  fVolNameToDetectorID["SensorSc1"]=4;
  fVolNameToDetectorID["SensorSc2"]=5;
}


Int_t KoaMapEncoder::VolNameToDetectorID(const char* volName)
{
  auto search = fVolNameToDetectorID.find(volName);
  if(search == fVolNameToDetectorID.end()){
    LOG(fatal) << "No detector volName: " << volName;
  }
  return search->second;
}

const char* KoaMapEncoder::DetectorIDToVolName(Int_t det)
{
  auto search = fDetectorIDToVolName.find(det);
  if(search == fDetectorIDToVolName.end()){
    LOG(fatal) << "No detector ID: " << det;
  }
  return search->second;
}

Int_t KoaMapEncoder::EncodeChannelID(const char* volName, Int_t ch)
{
  return EncodeChannelID(VolNameToDetectorID(volName),ch);
}

Int_t KoaMapEncoder::EncodeChannelID(Int_t det, Int_t ch)
{
  return (det<<24)+ch;
}

Int_t KoaMapEncoder::DecodeChannelID(Int_t id, Int_t& det)
{
  det = (id>>24) & 0xFF;
  return (id&0xFFFFFF);
}

Int_t KoaMapEncoder::DecodeChannelID(Int_t id, TString& volName)
{
  Int_t det =-1;
  Int_t ch = DecodeChannelID(id,det);
  volName = DetectorIDToVolName(det);

  return ch;
}

void KoaMapEncoder::GetRecDetIDRange(Int_t& low, Int_t& high)
{
  low = fRecDetIDRange[0];
  high= fRecDetIDRange[1];
}

void KoaMapEncoder::GetFwdDetIDRange(Int_t& low, Int_t& high)
{
  low = fFwdDetIDRange[0];
  high= fFwdDetIDRange[1];
}
