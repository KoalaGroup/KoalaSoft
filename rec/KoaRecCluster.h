//#pragma once
#ifndef KOA_REC_CLUSTER_H
#define KOA_REC_CLUSTER_H

#include "TObject.h"
#include <vector>
#include "TString.h"
#include <iostream>
#include "KoaMapEncoder.h"

#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/vector.hpp>

class KoaRecDigi;
class KoaMapEncoder;

/**
 * @brief a cluster (group of neighboring crystals) of hit emc crystals
 * @ingroup PndEmc
 */
class KoaRecCluster : public TObject
{
  friend std::ostream& operator<< (std::ostream& out, KoaRecCluster& cluster){
    out << "KoaRecCluster in " << cluster.GetDetName() << ": "
        << " energy: " << cluster.EnergyTotal()
        << " timestamp: "<< cluster.TimeTotal()
        << " position: " << cluster.PositionTotal()
        << ", from  " << cluster.NumberOfDigis() << " digits\n";
    return out;
  }

public:
	// Constructors
	KoaRecCluster();
  KoaRecCluster(Int_t detId);

	// Destructor
	virtual ~KoaRecCluster();
	
  virtual void Print() {
    std::cout << *this;
  }

	// all digis
  Double_t MaximaTotal() const;
  Double_t EnergyTotal() const;
  Double_t PositionTotal() const;
  Double_t TimeTotal() const;

	// digis above threshold
  Double_t Maxima() const;
	Double_t Energy() const;
	// Theta centroid of cluster in index units
	Double_t Position() const;
  Double_t Time() const;

	// Get Module in which cluster is located
	Int_t GetDetId() const { return fDetId; }
	TString GetDetName() const;

	Int_t NumberOfDigis() const { return fNrOfDigis; }
  Int_t NumberOfDigisAboveThresh() const;
	bool isInCluster(KoaRecDigi* theDigi) const;

	// Modifiers
  void Reset(Int_t id) {
    fNrOfDigis=0;
    fThreshold = 0;

    Int_t ch_id, det_id;
    KoaMapEncoder *fEncoder=KoaMapEncoder::Instance();
    ch_id = fEncoder->DecodeChannelID(id, det_id);
    fDetId = det_id;
  }

	void AddDigi(KoaRecDigi* theDigi);
  void SetThreshold(Double_t threshold) { fThreshold = threshold; }

 /* protected: */
 /*  template<class Archive> */
 /*  	void serialize(Archive & ar, const unsigned int version) */
 /*  	{ */
 /*  		boost::serialization::void_cast_register<KoaRecCluster, TObject>(); */

 /*  		ar & boost::serialization::base_object<TObject>(*this); */
 /*  		ar & fDetId; */
 /*  		ar & fIds; */
 /*  		ar & fEnergies; */
 /*  		ar & fTimestamps; */
 /*  	} */

private:
  Int_t    fDetId; // detId for this cluster
  Int_t    fNrOfDigis;
  Int_t    fIds[32]; // global ids of the digis
  Double_t   fEnergies[32]; //
  Double_t   fTimestamps[32]; //

  Double_t fThreshold; //! threshold to count digis contributing to this cluster
  
	ClassDef(KoaRecCluster,1)
};

#endif // EMCCLUSTER_HH
