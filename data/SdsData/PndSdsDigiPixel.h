// --------------------------------------------------------
// ----			PndSdsDigiPixel header file	---
// ----			Created 19.6.06 by T.Stockmanns ---
// --------------------------------------------------------

/** PndSdsDigiPixel.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 ** \brief Data class to store the digi output of a pixel module
 **
 ** \sa PndSdsDigi.h
 **/

#ifndef PNDSDSDIGIPIXEL_H
#define PNDSDSDIGIPIXEL_H

#include "PndSdsDigi.h"
#include "KoaDetectorList.h"

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <vector>


class PndSdsDigiPixel : public PndSdsDigi
  {
    friend std::ostream& operator<< (std::ostream& out, PndSdsDigiPixel& digi){
      out << "PndSdsDigiPixel in: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " Col/Row " << digi.GetPixelColumn() << "/" << digi.GetPixelRow()
      << " charge " << digi.GetCharge() << " e"
      << " timestamp "<< digi.GetTimeStamp()
      << ", from Point(s) ";
      std::vector<Int_t>indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        out << indices[i] << "  ";
      }
      out << std::endl;
      
      return out;
    }
    
    public : PndSdsDigiPixel();
    PndSdsDigiPixel(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge, Double_t timeStamp);
    
    
	virtual ~PndSdsDigiPixel(){};
    
    void Print() {
      std::cout << *this;
    }
    
	Int_t GetPixelColumn() const { return fCol; }
	Int_t GetPixelRow()    const { return fRow; }

	void SetPixelColumn(Int_t col){ fCol = col;}
	void SetPixelRow(Int_t row){ fRow = row;}

	bool operator==(PndSdsDigiPixel& myDigi){
		if (fSensorID == myDigi.GetSensorID())
			if (fFE == myDigi.GetFE())
				if (fCol == myDigi.GetPixelColumn())
					if (fRow == myDigi.GetPixelRow())
						return true;
		return false;
	}
	
	virtual bool equal(FairTimeStamp* data) {
	  PndSdsDigiPixel* myDigi = dynamic_cast <PndSdsDigiPixel*> (data);
	  if (myDigi != 0){
	    if (fSensorID == myDigi->GetSensorID())
			if (fFE == myDigi->GetFE())
				if (fCol == myDigi->GetPixelColumn())
					if (fRow == myDigi->GetPixelRow())
						return true;
	  }
	  return false;
	}

	virtual bool operator<(const PndSdsDigiPixel& myDigi) const{
		if (fDetID < myDigi.GetDetID()) 		return true;	else if(fDetID > myDigi.GetDetID()) return false;
		if (fSensorID < myDigi.GetSensorID()) 	return true; 	else if (fSensorID > myDigi.GetSensorID()) return false;
		if (fFE < myDigi.GetFE()) 				return true;	else if (fFE > myDigi.GetFE()) return false;
		if (fCol < myDigi.GetPixelColumn()) 	return true;	else if (fCol > myDigi.GetPixelColumn()) return false;
		if (fRow < myDigi.GetPixelRow()) 		return true;	else if (fRow > myDigi.GetPixelRow()) return false;
		return false;
	}
        
	virtual bool operator>(const PndSdsDigiPixel& myDigi) const{
		if (fDetID > myDigi.GetDetID()) 		return true;	else if(fDetID < myDigi.GetDetID()) return false;
		if (fSensorID > myDigi.GetSensorID()) 	return true; 	else if (fSensorID < myDigi.GetSensorID()) return false;
		if (fFE > myDigi.GetFE()) 				return true;	else if (fFE < myDigi.GetFE()) return false;
		if (fCol > myDigi.GetPixelColumn()) 	return true;	else if (fCol < myDigi.GetPixelColumn()) return false;
		if (fRow > myDigi.GetPixelRow()) 		return true;	else if (fRow < myDigi.GetPixelRow()) return false;
		return false;
	}

	PndSdsDigiPixel& operator=(const PndSdsDigiPixel& pix){
	        if (this != &pix){
		    this->PndSdsDigi::operator=(pix);
		    fCol = pix.GetPixelColumn();
		    fRow = pix.GetPixelRow();
	        }
		return *this;
	}

	#ifndef __CINT__ // for BOOST serialization
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			boost::serialization::void_cast_register<PndSdsDigiPixel, PndSdsDigi>();
			ar & boost::serialization::base_object<PndSdsDigi>(*this);
			ar & fCol;
			ar & fRow;
		}
	#endif // for BOOST serialization

    private :
	#ifndef __CINT__ // for BOOST serialization
		friend class boost::serialization::access;

	#endif // for BOOST serialization
		Int_t fCol, fRow;
    
    ClassDef(PndSdsDigiPixel,8);
  };

#endif
