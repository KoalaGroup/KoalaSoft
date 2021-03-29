//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

#ifndef KOACOMP_H
#define KOACOMP_H

#include "FairTask.h"

#include "TMatrixDSym.h"
#include "TString.h"
#include "PndTrackCand.h"
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

class KoaComp : public FairTask {
 public:
  // Constructors/Destructors ---------
  KoaComp();
  KoaComp(TString tBackPropBranchName, TString tRecoBranchName,
	    TString tOutputBranchName = "LMDCompa",
	    TString tKoaOutputBranchName = "KOALACompa",
	    TString tOutputFolder = "Koala");

  virtual ~KoaComp();

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
  TClonesArray* fBackPropArray;
  TClonesArray* fRecoArray;

  TString fBackPropBranchName;
  TString fRecoBranchName;
  TString fOutputBranchName;
  TString fOutputFolder;
  TString fKoaOutputBranchName;
  // Output Data----------
  TClonesArray* fTrackArray;
  TClonesArray* fKoaRecoArray;

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

std::vector <int> GetPndTrackCand();

  ClassDef(KoaComp, 2);
};

#endif
