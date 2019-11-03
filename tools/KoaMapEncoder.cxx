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
  fRecNrOfSensors = fRecDetIDRange[1] - fRecDetIDRange[0] + 1;

  fDetectorIDToVolName[4]="SensorSc1";
  fDetectorIDToVolName[5]="SensorSc2";
  fDetectorIDToVolName[6]="SensorSc3";
  fDetectorIDToVolName[7]="SensorSc4";
  fDetectorIDToVolName[8]="SensorSc5";
  fDetectorIDToVolName[9]="SensorSc6";
  fDetectorIDToVolName[10]="SensorSc7";
  fDetectorIDToVolName[11]="SensorSc8";
  fFwdDetIDRange[0]=4;
  fFwdDetIDRange[1]=11;
  fFwdNrOfSensors = fFwdDetIDRange[1] - fFwdDetIDRange[0] + 1;

  //-------------------------------------//
  fVolNameToDetectorID["SensorSi1"]=0;
  fVolNameToDetectorID["SensorSi2"]=1;
  fVolNameToDetectorID["SensorGe1"]=2;
  fVolNameToDetectorID["SensorGe2"]=3;

  fVolNameToDetectorID["SensorSc1"]=4;
  fVolNameToDetectorID["SensorSc2"]=5;
  fVolNameToDetectorID["SensorSc3"]=6;
  fVolNameToDetectorID["SensorSc4"]=7;
  fVolNameToDetectorID["SensorSc5"]=8;
  fVolNameToDetectorID["SensorSc6"]=9;
  fVolNameToDetectorID["SensorSc7"]=10;
  fVolNameToDetectorID["SensorSc8"]=11;

  //-------------------------------------//
  fDetectorIDToChNr[0]=48;
  fDetectorIDToChNr[1]=64;
  fDetectorIDToChNr[2]=32;
  fDetectorIDToChNr[3]=32;

  fDetectorIDToChNr[4]=1;
  fDetectorIDToChNr[5]=1;
  fDetectorIDToChNr[6]=1;
  fDetectorIDToChNr[7]=1;
  fDetectorIDToChNr[8]=1;
  fDetectorIDToChNr[9]=1;
  fDetectorIDToChNr[10]=1;
  fDetectorIDToChNr[11]=1;

  //-------------------------------------//
  for(int detID=fRecDetIDRange[0];detID<=fRecDetIDRange[1];detID++){
    for(int chID=0;chID<fDetectorIDToChNr[detID];chID++){
      fChIDs.emplace_back(EncodeChannelID(detID,chID));
    }
  }

  for(int detID=fFwdDetIDRange[0];detID<=fFwdDetIDRange[1];detID++){
    for(int chID=0;chID<fDetectorIDToChNr[detID];chID++){
      fChIDs.emplace_back(EncodeChannelID(detID,chID));
    }
  }

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

std::vector<Int_t> KoaMapEncoder::GetRecChIDs()
{
  std::vector<Int_t> ids;
  std::vector<Int_t> allIDs = GetChIDs();
  Int_t low, high; GetRecDetIDRange(low, high);
  Int_t detID;
  for ( auto id : allIDs ) {
    DecodeChannelID(id, detID);
    if( (detID >= low) && (detID <= high) ) {
      ids.emplace_back(id);
    }
  }
  return ids;
}

std::vector<Int_t> KoaMapEncoder::GetFwdChIDs()
{
  std::vector<Int_t> ids;
  std::vector<Int_t> allIDs = GetChIDs();
  Int_t low, high; GetFwdDetIDRange(low, high);
  Int_t detID;
  for ( auto id : allIDs ) {
    DecodeChannelID(id, detID);
    if( (detID >= low) && (detID <= high) ) {
      ids.emplace_back(id);
    }
  }
  return ids;
}

std::vector<Int_t> KoaMapEncoder::GetRecTdcChIDs()
{
  std::vector<Int_t> ids;
  for ( int i = 0; i < 48 ; i++ ) {
    ids.emplace_back(EncodeChannelID(0, i));
  }
  for ( int i = 0; i < 38 ; i++ ) {
    ids.emplace_back(EncodeChannelID(1, i));
  }

  return ids;
}
