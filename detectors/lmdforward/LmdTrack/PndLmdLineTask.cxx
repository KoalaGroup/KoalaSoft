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
#include "PndLmdLineTask.h"

// C/C++ Headers ----------------------
#include <iostream>

// Collaborating Class Headers --------
#include "FairRootManager.h"
#include "PndLinTrack.h"
#include "PndSdsHit.h"
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
#include <TCanvas.h>
#include <TF2.h>
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include <TH1.h>
#include <TLine.h>
#include <TMatrixDSym.h>
#include <TMatrixTSym.h>
#include <TPolyLine3D.h>
#include <TVirtualFitter.h>
//#include <PndSdsMCPoint.h>
#include <TMultiGraph.h>
#include <TPolyLine3D.h>
using namespace ROOT::Math;
using namespace std;

// TH1 *hchi2_0 = new TH1F("hchi2_0","#chi^{2};",4,-0.1,2.);
// TH1 *hchi2_1 = new TH1F("hchi2_1","#chi^{2};",40,-1,20.);
// TH1 *hchi2_2 = new TH1F("hchi2_2","#chi^{2};",100,-1,50.);
// TH1 *hchi2_3 = new TH1F("hchi2_3","#chi^{2};",100,-1,50.);

PndLmdLineTask::PndLmdLineTask(TString hitBranch)
    : FairTask("Connect 2 points task") {
  fTCandBranchName = "LMDTrackCand";
  fRecoBranchName = hitBranch;
  fTruePointBranch = "LMDPoint";  // True Points only for drawing!
}

PndLmdLineTask::~PndLmdLineTask() {
  cout << "PndLmdLineTask::~PndLmdLineTask()" << endl;
}

InitStatus PndLmdLineTask::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  if (ioman == 0) {
    Error("PndLmdLineTask::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fTCandArray = (TClonesArray*)ioman->GetObject(fTCandBranchName);

  if (fTCandArray == 0) {
    Error("PndLmdLineTask::Init", "trackcand-array not found!");
    return kERROR;
  }

  fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("PndLmdLineTask::Init", "reco-array not found!");
    return kERROR;
  }

  fTrackArray = new TClonesArray("PndLinTrack");
  ioman->Register("LMDTrack", "PndLmd", fTrackArray, kTRUE);

  std::cout << "-I- PndLmdLineTask: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void PndLmdLineTask::Exec(Option_t*) {
  std::cout << "PndLmdLineTask::Exec" << std::endl;
  // Reset output Array
  if (fTrackArray == 0) Fatal("PndLmdLineTask::Exec", "No TrackArray");
  fTrackArray->Delete();

  Int_t ntcand = fTCandArray->GetEntriesFast();

  // Detailed output
  if (fVerbose > 1)
    std::cout << " -I- PndLmdLineTask: contains " << ntcand << " RhoCandidates"
              << std::endl;
  if (fVerbose > 2) {
    std::cout << " Detailed Debug info on the candidates:" << std::endl;
    unsigned int index =
        12345;  // detid=12345,  //[R.K.03/2017] unused variable
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

  // Fitting
  // ----------------------------------------------------------------------------------
  if (fVerbose > 1)
    std::cout << " -I- PndLmdLineTask: start Fitting " << std::endl;
  int rec_tkr = 0;
  for (Int_t track = 0; track < ntcand; track++) {
    PndTrackCand* trcnd = (PndTrackCand*)fTCandArray->At(track);
    const int numPts = trcnd->GetNHits();  // read how many points in this track

    /// Obtain first approximation
    PndTrackCandHit theHit1 = trcnd->GetSortedHit(0);  // get 1st hit
    Int_t index1 = theHit1.GetHitId();
    PndSdsHit* Hit1sds = (PndSdsHit*)fRecoArray->At(index1);
    TVector3 posSeed = Hit1sds->GetPosition();
    PndTrackCandHit theHit2 = trcnd->GetSortedHit(numPts - 1);  // get last hit
    Int_t index2 = theHit2.GetHitId();
    PndSdsHit* Hit2sds = (PndSdsHit*)fRecoArray->At(index2);
    TVector3 pos2 = Hit2sds->GetPosition();
    TVector3 dirSeed = pos2 - posSeed;
    dirSeed *= 1. / dirSeed.Mag();
    // TVector3 posSeed = trcnd->getPosSeed();
    // TVector3 dirSeed = trcnd->getDirSeed();
    if (fVerbose > 2)
      std::cout << "Track: " << track << " Points: " << numPts << std::endl;
    ///------------------------------

    // TGraph2DErrors fitme(numPts); //new graph for fitting
    Int_t firstHit = -1, lastHit = -1;
    for (int ihit = 0; ihit < numPts; ihit++) {            // fill Graph
      PndTrackCandHit theHit = trcnd->GetSortedHit(ihit);  // get hit
      Int_t index = theHit.GetHitId();
      // Int_t detId = theHit.GetDetId(); //[R.K. 01/2017] unused variable
      // if(fVerbose>2) std::cout << "Point: "<< ihit<< " index: "<< index
      // <<std::endl;

      if (ihit == 0)
        firstHit = index;
      else if (ihit == numPts - 1)
        lastHit = index;
      // PndSdsHit* addHit = (PndSdsHit*) fRecoArray->At(index);
      // TVector3 addPos = addHit->GetPosition();
      // cout<<"#"<<ihit<<" addPos:"<<endl;
      // addPos.Print();
      // fitme.SetPoint(ihit, addPos.X(), addPos.Y(), addPos.Z());
      // fitme.SetPointError(ihit, addHit->GetDx(), addHit->GetDy(),
      // addHit->GetDz());

      //   PndSdsMCPoint *addHit = (PndSdsMCPoint*) fTruePointArray->At(index);
      //   //TEST ideal fit
      // TVector3 addPos = addHit->GetPosition();
      // fitme.SetPoint(ihit, addPos.X(), addPos.Y(), addPos.Z());
      // PndSdsHit* recHit = (PndSdsHit*) fRecoArray->At(index);
      // fitme.SetPointError(ihit, recHit->GetDx(), recHit->GetDy(),
      // recHit->GetDz());
    }  // end of Hits in TCand

    /*Double_t parFit[6]; //fit-parameter
    TMatrixDSym *COVmatrix = new TMatrixDSym(6);
    Double_t accuracy = line3Dfit(numPts, &fitme, posSeed, dirSeed, parFit,
    COVmatrix);*/

    //  if(accuracy>0 && accuracy<1e3){
    // start (P0, P2, P4), direction (P1, P3, P5) straight line
    PndLinTrack* trackfit = new PndLinTrack(
        "Lumi", posSeed.X(), dirSeed.X(), posSeed.Y(), dirSeed.Y(), posSeed.Z(),
        posSeed.Z(), 0, firstHit, lastHit, track);
    // PndLinTrack* trackfit = new PndLinTrack("Lumi", parFit[0], parFit[1],
    // parFit[2], parFit[3], parFit[4], parFit[5],
    //				    accuracy, firstHit, lastHit, track);
    // trackfit->SetCovarianceMatrix(*COVmatrix);
    new ((*fTrackArray)[rec_tkr]) PndLinTrack(*(trackfit));  // save Track
    delete trackfit;                                         // TEST
    rec_tkr++;
    //  }
  }  // end of TCand's

  // Done--------------------------------------------------------------------------------------

  // TCanvas *c1 = new TCanvas("hchi2");
  // c1->Divide(2,2);
  // c1->cd(1);
  // hchi2_0->Draw();
  // c1->cd(2);
  // hchi2_1->Draw();
  // c1->cd(3);
  // hchi2_2->Draw();
  // c1->cd(4);
  // hchi2_3->Draw();
  // //   c1->Write();
  // gPad->WaitPrimitive();
  std::cout << "Fitting done" << std::endl;
  return;
}

// // define the parameteric line equation
// void PndLmdLinFitTask::line(double t, double *p, double &x, double &y, double
// &z) {
//    // a parameteric line is define from 6 parameters but 4 are independent
//    // x0,y0,z0,z1,y1,z1 which are the coordinates of two points on the line
//    // can choose z0 = 0 if line not parallel to x-y plane and z1 = 1;
//    x = p[0] + p[1]*t;
//    y = p[2] + p[3]*t;
//    z = t;
//    //  std::cout<<"PndLmdLinFitTask::line z = "<<z<<std::endl;
// }

// calculate distance line-point
/*double PndLmdLinFitTask::distance2(double x,double y,double z, double *p) {
   // distance line point is D= | (xp-x0) cross  ux |
   // where ux is direction of line and x0 is a point in the line (like t = 0)
   XYZVector xp(x,y,z);
   // XYZVector x0(p[0], p[2], 0. );
   // XYZVector x1(p[0] + p[1], p[2] + p[3], 1. );
   //   XYZVector x0(p[0], p[2], fz0 ); //Move origin of local coordinates to
first lumi plane
   //   XYZVector x1(p[0] + p[1], p[2] + p[3], fz0+1. );
   XYZVector x0(p[0], p[2], p[4] ); //! Move origin of local coordinates to
first lumi plane
   XYZVector x1(p[0] + p[1], p[2] + p[3], p[5] ); //!
   XYZVector u = (x1-x0).Unit();
   double d2 = ((xp-x0).Cross(u)) .Mag2();
   return d2;
}*/

// function to be minimized
/*void PndLmdLinFitTask::SumDistance2(int &, double *, double & sum, double *
par, int ) {
   TGraph2D * gr = dynamic_cast<TGraph2D*>(
(TVirtualFitter::GetFitter())->GetObjectFit() );
   assert(gr != 0);
   double * x = gr->GetX();
   double * y = gr->GetY();
   double * z = gr->GetZ();
   int npoints = gr->GetN();
   sum = 0;
   for (int i  = 0; i < npoints; ++i) {
      double d = distance2(x[i],y[i],z[i],par);
      sum += d;
   }
   //if (firstIt && fVerbose>1)
   //   std::cout << "Total sum2 = " << sum << std::endl;
   //firstIt = false;
}*/

// calculate distance line-point in local coordinates
/*double PndLmdLinFitTask::distance_perp(double x,double y,double z, double
errx,double erry,double errz, double *p) {
  //Double_t t_min =
(p[1]*(x-p[0])+p[3]*(y-p[2])+p[5]*(z-p[4]))/(p[1]*p[1]+p[3]*p[3]+p[5]*p[5]);
  // p[5]=sqrt(1-p[1]*p[1]-p[3]*p[3]);//TEST
  //  Double_t t_min = (z-p[4])/p[5];
  //  Double_t t_min = (p[1]*(x-p[0])+p[3]*(y-p[2])+p[5]*(z-p[4])); //TEST
  Double_t t_min = (z-p[4]);
  Double_t fdx = pow((p[0]+p[1]*t_min-x)/errx,2);
  Double_t fdy = pow((p[2]+p[3]*t_min-y)/erry,2);
  //  Double_t fdz = pow((p[4]+p[5]*t_min-z)/errz,2);
  //  Double_t fdz = pow((p[4]+p[5]*t_min-z)/1.,2);
  // cout<<"fdx = pow("<<(p[0]+p[1]*t_min-x)<<"/"<<errx<<",2) = "<<fdx<<endl;
  // cout<<"fdy = pow("<<(p[2]+p[3]*t_min-y)<<"/"<<erry<<",2) = "<<fdy<<endl;
  // cout<<"fdz = pow("<<(p[4]+p[5]*t_min-z)<<"/"<<errz<<",2) = "<<fdz<<endl;
  //  cout<<"fdx = "<<fdx<<" fdy = "<<fdy<<" fdz = "<<fdz<<endl;
  //  Double_t fchi2 = fdx + fdy + fdz;
  Double_t fchi2 = fdx + fdy;
  // cout<<"fchi2 = "<<fchi2<<endl;
  return fchi2;
}*/

// calculate distance line-point in local coordinates
/*double PndLmdLinFitTask::distance_l(double x,double y,double z, double
errx,double erry,double errz, double *p) {
  // cout<<"(p[1]*p[1]+p[3]*p[3]) = "<<(p[1]*p[1]+p[3]*p[3])<<endl;
  // if((p[1]*p[1]+p[3]*p[3])>1) return 1e6;

  // double fdx = TMath::Power((x-(p[0] + p[1]*(z-fz0)))/errx,2);
  // double fdy = TMath::Power((y-(p[2] + p[3]*(z-fz0)))/erry,2);
  double fdx = TMath::Power((x-(p[0] + p[1]*(z-p[4])))/errx,2);
  double fdy = TMath::Power((y-(p[2] + p[3]*(z-p[4])))/erry,2);
  double fchi2 = fdx + fdy;
  std::cout<<"z = "<<z<<" fchi2 = "<<fchi2<<" fdx = "<<fdx<<" fdy =
"<<fdy<<std::endl;
  return fchi2;
}*/

// function to be minimized in local coordinates
/*void PndLmdLinFitTask::LocalFCN(int &, double *, double & sum, double * par,
int ) {
  TGraph2DErrors * gr = dynamic_cast<TGraph2DErrors*>(
(TVirtualFitter::GetFitter())->GetObjectFit() );
  assert(gr != 0);
  double * x = gr->GetX();
  double * y = gr->GetY();
  double * z = gr->GetZ();
  double * errx = gr->GetEX();
  double * erry = gr->GetEY();
  double * errz = gr->GetEZ();
  int npoints = gr->GetN();
  sum = 0;
  // double errMS[4]={0.,0.0031,0.0071,0.0119};//TEST with real MS error
  //  double errMS[4]={errx[0],0.0031,0.0071,0.0119};//TEST with real MS error
  for (int i  = 0; i < npoints; ++i) {
    // cout<<"hit#"<<i<<endl;
    // cout<<"Hit errors: x["<<i<<"]="<<errx[i]<<" y["<<i<<"]="<<erry[i]<<endl;
    // double errx_new = hypot(errx[i],errMS[i]);//TEST with real MS error
    // double erry_new = hypot(erry[i],errMS[i]);//TEST with real MS error
    // cout<<"errx_new ="<<errx_new<<endl;
    // cout<<"erry_new ="<<erry_new<<endl;
    //  double chi2 =
distance_perp(x[i],y[i],z[i],errx_new,erry_new,errz[i],par);

    double chi2 = distance_perp(x[i],y[i],z[i],errx[i],erry[i],errz[i],par);

    //double chi2 = distance_l(x[i],y[i],z[i],errx[i],erry[i],errz[i],par);
    sum += chi2;
    // if(i==0) hchi2_0->Fill(chi2);
    // if(i==1) hchi2_1->Fill(chi2);
    // if(i==2) hchi2_2->Fill(chi2);
    // if(i==3) hchi2_3->Fill(chi2);
    //    cout<<" "<<endl;
  }
  //  cout<<"CHI2 = "<<sum<<endl;
}*/

/*double PndLmdLinFitTask::line3Dfit(Int_t nd, TGraph2DErrors* gr, Double_t*
fitpar, Double_t* fitparerr)
{
  Int_t Npoint = gr->GetN();

  //The default minimizer is Minuit
  TVirtualFitter::SetDefaultFitter("Minuit");
  TVirtualFitter *min = TVirtualFitter::Fitter(0,4);
  min->SetObjectFit(gr);
  //min->SetFCN( *SumDistance2 );
  min->SetFCN(*LocalFCN);//using local coordinate in FCN
  Double_t arglist[100];
  arglist[0] = 1;
  min->ExecuteCommand("SET PRINT",arglist,1);

  double pStart[4] = {25.15,0.04,0.09,8.4e-5};
  double pStartErr[4] = {4.5,0.004,4.5,0.004};
  min->SetParameter(0,"x0",pStart[0],pStartErr[0],0,0);
  min->SetParameter(1,"Ax",pStart[1],pStartErr[1],0,0);
  min->SetParameter(2,"y0",pStart[2],pStartErr[2],0,0);
  min->SetParameter(3,"Ay",pStart[3],pStartErr[3],0,0);



  // // //minimize step 1
  // // arglist[0] = 100; //number of functiona calls
  // // arglist[1] = 0.001; //tolerance
  // // min->ExecuteCommand("HESSE", arglist ,2);

  // //minimize step 2
  arglist[0] = 1000; //number of functiona calls
  arglist[1] = 0.001; //tolerance
  min->ExecuteCommand("MIGRAD", arglist ,2);


  //if (minos) min->ExecuteCommand("MINOS",arglist,0);
   int nvpar,nparx;
   double amin,edm, errdef;
   min->GetStats(amin,edm,errdef,nvpar,nparx);
   if(fVerbose>1)
     min->PrintResults(1,amin);
   // gr->Draw("p0");

   // get fit parameters and errors
   for (int i = 0; i <4; ++i){
      fitpar[i] = min->GetParameter(i);
      fitparerr[i] = min->GetParError(i);
   }

   // return amin;
   Double_t chi2 = amin/(2.*Npoint-4);
   cout<<"Chi^2 = "<<chi2<<endl;
   return chi2;
}*/

/*double PndLmdLinFitTask::line3Dfit(Int_t nd, TGraph2DErrors* gr, TVector3
posSeed, TVector3 dirSeed, Double_t* fitpar, TMatrixDSym *covmatrix)
{
  cout<<"PndLmdLinFitTask::line3Dfit with SEED is used"<<endl;
  Int_t Npoint = gr->GetN();
  Double_t ErrX1 = gr->GetErrorX(0);
  Double_t ErrY1 = gr->GetErrorY(0);
  Double_t ErrZ1 = gr->GetErrorZ(0);
  Double_t ErrX2 = gr->GetErrorX(1);
  Double_t ErrY2 = gr->GetErrorY(1);
  Double_t ErrZ2 = gr->GetErrorY(1);

  Double_t errRx = TMath::Hypot(ErrX1,ErrX2);
  Double_t errRy = TMath::Hypot(ErrY1,ErrY2);
  Double_t errRz = TMath::Hypot(ErrZ1,ErrZ2);

  //The default minimizer is Minuit
  TVirtualFitter::SetDefaultFitter("Minuit");
  TVirtualFitter *min = TVirtualFitter::Fitter(0,5);
  min->SetObjectFit(gr);
  // min->SetFCN( *SumDistance2 );
  min->SetFCN(*LocalFCN);//using local coordinate in FCN
  Double_t arglist[100];
  arglist[0] = 1;
  min->ExecuteCommand("SET PRINT",arglist,1);

  cout<<"posSeed:"<<endl;
  posSeed.Print();
  cout<<"dirSeed:"<<endl;
  dirSeed.Print();
  double pStart[6] =
{posSeed.X(),dirSeed.X(),posSeed.Y(),dirSeed.Y(),posSeed.Z(),dirSeed.Z()};
  double pStartErr[6] = {ErrX1,errRx,ErrY1,errRy,ErrZ1,errRz};

  //stupid and must be removed!
  if(ErrX1==0 || ErrY1==0)
    for(int k=0;k<6;k++)  pStartErr[k]=0;

  min->SetParameter(0,"x0",pStart[0],pStartErr[0],0,0);
  min->SetParameter(1,"Ax",pStart[1],pStartErr[1],0,0);
  min->SetParameter(2,"y0",pStart[2],pStartErr[2],0,0);
  min->SetParameter(3,"Ay",pStart[3],pStartErr[3],0,0);
  min->SetParameter(4,"z0",pStart[4],0,0,0);
  // min->SetParameter(5,"Az",pStart[5],0,0,0);
  min->SetParameter(5,"Az",1.,0,0,0);

  // Now ready for minimization step
  arglist[0] = 1500;
  // arglist[0] = 1; //TEST
  arglist[1] = 1.;
  min->ExecuteCommand("MIGRAD", arglist,2);

  ///Get results ---------------------------------------------
   int nvpar,nparx;
   double amin,edm, errdef;
   min->GetStats(amin,edm,errdef,nvpar,nparx);
   if(fVerbose>1)
     min->PrintResults(1,amin);
   // gr->Draw("p0");

   Double_t fitparerr[6];
   // get fit parameters
   for (int i = 0; i <6; ++i){
      fitpar[i] = min->GetParameter(i);
      fitparerr[i] = min->GetParError(i);
   }

   // fitpar[5]=sqrt(1-fitpar[1]*fitpar[1]-fitpar[3]*fitpar[3]);
   // cout<<"SEED DIR=("<<dirSeed.X()<<", "<<dirSeed.Y()<<",
"<<dirSeed.Z()<<")"<<endl;
   // cout<<"RecTRK DIR=("<<fitpar[1]<<", "<<fitpar[3]<<",
"<<fitpar[5]<<")"<<endl;
   for(size_t i=0;i<4;i++){
     for(size_t j=0;j<4;j++){
       (*covmatrix)(i,j)= min->GetCovarianceMatrixElement(i,j);
     }
   }
   (*covmatrix)(4,4) =  gr->GetErrorZ(0)*gr->GetErrorZ(0);
   (*covmatrix)(4,4) += (*covmatrix)(0,0)*pow(tan(2.326*TMath::Pi()/180.),2);
   // double dp5_dp1 = fabs(fitpar[1]/pow(fitpar[5],3));
   // double dp5_dp3 = fabs(fitpar[3]/pow(fitpar[5],3));
   // double errdz2 = pow(dp5_dp1,2)*(*covmatrix)(1,1) +
pow(dp5_dp3,2)*(*covmatrix)(3,3) +
   //   2*dp5_dp1*dp5_dp3*(*covmatrix)(1,3);
   // cout<<"pow(dp5_dp1,2)*(*covmatrix)(1,1) =
"<<pow(dp5_dp1,2)*(*covmatrix)(1,1)<<endl;
   // cout<<"pow(dp5_dp3,2)*(*covmatrix)(3,3) =
"<<pow(dp5_dp3,2)*(*covmatrix)(3,3)<<endl;
   // cout<<"2*dp5_dp1*dp5_dp3*(*covmatrix)(1,3) =
"<<2*dp5_dp1*dp5_dp3*(*covmatrix)(1,3)<<endl;
   // (*covmatrix)(5,5) = errdz2;
   //(*covmatrix)(5,5) =
(fitpar[1]*fitpar[1]*(*covmatrix)(1,1)+fitpar[3]*fitpar[3]*(*covmatrix)(3,3))/pow(fitpar[5],6);
   for(size_t i=0;i<6;i++){
     for(size_t j=0;j<6;j++){
       cout<<(*covmatrix)(i,j)<<" ";
     }
         cout<<endl;
   }

   //  Double_t chi2 = amin/(3.*Npoint-6);
   // Double_t chi2 = amin/(3.*Npoint-3);
   //  Double_t chi2 = amin/(3.*Npoint-5);
   Double_t chi2 = amin/(2.*Npoint-4);
   //Double_t chi2 = amin/(3.*Npoint-4);
   //Double_t chi2 = amin;
   cout<<"After fit: Chi^2 = "<<chi2<<endl;
   ///-------------------------------------------------------------

   return chi2;
}*/

ClassImp(PndLmdLineTask);
