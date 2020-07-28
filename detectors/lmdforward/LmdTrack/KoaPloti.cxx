// -------------------------------------------------------------------------
// -----         KoaComp source file              -----
// -----       Created 14/01/19 by Jens Olaf Frech      -----
// -------------------------------------------------------------------------

// This Class' Header ------------------
#include "KoaPloti.h"

// C/C++ Headers ----------------------
#include <iostream>

// Collaborating Class Headers --------
#include "FairBaseParSet.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairTrackParP.h"
#include "PndGeoHandling.h"
#include "KoaLinTrack.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsMergedHit.h"
#include "PndTrack.h"
#include "TClonesArray.h"
#include "TrackData/PndTrackCand.h"
#include "TrackData/PndTrackCandHit.h"

#include "TGraph2DErrors.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TVector3.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLine.h>
// Fit Classes -----------
#include "Math/Factory.h"
#include "Math/Functor.h"



using std::cout;
using std::endl;

KoaPloti::KoaPloti()
    : FairTask("3D-Straight-Line-Fit"),
      fCompArray(0),
      fKoaCompArray(0),
      fRecoArray(0),
      fKoaRecoArray(0),
      fGeoH(0) {
  fCompBranchName = "LMDCompa";
fKoaCompBranchName = "KOALACompa";
  // fRecoBranchName = "LMDHitsStrip";
  fRecoBranchName = "LMDHitsPixel";
  //  fRecoBranchName = "LmdHits"; 
  fKoaRecoBranchName = "KoaHitsPixel";
  

  

 
}
  KoaPloti::KoaPloti(TString tCompBranchName,
			 TString tKoaCompBranchName, 
			 TString tRecoBranchName,
			 TString tKoaRecoBranchName)
    : FairTask("3D-Straight-Line-Fit"),
      fCompArray(0),
      fKoaCompArray(0),
      fRecoArray(0),
      fKoaRecoArray(0),
      fGeoH(0) {
fCompBranchName = tCompBranchName;
fKoaCompBranchName = tKoaCompBranchName;
fRecoBranchName = tRecoBranchName;
fKoaRecoBranchName = tKoaRecoBranchName;

 

}

KoaPloti::~KoaPloti() {
  //	delete fmin;
  cout << "KoaPloti::~KoaPloti()" << endl;
}
InitStatus KoaPloti::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  

  if (ioman == 0) {
    Error("KoaComp::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fCompArray = (TClonesArray*)ioman->GetObject(fCompBranchName);

  if (fCompArray == 0) {
    Error("KoaPloti::Init", "Comp-array not found!");
    return kERROR;
  }
fKoaCompArray = (TClonesArray*)ioman->GetObject(fKoaCompBranchName);

  if (fKoaCompArray == 0) {
    Error("KoaPloti::Init", "KoaComp-array not found!");
    return kERROR;
  }

  fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("KoaPloti::Init", "reco-array not found!");
    return kERROR;
  }



fKoaRecoArray = (TClonesArray*)ioman->GetObject(fKoaRecoBranchName);

  if (fKoaRecoArray == 0) {
    Error("KoaPloti::Init", "Koareco-array not found!");
    return kERROR;
  }


 hComp2D = TH2F("hComp2D", "Pos X vs Pos Y; X/cm;Y/cm", 100, -10, -0, 100 ,-3 ,1);
 hReco2D = TH2F("hReco2D", "Pos X vs Pos Y; X/cm;Y/cm", 100, -10, -0, 100 ,-3 ,1);
 hKoaComp2D = TH2F("hKoaComp2D", "Pos Z vs Pos Y; Z/cm;Y/cm", 100, 0, 20, 100 ,-6 ,6);
 hKoaReco2D = TH2F("hKoaReco2D", "Pos Z vs Pos Y; Z/cm;Y/cm", 100, 0, 20, 100 ,-6 ,6);
  

  

  std::cout << "-I- KoaComp: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void KoaPloti::Exec(Option_t*) {
  

  const unsigned int ntcomp = fCompArray->GetEntries();
  const unsigned int ntreco = fRecoArray->GetEntries();
  const unsigned int nkocomp = fKoaCompArray->GetEntries();
  const unsigned int nkoreco = fKoaRecoArray->GetEntries();
 

 



  // Detailed output
 if(ntreco>0){
  
  if (fVerbose > 2) {
    std::cout << " Enties exits for Reco" << std::endl;
  }}


  // Fitting
  // ----------------------------------------------------------------------------------
  //  if(fVerbose>1)
  // std::cout<<" -I- KoaComp: start Fitting "<<std::endl;
  
  
  for (unsigned int track = 0; track < ntcomp; track++) {
    
    PndTrack* trcnd = (PndTrack*)fCompArray->At(track);
    FairTrackParP numPts = trcnd->GetParamFirst();

    double HitX = numPts.GetX();  
    double HitY = numPts.GetY();


    hComp2D.Fill(HitX,HitY);
    
   
  }  // end of BackProp's
 if (fVerbose > 2) {
    std::cout << " CompArray ok" << std::endl;
  }

for (unsigned int track = 0; track < ntreco; track++) {
    
    PndSdsHit* Lreco = (PndSdsHit*)fRecoArray->At(track);
   double UnY = Lreco->GetY();
   double UnX = Lreco->GetX();

 if (fVerbose > 2) {
   std::cout << " UnX at "<< track << " is " << UnX << std::endl;}

    hReco2D.Fill(UnX,UnY);


    
   
  }  // end of BackProp's
if (fVerbose > 2) {
    std::cout << " RecoArray ok" << std::endl;
  }

for (unsigned int track = 0; track < nkoreco; track++) {
    
    PndSdsHit* Lkoreco = (PndSdsHit*)fKoaRecoArray->At(track);
   double UY = Lkoreco->GetY();
   double UZ = Lkoreco->GetZ();


   hKoaReco2D.Fill(UZ,UY);
    
   
  }  // end of BackProp's

if (fVerbose > 2) {
    std::cout << " KoaRecoArray ok" << std::endl;
  }

for (unsigned int track = 0; track < nkocomp; track++) {
    
    PndSdsHit* Lkocomp = (PndSdsHit*)fKoaCompArray->At(track);
   double nY = Lkocomp->GetY();
   double nZ = Lkocomp->GetZ();


   hKoaComp2D.Fill(nZ,nY);
    
   
  }  // end of BackProp's
if (fVerbose > 2) {
    std::cout << " KoaCompArray ok" << std::endl;
  }


  
  // Done--------------------------------------------------------------------------------------
 
  if (fVerbose > 2) std::cout << "Backprop finished" << std::endl;
  

  
 
}



void KoaPloti::Finish() {



 TFile f("Reco.root","RECREATE");
 f.cd();
hReco2D.Write();
f.Close();
TFile h("Comp.root","RECREATE");

 hComp2D.Write();

  h.Close();
TFile g("KoaComp.root","RECREATE");

hKoaComp2D.Write();

 g.Close();
TFile k("KoaReco.root","RECREATE");

hKoaReco2D.Write();

 k.Close();
}

ClassImp(KoaPloti);
