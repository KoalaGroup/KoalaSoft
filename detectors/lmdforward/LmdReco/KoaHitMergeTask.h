// -------------------------------------------------------------------------
// -----                 KoaHitMergeTask header file             -----
// -------------------------------------------------------------------------

#ifndef KOAHITMERGETASK_H
#define KOAHITMERGETASK_H

#include "FairTask.h"

#include <string>
#include <vector>

class TH2;
class TH1;
class TClonesArray;

class KoaHitMergeTask : public FairTask {
 public:
  /** Default constructor **/

  KoaHitMergeTask();
  KoaHitMergeTask(const char* name);

  /** Destructor **/
  virtual ~KoaHitMergeTask();

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

  ClassDef(KoaHitMergeTask, 0);
};

#endif /* KOALAHITMERGETASK_H */
