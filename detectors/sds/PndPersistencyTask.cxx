// -------------------------------------------------------------------------
// -----                  PndPersistencyTask source file                    -----
// -----             Created 28/02/18  by T.Stockmanns                 -----
// -------------------------------------------------------------------------
#include <PndPersistencyTask.h>



// -----   Default constructor   -------------------------------------------
PndPersistencyTask::PndPersistencyTask() : fPersistency(kFALSE)
{
}

// -------------------------------------------------------------------------

PndPersistencyTask::PndPersistencyTask(const char* name, Int_t iVerbose) : FairTask(name, iVerbose), fPersistency(kFALSE)
{

}

// -----   Destructor   ----------------------------------------------------
PndPersistencyTask::~PndPersistencyTask() {
}
// -------------------------------------------------------------------------


ClassImp(PndPersistencyTask)
