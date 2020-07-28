/*
 * PndSdsDigiPixelMCInfo.h
 *
 *  Created on: Oct 25, 2010
 *      Author: esch
 * brief class to save additional information for a digi
 *
 *
 */


#ifndef PNDSDSDIGIPIXELMCINFO_H_
#define PNDSDSDIGIPIXELMCINFO_H_

#include "PndSdsDigiPixel.h"

class PndSdsDigiPixelMCInfo: public PndSdsDigiPixel {

    friend std::ostream& operator<< (std::ostream& out, PndSdsDigiPixelMCInfo& digi){
      out << "PndSdsDigiPixelMCInfo in: " << digi.GetSensorID() << " FE: "
      << digi.GetFE() << " Col/Row " << digi.GetPixelColumn() << "/" << digi.GetPixelRow()
      << " charge " << digi.GetCharge() << " e"
      << " timestamp "<< digi.GetTimeStamp()
      << ", from Point(s) ";
      std::vector<Int_t>indices = digi.GetIndices();
      for (unsigned int i = 0; i < indices.size(); i++){
        std::cout << indices[i] << "  ";
      }

      out << " MCCharge: " << digi.GetMCCharge() << " AddNoise: " << digi.GetAddNoise() << " TimeWalk: " << digi.GetTimeWalk() << " TimeWalkCorrection: " << digi.GetTimeWalkCorrection();
      std::cout << std::endl;

      return out;
    }
public:
	PndSdsDigiPixelMCInfo();
	PndSdsDigiPixelMCInfo(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t totcharge, Double_t timeStamp, Double_t chargewonoise, Double_t addnoise, Double_t timewalk, Double_t timewalkcorrection, Double_t tof, Double_t digicharge);
	virtual ~PndSdsDigiPixelMCInfo();

	void SetMCCharge(Double_t charge) {fMCCharge = charge;}
	Double_t GetMCCharge() {return fMCCharge;}

	void SetAddNoise(Double_t charge) {fAddNoise = charge;}
	Double_t GetAddNoise() {return fAddNoise;}

	void SetTimeWalk(Double_t timewalk) {fTimeWalk = timewalk;}
	Double_t GetTimeWalk() {return fTimeWalk;}

	void SetTimeWalkCorrection(Double_t timewalkcorrection) {fTimeWalkCorrection = timewalkcorrection;}
	Double_t GetTimeWalkCorrection() {return fTimeWalkCorrection;}

	void SetTof(Double_t tof) {fTof = tof;}
	Double_t GetTof() {return fTof;}

	void SetDigiCharge(Double_t digicharge) {fDigiCharge = digicharge;}
	Double_t GetDigiCharge() {return fDigiCharge;}

private:
	Double_t fMCCharge;  // MC Charge in a Pixel w/o gaussian noise
	Double_t fAddNoise;  // gaussian noise for a pixel
	Double_t fTimeWalk;
	Double_t fTimeWalkCorrection;
	Double_t fTof;
	Double_t fDigiCharge;  // MC Charge in a Pixel with gaussian noise

	  ClassDef(PndSdsDigiPixelMCInfo,2);

};

#endif /* PNDSDSDIGIPIXELMCINFO_H_ */
