// -------------------------------------------------------------------------
// -----       PndLmdBPRungeKuttaTask cource file        -----
// -----                  Created 08/04/13  by A.Karavdina    -----
// -------------------------------------------------------------------------

// libc includes
#include <iostream>

// Root includes
#include <TMatrixDSym.h>
#include "TClonesArray.h"
#include "TROOT.h"
#include "TVector3.h"

// framework includes
#include "FairBaseParSet.h"
#include "FairHit.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "PndLmdBPRungeKuttaTask.h"
#include "PndMCTrack.h"
//#include "TGeant3.h"
#include "FairTrackParH.h"
#include "FairTrackParP.h"
#include "TDatabasePDG.h"

#include "GFFieldManager.h"
//#include "GFPandaField.h"
#include "PndGenfitField.h"
#include "RKTrackRep.h"

// PndSds includes
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
// PndLmd includes
#include <map>
#include <vector>
#include "PndLinTrack.h"
#include "PndTrack.h"

// -----   Default constructor   -------------------------------------------
PndLmdBPRungeKuttaTask::PndLmdBPRungeKuttaTask()
    : FairTask("Back Propagation Task for PANDA Lmd (with RK)"),
      fEventNr(0),
      fUseMVDPoint(false) {}
// -------------------------------------------------------------------------

PndLmdBPRungeKuttaTask::PndLmdBPRungeKuttaTask(Double_t pBeam, TVector3 IP)
    : FairTask("Geane Task for PANDA Lmd"), fEventNr(0), fUseMVDPoint(false) {
  fPbeam = pBeam;
  // if(fPDGid!=-2212){ //calculate momentum if particle is not antiproton
  //     }
  cout << "Beam Momentum for particle with PDGid#" << fPDGid << " this run is "
       << fPbeam << endl;
  vtx = IP;
  cout << "Interaction Point:" << endl;
  vtx.Print();

  // hxpull = new TH1D("hxpull","x/#sigma_{x}",1e2,-10,10.);
  // hypull = new TH1D("hypull","y/#sigma_{y}",1e2,-10,10.);
  // hzpull = new TH1D("hzpull","z/#sigma_{z}",1e2,-10,10.);
  // // hxresstep = new TH2D("hxresstep","x_{PCA} vs. z cood of back-propag
  // start",1e2,0,1200,1e3,-0.5,0.5); //15 GeV
  // hxresstep = new TH2D("hxresstep","x_{PCA} vs. z cood of back-propag
  // start",5e2,0,1500,1e3,-5,5);//1.5 GeV
}

// -----   Destructor   ----------------------------------------------------
PndLmdBPRungeKuttaTask::~PndLmdBPRungeKuttaTask() {}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdBPRungeKuttaTask::Init() {
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if (!ioman) {
    std::cout << "-E- PndLmdBPRungeKuttaTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  fMCHits = (TClonesArray*)ioman->GetObject("LMDPoint");
  if (!fMCHits) {
    std::cout << "-W- PndLmdBPRungeKuttaTask::Init: "
              << "No LMDPoint"
              << " array!" << std::endl;
    return kERROR;
  }

  //  fTracks = (TClonesArray*) ioman->GetObject("LMDTrack");
  fTracks = (TClonesArray*)ioman->GetObject("LMDPndTrackFilt");
  if (!fTracks) {
    std::cout << "-W- PndLmdBPRungeKuttaTask::Init: "
              << "No Track"
              << " array!" << std::endl;
    return kERROR;
  }

  fTrackParGeane = new TClonesArray("FairTrackParH");
  ioman->Register("GeaneTrackPar", "Geane", fTrackParGeane, kTRUE);

  fTrackParIni = new TClonesArray("FairTrackParH");
  ioman->Register("GeaneTrackIni", "Geane", fTrackParIni, kTRUE);

  fTrackParFinal = new TClonesArray("FairTrackParH");
  ioman->Register("GeaneTrackFinal", "Geane", fTrackParFinal, kTRUE);

  fDetName = new TClonesArray("TObjString");
  ioman->Register("DetName", "Geane", fDetName, kTRUE);

  fGeoH = PndGeoHandling::Instance();
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

  // // ///For Runge-Kutta usage ---------------------
  //  GFFieldManager::getInstance()->init(new GFPandaField());
  GFFieldManager::getInstance()->init(new PndGenfitField());
  // // ///-----------------------------------------------------

  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndLmdBPRungeKuttaTask::SetParContainers() {}

// -----   Public method Exec   --------------------------------------------
void PndLmdBPRungeKuttaTask::Exec(Option_t*) {
  std::map<int, std::vector<int> > mcHitMap;  // Track ->  MCHits
  fTrackParGeane->Delete();
  fTrackParIni->Delete();
  fTrackParFinal->Delete();
  fDetName->Delete();

  mcHitMap = AssignHitsToTracks();
  fEventNr++;

  // Charge & mass of particle
  Int_t PDGCode = -2212;  // antiproton
  //  Int_t PDGCode = fPDGid;
  TDatabasePDG* fdbPDG = TDatabasePDG::Instance();
  TParticlePDG* fParticle = fdbPDG->GetParticle(PDGCode);
  Double_t fCharge = fParticle->Charge() / 3.;
  //  cout<<"fCharge = "<<fCharge<<endl;

  // go through all tracks
  int glI = fTracks->GetEntriesFast();
  Int_t counterGeaneTrk = 0;
  for (Int_t i = 0; i < glI; i++) {
    TVector3 StartPos, StartPosErr, StartMom, StartMomErr, StartO, StartU,
        StartV;
    int p = 0;

    /// Get parameters of real track
    //   PndLinTrack* recTrack = (PndLinTrack*)(fTracks->At(i));
    // TString 	DecName = recTrack->GetDetName();
    // if(DecName!="Lumi") continue;

    // //Vector of particle momentum and starting point
    // TVector3 DirVec =  recTrack->GetDirectionVec();
    // StartPos = recTrack->GetStartVec();
    // StartPosErr = recTrack->GetStartErrVec();
    // double zerradd = hypot(StartPosErr.Z(),5e-04);
    // StartPosErr.SetZ(zerradd);//value for err_z is unknown from fit TODO: why
    // ???
    // StartMomErr = recTrack->GetDirectionErrVec();
    // StartMom = fPbeam*DirVec;
    // StartMomErr *=fPbeam;

    PndTrack* recTrack = (PndTrack*)(fTracks->At(i));
    FairTrackParP fFittedTrkP = recTrack->GetParamFirst();
    TVector3 PosRecLMD(fFittedTrkP.GetX(), fFittedTrkP.GetY(),
                       fFittedTrkP.GetZ());
    TVector3 MomRecLMD(fFittedTrkP.GetPx(), fFittedTrkP.GetPy(),
                       fFittedTrkP.GetPz());
    MomRecLMD *= fPbeam / MomRecLMD.Mag();
    double covMARS[6][6];
    fFittedTrkP.GetMARSCov(covMARS);
    TVector3 errMomRecLMD(sqrt(covMARS[0][0]), sqrt(covMARS[1][1]),
                          sqrt(covMARS[2][2]));
    TVector3 errPosRecLMD(sqrt(covMARS[3][3]), sqrt(covMARS[4][4]),
                          sqrt(covMARS[5][5]));

    StartPos = PosRecLMD;
    StartPosErr = errPosRecLMD;
    StartMom = MomRecLMD;
    StartMomErr = errMomRecLMD;

    if (fVerbose > 2) {
      cout << "------------------------------------------" << endl;
      cout << "StartPos:" << endl;
      StartPos.Print();
      cout << "StartPosErr:" << endl;
      StartPosErr.Print();
      cout << "" << endl;
      cout << "StartMom: " << StartMom.Mag() << endl;
      StartMom.Print();
      cout << "StartMomErr: " << StartMomErr.Mag() << endl;
      StartMomErr.Print();
    }
    TClonesArray& clref1 = *fTrackParIni;
    Int_t size1 = clref1.GetEntriesFast();

    // Runge-Kutta --------------------------------------

    //   TMatrixT<double> aCov;
    //   aCov.ResizeTo(7,7);
    // aCov[0][0] = covMARS[0][0];
    // aCov[1][1] = covMARS[2][2];
    // aCov[2][2] = covMARS[4][4];
    // aCov[3][3] = covMARS[1][1];
    // aCov[4][4] = covMARS[3][3];
    // aCov[5][5] = covMARS[5][5];
    // aCov[6][6] = 0.;

    // aCov[0][1] = covMARS[0][2];
    // aCov[1][0] = covMARS[0][2];
    // aCov[0][2] = covMARS[0][4];
    // aCov[2][0] = covMARS[0][4];
    // aCov[0][3] = covMARS[0][1];
    // aCov[3][0] = covMARS[0][1];
    // aCov[0][4] = covMARS[0][3];
    // aCov[4][0] = covMARS[0][3];
    // aCov[0][5] = covMARS[0][5];
    // aCov[5][0] = covMARS[0][5];
    // aCov[0][6] = 0.;
    // aCov[6][0] = 0.;

    // aCov[1][2] = covMARS[2][4];
    // aCov[2][1] = covMARS[2][4];
    // aCov[1][3] = covMARS[2][1];
    // aCov[3][1] = covMARS[2][1];
    // aCov[1][4] = covMARS[2][3];
    // aCov[4][1] = covMARS[2][3];
    // aCov[1][5] = covMARS[2][5];
    // aCov[5][1] = covMARS[2][5];
    // aCov[1][6] = 0.;
    // aCov[6][1] = 0.;

    // aCov[2][3] = covMARS[4][1];
    // aCov[3][2] = covMARS[4][1];
    // aCov[2][4] = covMARS[4][3];
    // aCov[4][2] = covMARS[4][3];
    // aCov[2][5] = covMARS[4][5];
    // aCov[5][2] = covMARS[4][5];
    // aCov[2][6] = 0.;
    // aCov[6][2] = 0.;

    // aCov[3][4] = covMARS[1][3];
    // aCov[4][3] = covMARS[1][3];
    // aCov[3][5] = covMARS[1][5];
    // aCov[5][3] = covMARS[1][5];
    // aCov[3][6] = 0.;
    // aCov[6][3] = 0.;

    // aCov[4][5] = covMARS[3][5];
    // aCov[5][4] = covMARS[3][5];
    // aCov[4][6] = 0.;
    // aCov[6][4] = 0.;

    // aCov[5][6] = 0.;
    // aCov[6][5] = 0.;

    // repfi->setCov(aCov); //TODO: aCov has to be converted in correct
    // variable. see RKTrackRep constructor for calculation diagonal elements

    // Propagate from 12m to 2m with small steps (if onve can call 6m as as
    // small step =\)
    const int nstep = 7;
    //      double zstep = 1124/nstep;
    TVector3 g3Pos = StartPos;
    TVector3 g3Mom = StartMom;
    TVector3 g3ErrPos = StartPosErr;
    TVector3 g3ErrMom = StartMomErr;
    TVector3 gErrPos, gErrMom;
    //   for(int js=1;js<nstep;js++){
    // Comment: seems back propagation in one step (for 11 m) is too much, while
    // it's divided only on steps 1m size within Runge-Kutta
    // try do smooth it by small step
    double zbend[nstep] = {661, 660.5, 660., 659,
                           319, 316,   220};  // entarance and exit mag.field
    for (int js = 0; js < nstep; js++) {
      if (fVerbose > 2) {
        cout << "current : step#" << js << endl;
        cout << "We start from:" << endl;
        g3Pos.Print();
        g3ErrPos.Print();
      }
      RKTrackRep* repfi3 =
          new RKTrackRep(g3Pos, g3Mom, g3ErrPos, g3ErrMom, PDGCode);
      double znew = zbend[js];
      TVector3 vtx2(0, 0, znew);
      TVector3 u(1, 0, 0);
      TVector3 v(0, 1, 0);
      GFDetPlane pl(vtx2, u, v);

      TMatrixT<double> cov2;
      TVector3 g2Pos, g2Mom;
      TVector3 g2ErrPos, g2ErrMom;
      repfi3->getPosMomCov(pl, g2Pos, g2Mom, cov2);

      // TODO: use full covariance matrix and not only diagonal elements
      if (cov2[0][0] != 0) {
        g2ErrPos.SetXYZ(sqrt(cov2[0][0]), sqrt(cov2[1][1]), sqrt(cov2[2][2]));
        g2ErrMom.SetXYZ(sqrt(cov2[3][3]), sqrt(cov2[4][4]), sqrt(cov2[5][5]));
        if (cov2[2][2] == 0) g2ErrPos.SetZ(StartPosErr.Z());
        gErrMom *= fPbeam;
      } else {
        g2ErrPos = StartPosErr;
        g2ErrMom = StartMomErr;
      }
      // if(fVerbose>2){
      //   cout<<"current Mom: "<<endl;
      //   g2Mom.Print();
      // }
      // RKTrackRep *repfi2 = new
      // RKTrackRep(g2Pos,g2Mom,g2ErrPos,g2ErrMom,PDGCode);
      // repfi2->extrapolateToPoint(vtx,gPos,gMom,gCov);
      // if(fVerbose>2){
      // cout<<"if try we go to IP now, gPos:"<<endl;
      // gPos.Print();
      // }

      // if(gCov[0][0]!=0){
      //   gErrPos.SetXYZ(sqrt(gCov[0][0]),sqrt(gCov[1][1]),sqrt(gCov[2][2]));
      //   gErrMom.SetXYZ(sqrt(gCov[3][3]),sqrt(gCov[4][4]),sqrt(gCov[5][5]));
      //   gErrMom *=fPbeam;
      // }
      // else{
      //   gErrPos = g2ErrPos;
      //   gErrMom = g2ErrMom;
      // }
      // if(fVerbose>2){
      //   gErrPos.Print();
      // }
      g3Pos = g2Pos;
      g3Mom = g2Mom;
      g3ErrPos = g2ErrPos;
      g3ErrMom = g2ErrMom;
      //	gMom*=fPbeam;
      //      	hxresstep->Fill(znew,gPos.X());
      //	delete repfi2;
      delete repfi3;
    }

    // And now propagate 2m
    RKTrackRep* repfi =
        new RKTrackRep(g3Pos, g3Mom, g3ErrPos, g3ErrMom, PDGCode);
    TVector3 gPos, gMom;
    TMatrixT<double> gCov(7, 7);
    repfi->extrapolateToPoint(vtx, gPos, gMom);
    // RKTrackRep doesn't contain extrapolateToPoint method with cov.mtx
    // calculation
    // the trick is to construct a GFDetPlane(poca, dirInPoca)
    // and the extrapolate again to that DetPlane
    // with the extrapolate function that gives you state and covariance
    // prediction.  [Johannes Rauch]
    TVector3 gDir = gMom;
    gDir *= (1. / gMom.Mag());
    GFDetPlane plv(gPos, gDir);
    repfi->getPosMomCov(plv, gPos, gMom, gCov);
    gErrPos.SetXYZ(sqrt(gCov[0][0]), sqrt(gCov[1][1]), sqrt(gCov[2][2]));
    gErrMom.SetXYZ(sqrt(gCov[3][3]), sqrt(gCov[4][4]), sqrt(gCov[5][5]));
    // gErrMom *=fPbeam;
    Bool_t isProp = true;
    FairTrackParH* fRes = new (clref1[size1])
        FairTrackParH(gPos, gMom, gErrPos, gErrMom, fCharge);
    //   fRes->CalCov();
    delete repfi;
    // Runge-Kutta(END) --------------------------------

    if (fVerbose > 2) {
      cout << "gPos:" << endl;
      gPos.Print();
      // cout<<"difference between final and initial point =
      // "<<(-StartPos.Mag()+gPos.Mag())<<endl;
      cout << "gErrPos:" << endl;
      gErrPos.Print();
      //  cout<<"difference between final and initial point error =
      //  "<<(-StartPosErr.Mag()+gErrPos.Mag())<<endl;
      cout << "gMom: " << gMom.Mag() << endl;
      gMom.Print();
      // cout<<"difference between initial and final momentum =
      // "<<(StartMom.Mag()-gMom.Mag())<<endl;
      cout << "gErrMom: " << gErrMom.Mag() << endl;
      // cout<<"difference between initial and final momentum error=
      // "<<(StartMomErr.Mag()-gErrMom.Mag())<<endl;
      gErrMom.Print();
      // if(gErrPos.X()!=0) hxpull->Fill(gPos.X()/gErrPos.X());
      // if(gErrPos.Y()!=0) hypull->Fill(gPos.Y()/gErrPos.Y());
      // if(gErrPos.Z()!=0) hzpull->Fill(gPos.Z()/gErrPos.Z());
    }
    //------------------------------------------

    if (isProp == kTRUE) {
      new ((*fTrackParFinal)[counterGeaneTrk])
          FairTrackParH(*(fRes));  // save Track
      //	new((*fTrackParFinal)[counterGeaneTrk]) FairTrackParP(*(fRes));
      ////save Track
      counterGeaneTrk++;
      //	cout<<"***** isProp TRUE *****"<<endl;
    } else {
      if (fVerbose > 2) {
        cout << "!!! Back-propagation with Runge-Kutta didn't return result !!!"
             << endl;
        cout << "StartPos:" << endl;
        StartPos.Print();
        cout << "StartPosErr:" << endl;
        StartPosErr.Print();

        cout << "StartMom: " << StartMom.Mag() << endl;
        StartMom.Print();
        cout << "StartMomErr: " << StartMomErr.Mag() << endl;
        StartMomErr.Print();
      }
      new ((*fTrackParFinal)[counterGeaneTrk]) FairTrackParH();  // save NULL
      //	new((*fTrackParFinal)[counterGeaneTrk]) FairTrackParP(); //save
      //NULL
      counterGeaneTrk++;
    }
  }
  if (fVerbose > 2) cout << "PndLmdBPRungeKuttaTask::Exec END!" << endl;
}

void PndLmdBPRungeKuttaTask::Finish() {}

std::map<int, std::vector<int> > PndLmdBPRungeKuttaTask::AssignHitsToTracks() {
  std::map<int, std::vector<int> > result;
  for (int i = 0; i < fMCHits->GetEntriesFast(); i++) {  // get all MC Hits
    PndSdsMCPoint* myPoint =
        (PndSdsMCPoint*)(fMCHits->At(i));  // sort MCHits with Tracks
    result[myPoint->GetTrackID()].push_back(i);
  }
  return result;
}

ClassImp(PndLmdBPRungeKuttaTask);
