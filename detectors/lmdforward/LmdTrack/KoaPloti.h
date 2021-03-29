//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOAPLOTI_H
#define KOAPLOTI_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
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

class KoaPloti : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaPloti();
  KoaPloti(TString tCompBranchName,TString tKoaCompBranchName, TString tRecoBranchName,TString tKoaRecoBranchName );

  virtual ~KoaPloti();

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
  TClonesArray* fCompArray;
  TClonesArray* fKoaCompArray;
  TClonesArray* fRecoArray;
  TClonesArray* fKoaRecoArray;

  TString fCompBranchName;
  TString fKoaCompBranchName;
  TString fRecoBranchName;
  TString fKoaRecoBranchName;

  TH2F hReco2D;
  TH2F hComp2D;
  TH2F hKoaComp2D;
  TH2F hKoaReco2D;
  ;
  // Output Data----------
  TClonesArray* fTrackArray;
  TClonesArray* fKoaArray;

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



  ClassDef(KoaPloti, 2);
};

#endif
