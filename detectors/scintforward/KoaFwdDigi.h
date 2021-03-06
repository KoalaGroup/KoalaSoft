// --------------------------------------------------------
// ----			KoaFwdDigi header file	---
// ----			Created 09.10.19 by Y.Zhou ---
// ----     Adopted from PndSdsDigi by T.Stockmanns in PandaRoot ---
// --------------------------------------------------------

/** KoaFwdDigi.h
 *@author Y.Zhou <y.zhou@fz-juelich.de>
 **
 ** \brief Base class for Digi information
 **
 **
 **/

#ifndef KOAFWDDIGI_H
#define KOAFWDDIGI_H

#include "FairTimeStamp.h"
#include "KoaMapEncoder.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>
#include <boost/serialization/void_cast.hpp>

class KoaFwdDigi : public FairTimeStamp
  {
    friend std::ostream& operator<< (std::ostream& out, KoaFwdDigi& digi){
      KoaMapEncoder *encoder = KoaMapEncoder::Instance();
      Int_t detId;
      encoder->DecodeChannelID(digi.GetDetID(), detId);
      out << "KoaFwdDigi in " << encoder->DetectorIDToVolName(detId) << ": "
      << " charge: " << digi.GetCharge() 
      << " timestamp: "<<digi.GetTimeStamp()
      << ", from Point(s): ";
      std::vector<Int_t> indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        std::cout << digi.GetIndex(i) << " " << std::endl;
      }
      return out;
    }
    
  public: 
    KoaFwdDigi();
    KoaFwdDigi(std::vector<Int_t> index, Int_t detID, Double_t charge);
    KoaFwdDigi(Int_t index, Int_t detID, Double_t charge);
		/**<constructor
     * \param index position of PndSdsMCPoint in TClonesArray
     * \param detID detector ID (from/for CbmPoint/Hit)
     * \param charge deposited charge in electrons
     */
		virtual ~KoaFwdDigi(){};
    
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

    void SetDetectorID(Int_t detID) { fDetID=detID; }

		virtual void Print() {
			std::cout << *this;
		}

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			boost::serialization::void_cast_register<KoaFwdDigi, FairTimeStamp>();

			ar & boost::serialization::base_object<FairTimeStamp>(*this);
			ar & fDetID;
			ar & fCharge;
		}

  protected:
		friend class boost::serialization::access;

		std::vector<Int_t> fIndex;   // indice of mc points contributing to this digi
		Int_t fDetID;                // branch ID of mc point array
		Double_t fCharge;            // collected charge, could be energy (MeV) in ideal Digitization
    
    ClassDef(KoaFwdDigi,1);
  };

#endif
