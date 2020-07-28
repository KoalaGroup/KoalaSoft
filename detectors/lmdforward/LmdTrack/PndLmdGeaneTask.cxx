// -------------------------------------------------------------------------
// -----                   PndLmdGeaneTask source file                 -----
// -----                 Created 18/07/08  by T.Stockmanns             -----
// -----           modified for Lmd by M. Michel & A.Karavdina         -----
// -------------------------------------------------------------------------
// libc includes
#include <iostream>

// Root includes
#include <TMatrixDSym.h>
#include "TClonesArray.h"
#include "TROOT.h"
#include "TTree.h"
#include "TVector3.h"

// framework includes
#include "FairBaseParSet.h"
#include "FairHit.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairTrackParH.h"
#include "FairTrackParP.h"
#include "PndLmdGeaneTask.h"
#include "KoaMCTrack.h"
#include "PndTrack.h"
#include "TDatabasePDG.h"
#include "TGeant3.h"
// PndSds includes
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsMergedHit.h"
// PndLmd includes
#include <map>
#include <vector>
#include "PndLinTrack.h"

// -----   Default constructor   -------------------------------------------
PndLmdGeaneTask::PndLmdGeaneTask()
    : FairTask("Geane Task for PANDA Lmd"), fEventNr(0), fUseMVDPoint(false) {
  track_branch_name = "LMDPndTrackFilt";
}
// -------------------------------------------------------------------------

PndLmdGeaneTask::PndLmdGeaneTask(Double_t pBeam, TVector3 IP,
                                 bool is_prefiltered)
    : FairTask("Geane Task for PANDA Lmd"), fEventNr(0), fUseMVDPoint(false) {
  fPDGid = -2212;
  fPbeam = pBeam;
  cout << "Beam Momentum for particle with PDGid#" << fPDGid << " this run is "
       << fPbeam << endl;
  vtx = IP;
  cout << "Interaction Point:" << endl;
  vtx.Print();

  if (is_prefiltered)
    track_branch_name = "LMDPndTrackFilt";
  else
    track_branch_name = "LMDPndTrack";
}

// -----   Destructor   ----------------------------------------------------
PndLmdGeaneTask::~PndLmdGeaneTask() {}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdGeaneTask::Init() {
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if (!ioman) {
    std::cout << "-E- PndLmdGeaneTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  //  fTracks = (TClonesArray*) ioman->GetObject("LMDTrack");
  fTracks = (TClonesArray*)ioman->GetObject(track_branch_name.c_str());
  if (!fTracks) {
    std::cout << "-W- PndLmdGeaneTask::Init: "
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

  fPro = new FairGeanePro();
  fGeoH = PndGeoHandling::Instance();
  // FairRun* fRun = FairRun::Instance(); //[R.K. 01/2017] unused variable?
  // FairRuntimeDb* rtdb = fRun->GetRuntimeDb(); //[R.K. 01/2017] unused
  // variable

  pndField = FairRunAna::Instance()->GetField();

  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndLmdGeaneTask::SetParContainers() {}

// -----   Public method Exec   --------------------------------------------
void PndLmdGeaneTask::Exec(Option_t*) {
  fTrackParGeane->Delete();
  fTrackParIni->Delete();
  fTrackParFinal->Delete();
  fDetName->Delete();

  if (fVerbose > 2) {
    cout << " ---- Info: " << fEventNr << endl;
  }
  fEventNr++;
  // Charge & mass of particle
  Int_t PDGCode = -2212;  // antiproton

  // go through all tracks
  int glI = fTracks->GetEntriesFast();
  // cout<<"glI = "<<glI<<endl;
  Int_t counterGeaneTrk = 0;

  for (Int_t i = 0; i < glI; i++) {
    TVector3 StartPos, StartPosErr, StartMom, StartMomErr, StartO, StartU,
        StartV;

    PndTrack* recTrack = (PndTrack*)(fTracks->At(i));
    FairTrackParP fFittedTrkP = recTrack->GetParamFirst();

    TVector3 PosRecLMD(fFittedTrkP.GetX(), fFittedTrkP.GetY(),
                       fFittedTrkP.GetZ());
    if (fFittedTrkP.GetZ() > 1130)
      continue;  // TEST: skip trks from 2nd plane. TODO: check are they fine???
    TVector3 MomRecLMD(fFittedTrkP.GetPx(), fFittedTrkP.GetPy(),
                       fFittedTrkP.GetPz());
    MomRecLMD *=
        fPbeam / MomRecLMD.Mag();  // external assumption about mom magnitude
    fFittedTrkP.SetPx(MomRecLMD.X());
    fFittedTrkP.SetPy(MomRecLMD.Y());
    fFittedTrkP.SetPz(MomRecLMD.Z());
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

    /// Propagate to the PCA (a space point) in 7 steps
    /// ---------------------------------
    // Comment: seems back propagation in one step (for 11 m) is too much
    // try smoothing it by small steps, which follow mag.field
    const int nstep = 7;
    double zbend[nstep] = {661, 660.5, 660., 659,
                           319, 316,   220};  // entarance and exit mag.field
    if (fVerbose > 2) {
      cout << "------------------------------------------" << endl;
      cout << "StartPos:" << endl;
      StartPos.Print();
      cout << "StartPosErr:" << endl;
      StartPosErr.Print();

      cout << "StartMom: " << StartMom.Mag() << endl;
      StartMom.Print();
      cout << "StartMomErr: " << StartMomErr.Mag() << endl;
      StartMomErr.Print();
      cout << "" << endl;
    }
    TClonesArray& clref1 = *fTrackParIni;
    Int_t size1 = clref1.GetEntriesFast();

    FairTrackParP* fStartPst = new FairTrackParP(fFittedTrkP);  // REC
    for (int js = 1; js < nstep; js++) {
      bool isProp;

      FairTrackParP* fResPst =
          PropToPlane(fStartPst, zbend[js], -1, isProp);  // back propagation

      if (isProp) {
        delete fStartPst;
        fStartPst = fResPst;
      } else
        break;
    }

    // ///and now Propagate to the PCA (a space point) in one step
    // ---------------------------------
    int ierr = 0;
    FairTrackParH* fStart = new (clref1[size1]) FairTrackParH(fStartPst, ierr);
    TClonesArray& clref = *fTrackParGeane;
    Int_t size = clref.GetEntriesFast();
    /////back propagation  to PCA -----
    FairTrackParH* fRes = new (clref[size]) FairTrackParH();
    fPro->SetPoint(vtx);
    fPro->PropagateToPCA(1, -1);  // back-propagate to point
    Bool_t isProp = fPro->Propagate(fStart, fRes, PDGCode);
    /////END back propagation  to PCA -----

    // // // /////back propagation  to line/plane TEST----
    // Bool_t isProp;
    // FairTrackParP* fResPst  = PropToXZPlane(fStartPst,0,-1,isProp);//back
    // propagation  to plane TEST
    // FairTrackParH *fRes = new(clref[size]) FairTrackParH(fResPst,ierr);

    //      // FairTrackParH* fRes  =  PropToLine(fStart,0,-1,isProp);//back
    //      propagation  to line TEST

    // // // // /////END back propagation  to line/plane TEST
    // ///----------------------------------------------------------------------
    delete fStartPst;

    ///----------------------------------------------------------------------

    //------- TEST of calculation errors -------
    TVector3 gPos(fRes->GetX(), fRes->GetY(), fRes->GetZ());
    TVector3 gMom(fRes->GetPx(), fRes->GetPy(), fRes->GetPz());

    TVector3 gErrPos(fRes->GetDX(), fRes->GetDY(), fRes->GetDZ());
    TVector3 gErrMom(fRes->GetDPx(), fRes->GetDPy(), fRes->GetDPz());
    // cout<<" "<<endl;
    if (fVerbose > 2) {
      //      cout<<"================= %%%% ===================="<<endl;

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

      cout << "================= %%%% ====================" << endl;
    }
    //------------------------------------------

    if (isProp == kTRUE) {
      new ((*fTrackParFinal)[counterGeaneTrk])
          FairTrackParH(*(fRes));  // save Track
      //	new((*fTrackParFinal)[counterGeaneTrk]) FairTrackParP(*(fRes));
      ////save Track
      counterGeaneTrk++;
      if (fVerbose > 2) cout << "***** isProp TRUE *****" << endl;
    } else {
      if (fVerbose > 2) {
        cout << "!!! Back-propagation with GEANE didn't return result !!!"
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
  // fMCTracks->Delete();
  // fMCHits->Delete();
  if (fVerbose > 2) cout << "PndLmdGeaneTask::Exec END!" << endl;
}

void PndLmdGeaneTask::Finish() {
  //  tprop->Write();
}

FairTrackParP* PndLmdGeaneTask::PropToPlane(FairTrackParP* fStartPst,
                                            double zpos, int dir,
                                            bool& isProp) {
  TVector3 stStartPos(fStartPst->GetX(), fStartPst->GetY(), fStartPst->GetZ());
  if (zpos > 1e3) {  // external assumption about mom magnitude [use it while in
                     // BOX and we know mom should be diff]
    TVector3 MomStartPos(fStartPst->GetPx(), fStartPst->GetPy(),
                         fStartPst->GetPz());
    MomStartPos *= fPbeam / MomStartPos.Mag();
    fStartPst->SetPx(MomStartPos.X());
    fStartPst->SetPy(MomStartPos.Y());
    fStartPst->SetPz(MomStartPos.Z());  // correct mom.magnitude
  }
  // propagate plane-to-plane
  TVector3 ist(fStartPst->GetIVer());
  TVector3 jst(fStartPst->GetJVer());
  TVector3 kst(fStartPst->GetKVer());
  TVector3 oc(0, 0, zpos);
  TVector3 dj(1., 0., 0.);
  TVector3 dk(0., 1., 0.);
  dj.SetMag(1);
  dk.SetMag(1);
  fPro->PropagateFromPlane(jst, kst);  // 1st detector plane
  fPro->PropagateToPlane(oc, dj, dk);  // virtual plane at fixed z
  if (dir < 0) fPro->setBackProp();
  FairTrackParP* fResPst = new FairTrackParP();
  isProp = fPro->Propagate(fStartPst, fResPst, fPDGid);
  return fResPst;
}

ClassImp(PndLmdGeaneTask);
