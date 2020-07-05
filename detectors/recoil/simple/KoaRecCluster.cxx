#include "KoaRecCluster.h"
#include "KoaRecDigi.h"
#include "KoaGeoHandler.h"
#include "KoaMapEncoder.h"
#include "FairLogger.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iterator>

KoaRecCluster::KoaRecCluster()
  : fDetId(-1),
    fNrOfDigis(0),
    fIds{ -1 },
    fEnergies{ -1 },
    fTimestamps{ -1 },
    fThreshold(0),
    fGeoHandler(nullptr)
{
  
}

KoaRecCluster::KoaRecCluster(Int_t detId)
  : fDetId(detId),
    fNrOfDigis(0),
    fIds{ -1 },
    fEnergies{ -1 },
    fTimestamps{ -1 },
    fThreshold(0),
    fGeoHandler(nullptr)
{
  
}

KoaRecCluster::KoaRecCluster(Int_t detId, KoaGeoHandler* geoHandler)
  : fDetId(detId),
    fNrOfDigis(0),
    fIds{ -1 },
    fEnergies{ -1 },
    fTimestamps{ -1 },
    fThreshold(0),
    fGeoHandler(geoHandler)
{
  
}

KoaRecCluster::~KoaRecCluster()
{
  
}

Double_t KoaRecCluster::MaximaTotal() const
{
  auto result = std::max_element(fEnergies, fEnergies+fNrOfDigis);
  return *result;
}

Double_t KoaRecCluster::EnergyTotal() const
{
  Double_t sum=0;
  for(int i=0; i<fNrOfDigis; i++) {
    sum += fEnergies[i];
  }

  return sum;
}

Double_t KoaRecCluster::PositionTotal() const
{
  auto sum = EnergyTotal();

  Double_t pos_corrected = 0;
  Double_t pos_low, pos_high, pos_center;
  Double_t global_pos[3] = {0};
  Double_t local_pos[3] = {0};
  for ( auto index=0; index<fNrOfDigis; index++) {
    pos_center = fGeoHandler->RecDetChToPosition(fIds[index], pos_low, pos_high);
    local_pos[2] = pos_center;
    fGeoHandler->LocalToGlobal(local_pos, global_pos,fDetId);
    pos_corrected += global_pos[2] * fEnergies[index] / sum;
  }

  return pos_corrected;
}

Double_t KoaRecCluster::TimeTotal() const
{
  Double_t min = -100;
  Bool_t init_flag = false;
  for ( auto index=0; index<fNrOfDigis; index++) {
    if( fTimestamps[index] > 0 ) {
      if (!init_flag) {
        min = fTimestamps[index];
        init_flag = true;
        continue;
      }

      if( min > fTimestamps[index] ){
        min = fTimestamps[index];
      }
    }
  }

  return min;
}

Int_t KoaRecCluster::ChIdTotal() const
{
  Double_t hit_pos = PositionTotal(); // in cm
  Double_t global_pos[3] = {0, 0, hit_pos};
  return fGeoHandler->RecGlobalPositionToDetCh(global_pos, fDetId);
}

Int_t KoaRecCluster::GetMaximaChId() const
{
  
  auto result = std::max_element(fEnergies, fEnergies+fNrOfDigis);
  Int_t index = std::distance(fEnergies, result);
  return fIds[index];
}

Int_t KoaRecCluster::GetFirstChId() const
{
  auto result = std::min_element(fIds,fIds+fNrOfDigis);
  return *result;
}

Int_t KoaRecCluster::GetFirstChIdAboveThresh() const
{
  int min_id = fIds[0];
  for( auto index=0; index<fNrOfDigis; index++) {
    if(fEnergies[index] > fThreshold) {
      if(fIds[index] < min_id)
        min_id = fIds[index];
    }
  }
  return min_id;
}

Double_t KoaRecCluster::Maxima() const
{
  Double_t max=-1;
  for ( auto index=0; index<fNrOfDigis; index++ ) {
    if ( fEnergies[index] > fThreshold && fEnergies[index]>max ) {
      max = fEnergies[index];
    }
  }
  return max;
}

Double_t KoaRecCluster::Energy() const
{
  Double_t sum=0;
  for ( auto index=0; index<fNrOfDigis; index++ ) {
    if ( fEnergies[index] > fThreshold ) {
      sum += fEnergies[index];
    }
  }
  return sum;
}

Double_t KoaRecCluster::Position() const
{
  auto sum = Energy();

  Double_t pos_corrected = 0;
  Double_t pos_low, pos_high, pos_center;
  Double_t global_pos[3] = {0};
  Double_t local_pos[3] = {0};
  for ( auto index=0; index<fNrOfDigis; index++) {
    if ( fEnergies[index] > fThreshold ) {
      pos_center = fGeoHandler->RecDetChToPosition(fIds[index], pos_low, pos_high);
      local_pos[2] = pos_center;
      fGeoHandler->LocalToGlobal(local_pos, global_pos,fDetId);
      pos_corrected += global_pos[2] * fEnergies[index] / sum;
    }
  }

  return pos_corrected;
}

Double_t KoaRecCluster::Time() const
{
  Double_t min = -100;
  Bool_t init_flag = false;
  for ( auto index=0; index<fNrOfDigis; index++) {
    if( fTimestamps[index] > 0 &&  fEnergies[index]>fThreshold ) {
      if (!init_flag) {
        min = fTimestamps[index];
        init_flag = true;
        continue;
      }

      if( min > fTimestamps[index] ){
        min = fTimestamps[index];
      }
    }
  }

  return min;
}

TString KoaRecCluster::GetDetName() const
{
  KoaMapEncoder *fEncoder=KoaMapEncoder::Instance();
  return TString(fEncoder->DetectorIDToVolName(fDetId));
}

Int_t KoaRecCluster::NumberOfDigisAboveThresh() const
{
  Double_t sum=0;
  for ( auto index=0; index<fNrOfDigis; index++ ) {
    if ( fEnergies[index] > fThreshold ) {
      sum++;
    }
  }
  return sum;
}

bool KoaRecCluster::isInCluster(KoaRecDigi* theDigi) const
{
  Int_t id = theDigi->GetDetID();
  Int_t ch_id, det_id;
  KoaMapEncoder *fEncoder=KoaMapEncoder::Instance();
  ch_id = fEncoder->DecodeChannelID(id, det_id);

  if ( fDetId != det_id )
    return false;

  for ( auto index=0; index<fNrOfDigis; index++) {
    if( std::abs(id-fIds[index]) == 1){
      return true;
    }
  }

  return false;
}

void KoaRecCluster::AddDigi(KoaRecDigi* theDigi)
{
  if (fNrOfDigis == 32 ) {
    LOG(WARNING) << "Too much digits in one cluster, ignore this cluster in later analysis!";
  }

  fIds[fNrOfDigis] = theDigi->GetDetID();
  fEnergies[fNrOfDigis] = theDigi->GetCharge();
  fTimestamps[fNrOfDigis] = theDigi->GetTimeStamp();
  fNrOfDigis++;
}

ClassImp(KoaRecCluster)
