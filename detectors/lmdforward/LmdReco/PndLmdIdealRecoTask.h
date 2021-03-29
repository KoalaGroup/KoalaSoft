// -------------------------------------------------------------------------
// -----                PndLmdIdealRecoTask source file                -----
// -----                 Created 04/02/10  by M.Michel                 -----
// -----             Based on PndMvdIdealRecoTask by R.Kliemt          -----
// -------------------------------------------------------------------------

/** PndMvdIdealRecoTask.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The ideal tracking produces tracks of type PndSdsHit by using MC information
 ** directly, but with the correct data interface.
 **/

#ifndef PNDLMDIDEALRECOTASK_H
#define PNDLMDIDEALRECOTASK_H

#include "PndSdsIdealRecoTask.h"

class TClonesArray;

class PndLmdIdealRecoTask : public PndSdsIdealRecoTask {
 public:
  /** Default constructor **/
  PndLmdIdealRecoTask();

  PndLmdIdealRecoTask(Double_t sx, Double_t sy, Double_t sz);

  /** Destructor **/
  virtual ~PndLmdIdealRecoTask();

  /** pure virtual method SetBranchNames
  **
  ** called by Init()
  ** function to set individual branch names
  **/
  virtual void SetBranchNames(TString inBranchname, TString outHitBranchname,
                              TString folderName);
  virtual void SetBranchNames();

  ClassDef(PndLmdIdealRecoTask, 2);
};

#endif
