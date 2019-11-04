#include "KoaRecCluster.h"
#include "KoaRecDigi.h"
#include <algorithm>
#include "KoaGeoHandler.h"
#include "KoaMapEncoder.h"
#include <cstdlib>
#include <cmath>

KoaRecCluster::KoaRecCluster()
  : fDetId(-1),
    fNrOfDigis(0),
    fIds{ -1 },
    fEnergies{ -1 },
    fTimestamps{ -1 },
    fThreshold(0)
{
  
}

KoaRecCluster::KoaRecCluster(Int_t detId)
  : fDetId(detId),
    fNrOfDigis(0),
    fIds{ -1 },
    fEnergies{ -1 },
    fTimestamps{ -1 },
    fThreshold(0)
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
  auto geoHandler = new KoaGeoHandler(kFALSE);

  Double_t pos_corrected = 0;
  Double_t pos_low, pos_high, pos_center;
  for ( auto index=0; index<fNrOfDigis; index++) {
    pos_center = geoHandler->RecDetChToPosition(fIds[index], pos_low, pos_high);
    pos_corrected += pos_center * fEnergies[index] / sum;
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
  auto geoHandler = new KoaGeoHandler(kFALSE);

  Double_t pos_corrected = 0;
  Double_t pos_low, pos_high, pos_center;
  for ( auto index=0; index<fNrOfDigis; index++) {
    if ( fEnergies[index] > fThreshold ) {
      pos_center = geoHandler->RecDetChToPosition(fIds[index], pos_low, pos_high);
      pos_corrected += pos_center * fEnergies[index] / sum;
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
  if (fNrOfDigis == 31) {
    std::cout << "Warning: too much digits in one cluster, ignore this cluster\n";
    return;
  }

  fIds[fNrOfDigis] = theDigi->GetDetID();
  fEnergies[fNrOfDigis] = theDigi->GetCharge();
  fTimestamps[fNrOfDigis] = theDigi->GetTimeStamp();
  fNrOfDigis++;
}

ClassImp(KoaRecCluster)
