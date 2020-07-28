// -------------------------------------------------------------------------
// -----               PndLmdHitProducerIdeal source file             -----
// -------------------------------------------------------------------------

#include "PndLmdHitProducerIdeal.h"

// -----   Default constructor   -------------------------------------------
PndLmdHitProducerIdeal::PndLmdHitProducerIdeal()
{

}
// -------------------------------------------------------------------------

void PndLmdHitProducerIdeal::SetBranchNames(TString inBranchname, TString outBranchname, TString folderName)
{
  fInBranchName = inBranchname;
  fOutBranchName = outBranchname;
  fFolderName = folderName;
}


void PndLmdHitProducerIdeal::SetBranchNames()
{
  fInBranchName = "LMDPoint";
  fOutBranchName = "LMDHit";
  fFolderName = "PndLmd";
}

// -----   Destructor   ----------------------------------------------------
PndLmdHitProducerIdeal::~PndLmdHitProducerIdeal()
{
}


ClassImp(PndLmdHitProducerIdeal);
