// -------------------------------------------------------------------------
// -----                 PndLmdHitMergeTask header file             -----
// -------------------------------------------------------------------------

#ifndef PNDLMDHITMERGETASK_H
#define PNDLMDHITMERGETASK_H

#include "FairTask.h"

#include <string>
#include <vector>

class TH2;
class TH1;
class TClonesArray;

class PndLmdHitMergeTask : public FairTask {
 public:
  /** Default constructor **/

  PndLmdHitMergeTask();
  PndLmdHitMergeTask(const char* name);

  /** Destructor **/
  virtual ~PndLmdHitMergeTask();

  /** Virtual method Init **/
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

 protected:
  TClonesArray* fHitArray;        // Input array of PndSdsHits
  TClonesArray* fMergedHitArray;  // Output array of PndSdsHits

  TString fHitBranchName;

  TH2* hdxdy;
  TH1* hdz;

  ClassDef(PndLmdHitMergeTask, 0);
};

#endif /* PNDLMDHITMERGETASK_H */
