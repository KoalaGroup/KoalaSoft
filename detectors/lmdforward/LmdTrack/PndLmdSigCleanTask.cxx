// -------------------------------------------------------------------------
// -----                   PndLmdSigCleanTask source file            -----
// -----                  Created 26/02/14  by A.Karavdina            -----
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
#include "PndLmdSigCleanTask.h"
#include "KoaMCTrack.h"
#include "PndTrack.h"
#include "TGeant3.h"
// PndSds includes
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "PndSdsMergedHit.h"
// PndLmd includes
#include <map>
#include <vector>

// -----   Default constructor   -------------------------------------------
PndLmdSigCleanTask::PndLmdSigCleanTask()
    : FairTask("Cleaning Tracks Task for PANDA Lmd"),
      fEventNr(0),
      fdX(0),
      fdY(0) {
  // tprop = new TNtuple();
}
// -------------------------------------------------------------------------

PndLmdSigCleanTask::PndLmdSigCleanTask(Double_t pBeam, TString dir)
    : FairTask("Cleaning Tracks  Task for PANDA Lmd"),
      fEventNr(0),
      fdX(0),
      fdY(0) {
  fdir = dir;
  fPbeam = pBeam;
  cout << "Beam Momentum in this run is " << fPbeam << endl;
  hResponse = new TH1D("hResponse", "", 1e3, -1, 1);
  fXYcut = false;
}

// -----   Destructor   ----------------------------------------------------
PndLmdSigCleanTask::~PndLmdSigCleanTask() {}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdSigCleanTask::Init() {
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if (!ioman) {
    std::cout << "-E- PndLmdSigCleanTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  fTrkArray = (TClonesArray*)ioman->GetObject("LMDPndTrackFilt");
  if (!fTrkArray) {
    std::cout << "-W- PndLmdTrkQTask::Init: "
              << "No Track"
              << " array!" << std::endl;
    return kERROR;
  }

  // Get rec.tracks after back propagation
  fRecBPTracks = (TClonesArray*)ioman->GetObject("GeaneTrackFinal");
  if (!fRecBPTracks) {
    std::cout << "-W- PndLmdSigCleanTask::Init: "
              << "No Track after back-propagation"
              << " array!" << std::endl;
    return kERROR;
  }

  fTrackParFinal = new TClonesArray("FairTrackParH");
  ioman->Register("LMDCleanTrack", "PndLmd", fTrackParFinal, kTRUE);

  fGeoH = PndGeoHandling::Instance();
  // FairRun* fRun = FairRun::Instance(); //[R.K. 01/2017] unused variable?
  // FairRuntimeDb* rtdb = fRun->GetRuntimeDb(); //[R.K. 01/2017] unused
  // variable

  // TMVA -----------------------------------------------------
  // This loads the library
  if (fabs(fPbeam - 1.5) < 1e-1) {
    TMVA::Tools::Instance();

    //   TMVA::Reader *
    reader = new TMVA::Reader("!Color:!Silent");

    // Create a set of variables and declare them to the reader
    // - the variable names MUST corresponds in name and type to those given in
    // the weight file(s) used

    reader->AddVariable("axrec", &axrec);
    reader->AddVariable("ayrec", &ayrec);
    reader->AddVariable("azrec", &azrec);
    reader->AddVariable("aprec", &aprec);
    reader->AddVariable("athrec", &athrec);
    reader->AddVariable("aphrec", &aphrec);

    //  TString dir    = "weights/";
    TString prefix = "TMVAClassification";
    fmethodName = "BDT method";
    TString weightfile =
        fdir + prefix + TString("_BDT") + TString(".weights.xml");
    reader->BookMVA(fmethodName, weightfile);
  }
  //------------------------------------------------------
  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndLmdSigCleanTask::SetParContainers() {
  // Get Base Container
  /// FairRun* ana = FairRun::Instance();
  // FairRuntimeDb* rtdb=ana->GetRuntimeDb();
}

// -----   Public method Exec   --------------------------------------------
void PndLmdSigCleanTask::Exec(Option_t*) {
  std::map<int, std::vector<int> > mcHitMap;  // Track ->  MCHits
  fTrackParFinal->Delete();

  if (fVerbose > 2) {
    cout << " ---- Info: " << fEventNr << endl;
  }
  fEventNr++;

  // go through all tracks
  const int nGeaneTrks = fRecBPTracks->GetEntriesFast();
  Int_t counterSigTrk = 0;
  for (Int_t iN = 0; iN < nGeaneTrks;
       iN++) {  // loop over all reconstructed trks
    FairTrackParH* fRes = (FairTrackParH*)fRecBPTracks->At(iN);
    // 1. Trk params before BP
    bool isCleanCand;
    if (fXYcut == kTRUE) {
      PndTrack* trkpnd = (PndTrack*)(fTrkArray->At(iN));
      FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();
      isCleanCand = CheckXY(&fFittedTrkP);
    } else {
      isCleanCand = kTRUE;
    }
    // 2. Trk params after BP
    bool isClean = Check(fRes);
    if (isClean == kTRUE && isCleanCand == kTRUE) {
      new ((*fTrackParFinal)[counterSigTrk])
          FairTrackParH(*(fRes));  // save Track
      counterSigTrk++;
      if (fVerbose > 2) cout << "***** isClean TRUE *****" << endl;
    } else {
      new ((*fTrackParFinal)[counterSigTrk]) FairTrackParH();  // save NULL
      counterSigTrk++;
      if (fVerbose > 2) cout << "***** isClean FALSE *****" << endl;
    }
  }  // [END] loop over all reconstructed trks
  if (fVerbose > 2) cout << "PndLmdSigCleanTask::Exec END!" << endl;
}

void PndLmdSigCleanTask::Finish() {}

bool PndLmdSigCleanTask::Check(
    FairTrackParH* fTrk) {  // answer TRUE means "it's a signal"
  bool res;
  if (fabs(fPbeam - 1.5) < 1e-1)
    res = CheckMVA(fTrk);  // MVA was trained only on sample with 1.5 GeV/c
                           // simulation ///TODO: extension to other energies?
  else {
    TVector3 MomRecBP = fTrk->GetMomentum();
    double prec = MomRecBP.Mag();
    res = CheckMom(prec);
  }
  return res;
}

bool PndLmdSigCleanTask::CheckMom(double prec) {
  bool res;
  if (abs(prec - fPbeam) > 3e-4)
    res = false;
  else
    res = true;
  return res;
}

bool PndLmdSigCleanTask::CheckMVA(FairTrackParH* fTrk) {
  // cout<<"Yes, TMVA game!"<<endl;
  bool res;
  TVector3 PosRecBP = fTrk->GetPosition();
  axrec = float(PosRecBP.X() - fdX);
  ayrec = float(PosRecBP.Y() - fdY);
  azrec = float(PosRecBP.Z());
  TVector3 MomRecBP = fTrk->GetMomentum();
  aprec = float(MomRecBP.Mag());
  Double_t lyambda = fTrk->GetLambda();
  athrec = float(TMath::Pi() / 2. - lyambda);
  aphrec = float(fTrk->GetPhi());
  double mva_response = reader->EvaluateMVA(fmethodName);
  hResponse->Fill(mva_response);
  // if(mva_response>-0.0599) res=true; //BDT

  // if(mva_response<-0.0411){//new training for non-point-like beam
  // [28/04/2014]
  // if(mva_response<0.0947){//new training for non-point-like beam [28/04/2014]
  if (mva_response <
      -0.5) {  // new training for non-point-like beam [28/09/2014]
    //   if(mva_response<0){
    // if(mva_response<-0.1452){
    // if(mva_response<-0.156){
    //  if(mva_response<-0.01){
    res = false;  // BDT //TEST
    //    cout<<"BDT="<<mva_response<<" for PCA:("<<axrec<<", "<<ayrec<<",
    //    "<<azrec<<") athrec = "<<1e3*athrec<<" aprec = "<<aprec<<endl;
  } else
    res = true;
  return res;
}

bool PndLmdSigCleanTask::CheckXY(FairTrackParP* fFittedTrkP) {
  TVector3 MomRecLMD(fFittedTrkP->GetPx(), fFittedTrkP->GetPy(),
                     fFittedTrkP->GetPz());
  MomRecLMD *= 1. / MomRecLMD.Mag();
  bool dirOKx = true;
  bool dirOKy = true;
  if (fVerbose > 0) cout << "!XThFilt!" << endl;
  double Xref = -19.1 + 1.12 * 1e3 * MomRecLMD.Theta() + fdX;
  double diffX = abs(fFittedTrkP->GetX() - Xref);
  if (fVerbose > 0)
    cout << "fFittedTrkP.GetX() = " << fFittedTrkP->GetX() << " Xref = " << Xref
         << " diffX = " << diffX << endl;
  if (diffX > 3.0) dirOKx = false;
  if (fVerbose > 0) cout << "!YPhFilt!" << endl;
  double Yref = -0.00651 + 0.045 * 1e3 * MomRecLMD.Phi() + fdY;
  double diffY = abs(fFittedTrkP->GetY() - Yref);
  if (fVerbose > 0)
    cout << "fFittedTrkP.GetY() = " << fFittedTrkP->GetY() << " Yref = " << Yref
         << " diffY = " << diffY << endl;
  if (diffY > 4.0) dirOKy = false;

  bool res = false;
  if (dirOKx && dirOKy) res = true;
  return res;
}

ClassImp(PndLmdSigCleanTask);
