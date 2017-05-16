/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaRec.h"

#include "KoaRecPoint.h"
#include "KoaRecGeo.h"
#include "KoaRecGeoPar.h"

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
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fKoaRecPointCollection(new TClonesArray("KoaRecPoint"))
{
  fListOfSensitives.push_back("SensorSi");
  fListOfSensitives.push_back("SensorGe");
}

KoaRec::KoaRec(const char* name, Bool_t active)
  : FairDetector(name, active, kKoaRec),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fKoaRecPointCollection(new TClonesArray("KoaRecPoint"))
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
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) { return kFALSE; }
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
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

  FairRootManager::Instance()->Register("KoaRecPoint", "KoaRec",
                                        fKoaRecPointCollection, kTRUE);

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
    LOG(INFO)<<"Constructing KoaRec geometry from ASCII file "<<fileName<<FairLogger::endl;
    ConstructASCIIGeometry();
  } else if (fileName.EndsWith(".root")) {
    LOG(INFO)<<"Constructing KoaRec geometry from ROOT file "<<fileName<<FairLogger::endl;
    ConstructRootGeometry();
  } else {
    LOG(FATAL) << "Geometry format not supported." << FairLogger::endl;
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
  LOG(DEBUG)<<"Read Geo file "<<GetGeometryFileName()<<FairLogger::endl;
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

KoaRecPoint* KoaRec::AddHit(Int_t trackID, Int_t detID,
                                      TVector3 pos, TVector3 mom,
                                      Double_t time, Double_t length,
                                      Double_t eLoss)
{
  TClonesArray& clref = *fKoaRecPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) KoaRecPoint(trackID, detID, pos, mom,
         time, length, eLoss);
}

ClassImp(KoaRec)
