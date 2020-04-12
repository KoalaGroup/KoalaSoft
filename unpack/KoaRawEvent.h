#ifndef KOA_RAW_EVENT_H
#define KOA_RAW_EVENT_H

#include <map>
#include <utility>
#include "KoaMapEncoder.h"

constexpr Int_t UNDER_THRESHOLD = -5;
constexpr Int_t ADC_OVERFLOW = 0x2000;
constexpr Int_t QDC_OVERFLOW = 0x1000;

/* Raw Event format after decoding.
 * Since it's an unamed class, it can only be registered as a tree branch through:
 * FairRootManager->RegisterAny() but not FairRootManager->Register()
 */
class KoaRawEvent
{
public:
  // Amplitudes
  Int_t     Si1A[48];
  Int_t     Si2A[64];
  Int_t     Ge1A[32];
  Int_t     Ge2A[32];
  Int_t     RecRearA[4];
  Int_t     FwdA[8];

  // Timestamps
  Float_t   Si1T[48];// unit: ns
  Float_t   Si2T[64];// unit: ns
  Float_t   Ge1T[32];// unit: ns
  Float_t   Ge2T[32];// unit: ns
  Float_t   RecRearT[4];// unit: ns
  Float_t   FwdT[8];// unit: ns

  // Mxdc32 Timestamp
  Long64_t  Timestamp; // frq of VME bus, unit: 25 ns

public:
  inline std::map<Int_t, Int_t*> GetAmplitudeValueMap() const;
  inline std::map<Int_t, Int_t*> GetRecAmplitudeValueMap() const;
  inline std::map<Int_t, Int_t*> GetFwdAmplitudeValueMap() const;
  inline std::map<Int_t, Int_t*> GetRecRearAmplitudeValueMap() const;

  inline std::map<Int_t, Float_t*> GetTimeValueMap() const;
  inline std::map<Int_t, Float_t*> GetRecTimeValueMap() const;
  inline std::map<Int_t, Float_t*> GetFwdTimeValueMap() const;
  inline std::map<Int_t, Float_t*> GetRecRearTimeValueMap() const;

  ClassDef(KoaRawEvent, 1)
};

inline std::map<Int_t, Int_t*> KoaRawEvent::GetAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(id, (Int_t*)Si1A+i);
    // value_map.emplace(std::make_pair(id, (Int_t*)Si1A+i));
    // value_map.emplace(std::make_pair<Int_t,const Int_t*>(id, Si1A+i));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    // value_map.emplace(id, Si2A+i);
    value_map.emplace(std::make_pair(id, (Int_t*)Si2A+i));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    // value_map.emplace(id, Ge1A+i);
    value_map.emplace(std::make_pair(id, (Int_t*)Ge1A+i));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    // value_map.emplace(id, Ge2A+i);
    value_map.emplace(std::make_pair(id, (Int_t*)Ge2A+i));
  }

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Int_t*)FwdA+i ));
  }

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Int_t*)RecRearA+i ));
  }

  return value_map;
}

inline std::map<Int_t, Int_t*> KoaRawEvent::GetRecAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Si1A+i ));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Si2A+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Ge1A+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    value_map.emplace(std::make_pair( id, (Int_t*)Ge2A+i ));
  }

  return value_map;
}

inline std::map<Int_t, Int_t*> KoaRawEvent::GetFwdAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Int_t*)FwdA+i ));
  }

  return value_map;
}

inline std::map<Int_t, Int_t*> KoaRawEvent::GetRecRearAmplitudeValueMap() const
{
  //
  std::map<Int_t, Int_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Int_t*)RecRearA+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si1T+i ));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si2T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge1T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge2T+i ));
  }

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Float_t*)FwdT+i ));
  }

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Float_t*)RecRearT+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetRecTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_low, rec_high;
  encoder->GetRecDetIDRange(rec_low, rec_high);

  // recoil front
  for( int i =0; i<48; i++) {
    auto id = encoder->EncodeChannelID(rec_low, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si1T+i ));
  }
  for( int i =0; i<64; i++) {
    auto id = encoder->EncodeChannelID(rec_low+1, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Si2T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+2, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge1T+i ));
  }
  for( int i =0; i<32; i++) {
    auto id = encoder->EncodeChannelID(rec_low+3, i);
    value_map.emplace(std::make_pair( id, (Float_t*)Ge2T+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetFwdTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);

  // fwd 
  for( int i =0; i<8; i++) {
    auto id = encoder->EncodeChannelID(fwd_low+i, 0);
    value_map.emplace(std::make_pair( id, (Float_t*)FwdT+i ));
  }

  return value_map;
}

inline std::map<Int_t, Float_t*> KoaRawEvent::GetRecRearTimeValueMap() const
{
  //
  std::map<Int_t, Float_t*> value_map;

  // get encoder
  auto encoder = KoaMapEncoder::Instance();
  Int_t rec_rear = encoder->GetRecRearID();

  // recoil rear
  for( int i =0; i<4; i++) {
    auto id = encoder->EncodeChannelID(rec_rear, i);
    value_map.emplace(std::make_pair( id, (Float_t*)RecRearT+i ));
  }

  return value_map;
}

#endif
