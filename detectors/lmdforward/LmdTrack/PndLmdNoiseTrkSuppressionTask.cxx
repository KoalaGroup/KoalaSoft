// -------------------------------------------------------------------------
// -----      PndLmdNoiseTrkSuppressionTask source file    -----
// -----                  Created 21/07/15  by A.Karavdina            -----
// -------------------------------------------------------------------------

// libc includes
#include <iostream>
#include <map>
#include <vector>

// Root includes
#include <TMatrixDSym.h>
#include "TClonesArray.h"
#include "TROOT.h"
#include "TTree.h"
#include "TVector3.h"

// framework includes
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairTrackParH.h"
#include "FairTrackParP.h"
#include "PndLmdNoiseTrkSuppressionTask.h"
#include "PndTrack.h"
// -----   Default constructor   -------------------------------------------
PndLmdNoiseTrkSuppressionTask::PndLmdNoiseTrkSuppressionTask()
    : FairTask("Cleaning Tracks from noise hits Task for PANDA Lmd"),
      fEventNr(0) {
  // tprop = new TNtuple();
  // fEventNr = 0;
}
// -------------------------------------------------------------------------

PndLmdNoiseTrkSuppressionTask::PndLmdNoiseTrkSuppressionTask(Double_t pBeam,
                                                             TString dir)
    : FairTask("Cleaning Tracks from noise hits Task for PANDA Lmd"),
      fEventNr(0) {
  fdir = dir;
  fPbeam = pBeam;
  std::cout << "Beam Momentum in this run is " << fPbeam << std::endl;
}

// -----   Destructor   ----------------------------------------------------
PndLmdNoiseTrkSuppressionTask::~PndLmdNoiseTrkSuppressionTask() {}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdNoiseTrkSuppressionTask::Init() {
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  if (!ioman) {
    std::cout << "-E- PndLmdNoiseTrkSuppressionTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  fTrkInArray = (TClonesArray*)ioman->GetObject("LMDPndTrackFilt");
  if (!fTrkInArray) {
    std::cout << "-W- PndLmdNoiseTrkSuppressionTask::Init: "
              << "No LMDPndTrack"
              << " array!" << std::endl;
    return kERROR;
  }

  fTrkOutArray = new TClonesArray("PndTrack");
  ioman->Register("LMDPndTrackFilt", "PndLmd", fTrkOutArray, kTRUE);

  // fGeoH = PndGeoHandling::Instance();
  // FairRun* fRun = FairRun::Instance(); //[R.K. 01/2017] unused variable?
  // FairRuntimeDb* rtdb = fRun->GetRuntimeDb(); //[R.K. 01/2017] unused
  // variable

  // TMVA -----------------------------------------------------
  // This loads the library
  // if(fabs(fPbeam-1.5)<1e-1 || fabs(fPbeam-15)<1e-1){
  TMVA::Tools::Instance();

  //   TMVA::Reader *
  reader = new TMVA::Reader("!Color:!Silent");

  // Create a set of variables and declare them to the reader
  // - the variable names MUST corresponds in name and type to those given in
  // the weight file(s) used
  reader->AddVariable("LMDTrackQ.fThetarecLMD", &athrec);
  reader->AddVariable("LMDTrackQ.fPhirecLMD", &aphrec);
  reader->AddVariable("LMDTrackQ.fXrecLMD", &axrec);
  reader->AddVariable("LMDTrackQ.fYrecLMD", &ayrec);

  //  TString dir    = "weights/";
  TString prefix = "TMVAClassification";
  fmethodName = "BDT method";
  TString weightfile =
      fdir + prefix + TString("_BDT") + TString(".weights.xml");
  reader->BookMVA(fmethodName, weightfile);
  // }
  //   else{
  // std::cout << "-W- PndLmdNoiseTrkSuppressionTask::Init: "<< "This method was
  // not trained for momentum"<< fPbeam << std::endl;
  // return kERROR;
  // }
  //------------------------------------------------------
  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndLmdNoiseTrkSuppressionTask::SetParContainers() {
  // Get Base Container
  /// FairRun* ana = FairRun::Instance();
  // FairRuntimeDb* rtdb=ana->GetRuntimeDb();
}

// -----   Public method Exec   --------------------------------------------
void PndLmdNoiseTrkSuppressionTask::Exec(Option_t*) {
  fTrkOutArray->Delete();
  if (fVerbose > 2) {
    std::cout << " ---- Info: " << fEventNr << std::endl;
  }

  // go through all tracks
  const int nTrks = fTrkInArray->GetEntries();
  int rec_trk = 0;
  for (Int_t iN = 0; iN < nTrks; iN++) {  // loop over all reconstructed trks
    PndTrack* trkpnd = (PndTrack*)(fTrkInArray->At(iN));
    FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();

    // check the track
    axrec = fFittedTrkP.GetX();
    ayrec = fFittedTrkP.GetY();
    TVector3 MomRecLMD(fFittedTrkP.GetPx(), fFittedTrkP.GetPy(),
                       fFittedTrkP.GetPz());
    MomRecLMD *= 1. / MomRecLMD.Mag();
    athrec = MomRecLMD.Theta();
    aphrec = MomRecLMD.Phi();
    double mva_response = reader->EvaluateMVA(fmethodName);
    if (fVerbose > 2)
      std::cout << "mva_response  = " << mva_response << std::endl;
    bool isSigTrk;
    if (mva_response < 0)
      isSigTrk = false;
    else
      isSigTrk = true;
    if (isSigTrk) {
      // save good trks
      new ((*fTrkOutArray)[rec_trk]) PndTrack(*(trkpnd));  // save Track
      rec_trk++;
    }
  }
  if (fVerbose > 2)
    std::cout << "Ev#" << fEventNr << ": " << rec_trk << " trks saved out of "
              << nTrks << std::endl;
  fEventNr++;
}

ClassImp(PndLmdNoiseTrkSuppressionTask);
