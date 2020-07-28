//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//
//-----------------------------------------------------------

#ifndef PNDLMDIDEALFITTASK_H
#define PNDLMDIDEALFITTASK_H

// Base Class Headers ----------------
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include "FairTask.h"

// Collaborating Class Headers -------
#include <map>
#include "TMatrixTSym.h"
#include "TString.h"
#include "TVector3.h"

// Collaborating Class Declarations --
class TClonesArray;
class TGeoManager;

// const Double_t fz0 = 1099.; //z-coordinate of first LMD plane
// void SumDistance2(int &, double *, double & sum, double * par, int ); //for
// Fitter
// void LocalFCN(int &, double *, double & sum, double * par, int ); //for
// Fitter in local coordinates
// minimization distance in 3D
// double distance2(double x,double y,double z, double *p);
// minimization distance in 2D in local coordinates
// double distance_l(double x, double y, double z, double errx, double erry,
// double errz, double *p);//in local coordinates
// minimization perpendicular distance between point and 3D line
// double distance_perp(double x,double y,double z, double errx,double
// erry,double errz, double *p);

class PndLmdIdealFitTask : public FairTask {
 public:
  // Constructors/Destructors ---------
  PndLmdIdealFitTask();
#ifndef __CINT__
  PndLmdIdealFitTask(const PndLmdIdealFitTask&) = delete;
  PndLmdIdealFitTask& operator=(const PndLmdIdealFitTask&) = delete;
#endif
  virtual ~PndLmdIdealFitTask();

  virtual InitStatus Init();

  virtual void Exec(Option_t* opt);

 protected:
  static Double_t fz0;  // z-coordinate of first LMD plane

  // Input Data------------
  TClonesArray* fTCandArray;
  TClonesArray* fRecoArray;
  TClonesArray* fMCPointArray;
  TClonesArray* fDigiArray;
  TClonesArray* fClustArray;
  TString fTCandBranchName;
  TString fRecoBranchName;
  TString fMCPointBranchName;
  TString fDigiBranchName;
  TString fClustBranchName;

  // Output Data----------
  TClonesArray* fTrackArray;

  // Bool_t firstIt;

  Int_t fTrackcount;

  Int_t fEvent;

  ClassDef(PndLmdIdealFitTask, 1);
};

#endif
