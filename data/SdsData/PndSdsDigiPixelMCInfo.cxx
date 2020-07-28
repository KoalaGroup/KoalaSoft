/*
 * PndSdsDigiPixelMCInfo.cxx
 *
 *  Created on: Oct 25, 2010
 *      Author: esch
 */

#include "PndSdsDigiPixelMCInfo.h"


PndSdsDigiPixelMCInfo::PndSdsDigiPixelMCInfo() : PndSdsDigiPixel(),
	fMCCharge(0.),
	fAddNoise(0.),
	fTimeWalk(0.),
	fTimeWalkCorrection(0.),
	fTof(0.),
	fDigiCharge(0.)
{

}
PndSdsDigiPixelMCInfo::PndSdsDigiPixelMCInfo(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t totcharge, Double_t timeStamp, Double_t chargewonoise, Double_t addnoise, Double_t timewalk, Double_t timewalkcorrection, Double_t tof, Double_t digicharge ) :
  PndSdsDigiPixel(index,detID,sensorID,fe,col,row,totcharge,timeStamp),fMCCharge(chargewonoise),fAddNoise(addnoise), fTimeWalk(timewalk), fTimeWalkCorrection(timewalkcorrection), fTof(tof), fDigiCharge(digicharge)
{


}

PndSdsDigiPixelMCInfo::~PndSdsDigiPixelMCInfo() {
	// TODO Auto-generated destructor stub
}

ClassImp(PndSdsDigiPixelMCInfo);
