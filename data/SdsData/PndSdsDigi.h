// --------------------------------------------------------
// ----			PndSdsDigi header file	---
// ----			Created 19.10.07 by T.Stockmanns ---
// --------------------------------------------------------

/** PndSdsDigi.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** \brief Base class for Digi information
 **
 **
 **/

#ifndef PNDSDSDIGI_H
#define PNDSDSDIGI_H

#include "FairTimeStamp.h"

#include "TObject.h"
#include "TString.h"
#include "KoaDetectorList.h" 
#include <iostream>
#include <vector>

#ifndef __CINT__ // for BOOST serialization
	#include <boost/serialization/void_cast.hpp>
#endif // for BOOST serialization

class PndSdsDigi : public FairTimeStamp
  {
    friend std::ostream& operator<< (std::ostream& out, PndSdsDigi& digi){
      out << "PndSds Digi in sensor: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " "
      << " charge: " << digi.GetCharge() << " e"
      << " timestamp: "<<digi.GetTimeStamp()
      << ", from Point(s): ";
      std::vector<Int_t> indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        std::cout << digi.GetIndex(i) << " " << std::endl;
      }
      return out;
    }
    
  public: 
    PndSdsDigi();
    PndSdsDigi(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Double_t charge, Double_t timestamp = -1);
    PndSdsDigi(Int_t index, Int_t detID, Int_t fSensorID, Int_t fe, Double_t charge, Double_t timestamp = -1);
		/**<constructor
     * \param index position of PndSdsMCPoint in TClonesArray
     * \param detID detector ID (from/for CbmPoint/Hit)
     * \param detName geoH->GetID(gGeoManager->GetPath()) information
     * \param fe front end ID
     * \param charge deposited charge in electrons
     */
		virtual ~PndSdsDigi(){};
    
		Int_t GetFE() const { return fFE;}
		//TString GetDetName()   const { return fDetName; }
		Int_t GetSensorID() const { return fSensorID; }
		Double_t GetCharge()	 const { return fCharge; }
		Int_t GetDetID() const { return fDetID;}
		std::vector<Int_t> GetIndices() const { return fIndex;}
		Int_t GetIndex(int i = 0) const{ return fIndex[i];}
		Int_t GetNIndices() const { return fIndex.size();}
    
		virtual void AddIndex(int index)
		{
			fIndex.push_back(index);
			AddLink(FairLink(fDetID, index));
		}
    
		virtual void AddIndex(std::vector<Int_t> index)
		{
			fIndex = index;
			AddLinks(FairMultiLinkedData(fDetID, index));
		}
		void SetCharge(double charge){fCharge = charge;}
    void AddCharge(double charge){fCharge += charge;}

    virtual bool operator<(const PndSdsDigi& myDigi) const{
    	if (fDetID < myDigi.GetDetID()) 		return true;	else if(fDetID > myDigi.GetDetID()) return false;
		if (fSensorID < myDigi.GetSensorID()) 	return true; 	else if (fSensorID > myDigi.GetSensorID()) return false;
		if (fFE < myDigi.GetFE()) 				return true;	else if (fFE > myDigi.GetFE()) return false;
    	return false;
    }

		virtual void Print() {
			std::cout << *this;
		}

	#ifndef __CINT__ // for BOOST serialization
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			boost::serialization::void_cast_register<PndSdsDigi, FairTimeStamp>();

			ar & boost::serialization::base_object<FairTimeStamp>(*this);
			ar & fDetID;
			ar & fSensorID;
			ar & fFE;
			ar & fCharge;
		}
	#endif // for BOOST serialization

  protected:
	#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

	#endif // for BOOST serialization
		std::vector<Int_t> fIndex;   // indice of mc points contributing to this digi
		Int_t fDetID;                // branch ID of mc point array
		Int_t fSensorID;             // Geometry ID for sensor volume
		Int_t fFE;                   // Frontend number
		Double_t fCharge;            // collected charge
    
    ClassDef(PndSdsDigi,4);
  };

#endif
