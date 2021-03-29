// -------------------------------------------------------------------------
// -----                 PndPersistencyTask header file                    -----
// -----           Created 28/02/18  by T. Stockmanns		         -----
// -------------------------------------------------------------------------


/** PndPersistencyTask.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Version 28/02/18 by T.Stockmanns
 **
 ** This class handles the persistency parameter used to define if an output branch is stored in a root file
 ** or not.
 **/


#ifndef PndBranchTask_H
#define PndBranchTask_H

#include "FairTask.h"

class PndPersistencyTask : public FairTask
{

 public:

  PndPersistencyTask();
  PndPersistencyTask(const char* name, Int_t iVerbose = 1);
  virtual ~PndPersistencyTask();

  void SetPersistency(Bool_t val=kTRUE){ fPersistency = val; }
  Bool_t GetPersistency(){ return fPersistency; }

 private:
  Bool_t fPersistency;                    //!   ///< Persistency flag


  ClassDef(PndPersistencyTask,1)


};






#endif
