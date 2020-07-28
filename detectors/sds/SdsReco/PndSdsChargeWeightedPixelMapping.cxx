#include "PndSdsChargeWeightedPixelMapping.h"
#include "TGeoManager.h"
#include "TGeoBBox.h"
#include "TClonesArray.h"
#include "TMath.h"

PndSdsChargeWeightedPixelMapping::PndSdsChargeWeightedPixelMapping()
:PndSdsPixelBackMapping(),
      fChargeConverter(NULL),
      flx(0.),
      fly(0.),
      fcols(0),
      frows(0)
{}
PndSdsChargeWeightedPixelMapping::PndSdsChargeWeightedPixelMapping(PndGeoHandling* geo)
:PndSdsPixelBackMapping(geo),
      fChargeConverter(NULL),
      flx(0.),
      fly(0.),
      fcols(0),
      frows(0)
{}

PndSdsHit PndSdsChargeWeightedPixelMapping::GetCluster(std::vector<PndSdsDigiPixel> pixelArray)
{
fDigiArray = pixelArray;
	Double_t col = 0, row = 0, charge = 0;
	Double_t tempCol = 0, tempRow = 0;
	std::vector<Double_t> timeValues;
	std::vector<Double_t> timeValueErrors;

	Int_t count = 0, mcindex=-1;
	//Double_t local[2], master[2];
  //TODO: Get away from default 10 Frontends per column?

	if (fDigiArray.size() == 1){
		if (fChargeConverter->DigiValueToCharge(fDigiArray[0]) > 0){
			col = fDigiArray[0].GetPixelColumn() + ((Int_t)(fDigiArray[0].GetFE()%10)) * fcols;
			if (col < 0){
				col -= 0.5;
				col += frows / 2;
			}
			else col += 0.5;
			row = fDigiArray[0].GetPixelRow()+ (fDigiArray[0].GetFE()/10) * frows;
			if (row < 0){
				row -= 0.5;
				row += flx /2;
			}
			else row += 0.5;
			if (fVerbose > 1)
				std::cout << "GetCluster:col/row " << col << " " << row << std::endl;
			count = 1;
			charge = fChargeConverter->DigiValueToCharge(fDigiArray[0]);
			  for(Int_t mcI = 0; mcI<fDigiArray[0].GetNIndices();mcI++){
				if (fDigiArray[0].GetIndex(mcI) > -1) {
				  mcindex = fDigiArray[0].GetIndex(mcI);
				  break;
				}
			  }
			  timeValues.push_back(fDigiArray[0].GetTimeStamp());
			  timeValueErrors.push_back(fDigiArray[0].GetTimeStampError());
		}
	}
	else {
		//cout << "Multiple Hits!" << std::endl;
		for (UInt_t i = 0; i < fDigiArray.size(); i++){
			//cout << "ActCol / Row" << col << " " << row << " added Col/Row " << fDigiArray[i].GetPixelColumn() << " " << fDigiArray[i].GetPixelRow() << endl;
			if (fChargeConverter->DigiValueToCharge(fDigiArray[i]) > 0){
				tempCol = fDigiArray[i].GetPixelColumn() + (Int_t)(fDigiArray[0].GetFE()%10) * fcols;
				tempRow = fDigiArray[i].GetPixelRow() + fDigiArray[0].GetFE()/10 * frows;
				col += (tempCol*fChargeConverter->DigiValueToCharge(fDigiArray[i]));
				row += (tempRow*fChargeConverter->DigiValueToCharge(fDigiArray[i]));
				charge += fChargeConverter->DigiValueToCharge(fDigiArray[i]);
				timeValues.push_back(fDigiArray[i].GetTimeStamp());
				timeValueErrors.push_back(fDigiArray[i].GetTimeStampError());
				count++;
        if(mcindex < 0){
          for(Int_t mcI = 0; mcI<fDigiArray[i].GetNIndices();mcI++){ 
            if (fDigiArray[i].GetIndex(mcI) > -1) {
              mcindex = fDigiArray[i].GetIndex(mcI);
              break;
            }
          }
        }//mcindex
        
			}
		}
		if (count > 0){
			if (charge > 0){
				col /= charge;
				row /= charge;
			}
			col += 0.5;
			row += 0.5;
		}
		else col = row = 0;
	}
	if (fVerbose > 1){
		std::cout << "Col: " << col << " Row: " << row << std::endl;
	}

  TVector3 offset = GetSensorDimensions(fDigiArray[0].GetSensorID());
  TVector3 locpos( col*flx - offset.X(), row*fly - offset.Y(), 0);
  TVector3 pos = fGeoH->LocalToMasterShortId(locpos,fDigiArray[0].GetSensorID());

  Double_t errZ = 2.*fGeoH->GetSensorDimensionsShortId(fDigiArray[0].GetSensorID()).Z();
  TMatrixD locCov(3,3);
  locCov[0][0]=flx*flx/12.;
  locCov[1][1]=fly*fly/12.;
  locCov[2][2]=errZ*errZ/12;
  TMatrixD hitCov=fGeoH->LocalToMasterErrorsShortId(locCov,fDigiArray[0].GetSensorID());
  TVector3 dpos(sqrt(hitCov[0][0]),sqrt(hitCov[1][1]),sqrt(hitCov[2][2]));
 //std::cout << "-I- PndSdsChargeWeightedPixelMapping Error DPos: " << dpos.x() << " " << dpos.y() << " " << dpos.z() << std::endl;

  Double_t meanTime = 0;
  //Double_t meanTimeError = 0;
  Double_t sumVar = 0;

  for (UInt_t t = 0; t < timeValues.size(); t++){
	  meanTime += timeValues[t] / (timeValueErrors[t] * timeValueErrors[t]);
	  sumVar += 1/(timeValueErrors[t] * timeValueErrors[t]);
  }

  if (sumVar > 0)
	  meanTime /= sumVar;



  PndSdsHit thehit(fDigiArray[0].GetDetID(),fDigiArray[0].GetSensorID(), pos, dpos, -1, charge, fDigiArray.size(),mcindex);
  thehit.SetCov(hitCov);
  thehit.SetTimeStamp(meanTime);
  thehit.SetTimeStampError(1/sumVar);
  //std::cout << "-I- PndSdsChargeWeightedPixelMapping TimeStamp: " << tempTime/count << std::endl;
  return thehit;
}

TGeoHMatrix PndSdsChargeWeightedPixelMapping::GetTransformation(Int_t sensorID)
{
  gGeoManager->cd(fGeoH->GetPath(sensorID));
  TGeoHMatrix* transMat = gGeoManager->GetCurrentMatrix();
  if (fVerbose > 2)
  	transMat->Print("");
  return *transMat;
}

TVector3 PndSdsChargeWeightedPixelMapping::GetSensorDimensions(Int_t sensorID)
{
	gGeoManager->cd(fGeoH->GetPath(sensorID));
	TGeoVolume* actVolume = gGeoManager->GetCurrentVolume();
	TGeoBBox* actBox = (TGeoBBox*)(actVolume->GetShape());
	TVector3 result;
	result.SetX(actBox->GetDX());
	result.SetY(actBox->GetDY());
	result.SetZ(actBox->GetDZ());

	//result.Dump();

	return result;
}
