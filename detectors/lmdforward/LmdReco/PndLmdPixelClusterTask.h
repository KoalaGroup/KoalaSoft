// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#ifndef PNDLMDPIXELCLUSTERTASK_H
#define PNDLMDPIXELCLUSTERTASK_H

#include "PndSdsPixelClusterTask.h"
#include "TString.h"

class FairRun;
class FairRuntimeDb;

class PndLmdPixelClusterTask : public PndSdsPixelClusterTask {
  FairRun* ana;
  FairRuntimeDb* rtdb;

 public:
  /** Default constructor **/
  PndLmdPixelClusterTask();

  /** Destructor **/
  virtual ~PndLmdPixelClusterTask();

  virtual void SetParContainers();
  virtual void SetBranchNames();
  virtual void SetClusterFinder();
  virtual void SetBackMapping();
  virtual void SetBranchNames(TString inBranchname, TString outHitBranchname,
                              TString outClustBranchname, TString folderName);
  /** Virtual method Exec **/
  void Exec(Option_t* opt);
  void FinishEvent();

  InitStatus Init();
  ClassDef(PndLmdPixelClusterTask, 3);
};

#endif /* LMDCLUSTERTASK_H */
