#include "KoaRecCluster.h"
#include "KoaRecDigi.h"
#include <algorithm>
#include "KoaGeoHandler.h"
#include "KoaMapEncoder.h"
#include <cstdlib>
#include <cmath>

KoaRecCluster::KoaRecCluster()
  : fDetId(-1),
    fIds(),
    fEnergies(),
    fTimestamps(),
    fThreshold(0),
    fEncoder(KoaMapEncoder::Instance())
{
  
}

KoaRecCluster::KoaRecCluster(Int_t detId,
                             integers ids,
                             doubles energies,
                             doubles timestamps)
  : fDetId(detId),
    fIds(ids),
    fEnergies(energies),
    fTimestamps(timestamps),
    fThreshold(0),
    fEncoder(KoaMapEncoder::Instance())
{
  
}

KoaRecCluster::~KoaRecCluster()
{
  
}

Double_t KoaRecCluster::MaximaTotal() const
{
  auto result = std::max_element(fEnergies.begin(), fEnergies.end());
  if(result != fEnergies.end()){
    return *result;
  }
  return -1;
}

Double_t KoaRecCluster::EnergyTotal() const
{
  Double_t sum=0;
  for ( auto& energy : fEnergies ) {
    sum += energy;
  }

  return sum;
}

Double_t KoaRecCluster::PositionTotal() const
{
  auto sum = EnergyTotal();
  auto geoHandler = new KoaGeoHandler(kFALSE);

  Double_t pos_corrected = 0;
  Double_t pos_low, pos_high, pos_center;
  Int_t nr  = fIds.size();
  for ( auto index=0; index<nr; index++) {
    pos_center = geoHandler->RecDetChToPosition(fIds[index], pos_low, pos_high);
    pos_corrected += pos_center * fEnergies[index] / sum;
  }

  return pos_corrected;
}

Double_t KoaRecCluster::TimeTotal() const
{
  auto result = std::min_element(fTimestamps.begin(), fTimestamps.end());
  if(result != fTimestamps.end()){
    return *result;
  }
  return -1;
}

Double_t KoaRecCluster::Maxima() const
{
  Double_t max=0;
  for ( auto& energy : fEnergies ) {
    if ( energy > fThreshold && energy>max) {
      max = energy;
    }
  }
  return max;
}

Double_t KoaRecCluster::Energy() const
{
  Double_t sum=0;
  for ( auto& energy : fEnergies ) {
    if ( energy > fThreshold ) {
      sum += energy;
    }
  }

  return sum;
}

Double_t KoaRecCluster::Position() const
{
  auto sum = Energy();
  auto geoHandler = new KoaGeoHandler(kFALSE);

  Double_t pos_corrected = 0;
  Double_t pos_low, pos_high, pos_center;
  Int_t nr  = fIds.size();
  for ( auto index=0; index<nr; index++) {
    if ( fEnergies[index] > fThreshold ) {
      pos_center = geoHandler->RecDetChToPosition(fIds[index], pos_low, pos_high);
      pos_corrected += pos_center * fEnergies[index] / sum;
    }
  }

  return pos_corrected;
}

Double_t KoaRecCluster::Time() const
{
  doubles localTimes;
  Int_t nr = fIds.size();
  for( auto index=0; index<nr; index++) {
    if ( fEnergies[index]>fThreshold ) {
      localTimes.emplace_back( fTimestamps[index] );
    }
  }
  auto result = std::min_element(localTimes.begin(), localTimes.end());
  if( result != localTimes.end()) {
    return *result;
  }
  return -1;
}

TString KoaRecCluster::GetDetName() const
{
  return TString(fEncoder->DetectorIDToVolName(fDetId));
}

Int_t KoaRecCluster::NumberOfDigis() const
{
  return fIds.size();
}

Int_t KoaRecCluster::NumberOfDigisAboveThresh() const
{
  Double_t sum=0;
  for ( auto& energy : fEnergies ) {
    if ( energy > fThreshold ) {
      sum++;
    }
  }

  return sum;
}

bool KoaRecCluster::isInCluster(KoaRecDigi* theDigi)
{
  auto id = theDigi->GetDetID();
  Int_t ch_id, det_id;
  ch_id = fEncoder->DecodeChannelID(id, det_id);

  if ( fDetId == -1 )
    return true;
  else if ( fDetId != det_id )
    return false;
  else {
    for ( auto& local_id : fIds ) {
      if( std::abs(id-local_id) == 1){
        return true;
      }
    }
  }

  return false;
}

void KoaRecCluster::AddDigi(KoaRecDigi* theDigi)
{
  auto id = theDigi->GetDetID();
  Int_t ch_id, det_id;
  ch_id = fEncoder->DecodeChannelID(id, det_id);

  if ( fDetId == -1 ) {
    fDetId = det_id;
  }

  fIds.emplace_back(id);
  fEnergies.emplace_back(theDigi->GetCharge());
  fTimestamps.emplace_back(theDigi->GetTimeStamp());
  return;
}
