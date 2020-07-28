// -------------------------------------------------------------------------
// -----         PndLmdTrksFilterTask source file              -----
// -----       Created 06/05/13  by A.Karavdina               -----
// -------------------------------------------------------------------------
// libc includes
#include <iostream>

// Root includes
#include <TMatrixDSym.h>
#include "TClonesArray.h"
#include "TROOT.h"
#include "TVector3.h"

// framework includes
#include "FairHit.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "PndLmdTrksFilterTask.h"
//#include "PndMCTrack.h"
// #include "FairBaseParSet.h"
// #include "TGeant3.h"
// #include "FairTrackParH.h"
// #include "FairTrackParP.h"
// #include "TDatabasePDG.h"
#include "PndTrack.h"

// PndSds includes
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsMergedHit.h"
// PndLmd includes
//#include "PndLinTrack.h"

#include <map>
#include <vector>

// -----   Default constructor   -------------------------------------------
PndLmdTrksFilterTask::PndLmdTrksFilterTask()
    : FairTask("Tracks filtering Task for PANDA Lmd"),
      fEventNr(0),
      fdX(0),
      fdY(0) {
  flSkipKinFilt = false;
  flBOXKinFilt = false;
  flXThKinFilt = false;
  fHitName = "LMDHitsMerged";
  fMCHitName = "LMDPoint";
  //  fClusterName = clusterBranch;
  //  fDigiName = digiBrunch;
  fTrkCandName = "LMDTrackCand";
  fTrkName = "LMDPndTrack";
  fTrkOutName = "LMDPndTrackFilt";
}

// -----   Destructor   ----------------------------------------------------
PndLmdTrksFilterTask::~PndLmdTrksFilterTask() {}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdTrksFilterTask::Init() {
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if (ioman == 0) {
    Error("PndLmdTrksFilterTask::Init", "RootManager not instantiated!");
    return kERROR;
  }

  fTrkArray = (TClonesArray*)ioman->GetObject(fTrkName);
  if (fTrkArray == 0) {
    Error("PndLmdTrksFilterTask::Init", "track-array not found!");
    return kERROR;
  }

  fTrkCandArray = (TClonesArray*)ioman->GetObject(fTrkCandName);
  if (fTrkCandArray == 0) {
    Error("PndLmdTrksFilterTask::Init", "trk-cand--array not found!");
    return kERROR;
  }

  fTrkOutArray = new TClonesArray("PndTrack");
  ioman->Register("LMDPndTrackFilt", "PndLmd", fTrkOutArray, kTRUE);

  //  htthetatphiTrkFit = new
  //  TNtuple("htthetatphiTrkFit","ntthetatphiTrk","tg_theta:tg_phi");
  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PndLmdTrksFilterTask::Exec(Option_t*) {
  fTrkOutArray->Delete();
  if (fVerbose > 4) {
    cout << "" << endl;
    cout << "--------- New Event " << fEventNr << "--------" << endl;
  }

  // go through all tracks
  const unsigned int gll = fTrkArray->GetEntriesFast();
  int trksH0[gll];             // hits on pl#0
  int trksH1[gll];             // hits on pl#1
  int trksH2[gll];             // hits on pl#2
  int trksH3[gll];             // hits on pl#3
  vector<unsigned int> trkHn;  // number of hits in trk
  vector<bool> trk_accept;
  //  vector<bool> stopch; //if trks were checked by chi2 there is no need to
  //  check them futher
  vector<double> vchi2;
  for (unsigned int i = 0; i < gll; i++) {
    trksH0[i] = -1;
    trksH1[i] = -1;
    trksH2[i] = -1;
    trksH3[i] = -1;
  }
  // fill vectors with trks hits
  for (unsigned int i = 0; i < gll; i++) {
    PndTrack* trkpnd = (PndTrack*)(fTrkArray->At(i));
    bool dirOK = true;
    // check trk kinematics -----
    FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();

    if (!flSkipKinFilt) {
      TVector3 MomRecLMD(fFittedTrkP.GetPx(), fFittedTrkP.GetPy(),
                         fFittedTrkP.GetPz());
      MomRecLMD *= 1. / MomRecLMD.Mag();
      if (fVerbose > 0) cout << "Check Kinematics!" << endl;
      //      cout<<"FLAGS: "<<bool(flSkipKinFilt)<<" "<<bool(flBOXKinFilt)<<"
      //      "<<bool(flXThKinFilt)<<endl;
      if (flBOXKinFilt) {
        if (fVerbose > 0) cout << "!BOXThPhFilt!" << endl;
        double thetaCent = MomRecLMD.Theta() - 0.040;
        //    if(fVerbose<2){
        if (abs(thetaCent) > 0.011 || abs(MomRecLMD.Phi()) > 0.25)
          dirOK = false;
        if (abs(fFittedTrkP.GetX()) > 1000. || abs(fFittedTrkP.GetY()) > 1000)
          dirOK = false;  // misaligned sensors give wierd results
        //    }
      }
      //      else{
      if (flXThKinFilt) {
        // double dist_max = 1.4;
        // if(fFittedTrkP.GetPz()<2)  dist_max = 1.8;
        if (fVerbose > 0) cout << "!XThFilt!" << endl;
        double Xref = -19.1 + 1.12 * 1e3 * MomRecLMD.Theta() + fdX;
        double diffX = abs(fFittedTrkP.GetX() - Xref);
        if (fVerbose > 0)
          cout << "fFittedTrkP.GetX() = " << fFittedTrkP.GetX()
               << " Xref = " << Xref << " diffX = " << diffX << endl;
        //	  if(diffX>1.5) dirOK=false;
        if (diffX > 3.0) dirOK = false;
      }
      if (flYPhKinFilt) {
        // double dist_max = 1.4;
        // if(fFittedTrkP.GetPz()<2)  dist_max = 1.8;
        if (fVerbose > 0) cout << "!YPhFilt!" << endl;
        double Yref = -0.00651 + 0.045 * 1e3 * MomRecLMD.Phi() + fdY;
        double diffY = abs(fFittedTrkP.GetY() - Yref);
        if (fVerbose > 0)
          cout << "fFittedTrkP.GetY() = " << fFittedTrkP.GetY()
               << " Yref = " << Yref << " diffY = " << diffY << endl;
        //	  if(diffY>2.1) dirOK=false;
        if (diffY > 4.0) dirOK = false;
      }

      //      }
    }

    // //--------------------------

    double chi2 = trkpnd->GetChi2();
    vchi2.push_back(chi2);
    trk_accept.push_back(dirOK);
    //  stopch.push_back(false);

    int candID = trkpnd->GetRefIndex();
    PndTrackCand* trkcand = (PndTrackCand*)fTrkCandArray->At(candID);
    const unsigned int Ntrkcandhits = trkcand->GetNHits();
    trkHn.push_back(Ntrkcandhits);
  }

  // compare trks on hit level
  for (int ittr = 0; ittr < 2;
       ittr++) {  // repeat comparision twice to avoid accepting trk twice due
                  // to different check
    for (unsigned int i = 0; i < gll; i++) {
      //   if(stopch[i]) continue;
      if (!trk_accept[i]) continue;
      for (unsigned int j = i + 1; j < gll; j++) {
        //    if(stopch[j]) continue;
        if (!trk_accept[j]) continue;
        int coundduphit = 4;  // count dublicate hits
        if (trksH0[i] != trksH0[j]) coundduphit--;
        if (trksH1[i] != trksH1[j]) coundduphit--;
        if (trksH2[i] != trksH2[j]) coundduphit--;
        if (trksH3[i] != trksH3[j]) coundduphit--;

        if (coundduphit > 1) {        // if 2 and more hits are similar
          if (trkHn[i] > trkHn[j]) {  // take trk with higher number of hits
            trk_accept[i] = true;
            trk_accept[j] = false;
          } else {
            if (trkHn[i] < trkHn[j]) {  // take trk with higher number of hits
              trk_accept[i] = false;
              trk_accept[j] = true;
            } else {
              if (vchi2[i] > vchi2[j]) {
                trk_accept[i] = false;
                trk_accept[j] = true;
              } else {
                trk_accept[i] = true;
                trk_accept[j] = false;
              }
              // stopch[i]=true;
              // stopch[j]=true;
            }
          }
          if (fVerbose > 4) {
            cout << " trk#" << i << ": has " << trkHn[i] << "hits;  trk#" << j
                 << ": has " << trkHn[j] << " hits" << endl;
            cout << " trk#" << i << " has chi2=" << vchi2[i] << " "
                 << " trk#" << j << " has chi2=" << vchi2[j] << endl;
            if (trk_accept[i]) cout << " trk#" << i << " accepted" << endl;
            if (trk_accept[j]) cout << " trk#" << j << " accepted" << endl;
          }
        }  // if 2 and more hits are similar
        else {
          if (coundduphit > 0 && trkHn[i] == 3 &&
              trkHn[j] == 3) {  // if 1 hit is similar
            if (vchi2[i] > vchi2[j]) {
              trk_accept[i] = false;
              trk_accept[j] = true;
            } else {
              trk_accept[i] = true;
              trk_accept[j] = false;
            }
          }  // if 1 hit is similar
        }
      }
    }
  }

  // save good trks
  int rec_trk = 0;
  for (unsigned int i = 0; i < gll; i++) {
    if (trk_accept[i]) {
      PndTrack* trkpnd = (PndTrack*)(fTrkArray->At(i));

      new ((*fTrkOutArray)[rec_trk]) PndTrack(*(trkpnd));  // save Track
      rec_trk++;
    }
  }
  if (fVerbose > 2)
    cout << "Ev#" << fEventNr << ": " << rec_trk << " trks saved out of " << gll
         << endl;

  if (fVerbose > 2) cout << "PndLmdTrksFilterTask::Exec END!" << endl;
  fEventNr++;
}

void PndLmdTrksFilterTask::FinishTask() {}

ClassImp(PndLmdTrksFilterTask);
