// -------------------------------------------------------------------------
// -----                PndLmdIdealClusterTask source file             -----
// -------------------------------------------------------------------------

#include "PndLmdIdealClusterTask.h"

// -----   Default constructor   -------------------------------------------
PndLmdIdealClusterTask::PndLmdIdealClusterTask() {}
// -------------------------------------------------------------------------

PndLmdIdealClusterTask::PndLmdIdealClusterTask(Double_t radius, Int_t FEcolumns,
                                               Int_t FErows, TString geoFile)
    : PndSdsIdealClusterTask(radius, FEcolumns, FErows, geoFile) {}

// -----   Destructor   ----------------------------------------------------
PndLmdIdealClusterTask::~PndLmdIdealClusterTask() {}
// -------------------------------------------------------------------------

void PndLmdIdealClusterTask::SetBranchNames(TString inBranchname,
                                            TString outHitBranchname,
                                            TString outClustBranchname,
                                            TString folderName) {
  fInBranchName = inBranchname;
  fOutBranchName = outHitBranchname;
  fClustBranchName = outClustBranchname;
  fFolderName = folderName;
}

void PndLmdIdealClusterTask::SetBranchNames() {
  fInBranchName = "LMDPixelDigis";
  fOutBranchName = "LMDIdealClusterHit";
  fClustBranchName = "LMBCluster";
  fFolderName = "PndLmd";
}

ClassImp(PndLmdIdealClusterTask);
