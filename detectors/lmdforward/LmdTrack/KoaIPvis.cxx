// -------------------------------------------------------------------------
// -----         KoaIPvis source file              -----
// -----       Created 22/05/19 by Jens Olaf Frech      -----
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
#include "KoaIPvis.h"
#include "PndTrack.h"

// PndSds includes
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsMergedHit.h"

#include <map>
#include <vector>

//Vis includes

#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLine.h>

// -----   Default constructor   -------------------------------------------
KoaIPvis::KoaIPvis()
    : FairTask("Tracks filtering task for koala"),
      fEventNr(0){
  fHitName = "LMDHitsMerged";
  fMCHitName = "LMDPoint";
  fTrkCandName = "LMDTrackCand";
  fTrkName = "LMDPndTrack";
  fTrkOutName = "LMDPndTrackFilt";
}

// -----   Destructor   ----------------------------------------------------
KoaIPvis::~KoaIPvis() {}

// -----   Public method Init   --------------------------------------------

InitStatus KoaIPvis::Init() {
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

  hIPBackProp = TH2F("BackPropOrigin", "Pos BackPropOrigin; X/cm;Y/cm", 100, -2, 2, 100 ,-2 ,2);
  hIPBPresi = TH1F("BackPropResidual", "Residual BackProp; Distance from IP/cm; Number of Events", 100, -0.1 , 5);
  hIPresiy = TH1F("BackPropResidualY", "Residual BackProp; Distance from IP in Y/cm; Number of Events", 100, -0.6 , 0.6);
  hIPresix = TH1F("BackPropResidualX", "Residual BackProp; Distance from IP in X/cm; Number of Events", 100, -0.6 , 0.6);
  hIPresiz = TH1F("BackPropResidualZ", "Residual BackProp; Distance from IP in Z/cm; Number of Events", 100, -0.01 , 0.01);
 
  
  fTrkOutArray = new TClonesArray("PndTrack");
  ioman->Register("LMDPndTrackFilt", "PndLmd", fTrkOutArray, kTRUE);

  //  htthetatphiTrkFit = new
  //  TNtuple("htthetatphiTrkFit","ntthetatphiTrk","tg_theta:tg_phi");
  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void KoaIPvis::Exec(Option_t*) {
  fTrkOutArray->Delete();

 const unsigned int gll = fTrkArray->GetEntriesFast();
int trksH0[gll];             // hits on pl#0
  int trksH1[gll];             // hits on pl#1
  int trksH2[gll];             // hits on pl#2
  int trksH3[gll];             // hits on pl#3
  vector<unsigned int> trkHn;  // number of hits in trk
 
 vector<bool> trk_accept;
  vector<double> vchi2;
  vector<double> IPX;
  vector<double> IPY;
  vector<double> IPZ;
  vector<double> IPdist;
  
  for (unsigned int i = 0; i < gll; i++) {
    trksH0[i] = -1;
    trksH1[i] = -1;
    trksH2[i] = -1;
    trksH3[i] = -1;
  }
 for (unsigned int i = 0; i < gll; i++) {
PndTrack* trkpnd = (PndTrack*)(fTrkArray->At(i));
    bool dirOK = true;
    // check trk kinematics -----
    FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();

    if (fVerbose > 0) cout << "Check Propagation!" << endl;

    double HitX = fFittedTrkP.GetX();
    double HitY = fFittedTrkP.GetY();
    double HitZ = fFittedTrkP.GetZ();
    double PX = fFittedTrkP.GetPx();
    double PY = fFittedTrkP.GetPy();
    double PZ = fFittedTrkP.GetPz();



    if (fVerbose > 3) {
      double nom = fFittedTrkP.GetUniqueID();
      cout << "Unique ID is " << nom << endl;
    }
   


    if (fVerbose > 0) cout << "HitZ is " << HitZ << endl;

    double dist = (((HitZ * PZ) + (HitY * PY) + (HitX * PX))/((PZ * PZ) + (PY * PY) + (PX * PX))); //gives scaling factor for point of closest approach

    //gives X and Y position on Z=0-plane
    double pocaX = HitX - dist * PX; 
    double pocaY = HitY - dist * PY;
    double pocaZ = HitZ - dist * PZ;

    double R = 2;
    double poca = sqrt(pocaX * pocaX + pocaY * pocaY +  pocaZ * pocaZ);
    if(R < poca){ dirOK = false;}

    if (fVerbose > 0) cout << "Distance from 0,0,0 is "<< poca  << endl;
    if (fVerbose > 1) cout << "HitX is "<< HitX <<" PX is " << PX << " x position on plane is "<< pocaX << endl;

    



  
 

  double chi2 = trkpnd->GetChi2();
    vchi2.push_back(chi2);
    IPX.push_back(pocaX);
    IPY.push_back(pocaY);
    IPZ.push_back(pocaZ);
    IPdist.push_back(poca);
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


 
    //save good events
    int rec_trk = 0;
    for (unsigned int i = 0; i < gll; i++) {
      if (trk_accept[i]) {
	if (3 < trkHn[i] ){
	PndTrack* trkpnd = (PndTrack*)(fTrkArray->At(i));

	hIPBackProp.Fill(IPX[i],IPY[i]);
	hIPBPresi.Fill(IPdist[i]);
	hIPresix.Fill(IPX[i]);
	hIPresiy.Fill(IPY[i]);
	hIPresiz.Fill(IPZ[i]);

	
	new ((*fTrkOutArray)[rec_trk]) PndTrack(*(trkpnd));  // save Track
	rec_trk++;
	}
      }
    }
    
}
void KoaIPvis::FinishTask() {
TFile f("IPBack.root","RECREATE");
 f.cd();
hIPBackProp.Write();
f.Close();

TFile g("IPResi.root","RECREATE");
 g.cd();
hIPBPresi.Write();
g.Close();

 TFile h("IPResix.root","RECREATE");
 h.cd();
hIPresix.Write();
h.Close();

 TFile k("IPResiy.root","RECREATE");
 k.cd();
hIPresiy.Write();
k.Close();


TFile mnop("IPResiz.root","RECREATE");
 mnop.cd();
hIPresiz.Write();
mnop.Close();
}

ClassImp(KoaIPvis);
