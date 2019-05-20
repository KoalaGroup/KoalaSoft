/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "KoaFwd.h"

#include "KoaFwdPoint.h"
#include "KoaFwdGeo.h"
#include "KoaFwdGeoPar.h"

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

KoaFwd::KoaFwd()
  : FairDetector("KoaFwd", kTRUE, kKoaFwd),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fKoaFwdPointCollection(new TClonesArray("KoaFwdPoint"))
{
  fListOfSensitives.push_back("SensorSc");
  fListOfSensitives.push_back("MonitorSc");
}

KoaFwd::KoaFwd(const char* name, Bool_t active)
  : FairDetector(name, active, kKoaFwd),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fKoaFwdPointCollection(new TClonesArray("KoaFwdPoint"))
{
  fListOfSensitives.push_back("SensorSc");
  fListOfSensitives.push_back("MonitorSc");
}

KoaFwd::~KoaFwd()
{
  if (fKoaFwdPointCollection) {
    fKoaFwdPointCollection->Delete();
    delete fKoaFwdPointCollection;
  }
}

void KoaFwd::Initialize()
{
  FairDetector::Initialize();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  // Parameter Container should be init in SetParContainer, not here. Besides, par is not used in this class
  // However, if the Parameter Container is used for output and values not read from file, then it is reasonable to
  // init it here.
  KoaFwdGeoPar* par=(KoaFwdGeoPar*)(rtdb->getContainer("KoaFwdGeoPar"));
}

Bool_t  KoaFwd::ProcessHits(FairVolume* vol)
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

  // Create KoaFwdPoint at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) { return kFALSE; }
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of KoaFwd det points in TParticle
    KoaStack* stack = (KoaStack*) gMC->GetStack();
    stack->AddPoint(kKoaFwd);
  }

  return kTRUE;
}

void KoaFwd::EndOfEvent()
{

  fKoaFwdPointCollection->Clear();

}



void KoaFwd::Register()
{

  /** This will create a branch in the output tree called
      KoaFwdPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  FairRootManager::Instance()->Register("KoaFwdPoint", "KoaFwd",
                                        fKoaFwdPointCollection, kTRUE);

}


TClonesArray* KoaFwd::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fKoaFwdPointCollection; }
  else { return NULL; }
}

void KoaFwd::Reset()
{
  fKoaFwdPointCollection->Clear();
}

void KoaFwd::ConstructGeometry()
{
  TString fileName=GetGeometryFileName();
  if (fileName.EndsWith(".geo")) {
    LOG(info)<<"Constructing KoaFwd geometry from ASCII file "<<fileName;
    ConstructASCIIGeometry();
  } else if (fileName.EndsWith(".root")) {
    LOG(info)<<"Constructing KoaFwd geometry from ROOT file "<<fileName;
    ConstructRootGeometry();
  } else {
    LOG(fatal) << "Geometry format not supported." ;
  }
}

Bool_t KoaFwd::CheckIfSensitive(std::string name)
{
  for (Int_t i = 0; i < fListOfSensitives.size(); i++){
    if (name.find(fListOfSensitives[i]) != std::string::npos)    
      return true;
  }
  return false;
}

void KoaFwd::ConstructASCIIGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  KoaFwdGeo*  Geo  = new KoaFwdGeo();
  LOG(debug)<<"Read Geo file "<<GetGeometryFileName();
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);

  Bool_t rc = geoFace->readSet(Geo);
  if (rc) { Geo->create(geoLoad->getGeoBuilder()); }
  TList* volList = Geo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  KoaFwdGeoPar* par=static_cast<KoaFwdGeoPar*>(rtdb->getContainer("KoaFwdGeoPar"));
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

KoaFwdPoint* KoaFwd::AddHit(Int_t trackID, Int_t detID,
                                      TVector3 pos, TVector3 mom,
                                      Double_t time, Double_t length,
                                      Double_t eLoss)
{
  TClonesArray& clref = *fKoaFwdPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) KoaFwdPoint(trackID, detID, pos, mom,
         time, length, eLoss);
}

ClassImp(KoaFwd)
