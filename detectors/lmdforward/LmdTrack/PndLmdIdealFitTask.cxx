//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//
//-----------------------------------------------------------

// This Class' Header ------------------
#include "PndLmdIdealFitTask.h"

// C/C++ Headers ----------------------
#include <iostream>

// Collaborating Class Headers --------
#include "FairRootManager.h"
#include "PndLinTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsDigiPixel.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TClonesArray.h"
#include "TrackData/PndTrackCand.h"
#include "TrackData/PndTrackCandHit.h"

#include "TFile.h"
#include "TGeoManager.h"
#include "TGeoTrack.h"
#include "TLorentzVector.h"

// Fit Classes -----------
#include <TMath.h>
#include <TRandom2.h>
#include <TVector3.h>
//#include <TStyle.h>
//#include <TCanvas.h>
#include <Math/Vector3D.h>
#include <TF2.h>
#include <TH1.h>
#include <TMatrixTSym.h>
#include <TPolyLine3D.h>
#include <TVirtualFitter.h>

using namespace ROOT::Math;
using namespace std;

Double_t PndLmdIdealFitTask::fz0 = 1099.;

PndLmdIdealFitTask::PndLmdIdealFitTask() : FairTask("3D-Ideal-Straight-Line") {
  fTCandBranchName = "LMDTrackCand";
  fRecoBranchName = "LMDHitsPixel";
  fMCPointBranchName = "LMDPoint";
  fDigiBranchName = "LMDPixelDigis";
  fClustBranchName = "LMDPixelClusterCand";
}

PndLmdIdealFitTask::~PndLmdIdealFitTask() {}

InitStatus PndLmdIdealFitTask::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  if (ioman == 0) {
    Error("PndLmdLinFitTask::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fTCandArray = (TClonesArray*)ioman->GetObject(fTCandBranchName);

  if (fTCandArray == 0) {
    Error("PndLmdLinFitTask::Init", "trackcand-array not found!");
    return kERROR;
  }

  fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("PndLmdLinFitTask::Init", "reco-array not found!");
    return kERROR;
  }

  fMCPointArray = (TClonesArray*)ioman->GetObject(fMCPointBranchName);

  if (fMCPointArray == 0) {
    Error("PndLmdLinFitTask::Init", "MCPoint-array not found!");
    return kERROR;
  }

  fDigiArray = (TClonesArray*)ioman->GetObject(fDigiBranchName);

  if (fDigiArray == 0) {
    Error("PndLmdLinFitTask::Init", "digi-array not found!");
    return kERROR;
  }

  fClustArray = (TClonesArray*)ioman->GetObject(fClustBranchName);

  if (fClustArray == 0) {
    Error("PndLmdLinFitTask::Init", "clust-array not found!");
    return kERROR;
  }

  fTrackArray = new TClonesArray("PndLinTrack");
  ioman->Register("LMDTrack", "PndLmd", fTrackArray, kTRUE);

  std::cout << "-I- PndLmdLinFitTask: Initialisation successfull" << std::endl;

  return kSUCCESS;
}

void PndLmdIdealFitTask::Exec(Option_t*) {
  std::cout << "PndLmdLinFitTask::Exec" << std::endl;
  // Reset output Array
  if (fTrackArray == 0) Fatal("PndLmdLinFitTask::Exec", "No TrackArray");
  fTrackArray->Delete();

  Int_t ntcand = fTCandArray->GetEntriesFast();

  // Detailed output
  if (fVerbose > 1)
    std::cout << " -I- PndLmdLinFitTask: contains " << ntcand
              << " RhoCandidates" << std::endl;
  if (fVerbose > 2) {
    std::cout << " Detailed Debug info on the candidates:" << std::endl;
    unsigned int index = 12345;  // detid=12345,  //[R.K.03/2017] unused
                                 // variable
    for (Int_t itr = 0; itr < ntcand; ++itr) {
      PndTrackCand* trcnd = (PndTrackCand*)fTCandArray->At(itr);
      std::cout << "TrackCand no. " << itr << " has " << trcnd->GetNHits()
                << " hits." << std::endl;
      std::cout << "Point: \t Index: " << std::endl;
      for (unsigned int ihit = 0; ihit < trcnd->GetNHits();
           ihit++) {                                         // fill Graph
        PndTrackCandHit theHit = trcnd->GetSortedHit(ihit);  // get hit
        index = theHit.GetHitId();
        // detid = theHit.GetDetId(); //[R.K.03/2017] unused variable
        std::cout << ihit << "\t" << index << std::endl;
      }
    }
  }

  // Cut evil event
  // if(ntcand>20){
  //  std::cout<<"ntcand="<<ntcand<<" Evil Event! skipping"<<std::endl;
  //  return;
  //}

  // Find MC-Track
  // ------------------------------------------------------------------------------
  if (fVerbose > 1)
    std::cout << " -I- PndLmdIdealFitTask: start Fitting " << std::endl;

  for (Int_t track = 0; track < ntcand; track++) {
    PndTrackCand* trcnd = (PndTrackCand*)fTCandArray->At(track);
    const int numPts = trcnd->GetNHits();  // read how many points in this track
    int fhit = ((PndTrackCandHit)trcnd->GetSortedHit(0)).GetHitId();
    int lhit = ((PndTrackCandHit)trcnd->GetSortedHit(numPts - 1)).GetHitId();

    if (fVerbose > 2)
      std::cout << "Track: " << track << " Points: " << numPts << std::endl;

    PndTrackCandHit none = trcnd->GetSortedHit(0);
    PndSdsHit* firstHit = (PndSdsHit*)fRecoArray->At(none.GetHitId());
    PndSdsClusterPixel* clust =
        (PndSdsClusterPixel*)fClustArray->At(firstHit->GetClusterIndex());
    PndSdsDigiPixel* astripdigi =
        (PndSdsDigiPixel*)fDigiArray->At(clust->GetDigiIndex(0));
    PndSdsMCPoint* firstPoint =
        (PndSdsMCPoint*)fMCPointArray->At(astripdigi->GetIndex());

    TVector3 trueTrack;
    firstPoint->Momentum(trueTrack);
    TVector3 truePos = firstPoint->GetPosition();

    // PndLinTrack* trackfit = new PndLinTrack("Lumi", truePos.Z(), truePos.X(),
    // trueTrack.X()/trueTrack.Z(), truePos.Y(), trueTrack.Y()/trueTrack.Z(),
    // 					    0, 0, 0, 0,
    // 					    0, fhit, lhit, track);
    PndLinTrack* trackfit =
        new PndLinTrack("Lumi", truePos.X(), trueTrack.X() / trueTrack.Z(),
                        truePos.Y(), trueTrack.Y() / trueTrack.Z(), truePos.Z(),
                        trueTrack.Z(), 0, fhit, lhit, track);

    new ((*fTrackArray)[track]) PndLinTrack(*(trackfit));  // save Track

  }  // end of TCand's

  // Done--------------------------------------------------------------------------------------

  std::cout << "Fitting done" << std::endl;

  return;
}

ClassImp(PndLmdIdealFitTask);
