/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 KoaMapEncoder header file                    ------
// -----                 Created 14/06/19  by Y. Zhou                 -----
// -------------------------------------------------------------------------


/** KoaMapEncoder.h
 ** Helper class to encode the channel id of different sensors in to a single interger
 ** as follows:
 **    id = (detector_id << 24) + (channel_id)
 **
 ** detector_id for different sensors:
 **    SensorSi1 : 0
 **    SensorSi2 : 1
 **    SensorGe1 : 2
 **    SensorGe2 : 3
 **    SensorSc1 : 4
 **    SensorSc2 : 5
 ** 
 ** channel_id starts from 0 for each sensor.
 **
 ** @author Y.Zhou <y.zhou@fz-juelich.de>
 **/

#ifndef KOAMAPENCODER_H
#define KOAMAPENCODER_H 1

#include "TString.h"
#include "TObject.h"
#include <map>

class KoaMapEncoder : public TObject
{
 public:
  ~KoaMapEncoder();

  Int_t VolNameToDetectorID(const char* volName);
  const char* DetectorIDToVolName(Int_t det);

  Int_t EncodeChannelID(const char* volName, Int_t ch);
  Int_t EncodeChannelID(Int_t det, Int_t ch);

  Int_t DecodeChannelID(Int_t id, Int_t& det); // return the channel id
  Int_t DecodeChannelID(Int_t id, TString& volName);

  void  GetRecDetIDRange(Int_t& low, Int_t& high);
  void  GetFwdDetIDRange(Int_t& low, Int_t& high);

  static KoaMapEncoder* Instance()
  {
    if(!fpInstance)
      fpInstance = new KoaMapEncoder();
    return fpInstance;
  }

 private:
  KoaMapEncoder();
  void Init();

  std::map<Int_t, TString> fDetectorIDToVolName;
  std::map<TString, Int_t> fVolNameToDetectorID;
  Int_t fRecDetIDRange[2];
  Int_t fFwdDetIDRange[2];

  static KoaMapEncoder *fpInstance;
};

#endif
