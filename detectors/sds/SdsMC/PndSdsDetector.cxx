#include "PndSdsDetector.h"

#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoNode.h"
#include "FairGeoRootBuilder.h"
#include "FairRootManager.h"
#include "FairRuntimeDb.h"
#include "FairRun.h"
#include "FairGeoMedia.h"
#include "FairGeoVolume.h"
#include "FairRunSim.h"
#include "FairVolume.h"
#include "FairMCEventHeader.h"

#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "TObjArray.h"
#include "TList.h"
#include "TKey.h"
#include "TGeoManager.h"
#include "TGeoVoxelFinder.h"
#include "TGeoMatrix.h"

#include "KoaStack.h"
#include "PndSdsMCPoint.h"
#include "PndSdsGeo.h"
#include "PndSdsGeoPar.h"
#include "PndGeoHandling.h"

#include <iostream>
#include <string>
#include <sstream>

class FairVolume;

// -----   Default constructor   -------------------------------------------
PndSdsDetector::PndSdsDetector() : 
    FairDetector(),
    fPersistance(kTRUE),
    fTrackID(-1),
    fVolumeID(-1),
    fPosIn(),
    fPosOut(),
    fMomIn(),
    fMomOut(),
    fTime(0.),
    fLength(0.),
    fELoss(0.),
    fGeoH(PndGeoHandling::Instance()),
    fPosIndex(0),
    fPndSdsCollection(NULL),
    fUseRadDamOption(false),
    fOutBranchName(""),
    fFolderName(""),
    fDetectorID(),
    fListOfSensitives()
{
//  fPndSdsCollection = new TClonesArray("PndSdsMCPoint");
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PndSdsDetector::PndSdsDetector (const char* name, Bool_t active)
: FairDetector(name, active),
    fPersistance(kTRUE),
    fTrackID(-1),
    fVolumeID(-1),
    fPosIn(),
    fPosOut(),
    fMomIn(),
    fMomOut(),
    fTime(0.),
    fLength(0.),
    fELoss(0.),
    fGeoH(PndGeoHandling::Instance()),
    fPosIndex(0),
    fPndSdsCollection(NULL),
    fUseRadDamOption(false),
    fOutBranchName(""),
    fFolderName(""),
    fDetectorID(),
    fListOfSensitives()
{
//  fPndSdsCollection = new TClonesArray("PndSdsMCPoint");
}
// -------------------------------------------------------------------------




// -----   Destructor   ----------------------------------------------------
PndSdsDetector::~PndSdsDetector()
{
  if (fPndSdsCollection)
  {
    fPndSdsCollection->Delete();
    delete fPndSdsCollection;
  }
}
// -------------------------------------------------------------------------
void PndSdsDetector::Initialize()
{
  std::cout<<" -I- Initializing PndSdsDetector()"<<std::endl;
  SetBranchNames();

  FairDetector::Initialize();
  if(0==gGeoManager) {
    std::cout<<" -E- No gGeoManager in PndSdsDetector::Initialize()!"<<std::endl;
    abort();
  }
  fGeoH->CreateUniqueSensorId("", fListOfSensitives);
  if(fVerboseLevel>0) fGeoH->PrintSensorNames();
}


//overwrite virtual method of FairDetector
void PndSdsDetector::SetSpecialPhysicsCuts()
{
  // Switched off. 
  return;
  
  //  FairRun* fRun = FairRun::Instance();
  //  
  //  //check for GEANT3, else abort
  //  if (strcmp(fRun->GetName(),"TGeant3") == 0) {
  //    
  //    //get material ID for customs settings
  //    int matIdVMC = gGeoManager->GetMedium("silicon")->GetId();
  //    
  //    //double cut_el = 1.0E-5;   // (GeV)
  //    //double cut_had = 1.0E-3;  // (GeV)
  //    double tofmax = 1.E10;    // (s)
  //    
  //    // Set new properties, physics cuts etc. for the TPCmixture
  //    gMC->Gstpar(matIdVMC,"PAIR",1); /** pair production*/
  //    gMC->Gstpar(matIdVMC,"COMP",1); /**Compton scattering*/
  //    gMC->Gstpar(matIdVMC,"PHOT",1); /** photo electric effect */
  //    gMC->Gstpar(matIdVMC,"PFIS",0); /**photofission*/
  //    gMC->Gstpar(matIdVMC,"DRAY",1); /**delta-ray*/
  //    gMC->Gstpar(matIdVMC,"ANNI",1); /**annihilation*/
  //    gMC->Gstpar(matIdVMC,"BREM",1); /**bremsstrahlung*/
  //    gMC->Gstpar(matIdVMC,"HADR",1); /**hadronic process*/
  //    gMC->Gstpar(matIdVMC,"MUNU",1); /**muon nuclear interaction*/
  //    gMC->Gstpar(matIdVMC,"DCAY",1); /**decay*/
  //    gMC->Gstpar(matIdVMC,"LOSS",1); /**energy loss*/
  //    gMC->Gstpar(matIdVMC,"MULS",1); /**multiple scattering*/
  //    gMC->Gstpar(matIdVMC,"STRA",0); 
  //    gMC->Gstpar(matIdVMC,"RAYL",1);
  //    
  //    gMC->Gstpar(matIdVMC,"CUTGAM",fCut_el); /** gammas (GeV)*/
  //    gMC->Gstpar(matIdVMC,"CUTELE",fCut_el); /** electrons (GeV)*/
  //    gMC->Gstpar(matIdVMC,"CUTNEU",fCut_had); /** neutral hadrons (GeV)*/
  //    gMC->Gstpar(matIdVMC,"CUTHAD",fCut_had); /** charged hadrons (GeV)*/
  //    gMC->Gstpar(matIdVMC,"CUTMUO",fCut_el); /** muons (GeV)*/
  //    gMC->Gstpar(matIdVMC,"BCUTE",fCut_el);  /** electron bremsstrahlung (GeV)*/
  //    gMC->Gstpar(matIdVMC,"BCUTM",fCut_el);  /** muon and hadron bremsstrahlung(GeV)*/ 
  //    gMC->Gstpar(matIdVMC,"DCUTE",fCut_el);  /** delta-rays by electrons (GeV)*/
  //    gMC->Gstpar(matIdVMC,"DCUTM",fCut_el);  /** delta-rays by muons (GeV)*/
  //    gMC->Gstpar(matIdVMC,"PPCUTM",fCut_el); /** direct pair production by muons (GeV)*/
  //    
  //    gMC->SetMaxNStep(1E6);
  //    
  //    Info("SetSpecialPhysicsCuts()","Using special physics cuts in MVD Sensors.");
  //  }
}




// -----   Public method ProcessHits  --------------------------------------
Bool_t  PndSdsDetector::ProcessHits(FairVolume* vol)
{
  //	std::cout<<"-I- PndSdsDetector::ProcessHits() : called. Please remove this line soon."<<std::endl;
  if ( gMC->IsTrackEntering() )
  {
    // Set parameters at entrance of volume. Reset ELoss.
    fELoss  = 0.;
    fTime   = gMC->TrackTime() * 1.0e09;
    fLength = gMC->TrackLength();
    gMC->TrackPosition(fPosIn);
    gMC->TrackMomentum(fMomIn);
  }
  
  // Sum energy loss for all steps in the active volume
  fELoss += gMC->Edep();
  
  
  // Create PndSdsMCPoint at exit of active volume
  
  if ( gMC->IsTrackExiting()    ||
      gMC->IsTrackStop()       ||
      gMC->IsTrackDisappeared()   ) {
    
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    
    if(0==fGeoH) {
      std::cout<<" -E- No PndGeoHandling loaded."<<std::endl;
      abort();
    }
    if (fVerboseLevel > 2){
      std::cout << "*******  Info from gMC *************" << std::endl;
      std::cout << "Hit in " << gMC->CurrentVolPath() << " with MCiD: " << vol->getMCid() << " PixelDetectorID: " << fVolumeID << std::endl;
      std::cout<<"VolumeID: "<<fGeoH->GetShortID(gMC->CurrentVolPath())<<std::endl;
      std::cout << "PosIn: " << fPosIn.X() << " " << fPosIn.Y() << " " << fPosIn.Z() << " " << fELoss << std::endl;
    }
    
    gMC->TrackPosition(fPosOut);
    gMC->TrackMomentum(fMomOut);
    
    if (fUseRadDamOption == false){
      if (fELoss == 0.) return kFALSE;
    }
    
    TString detPath = gMC->CurrentVolPath();
    PndSdsMCPoint* myPoint = AddHit(fTrackID, FairRootManager::Instance()->GetBranchId("MCTrack"), fGeoH->GetShortID(detPath),
                                    TVector3(fPosIn.X(),   fPosIn.Y(),   fPosIn.Z()),
                                    TVector3(fPosOut.X(),  fPosOut.Y(),  fPosOut.Z()),
                                    TVector3(fMomIn.Px(),  fMomIn.Py(),  fMomIn.Pz()),
                                    TVector3(fMomOut.Px(), fMomOut.Py(), fMomOut.Pz()),
                                    fTime, fLength, fELoss);
    
    if(fVerboseLevel>2) std::cout << myPoint << std::endl;
    
    // Increment number of PndSds points for TParticle
    KoaStack* stack = (KoaStack*) gMC->GetStack();
    stack->AddPoint(fDetectorID);
    ResetParameters();
  }
  
  return kTRUE;
}
// -------------------------------------------------------------------------



// -----   Public method EndOfEvent   --------------------------------------
void PndSdsDetector::EndOfEvent()
{
  if (fVerboseLevel)
    Print();
  
  if (fPndSdsCollection) {
	  fPndSdsCollection->Delete();
  } else {
	  if (fVerboseLevel > 1) {
		  std::cout << "-W- PndSdsDetector::EndOfEvent: no fPndSdsCollection pointer!" << std::endl;
	  }
  }
  fPosIndex = 0;
}
// -------------------------------------------------------------------------

void PndSdsDetector::FinishRun()
{
  
}

// -----   Public method Register   ----------------------------------------
void PndSdsDetector::Register()
{
	fPndSdsCollection = FairRootManager::Instance()->GetTClonesArray(fOutBranchName);
	if (! fPndSdsCollection){
		  std::cout << "-W- PndSdsDetector: New branch " << fOutBranchName << " created!" << std::endl;
		  FairRootManager::Instance()->Register(fOutBranchName, "PndSdsMCPoint", fFolderName, kTRUE);
	}
  //FairRootManager::Instance()->Register(fOutBranchName, fFolderName, fPndSdsCollection, fPersistance);
}
// -------------------------------------------------------------------------



// -----   Public method GetCollection   -----------------------------------
TClonesArray* PndSdsDetector::GetCollection(Int_t iColl) const
{
  if (iColl == 0)
    return fPndSdsCollection;
  else
    return NULL;
}
// -------------------------------------------------------------------------



// -----   Public method Print   -------------------------------------------
void PndSdsDetector::Print() const
{
  Int_t
  nHits = fPndSdsCollection->GetEntriesFast();
  
  std::cout << "-I- PndSdsDetector: " << nHits << " points registered in this event."  << std::endl;
  
  if (fVerboseLevel>1)
    for (Int_t i=0; i<nHits; i++)
      (*fPndSdsCollection)[i]->Print();
}
// -------------------------------------------------------------------------



// -----   Public method Reset   -------------------------------------------
void PndSdsDetector::Reset()
{
  fPndSdsCollection->Delete();
  ResetParameters();
}
// -------------------------------------------------------------------------



// -----   Public method CopyClones   --------------------------------------
void PndSdsDetector::CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset)
{
  Int_t
  nEntries = cl1->GetEntriesFast();
  
  std::cout << "-I- PndSdsDetector: " << nEntries << " entries to add." << std::endl;
  
  TClonesArray& clref = *cl2;
  
  PndSdsMCPoint
  *oldpoint = NULL;
  for (Int_t i=0; i<nEntries; i++)
  {
    oldpoint = (PndSdsMCPoint*) cl1->At(i);
    
    Int_t
    index = oldpoint->GetTrackID() + offset;
    
    oldpoint->SetTrackID(index);
    new (clref[fPosIndex]) PndSdsMCPoint(*oldpoint);
    fPosIndex++;
  }
  std::cout << "-I- PndSdsDetector: " << cl2->GetEntriesFast() << " merged entries."
  << std::endl;
}

// -------------------------------------------------------------------------
void PndSdsDetector::ConstructGeometry()
{
  // Set what is sensitive before creating geometry
  if (fListOfSensitives.size()==0) SetDefaultSensorNames();
  TString fileName=GetGeometryFileName();
  if(fileName.EndsWith(".geo")){
    ConstructASCIIGeometry();
  }else if(fileName.EndsWith(".root")){
    ConstructRootGeometry();
  }else{
    std::cout<< "Geometry format not supported " <<std::endl;
  }
}

// -------------------------------------------------------------------------
bool PndSdsDetector::CheckIfSensitive(std::string name)
{
  for (UInt_t i = 0; i < fListOfSensitives.size(); i++){
    if (name.find(fListOfSensitives[i]) != std::string::npos)
      return true;
  }
  return false;
}




// -----   Public method ConstructGeometry   -------------------------------
void PndSdsDetector::ConstructASCIIGeometry()
{
  // get pointer to the instantons which interface
  // to monte carlo
  
  FairGeoLoader *geoLoad = FairGeoLoader::Instance();
  FairGeoInterface *geoFace = geoLoad->getGeoInterface();
  PndSdsGeo *thePndSdsGeo  = new PndSdsGeo();
  
  thePndSdsGeo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(thePndSdsGeo);
  
  Bool_t rc = geoFace->readSet(thePndSdsGeo);
  
  if (rc)
    thePndSdsGeo->create(geoLoad->getGeoBuilder());
  
  TList* volList = thePndSdsGeo->getListOfVolumes();
  
  // store geo parameter
  FairRun *fRun = FairRun::Instance();
  
  FairRuntimeDb *rtdb= FairRun::Instance()->GetRuntimeDb();
  
  PndSdsGeoPar *par= (PndSdsGeoPar*)(rtdb->getContainer("PndSdsGeoPar"));
  
  TObjArray *fSensNodes = par->GetGeoSensitiveNodes();
  
  TObjArray *fPassNodes = par->GetGeoPassiveNodes();
  
  TListIter iter(volList);
  
  FairGeoNode   *node = NULL;
  FairGeoVolume *aVol = NULL;
  
  while( (node = (FairGeoNode*)iter.Next()) ) {
    aVol = dynamic_cast<FairGeoVolume*> ( node );
    if ( node->isSensitive()  ) {
      fSensNodes->AddLast( aVol );
    }else{
      fPassNodes->AddLast( aVol );
    }
  }
  
  par->setChanged();
  par->setInputVersion(fRun->GetRunId(),1);
  
  ProcessNodes ( volList );
}
// -------------------------------------------------------------------------

// -----   Public method SetExclusiveSensorType   -------------------------------
void PndSdsDetector::SetExclusiveSensorType(const TString sens)
{
  //Set one exclusive sensor type for testing purposes
  fListOfSensitives.clear();
  fListOfSensitives.push_back(sens.Data());
  std::cout<<"-I- PndSdsDetector: Only active sensor type is set to \""<<sens.Data()<<"\","<<std::endl;
  std::cout<<"    this is not a default setting."<<std::endl;
}
// -------------------------------------------------------------------------



// -----   Private method AddHit   -----------------------------------------
PndSdsMCPoint* PndSdsDetector::AddHit(Int_t trackID, Int_t detID, Int_t sensorID, TVector3 posIn,TVector3 posOut,TVector3 momIn, TVector3 momOut,
                                      Double_t time, Double_t length, Double_t eLoss)
{
//  TClonesArray&
//  clref = *fPndSdsCollection;
//
//  Int_t
//  size = clref.GetEntriesFast();
  fPndSdsCollection = FairRootManager::Instance()->GetTClonesArray(fOutBranchName);
  //FairMCEventHeader* header= (FairMCEventHeader*)FairRootManager::Instance()->GetObject("MCEventHeader.");

  if (fVerboseLevel >= 2)
    std::cout << "-I- PndSdsDetector: Adding Point at (" << posIn.X() << ", " << posIn.Y()
    << ", " << posIn.Z() << ") cm, (" << posOut.X() << ", " << posOut.Y()
    << ", " << posOut.Z() << ") cm,  detector " << fGeoH->GetPath(sensorID) << " " << detID << ", track "
    << trackID << ", energy loss " << eLoss*1e06 << " keV" << std::endl;
  
 PndSdsMCPoint* storedData = new((*fPndSdsCollection)[fPndSdsCollection->GetEntriesFast()]) PndSdsMCPoint(trackID, detID, sensorID, posIn, posOut,
                                        momIn, momOut, time, length, eLoss);

 return storedData;
  
}
// -------------------------------------------------------------------------



ClassImp(PndSdsDetector);
