#include "PndLmdDetector.h"

#include "TClonesArray.h"
#include "TGeoPhysicalNode.h"
#include "TVirtualMC.h"

#include <iostream>

// -----   Default constructor   -------------------------------------------
PndLmdDetector::PndLmdDetector() {
	SetDetectorID(kLUMI);
}

// -----   Standard constructor   ------------------------------------------
PndLmdDetector::PndLmdDetector(const char* name, Bool_t active) :
		PndSdsDetector(name, active) {
	SetDetectorID(kLUMI);
}

// -----   Destructor   ----------------------------------------------------
PndLmdDetector::~PndLmdDetector() {
}

void PndLmdDetector::SetBranchNames(char* outBranchname, char* folderName) {
	fOutBranchName = outBranchname;
	fFolderName = folderName;
}

void PndLmdDetector::SetBranchNames() {
	fOutBranchName = "LMDPoint";
	fFolderName = "PndLmd";
}

void PndLmdDetector::SetDefaultSensorNames() {
	fListOfSensitives.push_back("LumActive");
}

ClassImp(PndLmdDetector);
