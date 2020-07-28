// -------------------------------------------------------------------------
// -----                PndSdsRecoTask source file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------
// libc includes
#include <iostream>
#include <vector>

// Root includes
#include "TROOT.h"
#include "TClonesArray.h"
#include "TParticlePDG.h"
#include "TRandom.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"

// framework includes
#include "FairRootManager.h"
#include "PndSdsRecoTask.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "../pnddata/PndMCTrack.h"
#include "FairHit.h"
// PndSds includes
#include "PndSdsMCPoint.h"
#include "PndSdsDigiPixel.h"
#include "PndSdsHit.h"

// #include "PndSdsHitMaker.h"
// #include "PndSdsHitMakerFactory.h"
// #include "PndSdsDetectorDescr.h"


// -----   Default constructor   -------------------------------------------
PndSdsRecoTask::PndSdsRecoTask() :
  fHitCovMatrix(3,3),
  PndSdsTask("Reconstruction task for PANDA PndSds")
{
/*  fSigmaX=0.;
  fSigmaY=0.;
  fSigmaZ=0.;*/
}
// -------------------------------------------------------------------------
/*
// -----   Constructor   ---------------------------------------------------
PndSdsRecoTask::PndSdsRecoTask(Double_t sx, Double_t sy, Double_t sz) :
  fHitCovMatrix(3,3),
  SdsTask("Ideal reconstruction task for PANDA PndSds")
{
  fSigmaX=sx;
  fSigmaY=sy;
  fSigmaZ=sz;
}
// -------------------------------------------------------------------------

*/
// -----   Constructor   ---------------------------------------------------
PndSdsRecoTask::PndSdsRecoTask(std::string type) :
  PndSdsTask("Reconstruction task for PANDA PndSds")
{
  fMakerType = type;
  if(fVerbose>0)
    std::cout<<type<<" Reconstruction task for PANDA PndSds"<<std::endl;
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndSdsRecoTask::~PndSdsRecoTask()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus PndSdsRecoTask::Init()
{
  SetBranchNames();
  SetInBranchId();

  if(fVerbose>1)
    std::cout<<"PndSdsRecoTask::Init() called."<<std::endl;

  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) {
    std::cout << "-E- PndSdsRecoTask::Init: "
							<< "RootManager not instantiated!" << std::endl;
    return kFATAL;  }


  // Get MCTruth collection
//   fMctruthArray=(TClonesArray*) ioman->GetObject("MCTrack");
//   if(fMctruthArray==0)  {
//     std::cout << "-W- PndSdsRecoTask::Init: No McTruth array!" << std::endl;
//     return kERROR;  }


  // Get input array
  fDigiPixelArray=(TClonesArray*) ioman->GetObject(fPixelBranchName);
  if(fDigiPixelArray==0)  {
    std::cout << "-W- PndSdsRecoTask::Init: No fDigiPixelArray!" << std::endl;
    return kERROR;  }

  // Get input array
  fDigiStripArray=(TClonesArray*) ioman->GetObject(fStripBranchName);
  if(fDigiStripArray==0)  {
    std::cout << "-W- PndSdsRecoTask::Init: No fDigiStripArray!" << std::endl;
    return kERROR;  }

  // Create and register output array
  fHitOutputArray = new TClonesArray("PndSdsHit");
  ioman->Register(fOutBranchName, fFolderName, fHitOutputArray, kTRUE);

/*
  PndSdsDetectorDescr(
       Double_t pixelCellX, Double_t pixelCellXLong, Double_t pixelCellY,
       Double_t stripX, Double_t stripY, Double_t feY, Double_t feX,
       Double_t rpStripPitch, Double_t zstripPitch,
       unsigned int numOfRows, unsigned int numOfColumns,
       unsigned int numNormalColumns, Double_t rowOffsetEdge,
       unsigned int zFE, unsigned int rphiFE, unsigned int channelsFE);
*/
       // TODO remove hardcoded numbers & improve detector description class
       Double_t pixelCellX = 0.01;
       Double_t pixelCellXLong = 0.03;
       Double_t pixelCellY = 0.01;
       Double_t stripX = 0.004921;//pitch in sensor coordinates
       Double_t stripY = 0.0042969;//
       Double_t feY = 0.82;
       Double_t feX = 0.76;
       Double_t rpStripPitch = 0.;//0.00859375;
       Double_t zstripPitch = 0.;//0.00984375;
       unsigned int numOfRows = 0;
       unsigned int numOfColumns = 0;
       unsigned int numNormalColumns = 0;
       Double_t rowOffsetEdge = 0.;
       unsigned int zFE = 0;
       unsigned int rphiFE = 0;
       unsigned int channelsFE = 128;
  if(fVerbose>=1)
    std::cout<<"PndSdsRecoTask::Init(): Making PndSdsDetectorDescr "<<std::endl;

//   PndSdsDetectorDescr* detDescr = new PndSdsDetectorDescr(pixelCellX,pixelCellXLong,
//     pixelCellY,stripX,stripY,feY,feX,rpStripPitch,zstripPitch,numOfRows,
//     numOfColumns,numNormalColumns,rowOffsetEdge,zFE,rphiFE,channelsFE);
//   fHitMaker = PndSdsHitMakerFactory::theFactory().maker(fMakerType,detDescr);

//   if (fHitMaker == 0) return kERROR;

  fevent=0;

  if(fVerbose>1)
    std::cout<<"PndSdsRecoTask::Init() done."<<std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndSdsRecoTask::SetParContainers()
{
  // Get Base Container
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

}


// -----   Public method Exec   --------------------------------------------
void PndSdsRecoTask::Exec(Option_t*)
{
	// Fills PndSdsHits with the MC Truth
  // TODO filling of RecoHits, together with the sensor plane
  fevent++;
  if (fVerbose > 0) {
    std::cout<<"PndSdsRecoTask::Exec() started event no. "<<fevent<<std::endl;
  }
  if ( ! fHitOutputArray ) Fatal("Exec", "No fHitOutputArray");
  fHitOutputArray->Clear();

  if ( ! fDigiPixelArray ) Fatal("Exec", "No fDigiPixelArray");
  if ( ! fDigiStripArray ) Fatal("Exec", "No fDigiStripArray");

  // preparing arrays
  std::vector<PndSdsDigiPixel*> mvdPixelDigis;
  std::vector<PndSdsDigiStrip*> mvdStripDigis;
  std::vector<PndSdsHit*> mvdHits;

  //converting TClonesarrays of Digis to std::vector
  PndSdsDigiPixel* aDigiPixel = 0;
  for (Int_t k = 0; k < fDigiPixelArray->GetEntriesFast(); k++)
  {
    aDigiPixel = (PndSdsDigiPixel*)fDigiPixelArray->At(k);
    if (aDigiPixel != 0) {
      mvdPixelDigis.push_back(aDigiPixel);
    }
  }
  PndSdsDigiStrip* aDigiStrip = 0;
  for (Int_t h = 0; h < fDigiStripArray->GetEntriesFast(); h++)
  {
    aDigiStrip = (PndSdsDigiStrip*)fDigiStripArray->At(h);
    if (aDigiStrip != 0) {
      mvdStripDigis.push_back(aDigiStrip);
    }
  }
  if (fVerbose > 2) {
    std::cout<<"  mvdStripDigis[0] = "<<mvdStripDigis[0]<<std::endl;
    std::cout<<"PndSdsRecoTask::Exec() conversion done, start hitmaking."<<std::endl;
  }

  //  ---
//   bool success = fHitMaker->makeHits(mvdPixelDigis,mvdStripDigis,mvdHits);
  //  ---

/*  if (!success){
    std::cerr << "making PndSds hits was not successfull" << std::endl;
  }*/
  if (fVerbose > 2) {
    std::cout<<"PndSdsRecoTask::Exec() hitmaking done, reconvert now."<<std::endl;
  }

  //converting of std::vector Hits to TClonesarray
//   Int_t size = fHitOutputArray->GetEntriesFast();
//   Int_t s=0;
//   for (std::vector<PndSdsHit*>::iterator it = mvdHits.begin();
//        it != mvdHits.end(); it++)
//   { // size++ returns size and increases it then; ++size gives the increased one
//     s++;
//     if (*it==0){
//       std::cout<<"PndSdsRecoTask::Exec(): mvdHits["<<s
//                <<"] does not exist!"<<std::endl;
//       continue;
//     }
//     new ((*fHitOutputArray)[size++]) PndSdsHit(**it);
//     delete *it;
//   }
//
//   if (fVerbose > 0) {
//     std::cout<<fHitOutputArray->GetEntriesFast() <<" Hits created out of "
//              <<fDigiPixelArray->GetEntriesFast() <<" Pixel Digis and "
//              <<fDigiStripArray->GetEntriesFast() <<" Strip Digis."<<std::endl;
//   }

}





// -------------------------------------------------------------------------
void PndSdsRecoTask::InitTransMat()
{
  gGeoManager->cd(fCurrentPndSdsMCPoint->GetDetName());
  fCurrentTransMat = gGeoManager->GetCurrentMatrix();
  if (fVerbose > 1) {
    fCurrentTransMat->Print("");
  }
}

void PndSdsRecoTask::CalcDetPlane(TVector3& oVect, TVector3& uVect,TVector3& vVect)
{
  Double_t O[3], U[3], V[3], o[3], u[3], v[3];
  O[0]=oVect.x();  O[1]=oVect.y();  O[2]=oVect.z();
  U[0]=uVect.x();  U[1]=uVect.y();  U[2]=uVect.z();
  V[0]=vVect.x();  V[1]=vVect.y();  V[2]=vVect.z();

  if (fVerbose > 1) {
    std::cout<<"PndSdsRecoTask::CalcDetPlane from Detector "
             <<fCurrentPndSdsMCPoint->GetDetName()<<std::endl;
  }
  //make transformation
  fCurrentTransMat->LocalToMaster(O,o);
  fCurrentTransMat->LocalToMaster(U,u);
  fCurrentTransMat->LocalToMaster(V,v);
  oVect.SetXYZ(o[0],o[1],o[2]);
  uVect.SetXYZ(u[0],u[1],u[2]);
  vVect.SetXYZ(v[0],v[1],v[2]);
}


ClassImp(PndSdsRecoTask)
