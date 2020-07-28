// -------------------------------------------------------------------------
// -----         KoaEffi source file              -----
// -----       Created 14/01/19 by Jens Olaf Frech      -----
// -------------------------------------------------------------------------

// This Class' Header ------------------
#include "KoaEffi.h"

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

KoaEffi::KoaEffi()
  : FairTask("3D-Straight-Line-Fit"),
    fMCArray(0),
    fMCTrackArray(0),
    fRecoArray(0),
    fCompArray(0),
    fGeoH(0) {
  fMCBranchName = "KoalaLMDPoint";
  fMCTrackName = "MCTrack";
  fRecoBranchName = "KoalaHitsPixel";
  fCompBranchName = "KOALACompa";
 
}
  KoaEffi::KoaEffi(TString tMCBranchName,
		       TString tMCTrackName,
			       TString tRecoBranchName,
			       TString tCompBranchName)
    : FairTask("3D-Straight-Line-Fit"),
      fMCArray(0),
      fMCTrackArray(0),
      fRecoArray(0),
      fCompArray(0),
      fGeoH(0) {
    fMCBranchName = tMCBranchName;
    fMCTrackName = tMCTrackName;
    fRecoBranchName = tRecoBranchName;
    fCompBranchName = tCompBranchName;
}

KoaEffi::~KoaEffi() {
  //	delete fmin;
  cout << "KoaEffi::~KoaEffi()" << endl;
}
InitStatus KoaEffi::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  

  if (ioman == 0) {
    Error("KoalaComp::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fMCTrackArray = (TClonesArray*)ioman->GetObject(fMCTrackName);

  if (fMCTrackArray == 0) {
    Error("KoaEffi::Init", "MC-Track-array not found!");
    return kERROR;
  }

 fMCArray = (TClonesArray*)ioman->GetObject(fMCBranchName);

  if (fMCArray == 0) {
    Error("KoaEffi::Init", "MC-array not found!");
    return kERROR;
  }

   fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("KoaEffi::Init", "Reco-array not found!");
    return kERROR;
  }

  fCompArray = (TClonesArray*)ioman->GetObject(fCompBranchName);

  if (fCompArray == 0) {
    Error("KoaEffi::Init", "Comp-array not found!");
    return kERROR;
  }

 




  //was 100, -0.025, 0.0 , 100 , -0.015 , 0.005

  hMC2D = TH2F("hMC2D", "MC; Z/cm;Y/cm", 50, -0.05, 30, 100 ,-0.1,10);
hReco = TH2F("hReco", "MCReco; Z/cm;Y/cm", 50, -0.05, 30, 100 ,-0.1 ,10);
 hMCReco = TH2F("hMCReco", "MCReco; Z/cm;Y/cm", 50,-0.05, 30, 100 ,-0.1 ,10);
hComp =  TH2F("hComp", "MCComp; Z/cm;Y/cm", 50,-0.05, 30, 100 ,-0.1 ,10);
 hMCComp = TH2F("hMCComp", "MCComp; Z/cm;Y/cm", 50,-0.05, 30, 100 ,-0.1 ,10);
 hRecoComp = TH2F("hRecoComp", "RecoComp; Z/cm;Y/cm", 50,-0.05, 30, 100 ,-0.1 ,10);
 hKoalaResiY =  TH1F("hKoalaResiY", "KoalaResiY; Y-Y_{truth};Events", 100,-2.5, 2.5);
 hKoalaResiZ =  TH1F("hKoalaResiZ", "KoalaResiZ; Z-Z_{truth};Events", 100,-0.05, 0.05);
 
 
 
  

  

  std::cout << "-I- KoaEffi: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void KoaEffi::Exec(Option_t*) {
  

  const unsigned int ntMC = fMCTrackArray->GetEntries();
  const unsigned int ntReco = fRecoArray->GetEntries();
  const unsigned int ntComp = fCompArray->GetEntries();
  const unsigned int ntMCR = fMCArray->GetEntries();
 
 

 



  // Detailed output
 if(ntMC>0){
  
  if (fVerbose > 2) {
    std::cout << " Enties exits for Reco" << std::endl;
  }}


  // Fitting
  // ----------------------------------------------------------------------------------
  //  if(fVerbose>1)
  // std::cout<<" -I- KoalaComp: start Fitting "<<std::endl;

 
 int trksH0[ntReco];             // hits on pl#0
 int trksH1[ntReco];             // hits on pl#1
 int trksH2[ntReco];             // hits on pl#2
 int trksH3[ntReco];             // hits on pl#3
 vector<unsigned int> trkHn;  // number of hits in trk
 
 
 vector<double> MCX;
 vector<double> MCY;
 vector<double> MCZ;
 vector<double> RecoX;
 vector<double> RecoY;
 vector<double> RecoZ;
 vector<double> CompX;
 vector<double> CompY;
 vector<double> CompZ;
 
double Compfill;
 Compfill =0;

 
 double MCfill;
 MCfill =0;

 double Resifill;
 Resifill = 0;
 
 double Recofill;
 Recofill =0;
 
  for (unsigned int i = 0; i < ntReco; i++) {
    trksH0[i] = -1;
    trksH1[i] = -1;
    trksH2[i] = -1;
    trksH3[i] = -1;
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
 
 
 
 for (unsigned int irec = 0; irec < ntReco; irec++){
    std::cout << " ntReco "<< ntReco << std::endl;
      if(RecoX[irec]<499){  //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << " MC Reco Loop  "<< ntMC<< std::endl;
	for (unsigned int iMCR = 0; iMCR < ntMC; iMCR++){
	   KoaMCTrack* MCPos = (KoaMCTrack*)fMCTrackArray->At(iMCR);
	  //PndSdsMCPoint* MCPos = (PndSdsMCPoint*)fMCArray->At(iMCR);
	  double peX = MCPos->GetPx();
	  double peY = MCPos->GetPy();
	  double peZ = MCPos->GetPz();
	  double eE = MCPos->GetE();
	  // double jX = MCPos->GetX(); //nur fuer PndSdsMCPoint verwenden
	  // double jY= MCPos->GetY();
	  
	  
	   if (fVerbose > 0) {
	     std::cout << " RecoLoop entry? " << std::endl;}
	if(Recofill < 0.5){
	    // if(vX[itrk]==rX){
	       if (fVerbose > 2) {
		 std::cout << " Yes " <<  std::endl;
	       
	       // if(rX<1040){
		 std::cout << " RecoFill  "<< RecoX[irec]<< std::endl;}

	       TLorentzVector v1;
	       v1.SetPxPyPzE(peX,peY,peZ,eE);
	       double fRZm=v1.Z();
	       double fRYm=v1.Y();
	       double fRXm=v1.X();

	       double fRZ = fRZm * RecoX[irec]/fRXm;
	       double fRY = fRYm * RecoX[irec]/fRXm;
	       

	       Recofill = Recofill +1;
	      
	       
	     
	      
	       
	       hReco.Fill(fRZ,fRY);
	       
	       // }}
	    }}
	
     }
 }
  

 for (unsigned int trComp = 0; trComp < ntComp; trComp++) {
   
    
    PndSdsHit* trcomp = (PndSdsHit*)fCompArray->At(trComp);

    
   
    double suiX = trcomp->GetX();
    double suiY = trcomp->GetY();
    double suiZ = trcomp->GetZ();
    

    

  
    
    
    
    
    // end of Trk's
    if (fVerbose > 2) {
      std::cout << " CompArray ok" << std::endl;
    }
    
    
    
    
    
   CompX.push_back(suiX);
   CompY.push_back(suiY);
   CompZ.push_back(suiZ);
  
    

 }
 
 
 
 for (unsigned int ireci = 0; ireci < ntComp; ireci++){
    std::cout << " ntComp "<< ntComp << std::endl;
      if(CompX[ireci]<499){  //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << " MC Comp Loop  "<< ntMC<< std::endl;
	for (unsigned int iMCC = 0; iMCC < ntMC; iMCC++){
	   KoaMCTrack* MCPosC = (KoaMCTrack*)fMCTrackArray->At(iMCC);
	  //PndSdsMCPoint* MCPos = (PndSdsMCPoint*)fMCArray->At(iMCR);
	  double peiX = MCPosC->GetPx();
	  double peiY = MCPosC->GetPy();
	  double peiZ = MCPosC->GetPz();
	  double eiE = MCPosC->GetE();
	  // double jX = MCPos->GetX(); //nur fuer PndSdsMCPoint verwenden
	  // double jY= MCPos->GetY();
	  
	  
	   if (fVerbose > 0) {
	     std::cout << " CompLoop entry? " << std::endl;}
	if(Compfill < 0.5){
	    // if(vX[itrk]==rX){
	       if (fVerbose > 2) {
		 std::cout << " Yes " <<  std::endl;
	       
	       // if(rX<1040){
		 std::cout << " CompFill  "<< CompX[ireci]<< std::endl;}

	       TLorentzVector v2;
	       v2.SetPxPyPzE(peiX,peiY,peiZ,eiE);
	       double fCZm=v2.Z();
	       double fCYm=v2.Y();
	       double fCXm=v2.X();

	       double fCZ = fCZm * CompX[ireci]/fCXm;
	       double fCY = fCYm * CompX[ireci]/fCXm;
	       
	       

	       Compfill = Compfill +1;
	      
	       
	     
	      
	       
	       hComp.Fill(fCZ,fCY);
	       
	       // }}
	    }}
	
     }
 }
  

for (unsigned int iresi = 0; iresi < ntComp; iresi++){
      if(CompX[iresi]<499){  //muss bei Geometrieaenderungen angepasst werden
	// if(ntReco>4){
	std::cout << " MC Resi Loop  "<< ntMC<< std::endl;
	for (unsigned int iMCRs = 0; iMCRs < ntMCR; iMCRs++){
	  PndSdsMCPoint* MCPosR = (PndSdsMCPoint*)fMCArray->At(iMCRs);
	  double rX = MCPosR->GetX();
	  double rY = MCPosR->GetY();
	  double rZ = MCPosR->GetZ();
	  double jY = CompY[iresi];
	  double jZ = CompZ[iresi];

	  if(Resifill < 0.5){

	    Resifill = Resifill +1 ;

	 double  vResiY = jY -rY ;
	 double vResiZ = jZ - rZ;

	 // if(rZ>6 && rZ<7){
	 hKoalaResiY.Fill(vResiY);
	 hKoalaResiZ.Fill(vResiZ);
	 // }
	 if(fVerbose>2){	  
	  
	  std::cout << " vResiY =  "<< vResiY << " vResiZ =  "<< vResiZ << std::endl;
	  std::cout << " MCY =  "<< rY << " MCZ =  "<< rZ << std::endl;  
	  std::cout << " compY =  "<< jY << " CompZ =  "<< jZ << std::endl;     
	 }
	   
	
	  }	}}
 }
  
  

  for (unsigned int track = 0; track < ntMC; track++) {
    
    KoaMCTrack* Lkocomp = (KoaMCTrack*)fMCTrackArray->At(track);
    double nX = Lkocomp->GetPx();
    double nY = Lkocomp->GetPy();
    double nZ = Lkocomp->GetPz();
    double nE = Lkocomp->GetE();
     if(MCfill < 0.5){
     
       TLorentzVector v3;
       v3.SetPxPyPzE(nX,nY,nZ,nE);
       double mcZm=v3.Z();
       double mcYm=v3.Y();
       double mcXm=v3.X();

       double mcZ = mcZm * 90.0/mcXm;
       double mcY = mcYm * 90.0/mcXm;
    

    MCfill = MCfill + 1;
    
    MCX.push_back(nX);
    MCY.push_back(nY);
    MCZ.push_back(nZ);
    
    hMC2D.Fill(mcZ,mcY);
    // }
    }
  }
  
  
  // end of BackProp's
  if (fVerbose > 2) {
    std::cout << " KoalaCompArray ok" << std::endl;
  }
  
  

  // Done--------------------------------------------------------------------------------------
  
  if (fVerbose > 2) std::cout << "KoaEffi finished" << std::endl;
  
  
  
  
}


void KoaEffi::Finish() {


 hMCReco = hReco;
 hMCReco.Divide(&hMC2D);
 gStyle->SetOptStat(0);

 hMCComp = hComp;
 hMCComp.Divide(&hMC2D);

 hRecoComp = hComp;
 hRecoComp.Divide(&hReco);





 TFile kappa("SideMCReco.root","RECREATE");
 kappa.cd();
 //gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
hMCReco.Write();
gStyle->SetOptStat(0);
kappa.Close();

TFile komi("SideReco.root","RECREATE");
 komi.cd();
hReco.Write();
komi.Close();

TFile nomu("SideRecoComp.root","RECREATE");
 nomu.cd();
hRecoComp.Write();
 nomu.Close();

TFile stralsund("SideComp.root","RECREATE");
 stralsund.cd();
hComp.Write();
 stralsund.Close();

TFile mccc("SideMCComp.root","RECREATE");
 mccc.cd();
hMCComp.Write();
 mccc.Close();

TFile Maple("SideResiY.root","RECREATE");
 Maple.cd();
hKoalaResiY.Write();
 Maple.Close();

TFile Syrup("SideResiZ.root","RECREATE");
 Syrup.cd();
hKoalaResiZ.Write();
 Syrup.Close();


TFile h("SideMC.root","RECREATE");

 hMC2D.Write();

  h.Close();


}

ClassImp(KoaEffi);
