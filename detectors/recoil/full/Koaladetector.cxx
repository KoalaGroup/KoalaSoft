 
#include "Koaladetector.h"

#include "TClonesArray.h"
#include "TGeoPhysicalNode.h"
#include "TVirtualMC.h"

#include <iostream>

// -----   Default constructor   -------------------------------------------
Koaladetector::Koaladetector() {
  SetDetectorID(kKOALA);
}

// -----   Standard constructor   ------------------------------------------
Koaladetector::Koaladetector(const char* name, Bool_t active) :
		PndSdsDetector(name, active) {
	SetDetectorID(kKOALA);
}

// -----   Destructor   ----------------------------------------------------
Koaladetector::~Koaladetector() {
}

void Koaladetector::SetBranchNames(char* outBranchname, char* folderName) {
	fOutBranchName = outBranchname;
	fFolderName = folderName;
}

void Koaladetector::SetBranchNames() {
	fOutBranchName = "KoalaLMDPoint";
	fFolderName = "KoalaLmd";
}

void Koaladetector::SetDefaultSensorNames() {
	fListOfSensitives.push_back("KoalaActive");
}



//ab hier obsulete
/*
void Koaladetector::ModifyGeometry() {
	LOG(INFO) << "Modifying the geometry for the Lmd detector." << FairLogger::endl;

	TString detStr = "lmd_root";

	TGeoPNEntry* entry = gGeoManager->GetAlignableEntry(detStr.Data());
	if (entry) {
		LOG(INFO) << "Modifying using symlinks." << FairLogger::endl;
		ModifyGeometryBySymlink();
	}
	else {
		LOG(INFO) << "Modifying using full path." << FairLogger::endl;
		ModifyGeometryByFullPath();
	}
	LOG(DEBUG) << "Align in total " << fAlignmentMatrices.size() << " detectors." << FairLogger::endl;
	std::cout << "Koaladetector:modifyGeometry: success!\n";
}

void Koaladetector::ModifyGeometryByFullPath() {
	TString volPath;

	for (auto const& entry : fAlignmentMatrices) {
		volPath = entry.first;

		gGeoManager->cd(volPath);

		TGeoNode* n3 = gGeoManager->GetCurrentNode();
		TGeoMatrix* l3 = n3->GetMatrix();

		TGeoHMatrix nlocal = *l3 * entry.second;
		TGeoHMatrix* nl3 = new TGeoHMatrix(nlocal);  // new matrix, representing real position
		                                             // (from new local mis RS to the global one)

		TGeoPhysicalNode* pn3 = gGeoManager->MakePhysicalNode(volPath);

		pn3->Align(nl3);
	}
}

void Koaladetector::ModifyGeometryBySymlink() {
	TString detStr;
	for (auto const& alignment_matrix : fAlignmentMatrices) {
		detStr = alignment_matrix.first;

		TGeoPhysicalNode* node = NULL;
		TGeoPNEntry* entry = gGeoManager->GetAlignableEntry(detStr);
		if (entry) {
			node = gGeoManager->MakeAlignablePN(entry);
		}

		TGeoMatrix* l3 = NULL;
		if (node) {
			l3 = node->GetMatrix();
		}
		else {
			continue;
		}

		TGeoHMatrix nlocal = *l3 * alignment_matrix.second;
		TGeoHMatrix* nl3 = new TGeoHMatrix(nlocal);  // new matrix, representing real position
		                                             // (from new local mis RS to the global one)
		node->Align(nl3);
	}
}

void Koaladetector::SetMisalignmentMatrices(
    const std::map<std::string, TGeoHMatrix>& alignmentMatrices) {
	fAlignmentMatrices = alignmentMatrices;
	}*/

ClassImp(Koaladetector);
