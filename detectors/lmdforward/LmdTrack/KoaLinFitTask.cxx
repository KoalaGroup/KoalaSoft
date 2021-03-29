//-----------------------------------------------------------
//
// Description:
//      3D Straight Line fitter
//
// Author List:
//      Mathias Michel
//      Anastasia Karavdina
//-----------------------------------------------------------

// This Class' Header ------------------
#include "KoaLinFitTask.h"

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
#include "PndSdsMergedHit.h"
#include "PndTrack.h"
#include "TClonesArray.h"
#include "TrackData/PndTrackCand.h"
#include "TrackData/PndTrackCandHit.h"

#include "TGraph2DErrors.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TVector3.h"
// Fit Classes -----------
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "Math/Minimizer.h"

using std::cout;
using std::endl;

KoaLinFitTask::KoaLinFitTask()
    : FairTask("3D-Straight-Line-Fit"),
      fTCandArray(0),
      fRecoArray(0),
      fTrackArray(0),
      fGeoH(0) {
  fTCandBranchName = "KOALATrackCand";
  // fRecoBranchName = "LMDHitsStrip";
  fRecoBranchName = "KOALAHitsPixel";
  //  fRecoBranchName = "LmdHits";
  fOutputBranchName = "KOALAPndTrack";
  fOutputFolder = "Koala";

  fPbeam = 0;
  fPDGCode = -2212;  // barp
  fCharge = -1;      // barp
  fsigmaMSa = 0;
  fsigmaMSb = 0;
  ftotRadLen = 0;

  fmin = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

  fmin->SetMaxFunctionCalls(1000000);
  fmin->SetMaxIterations(100000);
  fmin->SetTolerance(0.001);

  for (int ih = 0; ih < 4; ih++) hitMergedfl[ih] = false;
}
KoaLinFitTask::KoaLinFitTask(TString tTCandBranchName,
                                   TString tRecoBranchName,
                                   TString tOutputBranchName,
                                   TString tOutputFolder)
    : FairTask("3D-Straight-Line-Fit"),
      fTCandArray(0),
      fRecoArray(0),
      fTrackArray(0),
      fGeoH(0) {
  fTCandBranchName = tTCandBranchName;
  fRecoBranchName = tRecoBranchName;
  fOutputBranchName = tOutputBranchName;
  fOutputFolder = tOutputFolder;

  fPbeam = 0;
  fPDGCode = -2212;  // barp
  fCharge = -1;      // barp
  //  fsigmaMS = 0;
  fsigmaMSa = 0;
  fsigmaMSb = 0;
  ftotRadLen = 0;

  fmin = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

  fmin->SetMaxFunctionCalls(1000000);
  fmin->SetMaxIterations(100000);
  fmin->SetTolerance(0.001);

  for (int ih = 0; ih < 4; ih++) hitMergedfl[ih] = false;
}

KoaLinFitTask::~KoaLinFitTask() {
  //	delete fmin;
  cout << "KoaLinFitTask::~KoaLinFitTask()" << endl;
}

InitStatus KoaLinFitTask::Init() {
  // Get ROOT Manager
  FairRootManager* ioman = FairRootManager::Instance();

  if (ioman == 0) {
    Error("KoaLinFitTask::Init", "RootManager not instantiated!");
    return kERROR;
  }

  // Get input collection
  fTCandArray = (TClonesArray*)ioman->GetObject(fTCandBranchName);

  if (fTCandArray == 0) {
    Error("KoaLinFitTask::Init", "trackcand-array not found!");
    return kERROR;
  }

  fRecoArray = (TClonesArray*)ioman->GetObject(fRecoBranchName);

  if (fRecoArray == 0) {
    Error("KoaLinFitTask::Init", "reco-array not found!");
    return kERROR;
  }

  fTrackArray = new TClonesArray("PndTrack");
  ioman->Register(fOutputBranchName, fOutputFolder, fTrackArray, kTRUE);

  // read beam momentum from base
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairBaseParSet* par =
      (FairBaseParSet*)(rtdb->findContainer("FairBaseParSet"));
  fPbeam = par->GetBeamMom();
  fPDGCode = -2212;  // barp
  fCharge = -1;      // barp

  fGeoH = PndGeoHandling::Instance();
  //  double totRadLen = 0.00306;//rad.length of whole plane
  cout << "RadLeng = " << ftotRadLen << endl;
  double totRadLen = ftotRadLen;
  if (totRadLen < 1e-6)
    totRadLen = 0.00306;  // standart rad.length of whole plane
  // totRadLen -=2*0.000175;// -flex-cable
  // totRadLen -=0.00053;// -sensor
  fsigmaMSb = ScatteredAngle(totRadLen);
  double totRadLenCable = 0.053;  // sensor
  totRadLenCable += 0.05;         // rest
  fsigmaMSa = ScatteredAngle(totRadLenCable);

  fmin->SetPrintLevel(fVerbose);

  std::cout << "-I- KoaLinFitTask: Initialisation successfull" << std::endl;
  return kSUCCESS;
}

void KoaLinFitTask::Exec(Option_t*) {
  // Reset output Array
  if (fTrackArray == 0) Fatal("KoaLinFitTask::Exec", "No TrackArray");
  fTrackArray->Delete();

  Int_t ntcand = fTCandArray->GetEntriesFast();

  // Detailed output
  if (fVerbose > 1)
    std::cout << " -I- KoaLinFitTask: contains " << ntcand
              << " RhoCandidates" << std::endl;
  if (fVerbose > 2) {
    std::cout << " Detailed Debug info on the candidates:" << std::endl;
    unsigned int index = 12345;  // detid=12345,  //[R.K.03/2017] unused
                                 // variable
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

  // Fitting
  // ----------------------------------------------------------------------------------
  //  if(fVerbose>1)
  // std::cout<<" -I- KoaLinFitTask: start Fitting "<<std::endl;
  int rec_tkr = 0;
  for (Int_t track = 0; track < ntcand; track++) {
    PndTrackCand* trcnd = (PndTrackCand*)fTCandArray->At(track);
    const int numPts = trcnd->GetNHits();  // read how many points in this track

    TGraph2DErrors fitme(numPts);  // new graph for fitting
    // Int_t firstHit=-1, lastHit=-1; //[R.K.03/2017] unused variable
    TVector3 hit0, hit1;
    for (int ihit = 0; ihit < numPts; ihit++) {            // fill Graph
      PndTrackCandHit theHit = trcnd->GetSortedHit(ihit);  // get hit
      Int_t index = theHit.GetHitId();
      // Int_t detId = theHit.GetDetId(); //[R.K. 01/2017] unused variable
      // if(fVerbose>2) std::cout << "Point: "<< ihit<< " index: "<< index
      // <<std::endl;

      //      PndSdsHit* addHit = (PndSdsHit*) fRecoArray->At(index);
      PndSdsMergedHit* addHit = (PndSdsMergedHit*)fRecoArray->At(index);
      //      cout<<"IsMerged??? "<<addHit->GetIsMerged()<<endl;
      hitMergedfl[ihit] = addHit->GetIsMerged();

      TVector3 addPos = addHit->GetPosition();
      double xhit = addPos.X();
      double yhit = addPos.Y();
      double zhit = addPos.Z();
      //      lmddim->Transform_global_to_lmd_local(xhit,yhit,zhit,false);
      // TVector3 addPos2(xhit,yhit,zhit);
      if (ihit == 0) {
        // firstHit=index; //[R.K.03/2017] unused variable
        hit0 = addPos;
      } else {
        if (ihit == 2) hit1 = addPos;
        //	if(ihit==1) 	  hit1 = addPos;
        //	if(ihit==numPts-1) 	  hit1 = addPos;
        if (ihit == numPts - 1) {
          // lastHit=index; //[R.K.03/2017] unused variable
          //	  hit1 = addPos2;
        }
      }
      double errxhit = addHit->GetDx();
      double erryhit = addHit->GetDy();
      double errzhit = addHit->GetDz();
      fitme.SetPoint(ihit, xhit, yhit, zhit);
      fitme.SetPointError(ihit, errxhit, erryhit, errzhit);
      // fitme.SetPointError(ihit, 0.5*errxhit,0.5*erryhit,0.5*errzhit);
    }  // end of Hits in TCand

    TVector3 dirSeed = hit1 - hit0;
    TVector3 posSeed = hit0;
    // cout<<"DirSeed before fit and norm:"<<endl;
    // dirSeed.Print();
    dirSeed = dirSeed.Unit();
    std::vector<double> fit_parameters(22);  // fit-parameter
    TMatrixDSym* COVmatrix = new TMatrixDSym(6);
    Double_t accuracy = line3DfitMS(&fitme, posSeed, dirSeed, fit_parameters,
                                    COVmatrix);  // with kink angles
    //    Double_t accuracy = line3Dfit(numPts, &fitme, posSeed, dirSeed,
    //    parFit, COVmatrix); //MS taking into account by hits errors

    // save as PndTrack
    TVector3 FitPoint(fit_parameters[0], fit_parameters[2], fit_parameters[4]);
    TVector3 FitDir(fit_parameters[1], fit_parameters[3], fit_parameters[5]);
    //  TVector3 FitDir(parFit[1]+parFit[9], parFit[3]+parFit[17],
    //  sqrt(1-(parFit[1]+parFit[9])*(parFit[1]+parFit[9])-(parFit[3]+parFit[17])*(parFit[3]+parFit[17])));//TEST
    TVector3 FitMom = FitDir * fPbeam;
    Double_t COVmatrixPosMom[6][6];

    for (int ij = 0; ij < 6; ij++) {
      for (int ji = 0; ji < 6; ji++) COVmatrixPosMom[ij][ji] = 0;
    }

    int iconver[6] = {3, 0, 4, 1, 5, 2};
    for (int ij = 0; ij < 6; ij++) {
      for (int ji = 0; ji < 6; ji++) {
        if (ij == 1 || ij == 3 || ij == 5) (*COVmatrix)(ij, ji) *= fPbeam;
        if (ji == 1 || ji == 3 || ji == 5) (*COVmatrix)(ij, ji) *= fPbeam;
        int km = iconver[ij];
        int mk = iconver[ji];
        COVmatrixPosMom[km][mk] = (*COVmatrix)(ij, ji);
      }
    }
    delete COVmatrix;

    // Read info about 1st plane(sensor)
    PndTrackCandHit theHit = trcnd->GetSortedHit(0);  // get 1st hit
    Int_t hitID = theHit.GetHitId();
    int sysID = theHit.GetDetId();
    PndSdsHit* myHit = (PndSdsHit*)(fRecoArray->At(hitID));
    Int_t id = myHit->GetSensorID();

    TVector3 oo, uu, vv;
    fGeoH->GetOUVShortId(id, oo, uu, vv);
    // TVector3 o = oo;
    TVector3 o = FitPoint;
    TVector3 dj = uu;
    TVector3 dk = vv;

    FairTrackParP* trkfitp = new FairTrackParP(
        FitPoint, FitMom, COVmatrixPosMom, fCharge, o, dj, dk);
    int flagpndtrk = 0;
    if (accuracy > 1e3)
      flagpndtrk = -1;  // quality of track: bad if chi2 is too large
    int ndf = 2 * (trcnd->GetNHits()) - 4;  // number d.o.f
    int pid = fPDGCode;

    PndTrack* trackfit = new PndTrack(
        *trkfitp, *trkfitp, *trcnd, flagpndtrk, accuracy, ndf, pid, track,
        sysID);  // TODO: FairTrackParP at 1st and last point???
    new ((*fTrackArray)[rec_tkr]) PndTrack(*(trackfit));  // save Track

    delete trackfit;  // TEST
    rec_tkr++;
    //}
  }  // end of TCand's

  // Done--------------------------------------------------------------------------------------
  if (fVerbose > 2) std::cout << "Fitting done" << std::endl;

  return;
}

// calculate distance line-point in local coordinates
double KoaLinFitTask::distance_MS(double x, double y, double z, double errx,
                                     double erry, const double* p,
                                     double* zpr) {
  double THfunc[8] = {1, 1, 1, 1, 1, 1, 1, 1};
  //  p[5] = sqrt(1-p[1]*p[1]-p[3]*p[3]);
  // Double_t t_min = p[1]*(x-p[0])+p[3]*(y-p[2])+p[5]*(z-p[4]);
  //  Double_t t_min = p[5]*(z-p[4]);
  // Double_t t_min = p[1]*(x-p[0])+p[3]*(y-p[2]);
  Double_t t_min = p[1] * (x - p[0]) + p[3] * (y - p[2]) +
                   sqrt(1 - p[1] * p[1] - p[3] * p[3]) * (z - p[4]);
  //  Double_t t_min = (z-p[4]);//TEST
  for (int iz = 0; iz < 8; iz++)
    if (((p[4] + t_min) - zpr[iz]) <= 0) THfunc[iz] = 0;

  double funcX = p[0] + p[1] * t_min +
                 (-p[6] + p[7]) * ((p[4] + t_min) - zpr[0]) * THfunc[0] +
                 (-p[8] + p[9]) * ((p[4] + t_min) - zpr[2]) * THfunc[2] +
                 (-p[10] + p[11]) * ((p[4] + t_min) - zpr[4]) * THfunc[4] +
                 (-p[12] + p[13]) * ((p[4] + t_min) - zpr[6]) * THfunc[6];
  double funcY = p[2] + p[3] * t_min +
                 (-p[14] + p[15]) * ((p[4] + t_min) - zpr[0]) * THfunc[0] +
                 (-p[16] + p[17]) * ((p[4] + t_min) - zpr[2]) * THfunc[2] +
                 (-p[18] + p[19]) * ((p[4] + t_min) - zpr[4]) * THfunc[4] +
                 (-p[20] + p[21]) * ((p[4] + t_min) - zpr[6]) * THfunc[6];

  double fdx = TMath::Power((x - funcX) / errx, 2);
  double fdy = TMath::Power((y - funcY) / erry, 2);
  double fdz = 0;
  double fchi2 = fdx + fdy + fdz;
  return fchi2;
}

// function to be minimized with kink angle due to multiple scattering
double KoaLinFitTask::FCN_MS(const double* vars) {
  double* x = fGraph2D->GetX();
  double* y = fGraph2D->GetY();
  double* z = fGraph2D->GetZ();
  double* errx = fGraph2D->GetEX();
  double* erry = fGraph2D->GetEY();
  int npoints = fGraph2D->GetN();
  double sum(0.0);
  double erralA = GetSigmaMS(0);
  double erralB = GetSigmaMS(1);
  double zpr[8];
  int izcur = 0;
  for (int izpl = 0; izpl < 4; izpl++) {
    zpr[izcur] = z[izpl];
    izcur++;
    zpr[izcur] = z[izpl];
    izcur++;
  }
  for (int i = 0; i < npoints; ++i) {
    double chi2 = distance_MS(x[i], y[i], z[i], errx[i], erry[i], vars, zpr);
    sum += chi2;
  }
  double fdal = 0;
  for (int jms = 0; jms < 8; jms = jms + 2) {
    double errTot = sqrt(erralA * erralA + erralB * erralB);
    fdal += TMath::Power(((vars[7 + jms] - vars[6 + jms]) / errTot), 2);
    fdal += TMath::Power(((vars[15 + jms] - vars[14 + jms]) / errTot), 2);
  }
  sum += fdal;
  return sum;
}

double KoaLinFitTask::ScatteredAngle(double radLen) {
  // Calculation of ThetaMS -------------------------------------
  // Charge & mass of particle
  // Int_t PDGCode = -2212; //barp //[R.K. 01/2017] unused variable
  Double_t fMass = 0.938272046;
  Double_t Ebeam = TMath::Hypot(fPbeam, fMass);
  TLorentzVector LorMom(0, 0, fPbeam, Ebeam);
  Double_t beta = LorMom.Beta();
  Double_t X_to_X0 = radLen;
  Double_t thetaMS = 13.6 * 1e-3 * TMath::Sqrt(X_to_X0) *
                     (1 + 0.038 * TMath::Log(X_to_X0)) / (beta * fPbeam);
  return thetaMS;
}

// chi2 with kink angles fit [G.Lutz, NIM A273 (1988)]
double KoaLinFitTask::line3DfitMS(TGraph2DErrors* gr,
                                     const TVector3& posSeed,
                                     const TVector3& dirSeed,
                                     std::vector<double>& fitpar,
                                     TMatrixDSym* covmatrix) {
  const int nparams = fitpar.size();
  ROOT::Math::Functor f(this, &KoaLinFitTask::FCN_MS, nparams);
  fmin->SetFunction(f);

  if (fVerbose > 2)
    cout << "KoaLinFitTask::line3Dfit with SEED is used (multiple "
            "scattering taking into account with kinks)"
         << endl;
  Int_t Npoint = gr->GetN();
  Double_t ErrX1 = gr->GetErrorX(0);
  Double_t ErrY1 = gr->GetErrorY(0);
  Double_t ErrZ1 = gr->GetErrorZ(0);

  Double_t ErrX2 = gr->GetErrorX(2);
  Double_t ErrY2 = gr->GetErrorY(2);

  Double_t errRx = TMath::Hypot(ErrX1, ErrX2);
  Double_t errRy = TMath::Hypot(ErrY1, ErrY2);

  fGraph2D = gr;

  if (fVerbose > 5) {
    cout << "Number of hits = " << Npoint << endl;
    cout << "posSeed:" << endl;
    posSeed.Print();
    TVector3 ErrPosSeed(ErrX1, ErrY1, ErrZ1);
    cout << "ErrposSeed:" << endl;
    ErrPosSeed.Print();
    cout << "dirSeed:" << endl;
    dirSeed.Print();
  }

  fmin->SetVariable(0, "x0", posSeed.X(), ErrX1);
  fmin->SetVariable(1, "Ax", dirSeed.X(), errRx);
  fmin->SetVariable(2, "y0", posSeed.Y(), ErrY1);
  fmin->SetVariable(3, "Ay", dirSeed.Y(), errRy);

  fmin->SetFixedVariable(4, "z0", posSeed.Z());
  fmin->SetFixedVariable(5, "Az", dirSeed.Z());

  double scaling_factor(1e-4);
  fmin->SetVariable(6, "al0x_a", 0.0, scaling_factor * fsigmaMSa);
  fmin->SetVariable(7, "al0x_b", 0.0, scaling_factor * fsigmaMSb);
  fmin->SetFixedVariable(8, "al1x_a", 0.0);
  fmin->SetVariable(9, "al1x_b", 0.0, scaling_factor * fsigmaMSb);
  fmin->SetFixedVariable(10, "al2x_a", 0.0);
  fmin->SetVariable(11, "al2x_b", 0.0, scaling_factor * fsigmaMSb);
  fmin->SetFixedVariable(12, "al3x_a", 0.0);
  fmin->SetFixedVariable(13, "al3x_b", 0.0);

  fmin->SetVariable(14, "al0y_a", 0.0, scaling_factor * fsigmaMSa);
  fmin->SetVariable(15, "al0y_b", 0.0, scaling_factor * fsigmaMSb);
  fmin->SetFixedVariable(16, "al1y_a", 0.0);
  fmin->SetVariable(17, "al1y_b", 0.0, scaling_factor * fsigmaMSb);
  fmin->SetFixedVariable(18, "al2y_a", 0.0);
  fmin->SetVariable(19, "al2y_b", 0.0, scaling_factor * fsigmaMSb);
  fmin->SetFixedVariable(20, "al3y_a", 0.0);
  fmin->SetFixedVariable(21, "al3y_b", 0.0);

  if (Npoint < 4) {
    fmin->FixVariable(11);
    fmin->FixVariable(19);
  }

  fmin->Minimize();

  double recpres = 1e-7;

  if (fmin->Edm() > 1e2 * recpres) {
    return 1e6;
  }

  // get fit parameters
  for (int i = 0; i < nparams; ++i) {
    fitpar[i] = fmin->X()[i];
  }

  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 6; j++) {
      (*covmatrix)(i, j) = fmin->CovMatrix(i, j);
    }
  }

  //!!!!!!!!!!!!!!!!!! z0, dz weren't fitted
  (*covmatrix)(4, 4) = (gr->GetErrorZ(0) * gr->GetErrorZ(0)) / 12.;

  fitpar[5] = sqrt(1 - fitpar[1] * fitpar[1] - fitpar[3] * fitpar[3]);
  double dp5_dp1 = fitpar[1] / fitpar[5];
  double dp5_dp3 = fitpar[3] / fitpar[5];
  double errdz2 = pow(dp5_dp1, 2) * (*covmatrix)(1, 1) +
                  pow(dp5_dp3, 2) * (*covmatrix)(3, 3) +
                  2 * fabs(dp5_dp1 * dp5_dp3 * (*covmatrix)(1, 3));
  (*covmatrix)(5, 5) = errdz2;
  //!!!!!!!!!!!!!!!!!!

  Double_t chi2 = fmin->MinValue() / (2. * Npoint - 4);

  if (fVerbose > 2) {
    cout << " chi2 = " << chi2 << endl;
    cout << "[AFTER FIT] start.point: (" << fitpar[0] << ", " << fitpar[2]
         << ", " << fitpar[4] << ")" << endl;
    cout << "[AFTER FIT] dir: (" << fitpar[1] << ", " << fitpar[3] << ", "
         << fitpar[5] << ")"
         << " sqrt(p1^2+p3^2+p5^2) = "
         << sqrt(fitpar[1] * fitpar[1] + fitpar[3] * fitpar[3] +
                 fitpar[5] * fitpar[5])
         << endl;
  }
  ///-------------------------------------------------------------

  return chi2;
}

void KoaLinFitTask::Finish() {}

ClassImp(KoaLinFitTask);
