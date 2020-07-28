#ifndef PNDLMDIDEALCLUSTERTASK_H
#define PNDLMDIDEALCLUSTERTASK_H

#include "PndSdsIdealClusterTask.h"

class PndLmdIdealClusterTask : public PndSdsIdealClusterTask {
 public:
  /** Default constructor \n
   **/
  PndLmdIdealClusterTask();
  PndLmdIdealClusterTask(Double_t radius, Int_t FEcolumns, Int_t FErows,
                         TString geoFile);

  /** Destructor **/
  virtual ~PndLmdIdealClusterTask();

  virtual void SetBranchNames(TString inBranchname, TString outHitBranchname,
                              TString outClustBranchname, TString folderName);
  virtual void SetBranchNames();

  ClassDef(PndLmdIdealClusterTask, 2);
};

#endif
