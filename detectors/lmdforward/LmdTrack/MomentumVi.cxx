// -------------------------------------------------------------------------
// -----         MomentumVi source file              -----
// -----       Created 25/10/19 by Jens Olaf Frech      -----
// -------------------------------------------------------------------------

// This Class' Header ------------------
#include "MomentumVi.h"

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

MomentumVi::MomentumVi()
  : FairTask("3D-Straight-Line-Fit"),
    fMCArray(0),
    fMCTrackArray(0),
    fRecoArray(0),
    fKoalaMCArray(0),
    fKoalaMCTrackArray(0),
    fKoalaRecoArray(0),
    fBackArray(0),
    fTrkArray(0),
    fGeoH(0) {
  fMCBranchName = "LMDPoint";
  fMCTrackName = "MCTrack";
  fRecoBranchName = "LMDHitsPixel";
  fKoalaMCBranchName = "KoalaPoint";
  fKoalaMCTrackName = "MCTrack";
  fKoalaRecoBranchName = "KoalaHitsPixel";
  fBackBranchName = "LMDPndTrackFilt";
  fTrkName = "LMDPndTrack";
  
}
MomentumVi::MomentumVi(TString tMCBranchName,
			 TString tMCTrackName,
			 TString tRecoBranchName,
			 TString tKoalaMCBranchName,
			 TString tKoalaMCTrackName,
			 TString tKoalaRecoBranchName,
			 TString tBackBranchName,
			 TString tTrkName)
    : FairTask("3D-Straight-Line-Fit"),
      fMCArray(0),
      fMCTrackArray(0),
      fRecoArray(0),
      fKoalaMCArray(0),
      fKoalaMCTrackArray(0),
      fKoalaRecoArray(0),
      fBackArray(0),
      fTrkArray(0),
      fGeoH(0) {
  fMCBranchName = tMCBranchName;
  fMCTrackName = tMCTrackName;
  fRecoBranchName = tRecoBranchName;
  fKoalaMCBranchName = tKoalaMCBranchName;
  fKoalaMCTrackName = tKoalaMCTrackName;
  fKoalaRecoBranchName = tKoalaRecoBranchName;
  fBackBranchName = tBackBranchName;
  fTrkName = tTrkName;
}

MomentumVi::~MomentumVi() {
  //	delete fmin;
  cout << "MomentumVi::~MomentumVi()" << endl;
}
InitStatus MomentumVi::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  

  if (ioman == 0) {
    Error("KoalaComp::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fMCArray = (TClonesArray*)ioman->GetObject(fMCTrackName);

  if (fMCArray == 0) {
    Error("MomentumVi::Init", "MC-array not found!");
    return kERROR;
  }

   fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("MomentumVi::Init", "Reco-array not found!");
    return kERROR;
  }

 

  fKoalaMCArray = (TClonesArray*)ioman->GetObject(fKoalaMCTrackName);

 if (fKoalaMCArray == 0) {
    Error("MomentumVi::Init", "MC-array not found!");
    return kERROR;
  }

   fKoalaRecoArray = (TClonesArray*)ioman->GetObject(fKoalaRecoBranchName);

  if (fKoalaRecoArray == 0) {
    Error("MomentumVi::Init", "Reco-array not found!");
    return kERROR;
  }

  fBackArray = (TClonesArray*)ioman->GetObject(fBackBranchName);

  if (fBackArray == 0) {
    Error("MomentumVi::Init", "Comp-array not found!");
    return kERROR;
  }

fTrkArray = (TClonesArray*)ioman->GetObject(fTrkName);

  if (fTrkArray == 0) {
    Error("KoalaEffi::Init", "Trk-array not found!");
    return kERROR;
  }

 




 
  hLMDAng = TH2F("hLMDAng", "LMDAng; #theta_{X}/rad;#theta_{Y}/rad", 50, -0.1, 0.0, 100 ,-0.1 ,0.1);
  hKoalaAng = TH2F("hKoalaAng", "KoalaAng; #theta_{Z}/rad;#theta_{Y}/rad", 50, -0.00, 0.2, 100 ,-0.3 ,0.5); 
  hLMDX = TH2F("hLMDX", "LMD Px; #theta_{X}/rad;P/[GeV/c]", 50,-0.05, 0.05, 100 ,1.495   ,1.505);
  hLMDY =  TH2F("hLMDY", "LMD Py; #theta_{Y}/rad;P/[GeV/c]", 50,-0.05, 0.05, 100 ,1.495 ,1.505);
  hKoalaZ = TH2F("hKoalaZ", "Koala Pz; #theta_{Z}/rad;P/[GeV/c]", 50,-0.1, 0.1, 100 ,-0.2 ,0.2);
  hKoalaY = TH2F("hKoalaY", "Koala Py; #theta_{Y}/rad;P/[GeV/c]", 50,-0.2, 0.5, 100 ,-0.2 ,0.2);
  hLMDphi = TH2F("hLMDphi", "LMD phi/P; #phi/rad;P/[GeV/c]", 50,-3.5, -2.5, 100 ,3.197 ,15);
  hLMDtheta = TH2F("hLMDtheta", "LMD theta/P; #theta/rad;P/[GeV/c]", 50,0.005, 0.025, 100 ,3.197 ,15);
  hKoalaphi = TH2F("hKoalaphi", "Koala phi/P; #phi/rad;P/[GeV/c]", 50,-0.1, 0.6, 100 ,0.0 ,0.7);
  hKoalatheta = TH2F("hKoalatheta", "Koala theta/P; #theta/rad;P/[GeV/c]", 50, 1.3, 1.6, 100 ,0.0 ,0.7);
  hKoalathetaphi = TH2F("hKoalathetaphi", "Koala theta/phi; #theta/rad;#phi/rad", 50, 1.3, 1.6, 100 ,-0.1 ,0.6);
  hKoalaphiMC = TH2F("hKoalaphiMC", "Koala phi/P MC; #phi/rad;P/[GeV/c]", 50,-0.1, 0.6, 100 ,0.0 ,0.7);
  hKoalathetaMC = TH2F("hKoalathetaMC", "Koala theta/P MC; #theta/rad;P/[GeV/c]", 50, 1.3, 1.6, 100 ,0.0 ,0.7);
  hKoalathetaphiMC = TH2F("hKoalathetaphiMC", "Koala theta/phi MC; #theta/rad;#phi/rad", 50, 1.3, 1.6, 100 ,-0.1 ,0.6);
  hKoalaHitphi = TH2F("hKoalaHitphi", "KoalaHit phi/P MC; #phi/rad;P/[GeV/c]", 50,-0.1, 0.6, 100 ,0.0 ,0.7);
  hKoalaHittheta = TH2F("hKoalaHittheta", "KoalaHit theta/P MC; #theta/rad;P/[GeV/c]", 50, 1.3, 1.6, 100 ,0.0 ,0.7);
  hKoalaHitthetaphi = TH2F("hKoalaHitthetaphi", "KoalaHit theta/phi ; #theta/rad;#phi/rad", 50, 1.3, 1.6, 100 ,-0.1 ,0.6);
  hLMDMCphi = TH2F("hLMDMCphi", "LMD phi/P MC; #phi/rad;P/[GeV/c]", 50,-0.1, 0.6, 100 ,3.1994 ,3.20);
  hLMDMCtheta = TH2F("hLMDMCtheta", "LMD theta/P MC; #theta/rad;P/[GeV/c]", 50,-0.02, 0.02, 100 ,3.1994 ,3.2);
  hLPhi = TH1F("hLPhi","LMD Phi; #phi/rad; Number of Events", 50, -3.5 , -2.5);
  hLPhiMC = TH1F("hLPhiMC"," LMD Phi MC; #phi/rad; Number of Events", 50, -3.5 , -2.5);
  hLP = TH1F("hLP","LMD P; P/[GeV/c]; Number of Events", 50, 1.499, 1.5);
  hLPMC = TH1F("hLPMC"," LMD P MC;P/[GeV/c]; Number of Events", 50, 1.499 , 1.5);
  hLTheta = TH1F("hLTheta"," LMD Theta; #theta/rad; Number of Events", 50, 0.005 , 0.025);
  hLThetaMC = TH1F("hLThetaMC"," LMD Theta MC; #theta/rad; Number of Events", 50, 0.005 , 0.025);
  hKPhi = TH1F("hKPhi","Koala Phi;  #phi/rad; Number of Events", 50, -0.1 , 0.6);
  hKPhiMC = TH1F("hKPhiMC"," Koala Phi MC; #phi/rad; Number of Events", 50, -0.1 , 0.6);
  hKP = TH1F("hKP","Koala P; P/[GeV/c]; Number of Events", 50, 0.0 , 0.5);
  hKPMC = TH1F("hKPMC","Koala P MC; P/[GeV/c]; Number of Events", 50, 0.00 , 0.5);
  hKTheta = TH1F("hKTheta","Koala Theta; #theta/rad; Number of Events", 50, 1.3, 1.6);
  hKThetaMC = TH1F("hKThetaMC","Koala Theta MC;  #theta/rad; Number of Events", 50, 1.3, 1.6);
  hKoPhi = TH1F("hKoPhi","Koalahit Phi;  #phi/rad; Number of Events", 50, -0.1 , 0.6);
  hKoP = TH1F("hKoP","Koalahhit P; P/[GeV/c]; Number of Events", 100, 0.0 , 0.35);
  hKoTheta = TH1F("hKoTheta","Koalahit Theta; #theta/rad; Number of Events", 50, 1.3, 1.6);
  
   hKoalaThetaReco = TH1F("hKoalaThetaReco", "Koala Theta Reco; #theta/rad; Number of Events", 50,1.3, 1.6);
 
  
  
  

  std::cout << "-I- MomentumVi: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void MomentumVi::Exec(Option_t*) {
  

  const unsigned int ntMC = fMCArray->GetEntries();
  const unsigned int ntTrk = fTrkArray->GetEntries();
  const unsigned int ntBack = fBackArray->GetEntries();
  const unsigned int ntReco = fRecoArray->GetEntries();
  const unsigned int ntKoalaReco = fKoalaRecoArray->GetEntries();
 
 

 



  // Detailed output
 if(ntMC>0){
  
  if (fVerbose > 2) {
    std::cout << " Enties exits for Reco" << std::endl;
  }}


  // Fitting
  // ----------------------------------------------------------------------------------
  //  if(fVerbose>1)
  // std::cout<<" -I- KoalaComp: start Fitting "<<std::endl;

 
 int trksH0[ntBack];             // hits on pl#0
 int trksH1[ntBack];             // hits on pl#1
 int trksH2[ntBack];             // hits on pl#2
 int trksH3[ntBack];             // hits on pl#3
 vector<unsigned int> trkHn;  // number of hits in trk
 
 vector<bool> trk_accept;
 vector<double> vchi2;
 vector<double> vX;
 vector<double> vY;
 vector<double> vZ;
 vector<double> BackPX;
 vector<double> BackPY;
 vector<double> BackPZ;
 vector<double> RecoX;
 vector<double> RecoY;
 vector<double> RecoZ;


 
 double MCfill;
 MCfill =0;
double KoalaMCfill;
 KoalaMCfill =0;
 double Koalafill;
 Koalafill =0;

double Recofill;
 Recofill =0;

 
 
 double Backfill;
 Backfill =0;
 
  for (unsigned int i = 0; i < ntBack; i++) {
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
    //   std::cout << " ntBack "<< ntBack << std::endl;
    if(trk_accept[itrk]){
      if(vZ[itrk]<464){   //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	//	std::cout << " MC Loop  "<< std::endl;
	for (unsigned int iMC = 0; iMC < ntMC; iMC++){
	  KoaMCTrack* MCPos = (KoaMCTrack*)fMCArray->At(iMC);
	 
	  double pX = MCPos->GetPx();
	  double pY = MCPos->GetPy();
	  double pZ = MCPos->GetPz();
	  double E = MCPos->GetE();
	  double SZ = MCPos->GetStartZ();

	 
	
	    // if(vX[itrk]==rX){
	       
	  if(pZ > 0.5){//lumi
	    // if(rX<1040){
	    if(Backfill<0.5){
	    double fX=pX/pZ;
	    double fY=pY/pZ;
	    double Pges = sqrt((pX * pX) + (pY * pY) + (pZ * pZ));
	    TLorentzVector v1;
	    v1.SetPxPyPzE(pX,pY,pZ,E);
	    double theta = v1.Theta();
	    double phi = v1.Phi();
	      Backfill= Backfill + 1;
	      hLMDAng.Fill(fX,fY);
	      hLMDX.Fill(fX,Pges);
	      hLMDY.Fill(fY,Pges);
	      hLMDphi.Fill(phi,Pges);
	      hLMDtheta.Fill(theta,Pges);
	      hLPhi.Fill(phi);
	      hLP.Fill(Pges);
	      hLTheta.Fill(theta);
	      
	    }}
	  if(pZ < 0.5){ //Koala
	     if(SZ<100){
	      
	      if(Koalafill<0.5){
		
		double mZ=pZ/pX;
		double mY=pY/pX;
		double Pkol = sqrt((pX * pX) + (pY * pY) + (pZ * pZ));
		TLorentzVector v2;
		v2.SetPxPyPzE(pX,pY,pZ,E);
		double koltheta = v2.Theta();
		double kolphi = v2.Phi();
		
		
		
		
		
		Koalafill= Koalafill + 1;
		
		hKoalaAng.Fill(mZ,mY);
		hKoalaZ.Fill(mZ,Pkol);
		hKoalaY.Fill(mY,Pkol);
		hKoalaphi.Fill(kolphi,Pkol);
		hKoalatheta.Fill(koltheta,Pkol);
		hKoalathetaphi.Fill(koltheta,kolphi);
		hKPhi.Fill(kolphi);
		hKP.Fill(Pkol);
		hKTheta.Fill(koltheta);
		
	      }
	     }  //  }}
	  }
	}
      }}
    
  }
  for (unsigned int track = 0; track < ntMC; track++) {
    
    KoaMCTrack* Lkocomp = (KoaMCTrack*)fMCArray->At(track);
   
    double nX = Lkocomp->GetPx();
    double nY = Lkocomp->GetPy();
    double nZ = Lkocomp->GetPz();
    double nE = Lkocomp->GetE();
     
       if(nZ > 1){
	 if(MCfill < 0.5){
    
	   
	   double PMCges = sqrt((nX * nX) + (nY * nY) + (nZ * nZ));
	   TLorentzVector v3;
	   v3.SetPxPyPzE(nX,nY,nZ,nE);
	   double MCtheta = v3.Theta();
	    double MCphi = v3.Phi();
	   
	   
	   
	   MCfill = MCfill + 1;
	   hLPhiMC.Fill(MCphi);
	   hLPMC.Fill(PMCges);
	   hLThetaMC.Fill(MCtheta);
	   
	   hLMDMCphi.Fill(MCphi,PMCges);
	   hLMDMCtheta.Fill(MCtheta,PMCges);
	   
	 }
       }
       if(nZ < 1){
	 if(KoalaMCfill < 0.5){
    
	  
	   TLorentzVector v4;
	   v4.SetPxPyPzE(nX,nY,nZ,nE);
	   double Pkoges = sqrt((nX * nX) + (nY * nY) + (nZ * nZ));
	   double kotheta = v4.Theta();
	   double kophi = v4.Phi();
	   
	   
	   
	   KoalaMCfill = KoalaMCfill + 1;
	   
	   
	  
	   hKPhiMC.Fill(kophi);
	   hKPMC.Fill(Pkoges);
	   hKThetaMC.Fill(kotheta);
	   hKoalaphiMC.Fill(kophi,Pkoges);
	   hKoalathetaMC.Fill(kotheta,Pkoges);
	   hKoalathetaphiMC.Fill(kotheta,kophi);
	 }
       }
  }


for (unsigned int trReco = 0; trReco < ntReco; trReco++) {
   
    
    PndSdsHit* trrec = (PndSdsHit*)fRecoArray->At(trReco);

    
   
    double suX = trrec->GetX();
    double suY = trrec->GetY();
    double suZ = trrec->GetZ();
    

    

  
    
    
    
    
    // end of Trk's
    if (fVerbose > 2) {
      std::cout << " RecoArray ok" << std::endl;
    }
    
    
    
    
    
   RecoX.push_back(suX);
   RecoY.push_back(suY);
   RecoZ.push_back(suZ);
  
    

 }
 
 
 
 for (unsigned int irec = 0; irec < ntKoalaReco; irec++){
    std::cout << " ntKoalaReco  "<< ntKoalaReco << std::endl;
      
	PndSdsHit* Lkoreco = (PndSdsHit*)fKoalaRecoArray->At(irec);
	double UY = Lkoreco->GetY();
	double UZ = Lkoreco->GetZ();
	double UX = Lkoreco->GetX();


	double Preco = sqrt((UY * UY) + (UX * UX) + (UZ * UZ));
	double Rtheta = acos( UZ / Preco);

	hKoalaThetaReco.Fill(Rtheta);


	std::cout << " MC Reco Loop  "<< ntMC<< std::endl;
	if(ntMC<3){
	for (unsigned int iMCR = 0; iMCR < ntMC; iMCR++){
	   KoaMCTrack* MCPosi = (KoaMCTrack*)fMCArray->At(iMCR);
	  //PndSdsMCPoint* MCPos = (PndSdsMCPoint*)fMCArray->At(iMCR);
	  double peX = MCPosi->GetPx();
	  double peY = MCPosi->GetPy();
	  double peZ = MCPosi->GetPz();
	  double Ee = MCPosi->GetE();
	  double SZe = MCPosi->GetStartZ();
	  // double jX = MCPos->GetX(); //nur fuer PndSdsMCPoint verwenden
	  // double jY= MCPos->GetY();
	  
	  
	   if (fVerbose > 0) {
	     std::cout << " RecoLoop entry? " << std::endl;}
	if(Recofill < 0.5){
	     
	  if(peZ < 1){
	       if (fVerbose > 2) {
		 std::cout << " Yes " <<  std::endl;}
	       
	        if(SZe<100){
		 
	       
	       
	       double Pekol = sqrt((peX * peX) + (peY * peY) + (peZ * peZ));
	       TLorentzVector v5;
	       v5.SetPxPyPzE(peX,peY,peZ,Ee);
	       double koaltheta = v5.Theta();
	       double koalphi = v5.Phi();
	       

	       if(Pekol > 0.4){
	       std::cout << " StartZ "<< SZe << std::endl;
	       std::cout << " Pekol "<< Pekol << std::endl;
	       std::cout << " KoalPhi "<< koalphi << std::endl;
	       std::cout << " KoalTheta "<< koaltheta << std::endl;}

	       
	      
	      
	       hKoPhi.Fill(koalphi);
	       hKoP.Fill(Pekol);
	       hKoTheta.Fill(koaltheta);
	       hKoalaHitphi.Fill(koalphi,Pekol);
	       hKoalaHittheta.Fill(koaltheta,Pekol);
	       hKoalaHitthetaphi.Fill(koaltheta,koalphi);
	       
	       Recofill = Recofill +1;
	      
	       
	     
	      
	       
	       
		} 
	  } // }}
	}}
	
	}
 }

  
  
  // end of BackProp's
  if (fVerbose > 2) {
    std::cout << " KoalaCompArray ok" << std::endl;
  }
  
  

  // Done--------------------------------------------------------------------------------------
  
  if (fVerbose > 2) std::cout << "Backprop finished" << std::endl;
  
  
  
  
}


void MomentumVi::Finish() {


 





 TFile POGGERS("LMDAng.root","RECREATE");
 POGGERS.cd();
 hLMDAng.Write();
 POGGERS.Close();

 TFile Ristarte("SideAng.root","RECREATE");
 Ristarte.cd();
 hKoalaAng.Write();
 Ristarte.Close();
 
 TFile Maiza("LMDX.root","RECREATE");
 Maiza.cd();
 hLMDX.Write();
 Maiza.Close();
 
 TFile Kanna("LMDY.root","RECREATE");
 Kanna.cd();
 hLMDY.Write();
 Kanna.Close();
 
 TFile cccp("SideZ.root","RECREATE");
 cccp.cd();
 hKoalaZ.Write();
 cccp.Close();

TFile phip("PhiP.root","RECREATE");
 phip.cd();
 hLMDphi.Write();
 phip.Close();

TFile thetap("ThetaP.root","RECREATE");
 thetap.cd();
 hLMDtheta.Write();
 thetap.Close();

TFile phipkol("PhiPKol.root","RECREATE");
 phipkol.cd();
 hKoalaphi.Write();
 phipkol.Close();

TFile thetapkol("ThetaPKol.root","RECREATE");
 thetapkol.cd();
 hKoalatheta.Write();
 thetapkol.Close();

TFile thetaphikol("ThetaPhiKol.root","RECREATE");
 thetaphikol.cd();
 hKoalathetaphi.Write();
 thetaphikol.Close();

TFile phipkolmc("PhiPKolMC.root","RECREATE");
 phipkolmc.cd();
 hKoalaphiMC.Write();
 phipkolmc.Close();

TFile thetapkolmc("ThetaPKolMC.root","RECREATE");
 thetapkolmc.cd();
 hKoalathetaMC.Write();
 thetapkolmc.Close();

TFile thetaphikolmc("ThetaPhiKolMC.root","RECREATE");
 thetaphikolmc.cd();
 hKoalathetaphiMC.Write();
 thetaphikolmc.Close();

TFile phipkolhit("PhiPKolHit.root","RECREATE");
 phipkolhit.cd();
 hKoalaHitphi.Write();
 phipkolhit.Close();

TFile thetapkolhit("ThetaPKolHit.root","RECREATE");
 thetapkolhit.cd();
 hKoalaHittheta.Write();
 thetapkolhit.Close();

TFile thetaphikolhit("ThetaPhiKolHit.root","RECREATE");
 thetaphikolhit.cd();
 hKoalaHitthetaphi.Write();
 thetaphikolhit.Close();

TFile phipmc("PhiPMC.root","RECREATE");
 phipmc.cd();
 hLMDMCphi.Write();
 phipmc.Close();

TFile thetapmc("ThetaPMC.root","RECREATE");
 thetapmc.cd();
 hLMDMCtheta.Write();
 thetapmc.Close();

 
TFile h("SideY.root","RECREATE");
 h.cd();
 hKoalaY.Write();
 h.Close();

 TFile LPhi("LPhi.root","RECREATE");
 LPhi.cd();
 hLPhi.Write();
 LPhi.Close();

 TFile LPhiMC("LPhiMC.root","RECREATE");
 LPhiMC.cd();
 hLPhiMC.Write();
 LPhiMC.Close();

 TFile LP("LP.root","RECREATE");
 LP.cd();
 hLP.Write();
 LP.Close();

 TFile LPMC("LPMC.root","RECREATE");
 LPMC.cd();
 hLPMC.Write();
 LPMC.Close();

 TFile LTheta("LTheta.root","RECREATE");
 LTheta.cd();
 hLTheta.Write();
 LTheta.Close();

 TFile LThetaMC("LThetaMC.root","RECREATE");
 LThetaMC.cd();
 hLThetaMC.Write();
 LThetaMC.Close();

TFile KPhi("KPhi.root","RECREATE");
 KPhi.cd();
 hKPhi.Write();
 KPhi.Close();

TFile KoPhi("KoPhi.root","RECREATE");
 KoPhi.cd();
 hKoPhi.Write();
 KoPhi.Close();

 TFile KPhiMC("KPhiMC.root","RECREATE");
 KPhiMC.cd();
 hKPhiMC.Write();
 KPhiMC.Close();

 TFile KP("KP.root","RECREATE");
 KP.cd();
 hKP.Write();
 KP.Close();

TFile KoP("KoP.root","RECREATE");
 KoP.cd();
 hKoP.Write();
 KoP.Close();

 TFile KPMC("KPMC.root","RECREATE");
 KPMC.cd();
 hKPMC.Write();
 KPMC.Close();

 TFile KTheta("KTheta.root","RECREATE");
 KTheta.cd();
 hKTheta.Write();
 KTheta.Close();

TFile KoTheta("KoTheta.root","RECREATE");
 KoTheta.cd();
 hKoTheta.Write();
 KoTheta.Close();

 TFile KThetaMC("KThetaMC.root","RECREATE");
 KThetaMC.cd();
 hKThetaMC.Write();
 KThetaMC.Close();
 
TFile KoalaThetaReco("ThetaReco.root","RECREATE");
 KoalaThetaReco.cd();
 hKoalaThetaReco.Write();
 KoalaThetaReco.Close();


}

ClassImp(MomentumVi);
  
