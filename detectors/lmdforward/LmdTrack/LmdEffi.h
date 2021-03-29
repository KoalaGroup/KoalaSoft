//-----------------------------------------------------------
//
// Description:
//      Efficiency determination tool
//
// Author List:
//      Jens Frech
//-----------------------------------------------------------

#ifndef LMDEFFI_H
#define LMDEFFI_H

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

class LmdEffi : public FairTask {
 public:
  // Constructors/Destructors ---------
  LmdEffi();
  LmdEffi(TString tMCBranchName, TString tMCTrackName,TString tRecoBranchName ,TString tTrkName ,TString tBackBranchName,TString tBackTrackBranchName, TString tCompBranchName );

  virtual ~LmdEffi();

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
  TClonesArray* fTrkArray;
  TClonesArray* fBackArray;  
  TClonesArray* fBackTrackArray;  
  TClonesArray* fCompArray;

  TString fMCBranchName;
  TString fMCTrackName;
  TString fRecoBranchName;
  TString fTrkName;
  TString fBackBranchName;
  TString fBackTrackBranchName;
  TString fCompBranchName;

  TH2F hMC2D;
  TH2F hBack2D;
  TH2F hComp2D;
  TH2F hMCComp;
  TH2F hCompBack;
  TH2F hBackdiv;
  TH2F hRecoTrack;
  TH2F hMCReco;
  TH2F hReco;
  TH2F hReco4Hits;
  TH2F hRecoComp;
  TH2F hTrackProp;
  TH2F hTrack2D;
  TH2F hBPPos;
  TH1F hRecoResiX;
  TH1F hRecoResiY;
  TH1F hCompResiX;
  TH1F hCompResiY;
  TH1F hCompBPResiZ;
  TH1F hCompBPResiY;
  TH1F hCompBPResiX;
  TH1F hCompResitheta;
  TH1F hCompResiphi;
  
  
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



  ClassDef(LmdEffi, 2);
};

#endif
