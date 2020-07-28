//-----------------------------------------------------------
//
// Description:
//      Task to generate and store some useful histograms
//
// Author List:
//	Anastasia Karavdina
//      Mathias Michel
//
//-----------------------------------------------------------

// This Class' Header ------------------
#include "PndLmdQATask.h"

// C/C++ Headers ----------------------
#include <iostream>

// Collaborating Class Headers --------
#include "FairRootManager.h"
#include "TClonesArray.h"
#include "PndLinTrack.h"
#include "TrackData/PndTrackCand.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TrackData/PndTrackCandHit.h"
#include "PndTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsDigiPixel.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "FairTrackParH.h"
#include "PndMCTrack.h"
#include <TMath.h>
#include <TVector3.h>
#include <TRandom2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
#include <TPolyLine3D.h>
#include <Math/Vector3D.h>
#include "TH2D.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TCanvas.h"
using namespace ROOT::Math;
using namespace std;

PndLmdQATask::PndLmdQATask(TString mcHitBranch, TString mcTrkBranch, TString clusterBranch, TString digiBrunch, TString hitBranch, TString trkCandBranch,TString trackBranch, TString geaneBranch, TString outFile)
  : FairTask("Histogram creator")
{
  fmcHitName=mcHitBranch;
  fmcTrkName=mcTrkBranch;
  fHitName=hitBranch;
  fClusterName = clusterBranch;
  fDigiName = digiBrunch;
  fTrkCandName = trkCandBranch;
  fTrkName=trackBranch;
  fGeaneName=geaneBranch;
  foutFile=outFile;
  fEvent=0;
  verboseLevel=false;
  // fPlab = Plab;
}

PndLmdQATask::~PndLmdQATask()
{
  // cout<<"start... PndLmdQATask::~PndLmdQATask()"<<endl;
  // delete hResMom;
  // delete hErrMom;
  // delete hPullMom;
  // delete hResTheta;
  // delete hErrTheta;
  // delete hPullTheta;
  // delete hResPhi;
  // delete hErrPhi;
  // delete hPullPhi;

  // delete hResPointPx;
  // delete hErrPointPx;
  // delete hPullPointPx;
  
  // delete hResPointPy;
  // delete hErrPointPy;
  // delete hPullPointPy;
  
  // delete hResPointPz;
  // delete hErrPointPz;
  // delete hPullPointPz;

  // delete hResPointX;
  // delete hPullPointX;
  // delete hResPointY;
  // delete hPullPointY;
  // delete hResPointZ;
  // delete hPullPointZ;

  // delete hhits;
  // delete hchi2;
  // delete hResLumiTrkMom;
  // delete hResLumiTrkTheta;
  // delete hResLumiTrkPhi;
  // delete hResLumiTrkPointX;
  // delete hResLumiTrkPointY;
  // delete hResLumiTrkPointZ;

  // delete hResLumiTrkPointPx;
  // delete hResLumiTrkPointPy;
  // delete hResLumiTrkPointPz;

  // delete hResLumiTrkPointXErr;
  // delete hResLumiTrkPointYErr;
  // delete hResLumiTrkPointZErr;
  // delete hResLumiTrkPointPxErr;
  // delete hResLumiTrkPointPyErr;
  // delete hResLumiTrkPointPzErr;

  // delete hResLumiTrkPointXPull;
  // delete hResLumiTrkPointYPull;
  // delete hResLumiTrkPointZPull;

  // delete hResLumiTrkPointPxPull;
  // delete hResLumiTrkPointPyPull;
  // delete hResLumiTrkPointPzPull;
  // delete hResLumiTrkThetaPull;
  // delete hResLumiTrkPhiPull;

   cout<<"PndLmdQATask::~PndLmdQATask().. finished"<<endl;
}

void PndLmdQATask::WriteHists(){

  // //Write histos
  TFile *f = new TFile(foutFile,"RECREATE");
  f->Print();

  //OutputResolutionAndPulls Directory
  f->mkdir("NearIP");
  f->cd("NearIP");

  hResMom->Write();
  //  hErrMom->Write();
  //  hPullMom->Write();
  hResTheta->Write();
  hResTheta_th->Write();
  hResTheta_ph->Write();
  hErrTheta->Write();
  hPullTheta->Write();
  hResPhi->Write();
  hErrPhi->Write();
  hPullPhi->Write();

  hResPointPx->Write();
  hErrPointPx->Write();
  hPullPointPx->Write();
  
  hResPointPy->Write();
  hErrPointPy->Write();
  hPullPointPy->Write();
  
  hResPointPz->Write();
  hErrPointPz->Write();
  hPullPointPz->Write();

  hResPointX->Write();
  hPullPointX->Write();
  hResPointY->Write();
  hPullPointY->Write();
  hResPointZ->Write();
  hPullPointZ->Write();
  f->cd();

  f->mkdir("NearLMD");
  f->cd("NearLMD");
  //Near 1st LMD plane
  hResHitX->Write();
  hResHitY->Write();
  hResHitZ->Write();
  hchi2->Write();
  hhits->Write();
  hResLumiTrkMom->Write();
  hResLumiTrkTheta->Write();

  hResLumiTrkTheta2D->Write();
  hMCLumiTrkTheta2D->Write();
  hRecLumiTrkTheta2D->Write();

  hResLumiTrkPhi->Write();
  hResLumiTrkPointX->Write();
  hResLumiTrkPointY->Write();
  hResLumiTrkPointZ->Write();

  hResLumiTrkPointPx->Write();
  hResLumiTrkPointPy->Write();
  hResLumiTrkPointPz->Write();
  hResLumiTrkPointXErr->Write();
  hResLumiTrkPointYErr->Write();
  hResLumiTrkPointZErr->Write();
  hResLumiTrkPointPxErr->Write();
  hResLumiTrkPointPyErr->Write();
  hResLumiTrkPointPzErr->Write();

  hResLumiTrkPointXPull->Write();
  hResLumiTrkPointYPull->Write();
  hResLumiTrkPointZPull->Write();

  hResLumiTrkPointPxPull->Write();
  hResLumiTrkPointPyPull->Write();
  hResLumiTrkPointPzPull->Write();
  hResLumiTrkThetaPull->Write();
  hResLumiTrkPhiPull->Write();
  f->cd();

  //RecoReso Directory
  f->mkdir("Pulls");
  f->cd("Pulls");

  TCanvas *c1 = new TCanvas("pulls_before_bp");
  c1->Divide(3,2);
  c1->cd(1);
  hResLumiTrkPointXPull->Draw();
  c1->cd(2);
  hResLumiTrkPointYPull->Draw();
  c1->cd(3);
  hResLumiTrkPointZPull->Draw();
  c1->cd(4);
  hResLumiTrkPointPxPull->Draw();
  c1->cd(5);
  hResLumiTrkPointPyPull->Draw();
  c1->cd(6);
  hResLumiTrkPointPzPull->Draw();
  c1->Write();
  c1->Close();

  TCanvas *c2 = new TCanvas("pulls_after_bp");
  c2->Divide(3,2);
  c2->cd(1);
  hPullPointX->Draw();
  c2->cd(2);
  hPullPointY->Draw();
  c2->cd(3);
  hPullPointZ->Draw();
  c2->cd(4);
  hPullPointPx->Draw();
  c2->cd(5);
  hPullPointPy->Draw();
  c2->cd(6);
  hPullPointPz->Draw();
  c2->Write();
  c2->Close();
  // f->cd();

//   f->mkdir("QA_cand");
//   f->cd("QA_cand");
//   TCanvas *c3 = new TCanvas("QA_candidates_PCA_zMC");
//   c3->Divide(3,3);
//   c3->cd(1);
//   hXrecZmc->Draw("colz");
//   c3->cd(2);
//   hYrecZmc->Draw("colz");
//   c3->cd(3);
//   hZrecZmc->Draw("colz");
//   c3->cd(4);
//   herrXrecZmc->Draw("colz");
//   c3->cd(5);
//   herrYrecZmc->Draw("colz");
//   c3->cd(6);
//   herrZrecZmc->Draw("colz");
//  c3->cd(7);
//  hPullLikeX_Zmc->Draw("colz");
//  c3->cd(8);
//  hPullLikeY_Zmc->Draw("colz");
//  c3->cd(9);
//  hPullLikeZ_Zmc->Draw("colz");
//  c3->Write();
//  c3->Close();

//  TCanvas *c4 = new TCanvas("QA_candidates_dir_zMC");
//   c4->Divide(3,3);
//   c4->cd(1);
//   hThrecZmc->Draw("colz");
//   c4->cd(2);
//   hPhrecZmc->Draw("colz");
//   c4->cd(3);
//   hPrecZmc->Draw("colz");
//   c4->cd(4);
//   herrThrecZmc->Draw("colz");
//   c4->cd(5);
//   herrPhrecZmc->Draw("colz");
//   c4->cd(6);
//   herrPrecZmc->Draw("colz");
//   c4->cd(7);
//   hPullLikeTh_Zmc->Draw("colz");
//   c4->cd(8);
//   hPullLikePh_Zmc->Draw("colz");
//   c4->cd(9);
//   hPullLikeP_Zmc->Draw("colz");
//   c4->Write();
//   c4->Close();

//  TCanvas *c5 = new TCanvas("QA_resolution_vs_zMC");
//   c5->Divide(3,2);
//   c5->cd(1);
//   hResXrecZmc->Draw("colz");
//   c5->cd(2);
//   hResYrecZmc->Draw("colz");
//   c5->cd(3);
//   hResZrecZmc->Draw("colz");
//   c5->cd(4);
//   hResThrecZmc->Draw("colz");
//   c5->cd(5);
//   hResPhrecZmc->Draw("colz");
//   c5->cd(6);
//   hResPrecZmc->Draw("colz");
//   c5->Write();
//   c5->Close();

//   /////////////////////////
// TCanvas *c31 = new TCanvas("QA_candidates_PCA_xMC");
//   c31->Divide(3,3);
//   c31->cd(1);
//   hXrecXmc->Draw("colz");
//   c31->cd(2);
//   hYrecXmc->Draw("colz");
//   c31->cd(3);
//   hZrecXmc->Draw("colz");
//   c31->cd(4);
//   herrXrecXmc->Draw("colz");
//   c31->cd(5);
//   herrYrecXmc->Draw("colz");
//   c31->cd(6);
//   herrZrecXmc->Draw("colz");
//  c31->cd(7);
//  hPullLikeX_Xmc->Draw("colz");
//  c31->cd(8);
//  hPullLikeY_Xmc->Draw("colz");
//  c31->cd(9);
//  hPullLikeZ_Xmc->Draw("colz");
//  c31->Write();
//  c31->Close();

//  TCanvas *c41 = new TCanvas("QA_candidates_dir_xMC");
//   c41->Divide(3,3);
//   c41->cd(1);
//   hThrecXmc->Draw("colz");
//   c41->cd(2);
//   hPhrecXmc->Draw("colz");
//   c41->cd(3);
//   hPrecXmc->Draw("colz");
//   c41->cd(4);
//   herrThrecXmc->Draw("colz");
//   c41->cd(5);
//   herrPhrecXmc->Draw("colz");
//   c41->cd(6);
//   herrPrecXmc->Draw("colz");
//   c41->cd(7);
//   hPullLikeTh_Xmc->Draw("colz");
//   c41->cd(8);
//   hPullLikePh_Xmc->Draw("colz");
//   c41->cd(9);
//   hPullLikeP_Xmc->Draw("colz");
//   c41->Write();
//   c41->Close();

//  TCanvas *c51 = new TCanvas("QA_resolution_vs_xMC");
//   c51->Divide(3,2);
//   c51->cd(1);
//   hResXrecXmc->Draw("colz");
//   c51->cd(2);
//   hResYrecXmc->Draw("colz");
//   c51->cd(3);
//   hResZrecXmc->Draw("colz");
//   c51->cd(4);
//   hResThrecXmc->Draw("colz");
//   c51->cd(5);
//   hResPhrecXmc->Draw("colz");
//   c51->cd(6);
//   hResPrecXmc->Draw("colz");
//   c51->Write();
//   c51->Close();


//  /////////////////////////
// TCanvas *c32 = new TCanvas("QA_candidates_PCA_yMC");
//   c32->Divide(3,3);
//   c32->cd(1);
//   hXrecYmc->Draw("colz");
//   c32->cd(2);
//   hYrecYmc->Draw("colz");
//   c32->cd(3);
//   hZrecYmc->Draw("colz");
//   c32->cd(4);
//   herrXrecYmc->Draw("colz");
//   c32->cd(5);
//   herrYrecYmc->Draw("colz");
//   c32->cd(6);
//   herrZrecYmc->Draw("colz");
//  c32->cd(7);
//  hPullLikeX_Ymc->Draw("colz");
//  c32->cd(8);
//  hPullLikeY_Ymc->Draw("colz");
//  c32->cd(9);
//  hPullLikeZ_Ymc->Draw("colz");
//  c32->Write();
//  c32->Close();

//  TCanvas *c42 = new TCanvas("QA_candidates_dir_yMC");
//   c42->Divide(3,3);
//   c42->cd(1);
//   hThrecYmc->Draw("colz");
//   c42->cd(2);
//   hPhrecYmc->Draw("colz");
//   c42->cd(3);
//   hPrecYmc->Draw("colz");
//   c42->cd(4);
//   herrThrecYmc->Draw("colz");
//   c42->cd(5);
//   herrPhrecYmc->Draw("colz");
//   c42->cd(6);
//   herrPrecYmc->Draw("colz");
//   c42->cd(7);
//   hPullLikeTh_Ymc->Draw("colz");
//   c42->cd(8);
//   hPullLikePh_Ymc->Draw("colz");
//   c42->cd(9);
//   hPullLikeP_Ymc->Draw("colz");
//   c42->Write();
//   c42->Close();

//  TCanvas *c52 = new TCanvas("QA_resolution_vs_yMC");
//   c52->Divide(3,2);
//   c52->cd(1);
//   hResXrecYmc->Draw("colz");
//   c52->cd(2);
//   hResYrecYmc->Draw("colz");
//   c52->cd(3);
//   hResZrecYmc->Draw("colz");
//   c52->cd(4);
//   hResThrecYmc->Draw("colz");
//   c52->cd(5);
//   hResPhrecYmc->Draw("colz");
//   c52->cd(6);
//   hResPrecYmc->Draw("colz");
//   c52->Write();
//   c52->Close();


//   hPullLikePointX->Write();
//   hPullLikePointY->Write();
//   hPullLikePointZ->Write();
//  hPullLikeX_Zmc->Write();
//  hPullLikeY_Zmc->Write();
//  hPullLikeZ_Zmc->Write();
//  hPullLikeTh_Zmc->Write();
//  hPullLikePh_Zmc->Write();
//  hPullLikeP_Zmc->Write();
//   hXrecZmc->Write();
//   hYrecZmc->Write();
//   hZrecZmc->Write();
//   hThrecZmc->Write();
//   hPhrecZmc->Write();
//   hPrecZmc->Write();
//   hResXrecZmc->Write();
//   hResYrecZmc->Write();
//   hResZrecZmc->Write();
//   hResThrecZmc->Write();
//   hResPhrecZmc->Write();
//   hResPrecZmc->Write();
//  herrXrecZmc->Write();
//   herrYrecZmc->Write();
//   herrZrecZmc->Write();
//   herrThrecZmc->Write();
//   herrPhrecZmc->Write();
//   herrPrecZmc->Write();

//  hPullLikeX_Xmc->Write();
//  hPullLikeY_Xmc->Write();
//  hPullLikeZ_Xmc->Write();
//  hPullLikeTh_Xmc->Write();
//  hPullLikePh_Xmc->Write();
//  hPullLikeP_Xmc->Write();
//   hXrecXmc->Write();
//   hYrecXmc->Write();
//   hZrecXmc->Write();
//   hThrecXmc->Write();
//   hPhrecXmc->Write();
//   hPrecXmc->Write();
//   hResXrecXmc->Write();
//   hResYrecXmc->Write();
//   hResZrecXmc->Write();
//   hResThrecXmc->Write();
//   hResPhrecXmc->Write();
//   hResPrecXmc->Write();
//  herrXrecXmc->Write();
//   herrYrecXmc->Write();
//   herrZrecXmc->Write();
//   herrThrecXmc->Write();
//   herrPhrecXmc->Write();
//   herrPrecXmc->Write();

// hPullLikeX_Ymc->Write();
//  hPullLikeY_Ymc->Write();
//  hPullLikeZ_Ymc->Write();
//  hPullLikeTh_Ymc->Write();
//  hPullLikePh_Ymc->Write();
//  hPullLikeP_Ymc->Write();
//   hXrecYmc->Write();
//   hYrecYmc->Write();
//   hZrecYmc->Write();
//   hThrecYmc->Write();
//   hPhrecYmc->Write();
//   hPrecYmc->Write();
//   hResXrecYmc->Write();
//   hResYrecYmc->Write();
//   hResZrecYmc->Write();
//   hResThrecYmc->Write();
//   hResPhrecYmc->Write();
//   hResPrecYmc->Write();
//  herrXrecYmc->Write();
//   herrYrecYmc->Write();
//   herrZrecYmc->Write();
//   herrThrecYmc->Write();
//   herrPhrecYmc->Write();
//   herrPrecYmc->Write();

//   f->cd();
  f->Write();
  f->Close();
  std::cout<<"PndLmdQATask::WriteHists() Finished successfull"<<std::endl;
}

void PndLmdQATask::FinishTask()
{
  // cout<<"PndLmdQATask::FinishTask()"<<endl;

  cout<<"Number of missed tracks is "<<mistrk<<" and number of ghost tracks is "<<ghosttrk<<endl;
  WriteHists();

  //clean up stuff
  // delete c1;
  // delete c2;
 
}

InitStatus PndLmdQATask::Init()
{
  tot = 0;
  all=0; uneff=0; mistrk=0; ghosttrk=0;

  //  fouthists = new TFile(foutFile,"RECREATE");

  //Get ROOT Manager
  FairRootManager* ioman= FairRootManager::Instance();

  if(ioman==0) 
    {
      Error("PndLmdQATask::Init","RootManager not instantiated!");
      return kERROR;
    }

  // Get input collection
  fmcHitArray=(TClonesArray*) ioman->GetObject(fmcHitName);
  if(fmcHitArray==0)
    {
      Error("PndLmdQATask::Init","mcHit-array not found!");
      return kERROR;
    }

  fHitArray=(TClonesArray*) ioman->GetObject(fHitName);
  if(fHitArray==0)
    {
      Error("PndLmdQATask::Init","hit-array not found!");
      return kERROR;
    }

  fTrkArray=(TClonesArray*) ioman->GetObject(fTrkName);
  if(fTrkArray==0)
    {
      Error("PndLmdQATask::Init","track-array not found!");
      return kERROR;
    }

  fmcTrkArray=(TClonesArray*) ioman->GetObject(fmcTrkName);
  if(fmcTrkArray==0)
    {
      Error("PndLmdQATask::Init","mcTrk-array not found!");
      return kERROR;
    }

  fGeaneArray=(TClonesArray*) ioman->GetObject(fGeaneName);
  if(fGeaneArray==0)
    {
      Error("PndLmdQATask::Init","geane-array not found!");
      return kERROR;
    }
  fTrkCandArray=(TClonesArray*) ioman->GetObject(fTrkCandName);
  if(fTrkCandArray==0)
    {
      Error("PndLmdQATask::Init","trk-cand--array not found!");
      return kERROR;
    }
  fClusterArray=(TClonesArray*) ioman->GetObject(fClusterName);
  if(fClusterArray==0)
    {
      Error("PndLmdQATask::Init","cluster-array not found!");
      return kERROR;
    }
  fDigiArray=(TClonesArray*) ioman->GetObject(fDigiName);
  if(fDigiArray==0)
    {
      Error("PndLmdQATask::Init","digi-array not found!");
      return kERROR;
    }
  //  double thetarange[2]={0.001,0.01};
  double thetam = 3.;
  // double thetarange[2]={1.5,10.};
  // double thetam =  thetarange[0];
  // if(fPlab<4) thetam =  thetarange[1];
  //Near IP
  hResMom = new TH1F("hResMom","P_{MC}-P_{REC};#deltaP,GeV/c",1e3,-1e-1,1e-1);
  //  hErrMom = new TH1F("hErrMom","#sigma_{P};#sigmaP,GeV/c",1e3,0,1e-3);
  //  hPullMom = new TH1F("hPullMom","(P_{MC}-P_{REC})/#sigma_{P};",1e3,-1e1,1e1);
  hResTheta = new TH1F("hResTheta","#theta_{MC}-#theta_{REC};#delta#theta,mrad",1e2,-thetam,thetam);//TEST
  hResTheta_th = new TH2F("hResTheta_th","#theta_{MC}-#theta_{REC};#theta_{MC}, mrad; #delta#theta,mrad",2e2,0,10,6e2,-thetam,thetam);//TEST
  hResTheta_ph = new TH2F("hResTheta_ph","#theta_{MC}-#theta_{REC};#phi_{MC}, rad; #delta#theta,mrad",2e2,-TMath::Pi(),TMath::Pi(),2e2,-thetam,thetam);//TEST
  hErrTheta = new TH1F("hErrTheta","#sigma(#theta_{REC});#sigma,rad",1e3,0,10*thetam);
   hPullTheta = new TH1F("hPullTheta","(#theta_{MC}-#theta_{REC})/#sigma_{#theta};",1e2,-10,10);
   hResPhi = new TH1F("hResPhi","#phi_{MC}-#phi_{REC};#delta#phi,rad",2e3,-1.,1.);
   hErrPhi = new TH1F("hErrPhi","#sigma(#phi_{REC});#sigma,rad",1e3,0,0.1);
   hPullPhi = new TH1F("hPullPhi","(#phi_{MC}-#phi_{REC})/#sigma_{#phi};",1e2,-10,10);

   hResPointPx = new TH1F("hResPointPx","Px_{MC}-Px_{REC};#deltaPx, GeV/c",1e2,-0.01,0.01);
   hErrPointPx = new TH1F("hErrPointPx","#sigma_{Px};#sigmaPx, GeV/c",1e3,0,0.001);
   hPullPointPx = new TH1F("hPullPointPx","(Px_{MC}-Px_{REC})/#sigma_{Px};(Px_{MC}-Px_{REC})/#sigma_{Px}",1e2,-10,10);
  
   hResPointPy = new TH1F("hResPointPy","Py_{MC}-Py_{REC};#deltaPy, GeV/c",1e2,-0.01,0.01);
   hErrPointPy = new TH1F("hErrPointPy","#sigma_{Py};#sigmaPy, GeV/c",1e3,0,0.001);
   hPullPointPy = new TH1F("hPullPointPy","(Py_{MC}-Py_{REC})/#sigma_{Py};(Py_{MC}-Py_{REC})/#sigma_{Py}",1e2,-10,10);
  
   hResPointPz = new TH1F("hResPointPz","Pz_{MC}-Pz_{REC};#deltaPz, GeV/c",1e2,-1e-4,1e-4);
   hErrPointPz = new TH1F("hErrPointPz","#sigma_{Pz};#sigmaPz, GeV/c",1e3,0,1e-3);
   hPullPointPz = new TH1F("hPullPointPz","(Pz_{MC}-Pz_{REC})/#sigma_{Pz};(Pz_{MC}-Pz_{REC})/#sigma_{Pz}",1e2,-10,10);

   hResPointX = new TH1F("hResPointX","X_{MC}-X_{REC};#deltaX,cm",1e2,-2.,2.);
   hPullPointX = new TH1F("hPullPointX","(X_{MC}-X_{REC})/#sigma_{X};(X_{MC}-X_{REC})/#sigma_{X}",1e2,-10,10);
   hResPointY = new TH1F("hResPointY","Y_{MC}-Y_{REC};#deltaY,cm",1e2,-2.,2.);
   hPullPointY = new TH1F("hPullPointY","(Y_{MC}-Y_{REC})/#sigma_{Y};(Y_{MC}-Y_{REC})/#sigma_{Y}",1e2,-10,10);
   hResPointZ = new TH1F("hResPointZ","Z_{MC}-Z_{REC};#deltaZ,cm",1e3,-0.15,0.15);
   hPullPointZ = new TH1F("hPullPointZ","(Z_{MC}-Z_{REC})/#sigma_{Z};(Z_{MC}-Z_{REC})/#sigma_{Z}",1e2,-10,10);

  //  //back-propagation QA candidates
//  hPullLikePointX = new TH1F("hPullLikePointX","X_{REC}/#sigma_{X};X_{REC}/#sigma_{X}",1e2,-10,10);
//  hPullLikePointY = new TH1F("hPullLikePointY","Y_{REC}/#sigma_{Y};Y_{REC}/#sigma_{Y}",1e2,-10,10);
//  hPullLikePointZ = new TH1F("hPullLikePointZ","Z_{REC}/#sigma_{Z};Z_{REC}/#sigma_{Z}",1e2,-10,10);
//  hPullLikeX_Zmc = new TH2D("hPullLikeX_Zmc",";Z_{MC}, cm;X_{REC}/#sigma_{X}",1e3,-60,60,1e3,-10,10);
//  hPullLikeY_Zmc = new TH2D("hPullLikeY_Zmc",";Z_{MC}, cm;Y_{REC}/#sigma_{Y}",1e3,-60,60,1e2,-10,10);
//  hPullLikeZ_Zmc = new TH2D("hPullLikeZ_Zmc",";Z_{MC}, cm;Z_{REC}/#sigma_{Z}",1e3,-60,60,1e2,-10,10);
// hPullLikeTh_Zmc = new TH2D("hPullLikeTh_Zmc",";Z_{MC}, cm;#theta_{REC}/#sigma_{#theta}",1e3,-60,60,2e3,-1000,1000);
//  hPullLikePh_Zmc = new TH2D("hPullLikePh_Zmc",";Z_{MC}, cm;#phi_{REC}/#sigma_{#phi}",1e3,-60,60,2e3,-1000,1000);
//  hPullLikeP_Zmc = new TH2D("hPullLikeP_Zmc",";Z_{MC}, cm;P_{REC}/P_{#phi}",1e3,-60,60,2e3,0,2e4);
//  hXrecZmc = new TH2D("hXrecZmc","; Z_{MC}, cm; X_{REC}, cm",1e3,-60,60,1e3,-5,5);
//  hYrecZmc = new TH2D("hYrecZmc","; Z_{MC}, cm; Y_{REC}, cm",1e3,-60,60,1e3,-5,5);
//  // hZrecZmc = new TH2D("hZrecZmc","; Z_{MC}, cm; Z_{REC}, cm",1e3,-60,60,2e3,-110.,110.); //LINE
//  hZrecZmc = new TH2D("hZrecZmc","; Z_{MC}, cm; Z_{REC}, cm",1e3,-60,60,2e3,-1.,1.);//PCA
//  hThrecZmc = new TH2D("hThrecZmc","; Z_{MC}, cm; #theta_{REC}, mrad",1e3,-60,60,1e3,0,20);
//  hPhrecZmc = new TH2D("hPhrecZmc","; Z_{MC}, cm; #phi_{REC}, rad",1e3,-60,60,1e3,-3.15,3.15);
//  hPrecZmc = new TH2D("hPrecZmc","; Z_{MC}, cm; P_{REC}, GeV/c",1e3,-60,60,1e3,0,2);
//  hResXrecZmc = new TH2D("hResXrecZmc","; Z_{MC}, cm; X_{MC}-X_{REC}, cm",3e2,-60,60,1e3,-5,5);
//  hResYrecZmc = new TH2D("hResYrecZmc","; Z_{MC}, cm; Y_{MC}-Y_{REC}, cm",3e2,-60,60,1e3,-5,5);
//  hResZrecZmc = new TH2D("hResZrecZmc","; Z_{MC}, cm; Z_{MC}-Z_{REC}, cm",3e2,-60,60,2e3,-200,200);
//  hResThrecZmc = new TH2D("hResThrecZmc","; Z_{MC}, cm; #theta_{MC}-#theta_{REC}, mrad",3e2,-60,60,1e3,-3,3);
//  hResPhrecZmc = new TH2D("hResPhrecZmc","; Z_{MC}, cm; #phi_{MC}-#phi_{REC}, rad",3e2,-60,60,1e3,-2.,2.);
//  hResPrecZmc = new TH2D("hResPrecZmc","; Z_{MC}, cm; P_{MC}-P_{REC}, GeV/c",3e2,-60,60,1e3,-10.,10.);

//  herrXrecZmc = new TH2D("herrXrecZmc","; Z_{MC}, cm; #sigma(X_{REC}), cm",1e3,-60,60,1e3,0,2);
//  herrYrecZmc = new TH2D("herrYrecZmc","; Z_{MC}, cm; #sigma(Y_{REC}), cm",1e3,-60,60,1e3,0,2);
//  herrZrecZmc = new TH2D("herrZrecZmc","; Z_{MC}, cm; #sigma(Z_{REC}), cm",1e3,-60,60,1e3,0,0.1);
//  herrThrecZmc = new TH2D("herrThrecZmc","; Z_{MC}, cm; #sigma(#theta_{REC}), mrad",1e3,-60,60,1e3,0,2.);
//  herrPhrecZmc = new TH2D("herrPhrecZmc","; Z_{MC}, cm; #sigma(#phi_{REC}), rad",1e3,-60,60,1e3,0,1.);
//  herrPrecZmc = new TH2D("herrPrecZmc","; Z_{MC}, cm; #sigma(P_{REC}), GeV/c",1e3,-60,60,1e3,0,0.1);


//  hPullLikeX_Xmc = new TH2D("hPullLikeX_Xmc",";X_{MC}, cm;X_{REC}/#sigma_{X}",1e3,-2,2,1e3,-10,10);
//  hPullLikeY_Xmc = new TH2D("hPullLikeY_Xmc",";X_{MC}, cm;Y_{REC}/#sigma_{Y}",1e3,-2,2,1e2,-10,10);
//  hPullLikeZ_Xmc = new TH2D("hPullLikeZ_Xmc",";X_{MC}, cm;Z_{REC}/#sigma_{Z}",1e3,-2,2,1e2,-10,10);
// hPullLikeTh_Xmc = new TH2D("hPullLikeTh_Xmc",";X_{MC}, cm;#theta_{REC}/#sigma_{#theta}",1e3,-2,2,2e3,-1000,1000);
//  hPullLikePh_Xmc = new TH2D("hPullLikePh_Xmc",";X_{MC}, cm;#phi_{REC}/#sigma_{#phi}",1e3,-2,2,2e3,-1000,1000);
//  hPullLikeP_Xmc = new TH2D("hPullLikeP_Xmc",";X_{MC}, cm;P_{REC}/P_{#phi}",1e3,-2,2,2e3,0,2e4);
//  hXrecXmc = new TH2D("hXrecXmc","; X_{MC}, cm; X_{REC}, cm",1e3,-2,2,1e3,-5,5);
//  hYrecXmc = new TH2D("hYrecXmc","; X_{MC}, cm; Y_{REC}, cm",1e3,-2,2,1e3,-5,5);
//  // hZrecXmc = new TH2D("hZrecXmc","; X_{MC}, cm; Z_{REC}, cm",1e3,-2,2,2e3,-110.,110.);//LINE
//  hZrecXmc = new TH2D("hZrecXmc","; X_{MC}, cm; Z_{REC}, cm",1e3,-2,2,2e3,-1.,1.);//PCA
//  hThrecXmc = new TH2D("hThrecXmc","; X_{MC}, cm; #theta_{REC}, mrad",1e3,-2,2,1e3,0,20);
//  hPhrecXmc = new TH2D("hPhrecXmc","; X_{MC}, cm; #phi_{REC}, rad",1e3,-2,2,1e3,-3.15,3.15);
//  hPrecXmc = new TH2D("hPrecXmc","; X_{MC}, cm; P_{REC}, GeV/c",1e3,-2,2,1e3,0,2);
//  hResXrecXmc = new TH2D("hResXrecXmc","; X_{MC}, cm; X_{MC}-X_{REC}, cm",3e2,-2,2,1e3,-5,5);
//  hResYrecXmc = new TH2D("hResYrecXmc","; X_{MC}, cm; Y_{MC}-Y_{REC}, cm",3e2,-2,2,1e3,-5,5);
//  hResZrecXmc = new TH2D("hResZrecXmc","; X_{MC}, cm; Z_{MC}-Z_{REC}, cm",3e2,-2,2,2e3,-200,200);
//  hResThrecXmc = new TH2D("hResThrecXmc","; X_{MC}, cm; #theta_{MC}-#theta_{REC}, mrad",3e2,-2,2,1e3,-3,3);
//  hResPhrecXmc = new TH2D("hResPhrecXmc","; X_{MC}, cm; #phi_{MC}-#phi_{REC}, rad",3e2,-2,2,1e3,-2.,2.);
//  hResPrecXmc = new TH2D("hResPrecXmc","; X_{MC}, cm; P_{MC}-P_{REC}, GeV/c",3e2,-2,2,1e3,-10.,10.);

//  herrXrecXmc = new TH2D("herrXrecXmc","; X_{MC}, cm; #sigma(X_{REC}), cm",1e3,-2,2,1e3,0,2);
//  herrYrecXmc = new TH2D("herrYrecXmc","; X_{MC}, cm; #sigma(Y_{REC}), cm",1e3,-2,2,1e3,0,2);
//  herrZrecXmc = new TH2D("herrZrecXmc","; X_{MC}, cm; #sigma(Z_{REC}), cm",1e3,-2,2,1e3,0,0.1);
//  herrThrecXmc = new TH2D("herrThrecXmc","; X_{MC}, cm; #sigma(#theta_{REC}), mrad",1e3,-2,2,1e3,0,2.);
//  herrPhrecXmc = new TH2D("herrPhrecXmc","; X_{MC}, cm; #sigma(#phi_{REC}), rad",1e3,-2,2,1e3,0,1.);
//  herrPrecXmc = new TH2D("herrPrecXmc","; X_{MC}, cm; #sigma(P_{REC}), GeV/c",1e3,-2,2,1e3,0,0.1);


//  ////////////

//  hPullLikeX_Ymc = new TH2D("hPullLikeX_Ymc",";Y_{MC}, cm;X_{REC}/#sigma_{X}",1e3,-2,2,1e3,-10,10);
//  hPullLikeY_Ymc = new TH2D("hPullLikeY_Ymc",";Y_{MC}, cm;Y_{REC}/#sigma_{Y}",1e3,-2,2,1e2,-10,10);
//  hPullLikeZ_Ymc = new TH2D("hPullLikeZ_Ymc",";Y_{MC}, cm;Z_{REC}/#sigma_{Z}",1e3,-2,2,1e2,-10,10);
// hPullLikeTh_Ymc = new TH2D("hPullLikeTh_Ymc",";Y_{MC}, cm;#theta_{REC}/#sigma_{#theta}",1e3,-2,2,2e3,-1000,1000);
//  hPullLikePh_Ymc = new TH2D("hPullLikePh_Ymc",";Y_{MC}, cm;#phi_{REC}/#sigma_{#phi}",1e3,-2,2,2e3,-1000,1000);
//  hPullLikeP_Ymc = new TH2D("hPullLikeP_Ymc",";Y_{MC}, cm;P_{REC}/P_{#phi}",1e3,-2,2,2e3,0,2e4);
//  hXrecYmc = new TH2D("hXrecYmc","; Y_{MC}, cm; X_{REC}, cm",1e3,-2,2,1e3,-5,5);
//  hYrecYmc = new TH2D("hYrecYmc","; Y_{MC}, cm; Y_{REC}, cm",1e3,-2,2,1e3,-5,5);
//  // hZrecYmc = new TH2D("hZrecYmc","; X_{MC}, cm; Z_{REC}, cm",1e3,-2,2,2e3,-110.,110.);//LINE
//  hZrecYmc = new TH2D("hZrecYmc","; Y_{MC}, cm; Z_{REC}, cm",1e3,-2,2,2e3,-1.,1.);//PCA
//  hThrecYmc = new TH2D("hThrecYmc","; Y_{MC}, cm; #theta_{REC}, mrad",1e3,-2,2,1e3,0,20);
//  hPhrecYmc = new TH2D("hPhrecYmc","; Y_{MC}, cm; #phi_{REC}, rad",1e3,-2,2,1e3,-3.15,3.15);
//  hPrecYmc = new TH2D("hPrecYmc","; Y_{MC}, cm; P_{REC}, GeV/c",1e3,-2,2,1e3,0,2);
//  hResXrecYmc = new TH2D("hResXrecYmc","; Y_{MC}, cm; X_{MC}-X_{REC}, cm",3e2,-2,2,1e3,-5,5);
//  hResYrecYmc = new TH2D("hResYrecYmc","; Y_{MC}, cm; Y_{MC}-Y_{REC}, cm",3e2,-2,2,1e3,-5,5);
//  hResZrecYmc = new TH2D("hResZrecYmc","; Y_{MC}, cm; Z_{MC}-Z_{REC}, cm",3e2,-2,2,2e3,-200,200);
//  hResThrecYmc = new TH2D("hResThrecYmc","; Y_{MC}, cm; #theta_{MC}-#theta_{REC}, mrad",3e2,-2,2,1e3,-3,3);
//  hResPhrecYmc = new TH2D("hResPhrecYmc","; Y_{MC}, cm; #phi_{MC}-#phi_{REC}, rad",3e2,-2,2,1e3,-2.,2.);
//  hResPrecYmc = new TH2D("hResPrecYmc","; Y_{MC}, cm; P_{MC}-P_{REC}, GeV/c",3e2,-2,2,1e3,-10.,10.);

//  herrXrecYmc = new TH2D("herrXrecYmc","; Y_{MC}, cm; #sigma(X_{REC}), cm",1e3,-2,2,1e3,0,2);
//  herrYrecYmc = new TH2D("herrYrecYmc","; Y_{MC}, cm; #sigma(Y_{REC}), cm",1e3,-2,2,1e3,0,2);
//  herrZrecYmc = new TH2D("herrZrecYmc","; Y_{MC}, cm; #sigma(Z_{REC}), cm",1e3,-2,2,1e3,0,0.1);
//  herrThrecYmc = new TH2D("herrThrecYmc","; Y_{MC}, cm; #sigma(#theta_{REC}), mrad",1e3,-2,2,1e3,0,2.);
//  herrPhrecYmc = new TH2D("herrPhrecYmc","; Y_{MC}, cm; #sigma(#phi_{REC}), rad",1e3,-2,2,1e3,0,1.);
//  herrPrecYmc = new TH2D("herrPrecYmc","; Y_{MC}, cm; #sigma(P_{REC}), GeV/c",1e3,-2,2,1e3,0,0.1);

  //Near 1st LMD plane
   hhits = new TH1I("hhits","number of hits in trk",7,0,7);
   hchi2 = new TH1F("hchi2","#chi^2 for reconstructed tracks;#chi^2;",1.5e2,-1,15.);
   hResLumiTrkMom = new TH1F("hResLumiTrkMom","P_{MC}-P_{REC}(near Lumi);#deltaP,GeV/c",1e3,-6e-7,6e-7);
   hResLumiTrkTheta = new TH1F("hResLumiTrkTheta","#theta_{MC}-#theta_{REC}(near Lumi);#delta#theta,rad",1e3,-6e-3,6e-3);
   hResLumiTrkTheta2D = new TH2D("hResLumiTrkTheta2D", ";#Delta#theta_{x}(near Lumi);#Delta#theta_{y},rad", 1e3,-0.0005, 0.0005, 1e3,-0.0005, 0.0005);
   hMCLumiTrkTheta2D = new TH2D("hMCLumiTrkTheta2D", ";#theta_{x}(MC near Lumi);#theta_{y},rad", 1e3, 0.030, 0.050, 1e3,-0.012, 0.012);
   hRecLumiTrkTheta2D = new TH2D("hRecLumiTrkTheta2D", ";#theta_{x}(Rec near Lumi);#theta_{y},rad", 1e3, 0.030, 0.050, 1e3,-0.012, 0.012);


   hResLumiTrkPhi = new TH1F("hResLumiTrkPhi","#phi_{MC}-#phi_{REC}(near Lumi);#delta#phi,rad",2e3,-1e-1,1e-1);
   hResLumiTrkPointX = new TH1F("hResLumiTrkPointX","X_{MC}-X_{REC}(near Lumi);#deltaX,cm",1e2,-0.02,0.02);
   hResLumiTrkPointY = new TH1F("hResLumiTrkPointY","Y_{MC}-Y_{REC}(near Lumi);#deltaY,cm",1e2,-0.02,0.02);
   hResLumiTrkPointZ = new TH1F("hResLumiTrkPointZ","Z_{MC}-Z_{REC}(near Lumi);#deltaZ,cm",1e2,-0.02,0.02);

   hResLumiTrkPointPx = new TH1F("hResLumiTrkPointPx","Px_{MC}-Px_{REC}(near Lumi);#deltaPx, GeV/c",1e2,-0.01,0.01);
   hResLumiTrkPointPy = new TH1F("hResLumiTrkPointPy","Py_{MC}-Py_{REC}(near Lumi);#deltaPy, GeV/c",1e2,-0.01,0.01);
   hResLumiTrkPointPz = new TH1F("hResLumiTrkPointPz","Pz_{MC}-Pz_{REC}(near Lumi);#deltaPz, GeV/c",1e2,-5e-4,5e-4);

   hResLumiTrkPointXErr = new TH1F("hResLumiTrkPointXErr","#sigma(X_{REC})(near Lumi);#sigma_{X},cm",1e2,0,0.02);
   hResLumiTrkPointYErr = new TH1F("hResLumiTrkPointYErr","#sigma(Y_{REC})(near Lumi);#sigma_{Y},cm",1e2,0,0.02);
   hResLumiTrkPointZErr = new TH1F("hResLumiTrkPointZErr","#sigma(Z_{REC})(near Lumi);#sigma_{Z},cm",1e2,0,0.02);
   hResLumiTrkPointPxErr = new TH1F("hResLumiTrkPointPxErr","#sigma(Px_{REC})(near Lumi);#sigma_{Px}, GeV/c",1e2,0,0.001);
   hResLumiTrkPointPyErr = new TH1F("hResLumiTrkPointPyErr","#sigma(Py_{REC})(near Lumi);#sigma_{Py}, GeV/c",1e2,0,0.001);
   hResLumiTrkPointPzErr = new TH1F("hResLumiTrkPointPzErr","#sigma(Pz_{REC})(near Lumi);#sigma_{Pz}, GeV/c",1e2,0,0.0001);

   hResLumiTrkPointXPull = new TH1F("hResLumiTrkPointXPull","(X_{MC}-X_{REC})/#sigma (near Lumi) ;(X_{MC}-X_{REC})/#sigma",1e2,-10.,10.);
   hResLumiTrkPointYPull = new TH1F("hResLumiTrkPointYPull","(Y_{MC}-Y_{REC})/#sigma (near Lumi);(Y_{MC}-Y_{REC})/#sigma",1e2,-10.,10.);
   hResLumiTrkPointZPull = new TH1F("hResLumiTrkPointZPull","(Z_{MC}-Z_{REC})/#sigma (near Lumi);(Z_{MC}-Z_{REC})/#sigma",1e3,-100.,100.);

   hResLumiTrkPointPxPull = new TH1F("hResLumiTrkPointPxPull","(Px_{MC}-Px_{REC})/#sigma (near Lumi);(Px_{MC}-Px_{REC})/#sigma",1e2,-10,10.);
   hResLumiTrkPointPyPull = new TH1F("hResLumiTrkPointPyPull","(Py_{MC}-Py_{REC})/#sigma (near Lumi);(Py_{MC}-Py_{REC})/#sigma",1e2,-10,10);
   hResLumiTrkPointPzPull = new TH1F("hResLumiTrkPointPzPull","(Pz_{MC}-Pz_{REC})/#sigma (near Lumi);(Pz_{MC}-Pz_{REC})/#sigma",1e2,-10,10);
   hResLumiTrkThetaPull = new TH1F("hResLumiTrkThetaPull","(#theta_{MC}-#theta_{REC})/#sigma (near Lumi);#delta#theta, rad",1e2,-10,10);
   hResLumiTrkPhiPull = new TH1F("hResLumiTrkPhiPull","(#phi_{MC}-#phi_{REC})/#sigma (near Lumi);#delta#phi, rad",1e2,-10,10);


   //info about hits
   hResHitX = new TH1F("hResHitX","X_{MC}-X_{rec};#deltaX,cm",2e3,-0.5,0.5);
   hResHitY = new TH1F("hResHitY","Y_{MC}-Y_{rec};#deltaY,cm",2e3,-0.5,0.5);
   hResHitZ = new TH1F("hResHitZ","Z_{MC}-Z_{rec};#deltaZ,cm",2e2,-3e-2,3e-2);


  std::cout << "-I- PndLmdQATask: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void PndLmdQATask::Exec(Option_t*)
{
fEvent++;
  //  std::cout<<"PndLmdQATask::Exec"<<std::endl;
  bool isPr = HitReco();
  if(isPr) ResoAndPulls();

  return;
}

bool PndLmdQATask::HitReco()
{
  bool isProblem = true;
    //const int nMCHits = fmcHitArray->GetEntriesFast(); //[R.K. 01/2017] unused variable
    const int nRecHits = fHitArray->GetEntriesFast();

    for (Int_t i=0; i<nRecHits; i++){

      PndSdsHit* hit = (PndSdsHit*)(fHitArray->At(i));
      //for pixel design
	PndSdsClusterPixel* myCluster = (PndSdsClusterPixel*)(fClusterArray->At(hit->GetClusterIndex()));
	PndSdsDigiPixel* astripdigi = (PndSdsDigiPixel*)(fDigiArray->At(myCluster->GetDigiIndex(0)));
	if (astripdigi->GetIndex(0) == -1)
	  continue;
	PndSdsMCPoint* mc = (PndSdsMCPoint*)(fmcHitArray->At(astripdigi->GetIndex(0)));
	//int MCidTOP = mc->GetTrackID(); //[R.K. 01/2017] unused variable
      // PndSdsHit *hit = (PndSdsHit*) fHitArray->At(i);
      // if(hit->GetRefIndex()<0) continue;
      // PndSdsMCPoint *mc = (PndSdsMCPoint*) fmcHitArray->At(hit->GetRefIndex());
      // if(!mc) continue;

      TVector3 recovec(hit->GetX(),hit->GetY(),hit->GetZ());
      TVector3 mcvec(mc->GetX()+mc->GetXOut(),mc->GetY()+mc->GetYOut(),mc->GetZ()+mc->GetZOut()); mcvec*=0.5;
     
      //      TVector3 mcvec(mc->GetXOut(),mc->GetYOut(),mc->GetZOut());
      TVector3 dvec(recovec-mcvec);
      // if(1e4*(mc->GetZOut()-mc->GetZ())<0) 
      // 	cout<<"For MCtrk#"<<MCidTOP<<" mc.Z() = "<<0.5*(mc->GetZ()+mc->GetZOut())<<" diff rec- mc [mkm] (x,y,z)  = ("<<1e4*dvec.X()<<", "<<1e4*dvec.Y()<<", "<<1e4*dvec.Z()<<")"<<endl;

      // if(hit->GetZ()<1135.) //Acc of first plane
      // 	h2dPnts->Fill(mc->GetX(),mc->GetY());  // = new TH2D("h2dPnts", "xy reconstructed points, cm",2e2,-20.,20., 2e2,-20.,20.);
  
      
      //   if(fabs(dvec.X())<2*0.0015 && fabs(dvec.Y())<2*0.0015){
      //    if(1e4*(mc->GetZOut()-mc->GetZ())<0){// secondary!
      //if(1e4*(mc->GetZOut()-mc->GetZ())>0 && abs(dvec.Z())>0.0100){// primary & merged hits!@15 GeV/c
      //if(1e4*(mc->GetZOut()-mc->GetZ())>0 && abs(dvec.Z())<0.0100){// primary & not-merged (single) hits!@15 GeV/c
      if(1e4*(mc->GetZOut()-mc->GetZ())>0){// primary
	hResHitX->Fill(dvec.X());  // = new TH1F("hResPointX","X_{MC}-X_{rec};#deltaX,cm",2e2,-1.5,1.5);
	hResHitY->Fill(dvec.Y());  // = new TH1F("hResPointY","Y_{MC}-Y_{rec};#deltaY,cm",2e2,-1.5,1.5);
	hResHitZ->Fill(dvec.Z());  // = new TH1F("hResPointZ","Z_{MC}-Z_{rec};#deltaZ,cm",2e2,-3e-2,3e-2);
	isProblem=true;
	//	cout<<"NOW!!!"<<endl;
      }
      else
	isProblem=false;
	//	cout<<"Event #"<<fEvent<<endl;
   
      // //TODO
      // hErrHitX->Fill(0);  // = new TH1F("hErrPointX","#sigma_{X};#sigmaX,cm",1e2,0,5e-1);
      // hErrHitY->Fill(0);  // = new TH1F("hErrPointY","#sigma_{Y};#sigmaY,cm",1e2,0,5e-1);
      // hErrHitZ->Fill(0);  // = new TH1F("hErrPointZ","#sigma_{Z};#sigmaZ,cm",1e2,0,5e-3);
      // hPullHitX->Fill(0);  // = new TH1F("hPullPointX","(X_{MC}-X_{rec})/#sigma_{X};",1e2,-10,10);
      // hPullHitY->Fill(0);  // = new TH1F("hPullPointY","(Y_{MC}-Y_{rec})/#sigma_{Y};",1e2,-10,10);
      // hPullHitZ->Fill(0);  // = new TH1F("hPullPointZ","(Z_{MC}-Z_{rec})/#sigma_{Z};",1e2,-10,10);

    }
    // //----------------------------------------------------------------------------------
    return isProblem;
}

void PndLmdQATask::ResoAndPulls()
{
    
    // Read GEANE & MC info -----------------------------------------------------------------
    const int nGeaneTrks = fGeaneArray->GetEntriesFast();
    const int nParticles = fmcTrkArray->GetEntriesFast();
    //const int nRecHits = fHitArray->GetEntriesFast(); //[R.K. 01/2017] unused variable
    const int nRecTrks = fTrkArray->GetEntriesFast();

    if(nGeaneTrks<nParticles)
      mistrk += nParticles-nGeaneTrks;
    
    if(nGeaneTrks>nParticles)
      ghosttrk += nGeaneTrks-nParticles;
    if(verboseLevel>0) {
      if(nParticles!=1) 
	std::cout<<"Hey, QA task is implemented only for 1 trk/event case. In Ev #"<<fEvent-1<<" you have "<<nParticles<<" MC tracks!"<<std::endl;
    }
    //    if(nParticles!=1) return; //TODO: currently works only 1 trk/event !
    if(verboseLevel>0)  
      cout<<"# "<< fEvent-1 <<"\t nGeaneTrks="<<nGeaneTrks<<" nParticles="<<nParticles<<" nRecTrks="<<nRecTrks<<endl;
    //TODO: correct assignment between MC and REC trks
    // vector<int> missedTrk;
    // missedTrk.resize(nParticles);
    // vector<int> ghostTrk;
    // ghostTrk.resize(nGeaneTrks);
    
 for (Int_t iN=0; iN<nGeaneTrks; iN++){// loop over all reconstructed trks
      FairTrackParH *fRes = (FairTrackParH*)fGeaneArray->At(iN);
      Double_t lyambda = fRes->GetLambda();
      if(lyambda==0){
	cout<<"GEANE didn't propagate this trk!"<<endl;
	//	glBADGEANE++;
      }
      if(lyambda==0) continue;

      /// Read REC track parameters near IP -----------------------------------
      TVector3 MomRecPCA = fRes->GetMomentum();
      //      MomRecPCA *= fPlab/MomRecPCA.Mag();
      TVector3 PosRecPCA = fRes->GetPosition();
      Double_t errPx = fRes->GetDPx();
      Double_t errPy = fRes->GetDPy();
      Double_t errPz = fRes->GetDPz();
      TVector3 errMomRecPCA(errPx,errPy,errPz);
      Double_t errX = fRes->GetDX();
      Double_t errY = fRes->GetDY();
      Double_t errZ = fRes->GetDZ();
      TVector3 errPosRecPCA(errX,errY,errZ);

      //Double_t thetaBP = TMath::Pi()/2. - lyambda; //[R.K. 01/2017] unused variable
      //   Double_t err_lyambda = fRes->GetDLambda();
      //Double_t phiBP = fRes->GetPhi(); //[R.K. 01/2017] unused variable
      //  Double_t err_phi = fRes->GetDPhi();

      //calculate theta & phi errors
      double fLmPCA = TMath::ASin(MomRecPCA.Z()/MomRecPCA.Mag());
      double cLmPCA= TMath::Cos(fLmPCA);
      //double  sLmPCA= TMath::Sin(fLmPCA); //[R.K. 01/2017] unused variable
      Double_t fPPCA =sqrt(MomRecPCA.X()*MomRecPCA.X()+MomRecPCA.Y()*MomRecPCA.Y()+MomRecPCA.Z()*MomRecPCA.Z());
      Double_t fDPPCA= (2*MomRecPCA.X()*errMomRecPCA.X()+2*MomRecPCA.Y()*errMomRecPCA.Y()+2*MomRecPCA.Z()*errMomRecPCA.Z())/(2*fPPCA); //dp
      Double_t err_lyambda = (-((MomRecPCA.Z()*fDPPCA)/pow(fPPCA,2)) + errMomRecPCA.Z()/fPPCA)/ TMath::Sqrt(1 - pow(MomRecPCA.Z(),2)/pow(fPPCA,2)); 
      Double_t err_phi = (-((MomRecPCA.Y()*fDPPCA/cLmPCA)/pow(fPPCA,2)) + (errMomRecPCA.Y()/cLmPCA)/fPPCA +(MomRecPCA.Y()*err_lyambda*TMath::Tan(fLmPCA)/cLmPCA)/fPPCA) /TMath::Sqrt(1 - (pow(MomRecPCA.Y(),2)*pow(1/cLmPCA,2))/pow(fPPCA,2)); 


	// Double_t CovGEANELAB[6][6];
	// fRes->GetMARSCov(CovGEANELAB);
	//	Double_t errMomRecBP = fRes->GetDQp();
      // ///get rid from most probably ghost track ----------
      // //TODO: find reason for such trks in Kalman
      // double pca_lim = 1.;//=10*sigma_Xpca~10*{0.093,0.11,0.12,0.22,0.55};
      // if(fPlab<5) pca_lim = 2.;
      // if(fPlab<2) pca_lim = 5.;
      // if(fabs(PosRecPCA.X())>pca_lim && fabs(PosRecPCA.Y())>pca_lim) continue; // PCA_x and PCA_y should be < 10sigmaX
      // ///get rid from most probably ghost track (END) ---     
      // ///------------------------------------------------------------------------------------

      /// Read REC track parameters near LMD -----------------------------------
      PndTrack *trkpnd = (PndTrack*)fTrkArray->At(iN);
      double chi2 = trkpnd->GetChi2();
      hchi2->Fill(chi2);
      FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();
      TVector3 PosRecLMD(fFittedTrkP.GetX(),fFittedTrkP.GetY(),fFittedTrkP.GetZ());
      TVector3 MomRecLMD(fFittedTrkP.GetPx(),fFittedTrkP.GetPy(),fFittedTrkP.GetPz());
      //    MomRecLMD *=fPlab/MomRecLMD.Mag();
      double covMARS[6][6];
      fFittedTrkP.GetMARSCov(covMARS);
      TVector3 errMomRecLMD(sqrt(covMARS[0][0]),sqrt(covMARS[1][1]),sqrt(covMARS[2][2]));
      TVector3 errPosRecLMD(sqrt(covMARS[3][3]),sqrt(covMARS[4][4]),sqrt(covMARS[5][5]));

      //calculate theta & phi errors
      double fLm = TMath::ASin(MomRecLMD.Z()/MomRecLMD.Mag());
      double cLm= TMath::Cos(fLm);
      //double  sLm= TMath::Sin(fLm); //[R.K. 01/2017] unused variable
      Double_t fP =sqrt(MomRecLMD.X()*MomRecLMD.X()+MomRecLMD.Y()*MomRecLMD.Y()+MomRecLMD.Z()*MomRecLMD.Z());
      Double_t fDP= (2*MomRecLMD.X()*errMomRecLMD.X()+2*MomRecLMD.Y()*errMomRecLMD.Y()+2*MomRecLMD.Z()*errMomRecLMD.Z())/(2*fP); //dp
      Double_t err_lyambdaLMD = (-((MomRecLMD.Z()*fDP)/pow(fP,2)) + errMomRecLMD.Z()/fP)/ TMath::Sqrt(1 - pow(MomRecLMD.Z(),2)/pow(fP,2)); 
      Double_t err_phiLMD = (-((MomRecLMD.Y()*fDP/cLm)/pow(fP,2)) + (errMomRecLMD.Y()/cLm)/fP +(MomRecLMD.Y()*err_lyambdaLMD*TMath::Tan(fLm)/cLm)/fP) /TMath::Sqrt(1 - (pow(MomRecLMD.Y(),2)*pow(1/cLm,2))/pow(fP,2)); 
      ///---------------------------------------------------------------------------------------

  
  	
	//Matching between MC & Rec on 1st hit level-----------------------------------
      int candID = trkpnd->GetRefIndex();
      PndTrackCand *trkcand = (PndTrackCand*)fTrkCandArray->At(candID);    
      const int Ntrkcandhits= trkcand->GetNHits();
      PndSdsMCPoint* MCPointHit;
      int MCid;
      bool hitmix = false;
      //if(Ntrkcandhits<4) continue; //require trks with hits on all planes
      //      if(Ntrkcandhits>3) continue; //require trks with hits not on all planes
      hhits->Fill(Ntrkcandhits);
      for (Int_t iHit = 0; iHit < Ntrkcandhits; iHit++){ // loop over rec.hits
	PndTrackCandHit candhit = (PndTrackCandHit)(trkcand->GetSortedHit(iHit));
	Int_t hitID = candhit.GetHitId();
	PndSdsHit* myHit = (PndSdsHit*)(fHitArray->At(hitID));
	
	//for pixel design
	PndSdsClusterPixel* myCluster = (PndSdsClusterPixel*)(fClusterArray->At(myHit->GetClusterIndex()));
	PndSdsDigiPixel* astripdigi = (PndSdsDigiPixel*)(fDigiArray->At(myCluster->GetDigiIndex(0)));
	if (astripdigi->GetIndex(0) == -1)
	  continue;
	PndSdsMCPoint* MCPoint = (PndSdsMCPoint*)(fmcHitArray->At(astripdigi->GetIndex(0)));
	int MCidTOP = MCPoint->GetTrackID();
	if(iHit<1){
	  MCPointHit = MCPoint;
	  MCid = MCidTOP;
	}
	else
	  if(MCid!=MCidTOP){
	    cout<<"REC trk contains hits from different MC trks! Skip event #"<<fEvent<<endl;
	    hitmix = true;
	  }
      }
      if(hitmix) continue;
      ///--------------------------------------------------------------------------

      
      /// Comporision between MC tracks, reconstructed tracks near LMD  and back propagated tracks -------------
      if(MCid<0) continue;
	/// Read MC track parameters near IP ------------------------------------
	PndMCTrack *mctrk =(PndMCTrack*) fmcTrkArray->At(MCid);
	//Int_t mcID = mctrk->GetPdgCode(); //[R.K. 01/2017] unused variable
	TVector3 MomMCpca = mctrk->GetMomentum();
	TVector3 PosMCpca = mctrk->GetStartVertex();
	//Double_t thetaMC = MomMCpca.Theta(); //[R.K. 01/2017] unused variable
	//Double_t phiMC = MomMCpca.Phi(); //[R.K. 01/2017] unused variable
	///------------------------------------------------------------------------------------

	MomRecPCA *= MomMCpca.Mag()/MomRecPCA.Mag();
	hResPointPx->Fill(MomMCpca.X()-MomRecPCA.X());
	hResPointPy->Fill(MomMCpca.Y()-MomRecPCA.Y());
	hResPointPz->Fill(MomMCpca.Z()-MomRecPCA.Z());
	hErrPointPx->Fill(errMomRecPCA.X());
	hErrPointPy->Fill(errMomRecPCA.Y());
	hErrPointPz->Fill(errMomRecPCA.Z());
	hPullPointPx->Fill((MomMCpca.X()-MomRecPCA.X())/errMomRecPCA.X());
	hPullPointPy->Fill((MomMCpca.Y()-MomRecPCA.Y())/errMomRecPCA.Y());
	hPullPointPz->Fill((MomMCpca.Z()-MomRecPCA.Z())/errMomRecPCA.Z());
	hResPointX->Fill(PosMCpca.X()-PosRecPCA.X());
	hResPointY->Fill(PosMCpca.Y()-PosRecPCA.Y());
	hResPointZ->Fill(PosMCpca.Z()-PosRecPCA.Z());
	hPullPointX->Fill((PosMCpca.X()-PosRecPCA.X())/errPosRecPCA.X());
	hPullPointY->Fill((PosMCpca.Y()-PosRecPCA.Y())/errPosRecPCA.Y());
	hPullPointZ->Fill((PosMCpca.Z()-PosRecPCA.Z())/errPosRecPCA.Z());

	// hPullLikePointX->Fill(PosRecPCA.X()/errPosRecPCA.X());
	// hPullLikePointY->Fill(PosRecPCA.Y()/errPosRecPCA.Y());
	// hPullLikePointZ->Fill(PosRecPCA.Z()/errPosRecPCA.Z());

	// hXrecZmc->Fill(PosMCpca.Z(),PosRecPCA.X());
	// hYrecZmc->Fill(PosMCpca.Z(),PosRecPCA.Y());
	// hZrecZmc->Fill(PosMCpca.Z(),PosRecPCA.Z());
	// hThrecZmc->Fill(PosMCpca.Z(),1e3*MomRecPCA.Theta());
	// hPhrecZmc->Fill(PosMCpca.Z(),MomRecPCA.Phi());
	// hPrecZmc->Fill(PosMCpca.Z(),MomRecPCA.Mag());

	// hResXrecZmc->Fill(PosMCpca.Z(),PosMCpca.X()-PosRecPCA.X());
	// hResYrecZmc->Fill(PosMCpca.Z(),PosMCpca.Y()-PosRecPCA.Y());
	// hResZrecZmc->Fill(PosMCpca.Z(),PosMCpca.Z()-PosRecPCA.Z());
	// hResThrecZmc->Fill(PosMCpca.Z(),1e3*(MomMCpca.Theta()-MomRecPCA.Theta()));
	// hResPhrecZmc->Fill(PosMCpca.Z(),MomMCpca.Phi()-MomRecPCA.Phi());
	// hResPrecZmc->Fill(PosMCpca.Z(),MomMCpca.Mag()-MomRecPCA.Mag());

	// herrXrecZmc->Fill(PosMCpca.Z(),errPosRecPCA.X());
	// herrYrecZmc->Fill(PosMCpca.Z(),errPosRecPCA.Y());
	// herrZrecZmc->Fill(PosMCpca.Z(),errPosRecPCA.Z());
	// herrThrecZmc->Fill(PosMCpca.Z(),1e3*err_lyambda);
	// herrPhrecZmc->Fill(PosMCpca.Z(),err_phi);
	// herrPrecZmc->Fill(PosMCpca.Z(),errMomRecPCA.Mag());

	// hPullLikeX_Zmc->Fill(PosMCpca.Z(),PosRecPCA.X()/errPosRecPCA.X());
	// hPullLikeY_Zmc->Fill(PosMCpca.Z(),PosRecPCA.Y()/errPosRecPCA.Y());
	// hPullLikeZ_Zmc->Fill(PosMCpca.Z(),PosRecPCA.Z()/errPosRecPCA.Z());
	// hPullLikeTh_Zmc->Fill(PosMCpca.Z(),MomRecPCA.Theta()/err_lyambda);
	// hPullLikePh_Zmc->Fill(PosMCpca.Z(),MomRecPCA.Phi()/err_phi);
	// hPullLikeP_Zmc->Fill(PosMCpca.Z(),MomRecPCA.Mag()/errMomRecPCA.Mag());


	// hXrecXmc->Fill(PosMCpca.X(),PosRecPCA.X());
	// hYrecXmc->Fill(PosMCpca.X(),PosRecPCA.Y());
	// hZrecXmc->Fill(PosMCpca.X(),PosRecPCA.Z());
	// hThrecXmc->Fill(PosMCpca.X(),1e3*MomRecPCA.Theta());
	// hPhrecXmc->Fill(PosMCpca.X(),MomRecPCA.Phi());
	// hPrecXmc->Fill(PosMCpca.X(),MomRecPCA.Mag());

	// hResXrecXmc->Fill(PosMCpca.X(),PosMCpca.X()-PosRecPCA.X());
	// hResYrecXmc->Fill(PosMCpca.X(),PosMCpca.Y()-PosRecPCA.Y());
	// hResZrecXmc->Fill(PosMCpca.X(),PosMCpca.Z()-PosRecPCA.Z());
	// hResThrecXmc->Fill(PosMCpca.X(),1e3*(MomMCpca.Theta()-MomRecPCA.Theta()));
	// hResPhrecXmc->Fill(PosMCpca.X(),MomMCpca.Phi()-MomRecPCA.Phi());
	// hResPrecXmc->Fill(PosMCpca.X(),MomMCpca.Mag()-MomRecPCA.Mag());

	// herrXrecXmc->Fill(PosMCpca.X(),errPosRecPCA.X());
	// herrYrecXmc->Fill(PosMCpca.X(),errPosRecPCA.Y());
	// herrZrecXmc->Fill(PosMCpca.X(),errPosRecPCA.Z());
	// herrThrecXmc->Fill(PosMCpca.X(),1e3*err_lyambda);
	// herrPhrecXmc->Fill(PosMCpca.X(),err_phi);
	// herrPrecXmc->Fill(PosMCpca.X(),errMomRecPCA.Mag());

	// hPullLikeX_Xmc->Fill(PosMCpca.X(),PosRecPCA.X()/errPosRecPCA.X());
	// hPullLikeY_Xmc->Fill(PosMCpca.X(),PosRecPCA.Y()/errPosRecPCA.Y());
	// hPullLikeZ_Xmc->Fill(PosMCpca.X(),PosRecPCA.Z()/errPosRecPCA.Z());
	// hPullLikeTh_Xmc->Fill(PosMCpca.X(),MomRecPCA.Theta()/err_lyambda);
	// hPullLikePh_Xmc->Fill(PosMCpca.X(),MomRecPCA.Phi()/err_phi);
	// hPullLikeP_Xmc->Fill(PosMCpca.X(),MomRecPCA.Mag()/errMomRecPCA.Mag());


	// ///////
	// hXrecYmc->Fill(PosMCpca.Y(),PosRecPCA.X());
	// hYrecYmc->Fill(PosMCpca.Y(),PosRecPCA.Y());
	// hZrecYmc->Fill(PosMCpca.Y(),PosRecPCA.Z());
	// hThrecYmc->Fill(PosMCpca.Y(),1e3*MomRecPCA.Theta());
	// hPhrecYmc->Fill(PosMCpca.Y(),MomRecPCA.Phi());
	// hPrecYmc->Fill(PosMCpca.Y(),MomRecPCA.Mag());

	// hResXrecYmc->Fill(PosMCpca.Y(),PosMCpca.X()-PosRecPCA.X());
	// hResYrecYmc->Fill(PosMCpca.Y(),PosMCpca.Y()-PosRecPCA.Y());
	// hResZrecYmc->Fill(PosMCpca.Y(),PosMCpca.Z()-PosRecPCA.Z());
	// hResThrecYmc->Fill(PosMCpca.Y(),1e3*(MomMCpca.Theta()-MomRecPCA.Theta()));
	// hResPhrecYmc->Fill(PosMCpca.Y(),MomMCpca.Phi()-MomRecPCA.Phi());
	// hResPrecYmc->Fill(PosMCpca.Y(),MomMCpca.Mag()-MomRecPCA.Mag());

	// herrXrecYmc->Fill(PosMCpca.Y(),errPosRecPCA.X());
	// herrYrecYmc->Fill(PosMCpca.Y(),errPosRecPCA.Y());
	// herrZrecYmc->Fill(PosMCpca.Y(),errPosRecPCA.Z());
	// herrThrecYmc->Fill(PosMCpca.Y(),1e3*err_lyambda);
	// herrPhrecYmc->Fill(PosMCpca.Y(),err_phi);
	// herrPrecYmc->Fill(PosMCpca.Y(),errMomRecPCA.Mag());

	// hPullLikeX_Ymc->Fill(PosMCpca.Y(),PosRecPCA.X()/errPosRecPCA.X());
	// hPullLikeY_Ymc->Fill(PosMCpca.Y(),PosRecPCA.Y()/errPosRecPCA.Y());
	// hPullLikeZ_Ymc->Fill(PosMCpca.Y(),PosRecPCA.Z()/errPosRecPCA.Z());
	// hPullLikeTh_Ymc->Fill(PosMCpca.Y(),MomRecPCA.Theta()/err_lyambda);
	// hPullLikePh_Ymc->Fill(PosMCpca.Y(),MomRecPCA.Phi()/err_phi);
	// hPullLikeP_Ymc->Fill(PosMCpca.Y(),MomRecPCA.Mag()/errMomRecPCA.Mag());

	hResTheta->Fill(1e3*(MomMCpca.Theta()-MomRecPCA.Theta()));
	hResTheta_th->Fill(1e3*MomMCpca.Theta(),1e3*(MomMCpca.Theta()-MomRecPCA.Theta()));
	hResTheta_ph->Fill(MomMCpca.Phi(),1e3*(MomMCpca.Theta()-MomRecPCA.Theta()));
	hResPhi->Fill(MomMCpca.Phi()-MomRecPCA.Phi());
	hPullTheta->Fill((MomMCpca.Theta()-MomRecPCA.Theta())/err_lyambda);
	hPullPhi->Fill((MomMCpca.Phi()-MomRecPCA.Phi())/err_phi);
	hErrTheta->Fill(err_lyambda);
	hErrPhi->Fill(err_phi);
	hResMom->Fill(MomMCpca.Mag()-MomRecPCA.Mag());
	//Near 1st LMD plane
	/// Read MC track parameters near LMD ------------------------------------
	TVector3 PosMClmd =  MCPointHit->GetPosition();
	double pxTrue =  MCPointHit->GetPx();
	double pyTrue =  MCPointHit->GetPy();
	double pzTrue =  MCPointHit->GetPz();
	TVector3 MomMClmd(pxTrue,pyTrue,pzTrue);
	TVector3 dirMClmd = MomMClmd;
	dirMClmd *=1./MomMClmd.Mag();
	double deltaZ = -PosMClmd.Z()+PosRecLMD.Z();
	//	double deltaZ = 0;
	double xneu=PosMClmd.X()+dirMClmd.X()*deltaZ;
	double yneu=PosMClmd.Y()+dirMClmd.Y()*deltaZ;
	double zneu = PosMClmd.Z()+deltaZ;
	PosMClmd.SetXYZ(xneu,yneu,zneu);
	//	MomMClmd = dirMClmd*MomMClmd.Mag();
	MomMClmd = dirMClmd*MomRecLMD.Mag();
	//	hResLumiTrkPointP->Fill((MomMClmd.Mag()-MomRecLMD.Mag()));
	//	hResLumiTrkPointPmcPrec->Fill(MomRecLMD.Mag(),MomMClmd.Mag());


	// MomMClmd *=1./MomMClmd.Mag();//TEST
	// MomRecLMD *=1./MomRecLMD.Mag();//TEST
	// errMomRecLMD *=1./MomRecLMD.Mag();//TEST

	//cout<<"MomMClmd.Mag() = "<<MomMClmd.Mag()<<" MomRecLMD.Mag() = "<<MomRecLMD.Mag()<<endl;
	// cout<<" MC - REC = "<<1e3*(MomMClmd.Mag()-MomRecLMD.Mag())<<" MeV"<<endl;
	///------------------------------------------------------------------------------------
	hResLumiTrkPointX->Fill(PosMClmd.X()-PosRecLMD.X());
	hResLumiTrkPointY->Fill(PosMClmd.Y()-PosRecLMD.Y());
	hResLumiTrkPointZ->Fill(PosMClmd.Z()-PosRecLMD.Z());
	hResLumiTrkPointXPull->Fill((PosMClmd.X()-PosRecLMD.X())/errPosRecLMD.X());
	hResLumiTrkPointYPull->Fill((PosMClmd.Y()-PosRecLMD.Y())/errPosRecLMD.Y());
	hResLumiTrkPointZPull->Fill((PosMClmd.Z()-PosRecLMD.Z())/errPosRecLMD.Z());

	hResLumiTrkPointPx->Fill(MomMClmd.X()-MomRecLMD.X());
	hResLumiTrkPointPy->Fill(MomMClmd.Y()-MomRecLMD.Y());
	hResLumiTrkPointPz->Fill(MomMClmd.Z()-MomRecLMD.Z());
	hResLumiTrkPointPxPull->Fill((MomMClmd.X()-MomRecLMD.X())/errMomRecLMD.X());
	hResLumiTrkPointPyPull->Fill((MomMClmd.Y()-MomRecLMD.Y())/errMomRecLMD.Y());
	hResLumiTrkPointPzPull->Fill((MomMClmd.Z()-MomRecLMD.Z())/errMomRecLMD.Z());


	hResLumiTrkTheta2D->Fill((MomMClmd.X()/MomMClmd.Z()-MomRecLMD.X()/MomRecLMD.Z()), (MomMClmd.Y()/MomMClmd.Z()-MomRecLMD.Y()/MomRecLMD.Z()));
	hMCLumiTrkTheta2D->Fill(MomMClmd.X()/MomMClmd.Z(), MomMClmd.Y()/MomMClmd.Z());
	hRecLumiTrkTheta2D->Fill(MomRecLMD.X()/MomRecLMD.Z(), MomRecLMD.Y()/MomRecLMD.Z());


	hResLumiTrkTheta->Fill(MomMClmd.Theta()-MomRecLMD.Theta());
	hResLumiTrkPhi->Fill(MomMClmd.Phi()-MomRecLMD.Phi());
	hResLumiTrkThetaPull->Fill((MomMClmd.Theta()-MomRecLMD.Theta())/err_lyambdaLMD);
	hResLumiTrkPhiPull->Fill((MomMClmd.Phi()-MomRecLMD.Phi())/err_phiLMD);
	hResLumiTrkPointXErr->Fill(errPosRecLMD.X());
	hResLumiTrkPointYErr->Fill(errPosRecLMD.Y());
	hResLumiTrkPointZErr->Fill(errPosRecLMD.Z());
	hResLumiTrkPointPxErr->Fill(errMomRecLMD.X());
	hResLumiTrkPointPyErr->Fill(errMomRecLMD.Y());
	hResLumiTrkPointPzErr->Fill(errMomRecLMD.Z());

      /// Comporision between MC tracks, reconstructed tracks near LMD  and back propagated tracks (END) -----
    }

  return;
}

ClassImp(PndLmdQATask);
