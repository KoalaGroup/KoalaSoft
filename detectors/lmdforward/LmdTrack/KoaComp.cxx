// -------------------------------------------------------------------------
// -----         KoaComp source file              -----
// -----       Created 14/01/19 by Jens Olaf Frech      -----
// -------------------------------------------------------------------------

// This Class' Header ------------------
#include "KoaComp.h"

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
// Fit Classes -----------
#include "Math/Factory.h"
#include "Math/Functor.h"



using std::cout;
using std::endl;

KoaComp::KoaComp()
    : FairTask("3D-Straight-Line-Fit"),
      fBackPropArray(0),
      fRecoArray(0),
      fTrackArray(0),
      fKoaRecoArray(0),
      fGeoH(0) {
  fBackPropBranchName = "LMDPndTrackFilt";
  // fRecoBranchName = "LMDHitsStrip";
  fRecoBranchName = "KoaHitsPixel";
  //  fRecoBranchName = "LmdHits";
  fOutputBranchName = "LMDCompa";
  fKoaOutputBranchName = "KOALACompa";
  fOutputFolder = "Koala";

  

 
}
KoaComp::KoaComp(TString tBackPropBranchName,
		     TString tRecoBranchName,
		     TString tOutputBranchName,
		     TString tKoaOutputBranchName,
		     TString tOutputFolder)
  : FairTask("3D-Straight-Line-Fit"),
    fBackPropArray(0),
    fRecoArray(0),
    fTrackArray(0),
    fKoaRecoArray(0),
    fGeoH(0) {
  fBackPropBranchName = tBackPropBranchName;
  fRecoBranchName = tRecoBranchName;
  fOutputBranchName = tOutputBranchName;
  fKoaOutputBranchName = tKoaOutputBranchName;
  fOutputFolder = tOutputFolder;

}

KoaComp::~KoaComp() {
  //	delete fmin;
  cout << "KoaComp::~KoaComp()" << endl;
}

InitStatus KoaComp::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  if (ioman == 0) {
    Error("KoaComp::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fBackPropArray = (TClonesArray*)ioman->GetObject(fBackPropBranchName);

  if (fBackPropArray == 0) {
    Error("KoaComp::Init", "trackcand-array not found!");
    return kERROR;
  }

  fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("KoaComp::Init", "reco-array not found!");
    return kERROR;
  }

  fTrackArray = new TClonesArray("PndTrack");
  ioman->Register(fOutputBranchName, fOutputFolder, fTrackArray, kTRUE);

  fKoaRecoArray = new TClonesArray("PndSdsHit");
  ioman->Register(fKoaOutputBranchName, fOutputFolder, fKoaRecoArray, kTRUE);

  

  

  std::cout << "-I- KoaComp: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void KoaComp::Exec(Option_t*) {
  // Reset output Array
  if (fTrackArray == 0) Fatal("KoaComp::Exec", "No TrackArray");
  fTrackArray->Delete();
  if (fKoaRecoArray == 0) Fatal("KoaComp::Exec", "No KoaRecoArray");
  fKoaRecoArray->Delete();

  const unsigned int ntback = fBackPropArray->GetEntries();
  const unsigned int ntreco = fRecoArray->GetEntries();
 

int trksH0[ntback];             // hits on pl#0
  int trksH1[ntback];             // hits on pl#1
  int trksH2[ntback];             // hits on pl#2
  int trksH3[ntback];             // hits on pl#3
  vector<unsigned int> trkHn;  // number of hits in trk
 
 vector<bool> trk_accept;
 vector<int> trk_secloop;

 trk_secloop = GetPndTrackCand(); //gives position of match to i in fRecoArray 



  // Detailed output
 if(ntreco>0){
  if (fVerbose > 1)
    std::cout << " -I- KoaBackProp: contains " << ntback
              << "-I- KoaReco: contains "<< ntreco << std::endl;
  if (fVerbose > 2) {
    std::cout << " Detailed Debug info on the candidates:" << std::endl;
  }}


  // Fitting
  // ----------------------------------------------------------------------------------
  //  if(fVerbose>1)
  // std::cout<<" -I- KoaComp: start Fitting "<<std::endl;
  int rec_trk = 0;
  
  for (unsigned int track = 0; track < ntback; track++) {
    bool ok = false;
    PndTrack* trcnd = (PndTrack*)fBackPropArray->At(track);
    const int numPts = trcnd->GetUniqueID();  // read out if entry exists in BackProp
    
    for (unsigned int trecotrack = 0; trecotrack < ntreco; trecotrack++) {

    PndSdsHit* recoID = (PndSdsHit*)fRecoArray->At(trecotrack);
    const int UnID = recoID->GetUniqueID();
    double energy = recoID->GetEloss();
    double suY = recoID->GetY();

    std::cout << " Y Position before cut: "<< suY << std::endl;
    
    if (fVerbose > 1)
      {  std::cout << " KOALA Energy is " << energy << std::endl;}

    if(numPts==UnID)
      {ok = true;}

    if(energy<0.000006)
      {ok = false;}

    if(suY > 30000)    // avoids false ok through secondaries
      {ok = false;}


    if(ok){
      std::cout << " Y Position after cut: "<< suY << std::endl;}
    
    }
   trk_accept.push_back(ok);
  }  // end of BackProp's
  
  // Done--------------------------------------------------------------------------------------
 
  if (fVerbose > 2) std::cout << "Backprop finished" << std::endl;
  
  for (unsigned int i = 0; i < ntback; i++) {
    if (trk_accept[i]) {

      PndTrack* trkcnd = (PndTrack*)(fBackPropArray->At(i));
  
 
      int fds = trk_secloop[i];
      PndSdsHit* recoID = (PndSdsHit*)(fRecoArray->At(fds));
     

      
   new ((*fTrackArray)[rec_trk]) PndTrack(*(trkcnd));  // save Track


   
   new ((*fKoaRecoArray)[rec_trk]) PndSdsHit(*(recoID));  // save Track


      rec_trk++;
    }
  }
  
 
}


vector<int> KoaComp::GetPndTrackCand()
{
const unsigned int ntback = fBackPropArray->GetEntries();
  const unsigned int ntreco = fRecoArray->GetEntries();
  vector<int> koalafct; //vector for storing position of matches in second loop
  
  for (unsigned int trackfct = 0; trackfct < ntback; trackfct++) {
   
    PndTrack* trcfct = (PndTrack*)fBackPropArray->At(trackfct);
    const int lumiID = trcfct->GetUniqueID();  // read out if entry exists in BackProp
    
    for (unsigned int trecotrackfct = 0; trecotrackfct < ntreco; trecotrackfct++) {

    PndSdsHit* koalaID = (PndSdsHit*)fRecoArray->At(trecotrackfct);
    const int UID = koalaID->GetUniqueID();
    
    
    
    if(lumiID==UID)
      { koalafct.push_back(trecotrackfct); }
    }
  }
  return koalafct;
}



void KoaComp::Finish() {}

ClassImp(KoaComp);
