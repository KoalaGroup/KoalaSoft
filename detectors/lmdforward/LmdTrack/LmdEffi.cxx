// -------------------------------------------------------------------------
// -----         LmdEffi source file              -----
// -----       Created 14/01/19 by Jens Olaf Frech      -----
// -------------------------------------------------------------------------

// This Class' Header ------------------
#include "LmdEffi.h"

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
#include "KoaMCTrack.h"
#include "TClonesArray.h"
#include "TrackData/PndTrackCand.h"
#include "TrackData/PndTrackCandHit.h"

#include "TGraph2DErrors.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TVector3.h"
#include "TEfficiency.h"
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
// Fit Classes -----------
#include "Math/Factory.h"
#include "Math/Functor.h"


using std::cout;
using std::endl;

LmdEffi::LmdEffi()
  : FairTask("3D-Straight-Line-Fit"),
    fMCArray(0),
    fMCTrackArray(0),
    fRecoArray(0),
    fTrkArray(0),
    fBackArray(0),
    fBackTrackArray(0),
    fCompBranchName(0),
    fGeoH(0) {
  fMCBranchName = "LMDPoint";
  fMCTrackName = "MCTrack";
  fRecoBranchName = "LMDHitsPixel";
  fTrkName = "LMDPndTrack";
  fBackBranchName = "LMDPndTrackFilt";
  fBackTrackBranchName = "LMDPndTracknoFilt";
  fCompBranchName = "LMDCompa";

  

  

 
}
  LmdEffi::LmdEffi(TString tMCBranchName,
		       TString tMCTrackName,
		       TString tRecoBranchName,
		       TString tTrkName,
		       TString tBackBranchName,
		       TString tBackTrackBranchName,
		       TString tCompBranchName)
    : FairTask("3D-Straight-Line-Fit"),
      fMCArray(0),
      fMCTrackArray(0),
      fRecoArray(0),
      fTrkArray(0),
      fBackArray(0),
      fBackTrackArray(0),
      fCompBranchName(0),
      fGeoH(0) {
    fMCBranchName = tMCBranchName;
    fMCTrackName = tMCTrackName;
    fRecoBranchName = tRecoBranchName;
    fTrkName = tTrkName;
    fBackBranchName = tBackBranchName;
    fBackTrackBranchName = tBackTrackBranchName;
    fCompBranchName = tCompBranchName;
 

}

LmdEffi::~LmdEffi() {
  //	delete fmin;
  cout << "LmdEffi::~LmdEffi()" << endl;
}
InitStatus LmdEffi::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  

  if (ioman == 0) {
    Error("LmdEffi::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fMCTrackArray = (TClonesArray*)ioman->GetObject(fMCTrackName);

  if (fMCTrackArray == 0) {
    Error("LmdEffi::Init", "MC-array not found!");
    return kERROR;
  }

   fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("LmdEffi::Init", "Reco-array not found!");
    return kERROR;
  }


   fTrkArray = (TClonesArray*)ioman->GetObject(fTrkName);

  if (fTrkArray == 0) {
    Error("LmdEffi::Init", "Trk-array not found!");
    return kERROR;
  }


  fBackArray = (TClonesArray*)ioman->GetObject(fBackBranchName);

  if (fBackArray == 0) {
    Error("LmdEffi::Init", "Back-array not found!");
    return kERROR;
  }

 fBackTrackArray = (TClonesArray*)ioman->GetObject(fBackTrackBranchName);

  if (fBackTrackArray == 0) {
    Error("LmdEffi::Init", "BackTrack-array not found!");
    return kERROR;
  }

 fCompArray = (TClonesArray*)ioman->GetObject(fCompBranchName);

  if (fCompArray == 0) {
    Error("LmdEffi::Init", "Comp-array not found!");
    return kERROR;
  }


  //was 100, -0.025, 0.0 , 100 , -0.015 , 0.005

 hMC2D = TH2F("hMC2D", "MC; X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hBack2D = TH2F("hBack2D", "MCBack;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hComp2D = TH2F("hComp2D", "MCComp;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hMCComp = TH2F("hMCComp", "MCComp;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hCompBack = TH2F("hCompBack", "CompBack;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hTrack2D = TH2F("hTrack2D", "HitRecoTrack;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hTrackProp = TH2F("hTrackProp", "HitRecoTrack;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hBackdiv = TH2F("hBackdiv", "MCBack;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hMCReco = TH2F("hMCReco", "RecoMC;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hReco = TH2F("hReco", "Reco;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
hReco4Hits = TH2F("hReco4Hits", "RecoReco4Hits;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
hRecoComp = TH2F("hRecoComp", "RecoReco4Hits;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hRecoTrack = TH2F("hRecoTrack", "RecoTrack;  X/cm;Y/cm", 2000, -8, -3, 100 ,-2 ,0.1);
 hRecoResiX = TH1F("hRecoResiX", "RecoResiX;X - X_{tr}/cm;Number of Events", 100, -0.005 , 0.005);
 hRecoResiY = TH1F("hRecoResiY", "RecoResiY;Y - Y_{tr}/cm;Number of Events", 100, -0.005 , 0.005);
 hCompResiX = TH1F("hCompResiX", "CompResiX;X - X_{tr}/cm;Number of Events", 100, -0.005 , 0.005);
 hCompResiY = TH1F("hCompResiY", "CompResiY;Y - Y_{tr}/cm;Number of Events", 100, -0.005 , 0.005);
 hCompBPResiZ = TH1F("hCompBPResiZ", "CompBPResiZ;Z - Z_{tr}/cm;Number of Events", 100, -0.01 , 0.005);
 hCompBPResiY = TH1F("hCompBPResiY", "CompBPResiY;Y - Y_{tr}/cm;Number of Events", 100, -0.5 , 0.5);
 hCompBPResiX = TH1F("hCompBPResiX", "CompBPResiX;X - X_{tr}/cm;Number of Events", 100, -0.5 , 0.5);
 hBPPos = TH2F("hBPPos", "BPPos;  X/cm;Y/cm", 100, -2, 2, 100 ,-2 ,2);
 hCompResitheta = TH1F("hCompResiTheta", "CompResi #theta ; #theta  - #theta _{tr};Number of Events", 100, -0.002 , 0.002);
 hCompResiphi = TH1F("hCompResiPhi", "CompResi #phi ; #phi  - #phi _{tr};Number of Events", 100, -0.002 , 0.002);
 
 
 
 
  

  

  std::cout << "-I- LmdEffi: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void LmdEffi::Exec(Option_t*) {
  

  const unsigned int ntMC = fMCTrackArray->GetEntries();
  const unsigned int ntReco = fRecoArray->GetEntries();
  const unsigned int ntTrk = fTrkArray->GetEntries();
  const unsigned int ntBack = fBackArray->GetEntries();
  const unsigned int ntBackTrack = fBackTrackArray->GetEntries();
  const unsigned int ntComp = fCompArray->GetEntries();
  
 

 



  // Detailed output
 if(ntMC>0){
  
  if (fVerbose > 2) {
    std::cout << " Enties exits for Reco" << std::endl;
  }}


  // Fitting
  // ----------------------------------------------------------------------------------
  //  if(fVerbose>1)
  // std::cout<<" -I- LmdComp: start Fitting "<<std::endl;

 
 int trksH0[ntTrk];             // hits on pl#0
 int trksH1[ntTrk];             // hits on pl#1
 int trksH2[ntTrk];             // hits on pl#2
 int trksH3[ntTrk];             // hits on pl#3
 vector<unsigned int> trkHn;  // number of hits in trk
 
 vector<bool> trk_accept;
 vector<bool> trk_fill;
 vector<bool> RecoHits;
 vector<double> vchi2;
 vector<bool> trk_accept_Track;
 vector<bool> trk_accept_comp;
 vector<double> vchi2comp;
 vector<bool> trk_fill_may;
 vector<double> vchi2sq;
 vector<double> vX;
 vector<double> vY;
 vector<double> vZ;
 vector<double> BackPX;
 vector<double> BackPY;
 vector<double> BackPZ;
 vector<double> vXbt;
 vector<double> vYbt;
 vector<double> vZbt;
 vector<double> BackPXbt;
 vector<double> BackPYbt;
 vector<double> BackPZbt;
 vector<double> MCX;
 vector<double> MCY;
 vector<double> MCZ;
 vector<double> RecoX;
 vector<double> RecoY;
 vector<double> RecoZ;
 vector<double> RecoPX;
 vector<double> RecoPY;
 vector<double> RecoPZ;
 vector<double> vXComp;
 vector<double> vYComp;
 vector<double> vZComp;
 vector<double> CompPX;
 vector<double> CompPY;
 vector<double> CompPZ;
 double MCfill;
 MCfill =0;
 double Backfill;
 Backfill =0;
 double Backfillbt;
 Backfillbt = 0;
 double Recofill;
 Recofill =0;
 double Compfill;
 Compfill =0;
 
  for (unsigned int i = 0; i < ntTrk; i++) {
    trksH0[i] = -1;
    trksH1[i] = -1;
    trksH2[i] = -1;
    trksH3[i] = -1;
  }
  
  
  for (unsigned int track = 0; track < ntBack; track++) {
    PndTrack* trcBack = (PndTrack*)fBackArray->At(track);
    FairTrackParP numPts = trcBack->GetParamFirst();
     bool dirOK = true;
    

    double chiX = trcBack->GetChi2();

    double PX = numPts.GetPx();
    double PY = numPts.GetPy();
    double PZ = numPts.GetPz();

 double X = numPts.GetX();
 double Y = numPts.GetY();
 double Z = numPts.GetZ();

  
    
   
  
 if (fVerbose > 2) {
    std::cout << " BackArray ok" << std::endl;
  }

  
 for (unsigned int tracki = 0; tracki < ntTrk; tracki++) {
    
    PndTrack* trci = (PndTrack*)fTrkArray->At(tracki);
    FairTrackParP trkpts = trci->GetParamFirst();

    double chi = trci->GetChi2();  

    double Px = trkpts.GetPx();
    double Py = trkpts.GetPy();
    double Pz = trkpts.GetPz();

    double TX = trkpts.GetX();
    double TY = trkpts.GetY();
    double TZ = trkpts.GetZ();
    
    if (chi!=chiX){dirOK=false;}
    
    // end of Trk's
    if (fVerbose > 2) {
      std::cout << " TrkArray ok" << std::endl;
    }
    
    vchi2.push_back(Px);
    trk_accept.push_back(dirOK);
    
    if(dirOK){
   vX.push_back(TX);
   vY.push_back(TY);
   vZ.push_back(TZ);
   BackPX.push_back(Px);
   BackPY.push_back(Py);
   BackPZ.push_back(Pz);
    }
    else{
      vX.push_back(5000);
      vY.push_back(5000);
      vZ.push_back(5000);
      BackPX.push_back(5000);
      BackPY.push_back(5000);
      BackPZ.push_back(5000);
    }
 }
  }
  for (unsigned int itrk = 0; itrk < ntBack; itrk++){
      std::cout << " ntBack "<< ntBack << std::endl;
    if(trk_accept[itrk]){
      if(vZ[itrk]<464){   //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << " MC Loop  "<< std::endl;
	for (unsigned int iMC = 0; iMC < ntMC; iMC++){
	  KoaMCTrack* MCPos = (KoaMCTrack*)fMCTrackArray->At(iMC);
	 
	  double pX = MCPos->GetPx();
	  double pY = MCPos->GetPy();
	  double pZ = MCPos->GetPz();
	  double oE = MCPos->GetE();

	 
	if(Backfill<0.5){
	    // if(vX[itrk]==rX){
	       
	  if(pZ > 1){
		 // if(rX<1040){

	    TLorentzVector v;
	    v.SetPxPyPzE(pX,pY,pZ,oE);
		 
	    double fXm=v.X();
	    double fYm=v.Y();
	    double fZm=v.Z();

	    double fX = fXm * 461/fZm;
	    double fY = fYm * 461/fZm;
	       Backfill= Backfill + 1;

	       std::cout << " MCBack Px  " << pX << " MCBack Py "<< pY << " MCBack Pz "  << pZ << " fX "<< fX << " fY "<< fY << std::endl;
	       
	      
	       hBack2D.Fill(fX,fY);
	  }
	       //  }}
	}}
	}
    }}
  //hier beginnt das einfügen
for (unsigned int com = 0; com < ntComp; com++) {
    PndTrack* trcComp = (PndTrack*)fCompArray->At(com);
    FairTrackParP numComp = trcComp->GetParamFirst();
     bool dirlOK = true;
    

    double chinX = trcComp->GetChi2();

    double PpX = numComp.GetPx();
    double PpY = numComp.GetPy();
    double PpZ = numComp.GetPz();

 double Xp = numComp.GetX();
 double Yp = numComp.GetY();
 double Zp = numComp.GetZ();

  
    
   
  
 if (fVerbose > 2) {
    std::cout << " CompArray ok" << std::endl;
  }

  
 for (unsigned int trackin = 0; trackin < ntTrk; trackin++) {
    
    PndTrack* trcin = (PndTrack*)fTrkArray->At(trackin);
    FairTrackParP trkptss = trcin->GetParamFirst();

    double chin = trcin->GetChi2();  

    double Pxn = trkptss.GetPx();
    double Pyn = trkptss.GetPy();
    double Pzn = trkptss.GetPz();

    double TXn = trkptss.GetX();
    double TYn = trkptss.GetY();
    double TZn = trkptss.GetZ();
    
    if (chin!=chinX){dirlOK=false;}
    
    // end of Trk's
    if (fVerbose > 2) {
      std::cout << "Comp  TrkArray ok" << std::endl;
    }
    
    vchi2comp.push_back(Pxn);
    trk_accept_comp.push_back(dirlOK);
    
    if(dirlOK){
   vXComp.push_back(TXn);
   vYComp.push_back(TYn);
   vZComp.push_back(TZn);
   CompPX.push_back(Pxn);
   CompPY.push_back(Pyn);
   CompPZ.push_back(Pzn);
    }
    else{
      vXComp.push_back(5000);
      vYComp.push_back(5000);
      vZComp.push_back(5000);
      CompPX.push_back(5000);
      CompPY.push_back(5000);
      CompPZ.push_back(5000);
    }
 }
  }
  for (unsigned int itrkn = 0; itrkn < ntComp; itrkn++){
    std::cout << " ntComp "<< ntComp << std::endl;
    if(trk_accept_comp[itrkn]){
      if(vZComp[itrkn]<464){   //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << "Comp MC Loop  "<< std::endl;
	for (unsigned int iMCn = 0; iMCn < ntMC; iMCn++){
	  KoaMCTrack* MCPosn = (KoaMCTrack*)fMCTrackArray->At(iMCn);
	 
	  double pXn = MCPosn->GetPx();
	  double pYn = MCPosn->GetPy();
	  double pZn = MCPosn->GetPz();
	  double nE = MCPosn->GetE();

	 
	if(Compfill<0.5){
	    // if(vX[itrk]==rX){
	  if(pZn > 1){ 
	       
		 // if(rX<1040){
	    TLorentzVector v1;
	    v1.SetPxPyPzE(pXn,pYn,pZn,nE);
		 
	    double fXnm=v1.X();
	    double fYnm=v1.Y();
	    double fZnm=v1.Z();

	    double fXn = fXnm * vZComp[itrkn]/fZnm;
	    double fYn = fYnm * vZComp[itrkn]/fZnm;
	    double fXnc = fXnm * 461/fZnm;
	    double fYnc = fYnm * 461/fZnm;
	    double ResiCompX = vXComp[itrkn] - fXn;
	    double ResiCompY = vYComp[itrkn] - fYn;

	    double thetaResiX = CompPX[itrkn] * pZn/CompPZ[itrkn];
	    double thetaResiY = CompPY[itrkn] * pZn/CompPZ[itrkn];

	    TLorentzVector vResi;
	    vResi.SetPxPyPzE(thetaResiX,thetaResiY,pZn,nE);

	    double CompTheta = vResi.Theta();
	    double CompPhi = vResi.Phi();
	    double CompThetaTh = v1.Theta();
	    double CompPhiTh = v1.Phi();

	    double ResiCompTheta = CompTheta - CompThetaTh;
	    double ResiCompPhi = CompPhi - CompPhiTh;
	       
	    
	       Compfill= Compfill + 1;

	       std::cout << " MCComp Px  " << pXn << " MCComp Py "<< pYn << " MCComp Pz "  << pZn << " fXn "<< fXn << " fYn "<< fYn << std::endl;
	       
	      
	       hComp2D.Fill(fXnc,fYnc);
	       hCompResiX.Fill(ResiCompX);
	       hCompResiY.Fill(ResiCompY);
	       hCompResiphi.Fill(ResiCompPhi);
	       hCompResitheta.Fill(ResiCompTheta);

	  }
	       //  }}
	}}
	}
    }}

  //hier endet das einfügen
  //hier beginnt das einfuegen
for (unsigned int Btrack = 0; Btrack < ntBackTrack; Btrack++) {
    PndTrack* trcBackTrack = (PndTrack*)fBackTrackArray->At(Btrack);
    FairTrackParP numPtsTrack = trcBackTrack->GetParamFirst();
     bool bdirOK = true;
    

    double chiB = trcBackTrack->GetChi2();

    double PXb = numPtsTrack.GetPx();
    double PYb = numPtsTrack.GetPy();
    double PZb = numPtsTrack.GetPz();

 double Xb = numPtsTrack.GetX();
 double Yb = numPtsTrack.GetY();
 double Zb = numPtsTrack.GetZ();

  
    
   
  
 if (fVerbose > 2) {
    std::cout << " CompArray ok" << std::endl;
  }


for (unsigned int trackib = 0; trackib < ntTrk; trackib++) {
    
    PndTrack* trcib = (PndTrack*)fTrkArray->At(trackib);
    FairTrackParP trkptsTrack = trcib->GetParamFirst();

    double chisq = trcib->GetChi2();  

    double Pxbt = trkptsTrack.GetPx();
    double Pybt = trkptsTrack.GetPy();
    double Pzbt = trkptsTrack.GetPz();

    double TXbt = trkptsTrack.GetX();
    double TYbt = trkptsTrack.GetY();
    double TZbt = trkptsTrack.GetZ();
    
    if (chisq!=chiB){bdirOK=false;}
    
    // end of Trk's
    if (fVerbose > 2) {
      std::cout << " TrkArray ok" << std::endl;
    }
    
    vchi2sq.push_back(Pxbt);
    trk_accept_Track.push_back(bdirOK);
    
    if(bdirOK){
   vXbt.push_back(TXbt);
   vYbt.push_back(TYbt);
   vZbt.push_back(TZbt);
   BackPXbt.push_back(Pxbt);
   BackPYbt.push_back(Pybt);
   BackPZbt.push_back(Pzbt);
    }
    else{
      vXbt.push_back(5000);
      vYbt.push_back(5000);
      vZbt.push_back(5000);
      BackPXbt.push_back(5000);
      BackPYbt.push_back(5000);
      BackPZbt.push_back(5000);
    }
 }
 }
  for (unsigned int itrkb = 0; itrkb < ntBackTrack; itrkb++){
    std::cout << " ntBackTrack "<< ntBackTrack << std::endl;
    if(trk_accept_Track[itrkb]){
      if(vZbt[itrkb]<464){   //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << " MC Loop BackTrack  "<< std::endl;
	for (unsigned int iMCbt = 0; iMCbt < ntMC; iMCbt++){
	  KoaMCTrack* MCPosbt = (KoaMCTrack*)fMCTrackArray->At(iMCbt);
	 
	  double pXbt = MCPosbt->GetPx();
	  double pYbt = MCPosbt->GetPy();
	  double pZbt = MCPosbt->GetPz();
	  double Ebt = MCPosbt->GetE();

	 
	  if(Backfillbt<0.5){
	    // if(vX[itrk]==rX){
	    if(pZbt > 1){
	       
		 TLorentzVector v2;
	    v2.SetPxPyPzE(pXbt,pYbt,pZbt,Ebt);
		 
	    double fXbtm=v2.X();
	    double fYbtm=v2.Y();
	    double fZbtm=v2.Z();

	    double fXbt = fXbtm * vZbt[itrkb]/fZbtm;
	    double fYbt = fYbtm * vZbt[itrkb]/fZbtm;

	    double fXbtc = fXbtm * 461/fZbtm;
	    double fYbtc = fYbtm * 461/fZbtm;


		 
	       
	      
	       Backfillbt= Backfillbt + 1;

	       std::cout << " MCBack Px BT " << pXbt << " MCBack Py BT "<< pYbt << " MCBack Pz BT "  << pZbt << " fX BT "<< fXbt << " fY BT "<< fYbt << std::endl;
	    
	       hTrack2D.Fill(fXbtc,fYbtc);
	    }
	       //  }}
	}}
	}
     }}

  //hier endet das einfuegen


 for (unsigned int trReco = 0; trReco < ntReco; trReco++) {
   bool dirrOK = false;
   bool OK4 = false;
    
    PndSdsHit* trrec = (PndSdsHit*)fRecoArray->At(trReco);

    
   
    double suX = trrec->GetX();
    double suY = trrec->GetY();
    double suZ = trrec->GetZ();
    

    if(suZ<465){
      dirrOK = true;
      for (unsigned int Reco2 = 0; Reco2 < ntReco; Reco2++) {
	PndSdsHit* trre = (PndSdsHit*)fRecoArray->At(Reco2);
	double posiZ = trre->GetZ();
	if(posiZ<485 && posiZ> 480){
	  for (unsigned int Reco3 = 0; Reco3 < ntReco; Reco3++) {
	    PndSdsHit* trre3 = (PndSdsHit*)fRecoArray->At(Reco3);
	    double posiZ3 = trre3->GetZ();
	    if(posiZ3<495 && posiZ3> 490){
	      for (unsigned int Reco4 = 0; Reco4 < ntReco; Reco4++) {
		PndSdsHit* trre4 = (PndSdsHit*)fRecoArray->At(Reco4);
		double posiZ4 = trre4->GetZ();
		if(posiZ4<505 && posiZ4> 500){
		  OK4 = true;
	}}
	}}
	}}
    }

  
    
    
    
    
    // end of Trk's
    if (fVerbose > 2) {
      std::cout << " RecoArray ok" << std::endl;
    }
    
    
    trk_fill.push_back(dirrOK);
    RecoHits.push_back(OK4);
    
    if(dirrOK){
   RecoX.push_back(suX);
   RecoY.push_back(suY);
   RecoZ.push_back(suZ);
  
    }
    else{
      RecoX.push_back(5000);
      RecoY.push_back(5000);
      RecoZ.push_back(5000);
      RecoPX.push_back(5000);
      RecoPY.push_back(5000);
      RecoPZ.push_back(5000);
    }
 }
 
 
 
 for (unsigned int irec = 0; irec < ntReco; irec++){
    std::cout << " ntReco "<< ntReco << std::endl;
    if(trk_fill[irec]){
      if(RecoZ[irec]<499){  //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << " MC Reco Loop  "<< ntMC<< std::endl;
	for (unsigned int iMCR = 0; iMCR < ntMC; iMCR++){
	   KoaMCTrack* MCPosp = (KoaMCTrack*)fMCTrackArray->At(iMCR);
	  //PndSdsMCPoint* MCPos = (PndSdsMCPoint*)fMCArray->At(iMCR);
	  double peX = MCPosp->GetPx();
	  double peY = MCPosp->GetPy();
	  double peZ = MCPosp->GetPz();
	  double eE = MCPosp->GetE();
	  // double jX = MCPosp->GetX(); //nur fuer PndSdsMCPoint verwenden
	  // double jY= MCPosp->GetY();
	  
	  
	   if (fVerbose > 0) {
	     std::cout << " RecoLoop entry? " << std::endl;}
	if(Recofill < 0.5){
	    // if(vX[itrk]==rX){
	  if(peZ > 1){
	       if (fVerbose > 2) {
		 std::cout << " Yes " <<  std::endl;
	       
	       // if(rX<1040){
		 std::cout << " RecoFill  "<< RecoX[irec]<< std::endl;}

	       TLorentzVector v3;
	    v3.SetPxPyPzE(peX,peY,peZ,eE);
		 
	    double fRXm=v3.X();
	    double fRYm=v3.Y();
	    double fRZm=v3.Z();

	    double fRX = fRXm * RecoZ[irec]/fRZm;
	    double fRY = fRYm * RecoZ[irec]/fRZm;

	    double mcEffX = fRXm * 461/fRZm;
	    double mcEffY = fRYm * 461/fRZm;
	       
	       if(RecoHits[irec]){
		 hReco4Hits.Fill(mcEffX,mcEffY);
	       }

	       Recofill = Recofill +1;
	      
	       double ResiRecoX = RecoX[irec]-fRX;
	       double ResiRecoY = RecoY[irec]-fRY;
	       hRecoResiX.Fill(ResiRecoX);
	       hRecoResiY.Fill(ResiRecoY);
	      
	       
	       hReco.Fill(mcEffX,mcEffY);
	  }
	       // }}
	    }}
	}
     }
 }
  
  

  for (unsigned int track = 0; track < ntMC; track++) {
    
    KoaMCTrack* Lkocomp = (KoaMCTrack*)fMCTrackArray->At(track);
   
    double nX = Lkocomp->GetPx();
    double nY = Lkocomp->GetPy();
    double nZ = Lkocomp->GetPz();
    double nE = Lkocomp->GetE();
     if(MCfill < 0.5){
       if(nZ > 1){
    
	 TLorentzVector v4;
	 v4.SetPxPyPzE(nX,nY,nZ,nE);
	 
	 double mcXm=v4.X();
	 double mcYm=v4.Y();
	 double mcZm=v4.Z();

	double mcX = mcXm * 461/mcZm;
	double mcY = mcYm * 461/mcZm;
    

    MCfill = MCfill + 1;
    
    MCX.push_back(nX);
    MCY.push_back(nY);
    MCZ.push_back(nZ);
    
    hMC2D.Fill(mcX,mcY);
       }
    }
  }
  
  
  // end of BackProp's
  if (fVerbose > 2) {
    std::cout << " KoaCompArray ok" << std::endl;
  }
 for (unsigned int idayo = 0; idayo < ntComp; idayo++) {
PndTrack* trkBPComp = (PndTrack*)(fCompArray->At(idayo));
    bool dirOK = true;
    // check trk kinematics -----
    FairTrackParP fFittedTrkP = trkBPComp->GetParamFirst();

    if (fVerbose > 0) cout << "Check Propagation!" << endl;

    double HitX = fFittedTrkP.GetX();
    double HitY = fFittedTrkP.GetY();
    double HitZ = fFittedTrkP.GetZ();
    double PXbp = fFittedTrkP.GetPx();
    double PYbp = fFittedTrkP.GetPy();
    double PZbp = fFittedTrkP.GetPz();


    double aprop = ((PXbp * HitX)+(PXbp * HitY) + (PZbp * HitZ))/((PXbp * PXbp) + (PYbp * PYbp) + (PZbp * PZbp));
   
    double ResiBPZ = - aprop * PZbp + HitZ;
    double ResiBPY = - aprop * PYbp + HitY;
    double ResiBPX = - aprop * PXbp + HitX;

    if (fVerbose > 0) cout << "HitZ is " << HitZ << endl;

    double dist = HitZ/PZbp; //gives scaling factor for reaching the Z=0-plane

    //gives X and Y position on Z=0-plane
    double ZplaneX = HitX - dist * PXbp; 
    double ZplaneY = HitY - dist * PYbp;

    double R = 2;
    double poca = sqrt(ZplaneX * ZplaneX + ZplaneY * ZplaneY);
    //if(R < poca){ 

    if (fVerbose > 0) cout << "Distance from 0,0,0 is "<< poca  << endl;
    hBPPos.Fill(ZplaneX,ZplaneY);
    hCompBPResiZ.Fill(ResiBPZ);
    hCompBPResiY.Fill(ResiBPY);
    hCompBPResiX.Fill(ResiBPX);
    // }
 }
  

  // Done--------------------------------------------------------------------------------------
  
  if (fVerbose > 2) std::cout << "LmdEffi finished" << std::endl;
  
  
  
  
}


void LmdEffi::Finish() {
  hBackdiv = hBack2D;
  hBackdiv.Divide(&hMC2D);
gStyle->SetOptStat(0);

 hRecoTrack = hTrack2D;
 hRecoTrack.Divide(&hReco);
 gStyle->SetOptStat(0);

 hRecoComp = hReco4Hits;
 hRecoComp.Divide(&hReco);
 gStyle->SetOptStat(0);

 hTrackProp = hBack2D;
 hTrackProp.Divide(&hTrack2D);
 gStyle->SetOptStat(0);

 hMCReco = hReco;
 hMCReco.Divide(&hMC2D);
 gStyle->SetOptStat(0);

 hMCComp = hComp2D;
 hMCComp.Divide(&hMC2D);

 hCompBack = hComp2D;
 hCompBack.Divide(&hBack2D);
 

 TFile f("Back.root","RECREATE");
 f.cd();
hBack2D.Write();
f.Close();

TFile g("Backdiv.root","RECREATE");
 g.cd();
 //gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
hBackdiv.Write();
gStyle->SetOptStat(0);
g.Close();

TFile mn("RecoTrack.root","RECREATE");
 mn.cd();
 //gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
hRecoTrack.Write();
gStyle->SetOptStat(0);
mn.Close();

TFile kawauso("BackTrack.root","RECREATE");
 kawauso.cd();
 //gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
hTrackProp.Write();
gStyle->SetOptStat(0);
kawauso.Close();

 TFile kappa("MCReco.root","RECREATE");
 kappa.cd();
 //gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
hMCReco.Write();
gStyle->SetOptStat(0);
kappa.Close();

TFile komi("EffReco.root","RECREATE");
 komi.cd();
hReco.Write();
komi.Close();

TFile end("ReComp.root","RECREATE");
 end.cd();
hRecoComp.Write();
end.Close();

TFile Doppio("MCComp.root","RECREATE");
 Doppio.cd();
 hMCComp.Write();
 Doppio.Close();

TFile Tejina("Comp2D.root","RECREATE");
 Tejina.cd();
 hComp2D.Write();
 Tejina.Close();

TFile Reimu("CompBack.root","RECREATE");
 Reimu.cd();
 hCompBack.Write();
 Reimu.Close();

 TFile BackPropPos("BackPropPos.root","RECREATE");
 BackPropPos.cd();
 hBPPos.Write();
 BackPropPos.Close();
 
TFile h("MC.root","RECREATE");

 hMC2D.Write();

  h.Close();

  TFile Erythrocyte("RecoResiX.root","RECREATE");
  Erythrocyte.cd();
  hRecoResiX.Write();
  Erythrocyte.Close();

 TFile Eosinophil("RecoResiY.root","RECREATE");
 Eosinophil.cd();
 hRecoResiY.Write();
 Eosinophil.Close();
 
 TFile Macrophage("CompResiY.root","RECREATE");
 Macrophage.cd();
 hCompResiY.Write();
 Macrophage.Close();
 
 TFile Syrup("CompBPResiZ.root","RECREATE");
 Syrup.cd();
 hCompBPResiZ.Write();
 Syrup.Close();

 TFile Basophil("CompResiX.root","RECREATE");
 Basophil.cd();
 hCompResiX.Write();
 Basophil.Close();

 TFile PMD("CompBPResiX.root","RECREATE");
 PMD.cd();
 hCompBPResiX.Write();
 PMD.Close();

 TFile Syrupy("CompBPResiY.root","RECREATE");
 Syrupy.cd();
 hCompBPResiY.Write();
 Syrupy.Close();

 
 TFile Thrombocyte("CompResiTheta.root","RECREATE");
 Thrombocyte.cd();
 hCompResitheta.Write();
 Thrombocyte.Close();
 
 TFile Lymphocyte("CompResiPhi.root","RECREATE");
 Lymphocyte.cd();
 hCompResiphi.Write();
 Lymphocyte.Close();

  TEfficiency* pEff = 0;
  if(TEfficiency::CheckConsistency(hBack2D,hMC2D)){
if (fVerbose > 2) {
    std::cout << " ConstCheck ok" << std::endl;
  }

 pEff= new TEfficiency(hBack2D,hMC2D); 
  TFile Eff("Efficiency.root","RECREATE");
  Eff.cd();
  pEff->Write();

  Eff.Close();

  }
gStyle->SetOptStat(0);
}

ClassImp(LmdEffi);
