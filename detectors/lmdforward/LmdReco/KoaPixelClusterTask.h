// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#ifndef KOAPIXELCLUSTERTASK_H
#define KOAPIXELCLUSTERTASK_H

#include "PndSdsPixelClusterTask.h"
#include "TString.h"

class FairRun;
class FairRuntimeDb;

class KoaPixelClusterTask : public PndSdsPixelClusterTask {
  FairRun* ana;
  FairRuntimeDb* rtdb;

 public:
  /** Default constructor **/
  KoaPixelClusterTask();

  /** Destructor **/
  virtual ~KoaPixelClusterTask();

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
  ClassDef(KoaPixelClusterTask, 3);
};

#endif /* LMDCLUSTERTASK_H */
