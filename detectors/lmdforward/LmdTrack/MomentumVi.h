//-----------------------------------------------------------
//
// Description:
//      Plot Angle vs Momentum
//
// Author List:
//      Jens Frech
//-----------------------------------------------------------

#ifndef MOMENTUMVIS_H
#define MOMENTUMVIS_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <vector>

class PndGeoHandling;
class TGraph2DErrors;
class TClonesArray;
class TGeoManager;
class TVector3;
namespace ROOT {
namespace Math {
class Minimizer;
}
}

class MomentumVi : public FairTask {
 public:
  // Constructors/Destructors ---------
  MomentumVi();
  MomentumVi(TString tMCBranchName, TString tMCTrackName,TString tRecoBranchName,TString tKoalaMCBranchName,TString tKoalaMCTrackName, TString tKoalaRecoBranchName, TString tBackBranchName, TString tTrkName);

  virtual ~MomentumVi();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

  virtual void Finish();

  void SetRadLen(double x) { ftotRadLen = 1e-2 * x; }  // rad.length X/X0 [%]

 protected:
  double FCN_MS(const double* vars);
  static double distance_MS(double x, double y, double z, double errx,
                            double erry, const double* p, double* zpr);
  double ScatteredAngle(double radLen);  // calculate uncertainty for kink angle
  double line3DfitMS(TGraph2DErrors* gr, const TVector3& posSeed,
                     const TVector3& dirSeed, std::vector<double>& fitpar,
                     TMatrixDSym* covmatrix);  // fit with kink angle
  double GetSigmaMS(int side) {
    if (side < 1)
      return fsigmaMSa;
    else
      return fsigmaMSb;
  }

  // Input Data------------
  TClonesArray* fMCArray;
  TClonesArray* fMCTrackArray;
  TClonesArray* fRecoArray;
  TClonesArray* fKoalaMCArray;
  TClonesArray* fKoalaMCTrackArray;
  TClonesArray* fKoalaRecoArray;
  TClonesArray* fBackArray;
  TClonesArray* fTrkArray;
  

  TString fMCBranchName;
  TString fMCTrackName;
  TString fRecoBranchName;
  TString fKoalaMCBranchName;
  TString fKoalaMCTrackName;
  TString fKoalaRecoBranchName;
  TString fBackBranchName;
  TString fTrkName;
  

  TH2F hLMDAng;
  TH2F hKoalaAng;
  TH2F hLMDX;
  TH2F hLMDY;
  TH2F hLMDtheta;
  TH2F hLMDMCphi;
  TH2F hLMDMCtheta;
  TH2F hLMDphi;
  TH2F hKoalaphi;
  TH2F hKoalatheta;
  TH2F hKoalathetaphi;
  TH2F hKoalaHitphi;
  TH2F hKoalaHittheta;
  TH2F hKoalaHitthetaphi;
  TH2F hKoalaHitphireco;
  TH2F hKoalaHitthetareco;
  TH2F hKoalaHitthetaphireco;
  TH2F hKoalaphiMC;
  TH2F hKoalathetaMC;
  TH2F hKoalathetaphiMC;
  TH2F hKoalaZ;
  TH2F hKoalaY;
  TH1F hLPhi;
  TH1F hLPhiMC;
  TH1F hLP;
  TH1F hLPMC;
  TH1F hLTheta;
  TH1F hLThetaMC;
  TH1F hKPhi;
  TH1F hKPhiMC;
  TH1F hKP;
  TH1F hKPMC;
  TH1F hKTheta;
  TH1F hKThetaMC;
  TH1F hKoPhi;
  TH1F hKoP;
  TH1F hKoTheta;
  TH1F hKoalaThetaReco;
  
  
  
  // Output Data----------
  TClonesArray* fMCOutArray;
  TClonesArray* fBackoutArray;

  double fPbeam;
  double fsigmaMSa;  // single hit before CVD diamond
  double fsigmaMSb;  // single hit after CVD diamond

  bool hitMergedfl[4];
  double fPDGCode;
  int fCharge;
  PndGeoHandling* fGeoH;

  ROOT::Math::Minimizer* fmin;
  TGraph2DErrors* fGraph2D;

  double ftotRadLen;  // X/X0



  ClassDef(MomentumVi, 2);
};

#endif
