#ifndef PndSdsPixel_HH
#define PndSdsPixel_HH

#include <iostream>
#include <string>
#include <vector>
#include "Rtypes.h"

class PndSdsPixel
{
	public :  
      PndSdsPixel() :
			  fFe(-1),
			  fCol(-1),
			  fRow(-1),
			  fCharge(-1.0),
		    fSensorID(-1),
		    fMCIndex(),
		    fAddNoise(0.)
		    {};
		  
		  PndSdsPixel(Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge, int index=-1) :
			  fFe(fe),
			  fCol(col),
			  fRow(row),
			  fCharge(charge),
		    fSensorID(sensorID),
		    fMCIndex(),
		    fAddNoise(0.)
      {
			  if (index >= 0) fMCIndex.push_back(index);
		  };
		  
		  void SetCol(Int_t col) {fCol = col;};
		  void SetRow(Int_t row) {fRow = row;};
		  void SetCharge(Double_t charge) {fCharge = charge;};
		  void SetSensorID(Int_t sensorID) {fSensorID = sensorID;};
		  void SetFE (Int_t fe) {fFe = fe;};
		  void SetAddNoise (Double_t addnoise) {fAddNoise=addnoise;};
		  
		  Int_t GetCol() const {return fCol;};
		  Int_t GetRow() const {return fRow;};
		  Double_t GetCharge() const {return fCharge;};
		  Int_t GetSensorID() const {return fSensorID;};
		  Int_t GetFE() const {return fFe;};
		  std::vector<int> GetMCIndex(){return fMCIndex;};
                  int GetFirstMCIndex(){ 
		                        if (fMCIndex.size() > 0) 
		                          return fMCIndex[0]; 
		                        return -2; 
		                  }; 
          Double_t GetAddNoise() const {return fAddNoise;};
			  
		  void AddCharge(Double_t charge){fCharge+= charge;};
		  void AddMCIndex(int i){fMCIndex.push_back(i);};
		  
		  friend std::ostream& operator<< (std::ostream& out, PndSdsPixel pixel)
		  {
			out << "Detector: " << pixel.GetSensorID() << " FE: " << pixel.GetFE() << " Pixel (C/R): " << pixel.GetCol() << " " << pixel.GetRow()
			    << " Charge: " << pixel.GetCharge() << " from MCHit: " << pixel.GetFirstMCIndex();
			return out;
		  };	

	
	private : 
		  Int_t fFe;
		  Int_t fCol;
		  Int_t fRow;
		  Double_t fCharge;
		  Int_t fSensorID;
		  std::vector<int> fMCIndex;		///< List of indices of the corresponding MC hits
		  Double_t fAddNoise;               //  Variable for testing
};


#endif
