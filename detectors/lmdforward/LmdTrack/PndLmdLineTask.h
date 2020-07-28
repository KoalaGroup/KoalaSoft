//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//
//-----------------------------------------------------------

#ifndef PNDLMDLINETASK_H
#define PNDLMDLINETASK_H

// Base Class Headers ----------------
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TMatrixDSym.h"
#include "TMatrixTSym.h"
#include "TString.h"
#include "TVector3.h"
// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

class PndLmdLineTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdLineTask(TString hitBranch = "LMDHitsStrip");
#ifndef __CINT__
  PndLmdLineTask(const PndLmdLineTask&) = delete;
  PndLmdLineTask& operator=(const PndLmdLineTask&) = delete;
#endif
  virtual ~PndLmdLineTask();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

 protected:
  // static void SumDistance2(int &, double *, double & sum, double * par, int
  // ); //for Fitter
  // static void LocalFCN(int &, double *, double & sum, double * par, int );
  // //for Fitter in local coordinates
  /* //minimization distance in 3D */
  // static double distance2(double x,double y,double z, double *p);
  // minimization distance in 2D in local coordinates
  // static double distance_l(double x, double y, double z, double errx, double
  // erry, double errz, double *p);
  // minimization perpendicular distance between point and 3D line
  // static double distance_perp(double x,double y,double z, double errx,double
  // erry,double errz, double *p);

  // Input Data------------
  TClonesArray* fTCandArray;
  TClonesArray* fRecoArray;
  TClonesArray* fTruePointArray;

  TString fTCandBranchName;
  TString fRecoBranchName;
  TString fTruePointBranch;
  // Output Data----------
  TClonesArray* fTrackArray;

  // Bool_t firstIt;

  Int_t fTrackcount;

  Int_t fEvent;

  // Fitting ------------
  // void line(double t, double *p, double &x, double &y, double &z);
  double line3Dfit(Int_t nd, TGraph2DErrors* gr, Double_t* fitpar,
                   Double_t* fitparErr);
  double line3Dfit(Int_t nd, TGraph2DErrors* gr, TVector3 posSeed,
                   TVector3 dirSeed, Double_t* fitpar, TMatrixDSym* covmatrix);
  // double line3Dfit(Int_t nd, TGraph2DErrors* gr, TVector3 posSeed, TVector3
  // dirSeed, Double_t* fitpar);

  ClassDef(PndLmdLineTask, 1);
};

#endif
