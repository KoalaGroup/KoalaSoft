// -------------------------------------------------------------------------
// -----            PndLmdTrackFinderCATask                    -----
// -----       Created 18/05/11  by A. Karavdina              -----
// -------------------------------------------------------------------------

#ifndef PNDLMDTRACKFINDERCATASK_H
#define PNDLMDTRACKFINDERCATASK_H
#include "FairTask.h"
#include "KoaMCTrack.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsGeoPar.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "TrackData/PndTrackCand.h"

#include <string>
#include <vector>
#include "PndSdsCell.h"
#include "TH2.h"
#include "TNtuple.h"

class TClonesArray;

class PndLmdTrackFinderCATask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdTrackFinderCATask();
  /** Constructor **/
  PndLmdTrackFinderCATask(const bool missPl, const double setdmax,
                          Int_t innSensPP = 8, Int_t innP = 4,
                          TString hitBranch = "LMDHitsPixel");
  /** Destructor **/
  virtual ~PndLmdTrackFinderCATask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  virtual InitStatus ReInit();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  void SetVerbose(Int_t verbose) { fVerbose = verbose; };
  void SetInaccuracy(Double_t accu) { dXY = accu; };
  void SetSensStripFlag(bool fS) { flagStipSens = fS; };
  void SetSensPixelFlag(bool fS) { flagPixelSens = fS; };
  void SetTrkCandCutsFlag(bool fS) { flagTrkCandCuts = fS; };
  void FinishTask();

 private:
  Double_t dXY;
  double rule_max;
  int nSensPP;  // number of sensors on one plane
  int nP;       // number of planes
  bool SortHitsByDet(std::vector<std::vector<std::pair<Int_t, bool> > >& hitsd,
                     Int_t nPixelHits);
  bool SortHitsByDetSimple(std::vector<std::vector<Int_t> >& hitsd,
                           Int_t nPixelHits);
  bool SortHitsByDetSimple2(std::vector<std::vector<Int_t> >& hitsd,
                            Int_t nPixelHits);  // Uses PmdLmdDim class
  bool SortHitsByZ(std::vector<std::vector<std::pair<Int_t, bool> > >& hitsd,
                   Int_t nPixelHits);
  Double_t GetTrackDip(KoaMCTrack* myTrack);
  Double_t GetTrackCurvature(KoaMCTrack* myTrack);
  bool Neighbor(int& icell0, int& icell1);
  bool Neighbor(PndSdsCell* cell0, PndSdsCell* cell1);
  void Evolution(int& pv0, int& pv1, int& pv0_n, int& pv1_n, bool isch);
  TClonesArray* ForwardEvolution(TClonesArray* fCellArray, int niter = 100);
  TClonesArray* CookAllCells(std::vector<std::vector<Int_t> > hitsd);
  TClonesArray* CookCells(std::vector<std::vector<Int_t> > hitsd, int& pl0,
                          int& pl1, TClonesArray* tCellArray);
  TString fHitBranchPixel;

  bool missPlAlgo;
  bool flagStipSens;
  bool flagPixelSens;
  bool flagTrkCandCuts;
  /** Input array of PndSdsDigis and PndSdsHits**/
  TClonesArray* fPixelHitArray;

  /** Output array of Track-Cand **/
  TClonesArray* fTrackCandArray;
  TClonesArray* fCellArray;

  void Register();
  void Reset();
  void ProduceHits();

  ClassDef(PndLmdTrackFinderCATask, 4);
};

#endif /* PndLmdTrackFinderCATASK_H */
