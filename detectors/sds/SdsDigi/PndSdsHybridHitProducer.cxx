// -------------------------------------------------------------------------
// -----                PndSdsHybridHitProducer source file             -----
// -------------------------------------------------------------------------


#include "TClonesArray.h"
#include "TArrayD.h"
#include "TGeoManager.h"

#include "FairRootManager.h"
#include "PndSdsHybridHitProducer.h"
#include "PndSdsMCPoint.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairGeoNode.h"
#include "FairGeoNode.h"
#include "FairGeoVector.h"
#include "FairRunAna.h"
#include "FairEventHeader.h"

#include "PndStringSeparator.h"
#include "PndSdsCalcPixel.h"
#include "PndSdsCalcPixelDif.h"
#include "PndSdsCalcFePixel.h"
#include "PndSdsDigiPixel.h"
#include "PndSdsDigiPixelMCInfo.h"

#include "PndSdsFEAmpModelSimple.h"

#if (ROOT_VERSION_CODE >= ROOT_VERSION(5,34,10))
  #include "FairMultiLinkedData_Interface.h"
#endif

#include "KoaDetectorList.h"

// -----   Default constructor   -------------------------------------------
PndSdsHybridHitProducer::PndSdsHybridHitProducer() :
  PndSdsTask("SDS Hybrid Hit Producer"),
  fDigiPixelMCInfo(kFALSE),
  fPointArray(NULL),
  fPixelArray(NULL),
  fPixelMCArray(NULL),
  fDigiPar(NULL),
  fTotDigiPar(NULL),
  fChargeConverter(NULL),
  fMCEventHeader(NULL),
  fDataBuffer(NULL),
  flx(0.),
  fly(0.),
  fthreshold(0.),
  fnoise(0.),
  fqsigma(0.),
  fcols(0),
  frows(0),
  fPixelHits(0),
  fGeoH(NULL),
  fEventNr(0),
  fOverwriteParams(kFALSE),
  fTimeOrderedDigi(kFALSE),
  fPixelList()
{
  if(fVerbose>0) Info("PndSdsHybridHitProducer","SDS Hybrid Digi Producer created, Parameters will be taken from RTDB");
  SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------

PndSdsHybridHitProducer::PndSdsHybridHitProducer(const char* name) :
PndSdsTask(name),
  fDigiPixelMCInfo(kFALSE),
  fPointArray(NULL),
  fPixelArray(NULL),
  fPixelMCArray(NULL),
  fDigiPar(NULL),
  fTotDigiPar(NULL),
  fChargeConverter(NULL),
  fMCEventHeader(NULL),
  fDataBuffer(NULL),
  flx(0.),
  fly(0.),
  fthreshold(0.),
  fnoise(0.),
  fqsigma(0.),
  fcols(0),
  frows(0),
  fPixelHits(0),
  fGeoH(NULL),
  fEventNr(0),
  fOverwriteParams(kFALSE),
  fTimeOrderedDigi(kFALSE),
  fPixelList()
{
  if(fVerbose>0) Info("PndSdsHybridHitProducer","%s created, Parameters will be taken from RTDB",name);
  SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------

PndSdsHybridHitProducer::PndSdsHybridHitProducer(Double_t lx, Double_t ly, Double_t threshold, Double_t noise) :
PndSdsTask("SDS Hybrid Digi Producer (PndSdsHybridHitProducer)"),
  fDigiPixelMCInfo(kFALSE),
  fPointArray(NULL),
  fPixelArray(NULL),
  fPixelMCArray(NULL),
  fDigiPar(NULL),
  fTotDigiPar(NULL),
  fChargeConverter(NULL),
  fMCEventHeader(NULL),
  fDataBuffer(NULL),
  flx(lx),
  fly(ly),
  fthreshold(threshold),
  fnoise(noise),
  fqsigma(0.),
  fcols(104),
  frows(104),
  fPixelHits(0),
  fGeoH(NULL),
  fEventNr(0),
  fOverwriteParams(kTRUE),
  fTimeOrderedDigi(kFALSE),
  fPixelList()
{
  fTimeOrderedDigi = kFALSE;
  if(fVerbose>0) Info("PndSdsHybridHitProducer","SDS Hybrid Digi Producer created, Parameters will be overwritten in RTDB");
  SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
PndSdsHybridHitProducer::~PndSdsHybridHitProducer()
{
	if (fChargeConverter!=0) delete fChargeConverter;
	if (fDataBuffer!= 0) delete fDataBuffer;
}
// -------------------------------------------------------------------------

// -----   Initialization  of Parameter Containers -------------------------
void PndSdsHybridHitProducer::SetParContainers()
{
  if ( fGeoH == NULL )
    fGeoH = PndGeoHandling::Instance();

  fGeoH->SetParContainers();
  if( ! fDigiPar) Fatal("SetParContainers","No digitiztion parameters specified.");
  if(fVerbose>1) Info("SetParContainers","done.");
  return;
}

InitStatus PndSdsHybridHitProducer::ReInit()
{
  SetParContainers();
  return kSUCCESS;
}

// -----   Public method Init   --------------------------------------------
InitStatus PndSdsHybridHitProducer::Init()
{
  SetBranchNames();
  
  FairRun* ana = FairRun::Instance();
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman )
  {
    std::cout << "-E- PndSdsHybridHitProducer::Init: "
    << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }
  
  
  fPointArray = (TClonesArray*) ioman->GetObject(fInBranchName);  
  if ( ! fPointArray )
  {
    std::cout << "-W- PndSdsHybridHitProducer::Init: "
    << "No SDSPoint array!" << std::endl;
    return kERROR;
  }
  
  
  // Create and register output array
  //  fPixelArray	= new TClonesArray("PndSdsDigiPixel");
  //  if(fVerbose>1) Info("Init","Registering this branch: %s/%s",fFolderName.Data(),fOutBranchName.Data());
  //  ioman->Register(fOutBranchName, fFolderName, fPixelArray, fPersistance);
  //  fPixelArray = ioman->Register(fOutBranchName, "PndSdsDigiPixel", fFolderName, fPersistance);
  
  fDataBuffer = new PndSdsDigiPixelWriteoutBuffer(fOutBranchName, fFolderName, GetPersistency());
  fDataBuffer = (PndSdsDigiPixelWriteoutBuffer*)ioman->RegisterWriteoutBuffer(fOutBranchName, fDataBuffer);
  fDataBuffer->ActivateBuffering(fTimeOrderedDigi);
  
  
  if(fOverwriteParams==kTRUE){
    fDigiPar->SetXPitch(flx);
    fDigiPar->SetYPitch(fly);
    fDigiPar->SetThreshold(fthreshold);
    fDigiPar->SetNoise(fnoise);
    fDigiPar->SetFECols(fcols);
    fDigiPar->SetFERows(frows);
    fDigiPar->setInputVersion(ana->GetRunId(),1);
    fDigiPar->setChanged();
	  if(fVerbose>0) Info("Init","RTDB updated");
  }
  
  if(fVerbose>2) fDigiPar->Print();
  
  flx = fDigiPar->GetXPitch();
  fly = fDigiPar->GetYPitch();
  fthreshold = fDigiPar->GetThreshold();
  fnoise = fDigiPar->GetNoise();
  fcols = fDigiPar->GetFECols();
  frows = fDigiPar->GetFERows();
  fqsigma = fDigiPar->GetQCloudSigma();
  
  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PndSdsHybridHitProducer::Exec(Option_t*)
{
  if(fVerbose>3) Info("Exec","Start");
  //
  //  if (fFEModel == 0)
  //	  std::cout << "-E- PndSdsHybridHitProducer::Exec No front end model defined!" << std::endl;
  
  
  Double_t EventTime = FairRootManager::Instance()->GetEventTime();
  
  if(fVerbose>0)
    {
      std::cout << std::endl;
      std::cout << "-I- PndSdsHybridHitProducer::Exec EventTime: " << EventTime << " event: " << FairRootManager::Instance()->GetEntryNr() << std::endl;
    }
  
  fPixelList.clear();
  fGeoH->SetVerbose(fVerbose);  
  // Declare some variables
  PndSdsMCPoint *point = NULL;
  
  if( ! fChargeConverter) Fatal("Exec","No charge converter specified");
  //  Int_t detID = 0;      // Detector ID
  fChargeConverter->StartExecute();		//here parameters that change every event are set
  
  // Loop over PndSdsMCPoints
  Int_t nPoints = fPointArray->GetEntriesFast();
  Int_t iFePixel = 0;
  fPixelHits = 0;
  
  if(fVerbose>3) Info("Exec","Begin loop for %i points",nPoints);
  for (Int_t iPoint = 0; iPoint < nPoints; iPoint++)
  {
    point = (PndSdsMCPoint*) fPointArray->At(iPoint);
    if ( ! point){
      std::cout<< "No Point!" << std::endl;
      continue;
    }
    if (fVerbose > 1){
      std::cout << "****Global Point: " << std::endl;
      point->Print("");
    }
    FairGeoVector posInL, posOutL;
    GetLocalHitPoints(point, posInL, posOutL);
    
    if (fVerbose > 1){
      std::cout << "posOutL: " << std::endl;
      std::cout << posInL.X() << " " << posInL.Y() << " " << posInL.Z() << std::endl;
      std::cout << posOutL.X() << " " << posOutL.Y() << " " << posOutL.Z() << std::endl;
    }
    
    if (fVerbose > 1){
      FairGeoVector meanPosL = posInL + posOutL;
      meanPosL /= 2;
      meanPosL.Print();
      std::cout << "Energy: " << point->GetEnergyLoss() << std::endl;
      std::cout << point->GetSensorID() << std::endl;
      std::cout << fGeoH->GetPath(point->GetSensorID()) << std::endl;
      std::cout << "Time since Event started: " << point->GetTime() << std::endl;
    }
    std::vector<PndSdsPixel> myFePixels;
    if (   fGeoH->GetPath(point->GetSensorID()).Contains("Pixel")
        ||
        ( fGeoH->GetPath(point->GetSensorID()).Contains("Sensor") &&
         !fGeoH->GetPath(point->GetSensorID()).Contains("Strip")     )
        )
    {
      std::vector<PndSdsPixel> myPixels;
      if(fqsigma>0){
        // Define sensor by pixelsizes threshold and noise from macro outside
        PndSdsCalcPixelDif PixelCalc(*fDigiPar);
        // Calculate a cluster of Pixels fired (in sensor system)
        myPixels = PixelCalc.GetPixels (posInL.getX(), posInL.getY(),
                                        posOutL.getX(), posOutL.getY(), 
                                        point->GetEnergyLoss());
      } else {
        // Define sensor by pixelsizes threshold and noise from macro outside
        PndSdsCalcPixel PixelCalc(flx, fly);
        // Calculate a cluster of Pixels fired (in sensor system)
        myPixels = PixelCalc.GetPixels (posInL.getX(), posInL.getY(),
                                        posOutL.getX(), posOutL.getY(),
                                        point->GetEnergyLoss());
      }
      if (myPixels.size() == 0){
        if (fVerbose > 1) std::cout << "Deposited charge below threshold" << std::endl;
      } else {
        fPixelHits += myPixels.size();
        if (fVerbose > 1) std::cout  << "SensorPixels: " << std::endl;
        for(UInt_t i = 0; i < myPixels.size(); i++)
        {
          myPixels[i].SetSensorID(point->GetSensorID());
          if (fVerbose > 1) std::cout << myPixels[i] << std::endl;
        }
        // Calculate channel numbers
        PndSdsCalcFePixel feCalc(*fDigiPar); //TODO: Why do we set 10 column Frontends per hand?
        myFePixels = feCalc.CalcFEHits(myPixels);
        if (fVerbose > 1){
          std::cout << "FePixels: " << myFePixels.size() << std::endl;
          for(UInt_t i = 0; i < myFePixels.size(); i++){
            std::cout << myFePixels[i] << std::endl;
          }
        }
        AddHits(&myFePixels, iPoint);
      }//endif myPixels.size
      
    }//endif pixel
  }   // Loop over MCPoints
  
  // convert to digi data type after all charge is collected
  // and apply gaussian noise
  
  Double_t charge=0;
  for (unsigned int iPix = 0; iPix < fPixelList.size(); iPix++)
  {
    if(fVerbose>1) std::cout << "fPixelList.size()" <<  fPixelList.size() << std::endl;
    point = (PndSdsMCPoint*) fPointArray->At(fPixelList[iPix].GetMCIndex()[0]);
    charge=fPixelList[iPix].GetCharge();
    //std::cout << fPixelList[iPix] << std::endl;

    if (fVerbose > 1)  std::cout << fPixelList[iPix] << std::endl;
    
    //	if (fFEModel > 0){
    //		double correctedTimeStamp = (fFEModel->GetTimeStamp(EventTime, 0, charge) - fFEModel->GetTimeWalkFromTot(fFEModel->GetTotFromCharge(charge)) - fFEModel->GetTimeStep()/2);
    //			std::cout << "FEModel-Test: " << point->GetEnergyLoss() << " " << charge << " " << fChargeConverter->ChargeToDigiValue(charge) << " " << fFEModel->GetTotFromCharge(charge) << " " << fFEModel->GetChargeFromTot(fFEModel->GetTotFromCharge(charge)) << std::endl
    //					<< " Time: " << point->GetTimeStamp() << " " << fFEModel->GetTimeStamp(EventTime, point->GetTime(), charge) << " " << correctedTimeStamp << std::endl
    //					<< " TimeDifference: " << point->GetTimeStamp() - correctedTimeStamp << std::endl;
    //			if ((point->GetTimeStamp() - correctedTimeStamp) > 10 || (point->GetTimeStamp() - correctedTimeStamp) < -10) {
    //				std::cout << "BigDifference!" << std::endl;
    //			}
    //	}

    Int_t smearedCharge = (Int_t)fChargeConverter->ChargeToDigiValue(charge);
	Double_t smearedChargeInE = fChargeConverter->DigiValueToCharge(smearedCharge);
    Int_t timeStamp = (Int_t)fChargeConverter->GetTimeStamp(point->GetTime(),smearedChargeInE, EventTime);

    if (smearedChargeInE < fthreshold)
    	smearedChargeInE = fthreshold;
   	Double_t timewalk = fChargeConverter->GetTimeWalk(smearedChargeInE);

    Double_t correctedTimeStamp = timeStamp - timewalk - fChargeConverter->GetTimeStep()/2;

    if (fVerbose > 2){
    	std::cout << "TimeStampCalc: EventTime: " << EventTime << " ToF " << point->GetTime() << " charge " << smearedChargeInE << " TW: " << timewalk << " CorrectedTS: " << correctedTimeStamp << std::endl;
    	std::cout << "Diff TimeStamp - EventTime " << correctedTimeStamp - EventTime << std::endl;
   	}
    PndSdsDigiPixel *tempPixel = new PndSdsDigiPixel( fPixelList[iPix].GetMCIndex(), fInBranchId, fPixelList[iPix].GetSensorID() ,fPixelList[iPix].GetFE(),
                                                     fPixelList[iPix].GetCol(), fPixelList[iPix].GetRow(),
                                                     smearedCharge, correctedTimeStamp); //fChargeConverter->GetTimeStamp(point->GetTime(), charge,fEventHeader->GetEventTime()) );
    
    if (fTimeOrderedDigi){
		tempPixel->ResetLinks();
		std::vector<int> indices = fPixelList[iPix].GetMCIndex();
		FairEventHeader* evtHeader = (FairEventHeader*)FairRootManager::Instance()->GetObject("EventHeader.");
		for (int i = 0; i < (int)indices.size(); i++){
			tempPixel->SetInsertHistory(true);
			tempPixel->AddLink(FairLink(evtHeader->GetInputFileId(), evtHeader->GetMCEntryNumber(),  fInBranchId, indices[i]));
			PndSdsMCPoint* myPoint = (PndSdsMCPoint*)fPointArray->At(indices[i]);
			tempPixel->AddLinks(*(myPoint->GetPointerToLinks()));
		}
		tempPixel->AddLink(FairLink(-1, fEventNr, "EventHeader.", -1));
    }
    fDataBuffer->FillNewData(tempPixel, fChargeConverter->ChargeToDigiValue(fPixelList[iPix].GetCharge())*6 + EventTime, point->GetTime()+EventTime);
    if (fVerbose > 0){
	  std::cout << "PixelDigi: " << (tempPixel) << std::endl;
#if (ROOT_VERSION_CODE >= ROOT_VERSION(5,34,10))
	  std::cout << "Links in Digi: " << (FairMultiLinkedData_Interface*)(tempPixel) << std::endl;
#else
	  std::cout << "Links in Digi: " << (FairMultiLinkedData)(*tempPixel) << std::endl;
#endif
	}
    delete tempPixel;
    

  }
  
  
  
  
  fChargeConverter->EndExecute();
  // Event summary
  
  if (fVerbose > 1){
    std::cout << "-I- PndSdsHybridHitProducer: " << nPoints << " PndSdsMCPoints, "
    << fPixelHits << " Digi created." << " " << iFePixel
    << "  (event "<<fEventNr <<")"<< std::endl;
    
    
  }
  fEventNr++;
  if(fVerbose>3) Info("Exec","Loop MC points");
}

void PndSdsHybridHitProducer::GetLocalHitPoints(PndSdsMCPoint* myPoint, FairGeoVector& myHitIn, FairGeoVector& myHitOut)
{
  
  if (fVerbose > 1)
    std::cout << "GetLocalHitPoints" << std::endl;
  TGeoHMatrix trans = GetTransformation(myPoint->GetSensorID());
  
  Double_t posIn[3];
  Double_t posOut[3];
  Double_t posInLocal[3];
  Double_t posOutLocal[3];
  
  posIn[0] = myPoint->GetX();
  posIn[1] = myPoint->GetY();
  posIn[2] = myPoint->GetZ();
  
  posOut[0] = myPoint->GetXOut();
  posOut[1] = myPoint->GetYOut();
  posOut[2] = myPoint->GetZOut();
  
  if (fVerbose > 1){
    for (Int_t i = 0; i < 3; i++)
      std::cout << "posIn "<< i << ": " << posIn[i] << std::endl;
    
    trans.Print("");
  }
  
  trans.MasterToLocal(posIn, posInLocal);
  trans.MasterToLocal(posOut, posOutLocal);
  
  if (fVerbose > 1) {
    for (Int_t i = 0; i < 3; i++){
      std::cout << "posInLocal "<< i << ": " << posInLocal[i] << std::endl;
      std::cout << "posOutLocal "<< i << ": " << posOutLocal[i] << std::endl;
    }
  }
  
  
  //posIn/OutLocal have the center of the coordinate system in the center of the shape
  //typically sensors have their coordinate system centered at the lower left corner
  
  TVector3 offset = GetSensorDimensions(myPoint->GetSensorID());
  
  if (fVerbose > 1){
	  std::cout << "SensorDimension for: " << myPoint->GetSensorID() << std::endl;
	  std::cout << offset.X() << " " << offset.Y() << " " << offset.Z() << std::endl;
  }
  
  posInLocal[0] += offset.x();
  posInLocal[1] += offset.y();
  //posInLocal[2] += offset.z();
  
  posOutLocal[0] += offset.x();
  posOutLocal[1] += offset.y();
  //posOutLocal[2] += offset.z();
  
  
  myHitIn.setVector(posInLocal);
  myHitOut.setVector(posOutLocal);
  
}

TGeoHMatrix PndSdsHybridHitProducer::GetTransformation(Int_t sensorID)
{
  //PndGeoHandling GeoH(gGeoManager);
  gGeoManager->cd(fGeoH->GetPath(sensorID));
  TGeoHMatrix* transMat = gGeoManager->GetCurrentMatrix();
  if (fVerbose > 1)
    transMat->Print("");
  return *transMat;
}

TVector3 PndSdsHybridHitProducer::GetSensorDimensions(Int_t sensorID)
{
  //PndGeoHandling GeoH(gGeoManager);
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

void PndSdsHybridHitProducer::AddHits(std::vector<PndSdsPixel>* hits, int mcIndex)
{
	for (UInt_t i = 0; i < hits->size(); i++){
		AddHit((*hits)[i], mcIndex);
	}
	if (fVerbose > 1) std::cout << "Size of fPixelList: " << fPixelList.size() << std::endl;
}

void PndSdsHybridHitProducer::AddHit(PndSdsPixel& hit, int mcIndex)
{
	bool found = false;
	if(fVerbose > 1) std::cout << "Adding Hits to PixelList with mcIndex: " << mcIndex << std::endl;
  // check if the channel fired already
	for (UInt_t i = 0; i < fPixelList.size(); i++){
		if ( fPixelList[i].GetSensorID() == hit.GetSensorID() &&
        fPixelList[i].GetFE() == hit.GetFE() &&
        fPixelList[i].GetCol() == hit.GetCol() &&
        fPixelList[i].GetRow() == hit.GetRow() )
		{
			if (fVerbose > 1)
				std::cout << "Pixel " << hit.GetSensorID()
        << " FE/col/row " << hit.GetFE()
        << "/" << hit.GetCol()
        << "/" << hit.GetRow() << " already hit!"<< std::endl;
			fPixelList[i].AddCharge(hit.GetCharge());
			fPixelList[i].AddMCIndex(mcIndex);
			return;
		}
	}
	if (found == false){
		hit.AddMCIndex(mcIndex);
		fPixelList.push_back(hit);
	}
}

//______________________________________________________________________________

// -------------------------------------------------------------------------

void PndSdsHybridHitProducer::FinishEvent()
{
  // called after all Tasks did their Exex() and the data is copied to the file
  
	if(fDigiPixelMCInfo==kTRUE)
  {
		fPixelMCArray->Delete();
  }
  //	  fPixelArray->Delete();
  FinishEvents();
}
// -------------------------------------------------------------------------

void PndSdsHybridHitProducer::FinishTask()
{
  // called after all Tasks did their Exex() and the data is copied to the file
  //	if (fTimeOrderedDigi){
  //		fDataBuffer->WriteOutAllData();
  //	}
  
}

ClassImp(PndSdsHybridHitProducer);
