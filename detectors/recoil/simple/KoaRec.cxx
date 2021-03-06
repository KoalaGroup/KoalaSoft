/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRec.h"
#include "KoaGeoHandler.h"

#include "KoaRecPoint.h"
#include "KoaRecGeo.h"
#include "KoaRecGeoPar.h"
#include "KoaRecMisalignPar.h"
#include "KoaMapEncoder.h"
#include "KoaGeoHandler.h"

#include "FairVolume.h"
#include "FairGeoVolume.h"
#include "FairGeoNode.h"
#include "FairRootManager.h"
#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "KoaDetectorList.h"
#include "KoaStack.h"
#include "KoaRecMisalignPar.h"

#include "TClonesArray.h"
#include "TVirtualMC.h"
#include "TGeoManager.h"
#include "TGeoBBox.h"
#include "TGeoCompositeShape.h"
#include "TGeoTube.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"

#include <iostream>
using std::cout;
using std::endl;

KoaRec::KoaRec()
  : FairDetector("KoaRec", kTRUE, kKoaRec),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fPosEnd(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fKoaRecPointCollection(new TClonesArray("KoaRecPoint")),
    fGeoHandler(new KoaGeoHandler(kTRUE)),
    fModifyGeometry(kFALSE),
    fMisalignPar(nullptr),
    fNrOfSensors(-1),
    fSensorShiftX(),
    fSensorShiftY(),
    fSensorShiftZ(),
    fSensorRotPhi(),
    fSensorRotTheta(),
    fSensorRotPsi()
{
  fListOfSensitives.push_back("SensorSi");
  fListOfSensitives.push_back("SensorGe");
}

KoaRec::KoaRec(const char* name, Bool_t active)
  : FairDetector(name, active, kKoaRec),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fPosEnd(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fKoaRecPointCollection(new TClonesArray("KoaRecPoint")),
    fGeoHandler(new KoaGeoHandler(kTRUE)),
    fModifyGeometry(kFALSE),
    fMisalignPar(nullptr),
    fNrOfSensors(-1),
    fSensorShiftX(),
    fSensorShiftY(),
    fSensorShiftZ(),
    fSensorRotPhi(),
    fSensorRotTheta(),
    fSensorRotPsi()
{
  fListOfSensitives.push_back("SensorSi");
  fListOfSensitives.push_back("SensorGe");
}

KoaRec::~KoaRec()
{
  if (fKoaRecPointCollection) {
    fKoaRecPointCollection->Delete();
    delete fKoaRecPointCollection;
  }

  delete fGeoHandler;
}

void KoaRec::SetParContainers()
{
  if(fModifyGeometry){
    LOG(info)<< "Set Recoil detector  missallign parameters";
    FairRuntimeDb* rtdb=FairRun::Instance()->GetRuntimeDb();
    LOG_IF(FATAL, !rtdb) << "No runtime database";

    // read in the misalignment parameters from parameter file
    fMisalignPar = static_cast<KoaRecMisalignPar*>(rtdb->getContainer("KoaRecMisalignPar"));
    
  }
}

void KoaRec::InitParContainers()
{
  if(fModifyGeometry){
    LOG(info)<< "Initialize Recoil detector missallign parameters";
    fNrOfSensors = fMisalignPar->GetNrOfSensors();
    fSensorShiftX = fMisalignPar->GetSensorShiftX();
    fSensorShiftY = fMisalignPar->GetSensorShiftY();
    fSensorShiftZ = fMisalignPar->GetSensorShiftZ();
    fSensorRotPhi = fMisalignPar->GetSensorRotPhi();
    fSensorRotTheta = fMisalignPar->GetSensorRotTheta();
    fSensorRotPsi = fMisalignPar->GetSensorRotPsi();
    LOG(info)<< "Recoil detector misalignment parameters initialized";
  }
}

void KoaRec::Initialize()
{
  FairDetector::Initialize();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  // Parameter Container should be init in SetParContainer, not here. Besides, par is not used in this class
  // However, if the Parameter Container is used for output and values not read from file, then it is reasonable to
  // init it here.
  KoaRecGeoPar* par=(KoaRecGeoPar*)(rtdb->getContainer("KoaRecGeoPar"));
}

Bool_t  KoaRec::ProcessHits(FairVolume* vol)
{
  /** This method is called from the MC stepping */

  //Set parameters at entrance of volume. Reset ELoss.
  if ( gMC->IsTrackEntering() ) {
    fELoss  = 0.;
    fTime   = gMC->TrackTime() * 1.0e09;
    fLength = gMC->TrackLength();
    gMC->TrackPosition(fPos);
    gMC->TrackMomentum(fMom);
  }

  // Sum energy loss for all steps in the active volume
  fELoss += gMC->Edep();

  // Create KoaRecPoint at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    // fVolumeID = vol->getMCid();
    fVolumeID = fGeoHandler->GetDetIdByName(vol->GetName());
    // std::cout<<vol->GetName()<<",volumeID="<< vol->getVolumeId()<<",modID="<<\
      vol->getModId()<<",MCid="<<vol->getMCid()<<",CurrentVolID="<<gMC->CurrentVolOffID(0,copy)<<\
      ", volumeName="<< gMC->CurrentVolName()<<", volPath="<< gMC->CurrentVolPath()<< std::endl;
    gMC->TrackPosition(fPosEnd);
    if (fELoss == 0. && gMC->TrackPid()!=0) { return kFALSE; }
    AddHit(fTrackID,
           fVolumeID,
           TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fPosEnd.X(),  fPosEnd.Y(),  fPosEnd.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()),
           fTime,
           fLength,
           fELoss);

    // Increment number of KoaRec det points in TParticle
    KoaStack* stack = (KoaStack*) gMC->GetStack();
    stack->AddPoint(kKoaRec);
  }

  return kTRUE;
}

void KoaRec::EndOfEvent()
{

  fKoaRecPointCollection->Clear();

}



void KoaRec::Register()
{

  /** This will create a branch in the output tree called
      KoaRecPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  if(!gMC->IsMT()){
    FairRootManager::Instance()->Register("KoaRecPoint", "KoaRec",
                                          fKoaRecPointCollection, kTRUE);
  }
  else{
    FairRootManager::Instance()->RegisterAny("KoaRecPoint",
                                          fKoaRecPointCollection, kTRUE);
  }
}


TClonesArray* KoaRec::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fKoaRecPointCollection; }
  else { return NULL; }
}

void KoaRec::Reset()
{
  fKoaRecPointCollection->Clear();
}

void KoaRec::ConstructGeometry()
{
  TString fileName=GetGeometryFileName();
  if (fileName.EndsWith(".geo")) {
    LOG(info)<<"Constructing KoaRec geometry from ASCII file "<<fileName;
    ConstructASCIIGeometry();
  } else if (fileName.EndsWith(".root")) {
    LOG(info)<<"Constructing KoaRec geometry from ROOT file "<<fileName;
    ConstructRootGeometry();
  } else {
    LOG(fatal) << "Geometry format not supported." ;
  }
}

Bool_t KoaRec::CheckIfSensitive(std::string name)
{
  for (Int_t i = 0; i < fListOfSensitives.size(); i++){
    if (name.find(fListOfSensitives[i]) != std::string::npos)    
      return true;
  }
  return false;
}

void KoaRec::ConstructASCIIGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  KoaRecGeo*  Geo  = new KoaRecGeo();
  LOG(debug)<<"Read Geo file "<<GetGeometryFileName();
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);

  Bool_t rc = geoFace->readSet(Geo);
  if (rc) { Geo->create(geoLoad->getGeoBuilder()); }
  TList* volList = Geo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  KoaRecGeoPar* par=static_cast<KoaRecGeoPar*>(rtdb->getContainer("KoaRecGeoPar"));
  TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
  TObjArray* fPassNodes = par->GetGeoPassiveNodes();

  TListIter iter(volList);
  FairGeoNode* node   = NULL;
  FairGeoVolume* aVol=NULL;

  while( (node = static_cast<FairGeoNode*>(iter.Next())) ) {
    aVol = dynamic_cast<FairGeoVolume*> ( node );
    if ( node->isSensitive()  ) {
      fSensNodes->AddLast( aVol );
    } else {
      fPassNodes->AddLast( aVol );
    }
  }
  par->setChanged();
  par->setInputVersion(fRun->GetRunId(),1);

  ProcessNodes ( volList );
}

KoaRecPoint* KoaRec::AddHit(Int_t trackID,
                            Int_t detID,
                            TVector3 posIn,
                            TVector3 posEnd,
                            TVector3 mom,
                            Double_t time,
                            Double_t length,
                            Double_t eLoss)
{
  TClonesArray& clref = *fKoaRecPointCollection;
  Int_t size = clref.GetEntriesFast();
  KoaRecPoint* myPoint = new(clref[size]) KoaRecPoint(trackID, detID, posIn, posEnd, mom, time, length, eLoss);
  // myPoint->SetLink(FairLink(-1, fEventNr, FairRootManager::Instance()->GetBranchId("MCTrack"), trackID));
  return myPoint;
}

FairModule* KoaRec::CloneModule() const
{
  return new KoaRec(*this);
}

std::map<std::string, TGeoHMatrix> KoaRec::getMisalignmentMatrices()
{
  LOG(info) << " Create misalignment matrices for Recoil detector";
  std::map<std::string, TGeoHMatrix> matrices;

  Int_t low, high;
  TString volPath;
  KoaMapEncoder* fMapEncoder = KoaMapEncoder::Instance();

  // misalignment matrix for the sensors individually
  fMapEncoder->GetRecDetIDRange(low,high);
  for(int detId=low;detId <= high;detId++){
    volPath = fGeoHandler->GetDetPathById(detId);

    Double_t dx = fSensorShiftX[detId];
    Double_t dy = fSensorShiftY[detId];
    Double_t dz = fSensorShiftZ[detId];
    Double_t dphi = fSensorRotPhi[detId];
    Double_t dtheta = fSensorRotTheta[detId];
    Double_t dpsi = fSensorRotPsi[detId];

    TGeoRotation* rrot = new TGeoRotation("rot",dphi,dtheta,dpsi);
    TGeoCombiTrans localdelta = *(new TGeoCombiTrans(dx,dy,dz, rrot));
    TGeoHMatrix ldm = TGeoHMatrix(localdelta);

    std::string thisPath(volPath);
    matrices[thisPath] = ldm;
  }

  LOG(info) << " Misalignment matrices for Recoil detector is created";
  return matrices;
}

void KoaRec::RegisterAlignmentMatrices()
{
  if (fModifyGeometry) {
    LOG(info) << " Register misalignment matrices for Recoil detector";
    std::map<std::string, TGeoHMatrix> matrices;

    Int_t low, high;
    TString volPath;
    KoaMapEncoder* fMapEncoder = KoaMapEncoder::Instance();

    // misalignment matrix for the sensors individually
    fMapEncoder->GetRecDetIDRange(low,high);
    for(int detId=low;detId <= high;detId++){
      volPath = fGeoHandler->GetDetPathById(detId);

      Double_t dx = fSensorShiftX[detId];
      Double_t dy = fSensorShiftY[detId];
      Double_t dz = fSensorShiftZ[detId];
      Double_t dphi = fSensorRotPhi[detId];
      Double_t dtheta = fSensorRotTheta[detId];
      Double_t dpsi = fSensorRotPsi[detId];

      TGeoRotation* rrot = new TGeoRotation("rot",dphi,dtheta,dpsi);
      TGeoCombiTrans localdelta = *(new TGeoCombiTrans(dx,dy,dz, rrot));
      TGeoHMatrix ldm = TGeoHMatrix(localdelta);

      std::string thisPath(volPath);
      matrices[thisPath] = ldm;

      for(int i=0;i<9;i++) {
        // LOG(info) << "Rotation" << rrot[i];
      }
      LOG(info) << "Rec, det"<<detId << ": " << dx << " " << dy << " " <<dz;
      
    }

    LOG(info) << " Misalignment matrices for Recoil detector is registered";

    FairRun* run = FairRun::Instance();
    run->AddAlignmentMatrices(matrices);
  }
}

// [TODO] Check MT usage, whether rhs data need to be cloned
KoaRec::KoaRec(const KoaRec& rhs) :
  FairDetector(rhs),
  fTrackID(-1),
  fVolumeID(-1),
  fPos(),
  fPosEnd(),
  fMom(),
  fTime(-1.),
  fLength(-1.),
  fELoss(-1),
  fKoaRecPointCollection(new TClonesArray("KoaRecPoint")),
  fModifyGeometry(kFALSE),
  fMisalignPar(nullptr),
  fNrOfSensors(-1),
  fSensorShiftX(),
  fSensorShiftY(),
  fSensorShiftZ(),
  fSensorRotPhi(),
  fSensorRotTheta(),
  fSensorRotPsi()
{
  fListOfSensitives.push_back("SensorSi");
  fListOfSensitives.push_back("SensorGe");
}

ClassImp(KoaRec)

