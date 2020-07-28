// -------------------------------------------------------------------------
// -----                    PndLinTrack source file                -----
// -----                                 -----
// -------------------------------------------------------------------------

#include "PndLinTrack.h"
#include <cmath>
#include <iostream>
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoNode.h"
#include "TGeoVolume.h"
#include "TMath.h"
#include "stdlib.h"

// -----   Default constructor   -------------------------------------------
PndLinTrack::PndLinTrack() {
  // std::cout<<"/lmd/LmdTrack/PndLinTrack()"<<std::endl;
  // fCovMatrix = new TMatrixDSym(6);
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
PndLinTrack::PndLinTrack(TString detName, Double_t p0, Double_t p1, Double_t p2,
                         Double_t p3, Double_t p4, Double_t p5, Double_t chi,
                         Int_t first, Int_t last, Int_t cand) {
  fDetName = detName;
  fP0 = p0;
  fP1 = p1;
  fP2 = p2;
  fP3 = p3;
  fP4 = p4;
  fP5 = p5;
  fChiSq = chi;
  fFirst = first;
  fLast = last;
  fCandId = cand;
  // fP0err = p0err; fP1err = p1err; fP2err = p2err; fP3err = p3err;
  // fz0 = z0;
  // fCovMatrix = NULL;
  fCovMatrix.ResizeTo(6, 6);
  // fCovMatrix = TMatrixDSym(6);
}

// TVector3 PndLinTrack::GetStartVec(){
//   return TVector3(fP0,fP2,fP4);
//   // return TVector3(fP0,fP2,fP4-0.0075);//go out middle of the plane
// }

// TVector3 PndLinTrack::GetDirectionVec(){
//   //  double l = 1./sqrt(1+fP1*fP1+fP3*fP3);
//   // double l = 1./sqrt(fP1*fP1+fP3*fP3+fP5*fP5);
//   // return TVector3(fP1*l,fP3*l,fP5*l);
//   //  double l = sqrt(1-fP1*fP1-fP3*fP3);
//   // double l = sqrt(1-hypot(fP1,fP3));
//   //  std::cout<<"fP1 = "<<fP1<<" fP3 = "<<fP3<<" l = "<<l<<std::endl;
//   // TVector3 res = TVector3(fP1,fP3,l);
//  TVector3 res = TVector3(fP1,fP3,fP5);
//  // res *= 1./res.Mag();
//  return res;
// }

TVector3 PndLinTrack::GetStartErrVec() {
  return TVector3(TMath::Sqrt((fCovMatrix)(0, 0)),
                  TMath::Sqrt((fCovMatrix)(2, 2)),
                  TMath::Sqrt((fCovMatrix)(4, 4)));
}

TVector3 PndLinTrack::GetDirectionErrVec() {
  // double err_dx = sqrt((fCovMatrix)(1,1));
  // double err_dy = sqrt((fCovMatrix)(3,3));
  // double l = sqrt(1-fP1*fP1-fP3*fP3);
  // double err_dz = sqrt(pow(fP1/l,2)*((fCovMatrix)(1,1))+
  // pow(fP3/l,2)*((fCovMatrix)(3,3))
  // 		       +2*fP1*fP3/(l*l)*((fCovMatrix)(1,3)));
  // return TVector3(err_dx,err_dy,err_dz);
  // double l = 1./sqrt(1+fP1*fP1+fP3*fP3);
  // // std::cout<<"l = "<<l<<" pow(l,3) = "<<pow(l,3)<<" p1="<<fP1<<"
  // p3="<<fP3<<std::endl;
  // double ddx_dp1=(1+fP3*fP3);
  // double ddx_dp3=fP1*fP3;
  // double err_dx =
  // pow(l,3)*sqrt(ddx_dp1*ddx_dp1*((fCovMatrix)(1,1))+ddx_dp3*ddx_dp3*((fCovMatrix)(3,3))
  // 		      +(2*ddx_dp1*ddx_dp3*((fCovMatrix)(1,3))));
  // std::cout<<"err_dx = "<<ddx_dp1*ddx_dp1*((fCovMatrix)(1,1))<<" +
  // "<<ddx_dp3*ddx_dp3*((fCovMatrix)(3,3))
  //  	  <<" + "<<2*ddx_dp1*ddx_dp3*((fCovMatrix)(1,3))<<" =
  //  "<<err_dx<<std::endl;

  // double ddy_dp1=fP1*fP3;
  // double ddy_dp3=(1+fP1*fP1);
  // double err_dy =
  // pow(l,3)*sqrt(ddy_dp1*ddy_dp1*((fCovMatrix)(1,1))+ddy_dp3*ddy_dp3*((fCovMatrix)(3,3))
  // 		      +(2*ddy_dp1*ddy_dp3*fabs((fCovMatrix)(1,3))));

  // double ddz_dp1=fP1;
  // double ddz_dp3=fP3;
  // double err_dz
  // =pow(l,3)*sqrt(ddz_dp1*ddz_dp1*((fCovMatrix)(1,1))+ddz_dp3*ddz_dp3*((fCovMatrix)(3,3))
  // 		      +(2*ddz_dp1*ddz_dp3*fabs((fCovMatrix)(1,3))));
  // return TVector3(err_dx,err_dy,err_dz);

  //  double l = pow(fP1*fP1+fP3*fP3+fP5*fP5,-0.5);
  //   double l3 = pow(l,3);
  //   double p12 = pow(fP1,2);
  //   double p32 = pow(fP3,2);
  //   double p52 = pow(fP5,2);
  //   double p1p3 = fP1*fP3;
  //   double p1p5 = fP1*fP5;
  //   double p3p5 = fP3*fP5;

  //   double err_dx =
  //   sqrt(pow((l-p12*l3),2)*((fCovMatrix)(1,1))+pow((p1p3*l3),2)*((fCovMatrix)(3,3))+pow((p1p5*l3),2)*((fCovMatrix)(5,5))+2*((l-p12*l3)*(-fP1*fP3*l3)*((fCovMatrix)(1,3))+(l-p12*l3)*(-fP1*fP5*l3)*((fCovMatrix)(1,5))+p12*fP3*fP5*l3*l3*((fCovMatrix)(3,5))));
  // double err_dy =
  // sqrt(pow((l-p32*l3),2)*((fCovMatrix)(3,3))+pow((p1p3*l3),2)*((fCovMatrix)(1,1))+pow((p3p5*l3),2)*((fCovMatrix)(5,5))+2*((l-p32*l3)*(-fP1*fP3*l3)*((fCovMatrix)(1,3))+(l-p32*l3)*(-fP3*fP5*l3)*((fCovMatrix)(3,5))+p32*fP1*fP5*l3*l3*((fCovMatrix)(1,5))));
  // double err_dz =
  // sqrt(pow((l-p52*l3),2)*((fCovMatrix)(5,5))+pow((p3p5*l3),2)*((fCovMatrix)(3,3))+pow((p1p5*l3),2)*((fCovMatrix)(1,1))+2*((l-p52*l3)*(-fP1*fP5*l3)*((fCovMatrix)(1,5))+(l-p52*l3)*(-fP3*fP5*l3)*((fCovMatrix)(3,5))+p52*fP1*fP3*l3*l3*((fCovMatrix)(1,3))));
  //  return TVector3(err_dx,err_dy,err_dz);
  return TVector3(TMath::Sqrt((fCovMatrix)(1, 1)),
                  TMath::Sqrt((fCovMatrix)(3, 3)),
                  TMath::Sqrt((fCovMatrix)(5, 5)));
}

void PndLinTrack::GetParErr(Double_t* errpar) {
  errpar[0] = TMath::Sqrt((fCovMatrix)(0, 0));
  errpar[1] = TMath::Sqrt((fCovMatrix)(1, 1));
  errpar[2] = TMath::Sqrt((fCovMatrix)(2, 2));
  errpar[3] = TMath::Sqrt((fCovMatrix)(3, 3));
  errpar[4] = TMath::Sqrt((fCovMatrix)(4, 4));
  errpar[5] = TMath::Sqrt((fCovMatrix)(5, 5));
}

// -----   Destructor   ----------------------------------------------------
PndLinTrack::~PndLinTrack() {}

// -------------------------------------------------------------------------
ClassImp(PndLinTrack);
