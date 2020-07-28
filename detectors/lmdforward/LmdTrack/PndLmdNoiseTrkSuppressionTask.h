// -------------------------------------------------------------------------
// -----      PndLmdNoiseTrkSuppressionTask header file            -----
// -----                  Created 21/07/15  by A.Karavdina            -----
// -------------------------------------------------------------------------
/** PndLmdNoiseTrkSuppressionTask.h
 *@author A.Karavdina <karavdin@kph.uni-mainz.de>
 **
 ** Clean sample with reconstructed tracks before back propagation
 ** from background due to noise hits
 ** by multivariable cut
 **/
#ifndef PndLmdNoiseTrkSuppressionTask_H
#define PndLmdNoiseTrkSuppressionTask_H

// framework includes
#include "FairTask.h"
// TMVA includes
#include "TMVA/MethodCuts.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

class PndLmdNoiseTrkSuppressionTask : public FairTask {
 public:
  /** Default constructor **/
  PndLmdNoiseTrkSuppressionTask();

  /// Set up beam momuntum value
  PndLmdNoiseTrkSuppressionTask(Double_t pBeam, TString dir);

  /** Destructor **/
  ~PndLmdNoiseTrkSuppressionTask();

  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();
  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  //  virtual void Finish();

 private:
  TClonesArray* fTrkInArray;
  TClonesArray* fTrkOutArray;

  // PndGeoHandling* fGeoH;
  int fEventNr;
  Double_t fPbeam;

  // MVA Data -------
  TString fdir;
  TString fmethodName;
  Float_t axrec, ayrec;
  Float_t athrec, aphrec;
  TMVA::Reader* reader;

  ClassDef(PndLmdNoiseTrkSuppressionTask, 1);
};

#endif
