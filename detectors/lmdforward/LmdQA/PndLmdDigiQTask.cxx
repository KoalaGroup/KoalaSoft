// -------------------------------------------------------------------------
// -----              PndLmdDigiQTask source file                -----
// -----            Created 19/09/14  by A.Karavdina          -----
// -------------------------------------------------------------------------
// libc includes
#include <iostream>

// Root includes
#include "TROOT.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include <TMatrixDSym.h>

// framework includes
#include "FairRootManager.h"
#include "PndLmdGeaneTask.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairHit.h"
#include "PndMCTrack.h"
#include "FairBaseParSet.h"
#include "TGeant3.h"
#include "FairTrackParH.h"
#include "FairTrackParP.h"
#include "TDatabasePDG.h"
#include "PndTrack.h"

#include "FairMCEventHeader.h"

// PndSds includes
#include "PndSdsMCPoint.h"
#include "PndSdsHit.h"
#include "PndSdsMergedHit.h"

#include <vector>
#include <map>

#include "PndLmdDigiQTask.h"
#include "LmdMC/PndLmdGeometryHelper.h"

// // -----   Default constructor   -------------------------------------------
// PndLmdDigiQTask::PndLmdDigiQTask() : FairTask("Track Quality  Task for PANDA Lmd"), fEventNr(0)
// {
// }
// // -------------------------------------------------------------------------

PndLmdDigiQTask::PndLmdDigiQTask(TString digiBranch) :
		FairTask("Digis Quality Task for PANDA Lmd"), fEventNr(0), lmd_geo_helper(
				PndLmdGeometryHelper::getInstance()) {
	fWriteAllMC = false;
	fDigiName = digiBranch;
}

// -----   Destructor   ----------------------------------------------------
PndLmdDigiQTask::~PndLmdDigiQTask() {
}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdDigiQTask::Init() {

	// Get RootManager
	FairRootManager* ioman = FairRootManager::Instance();
	if (!ioman) {
		std::cout << "-E- PndLmdDigiQTask::Init: "
				<< "RootManager not instantiated!" << std::endl;
		return kFATAL;
	}

	// fMCHeader = (TClonesArray*) ioman->GetObject("MCEventHeader.");
	// if ( !fMCHeader)	{
	//   std::cout << "-W- PndLmdDigiQTask::Init: "<< "No MCEventHeader "<<" object!" << std::endl;
	//   return kERROR;
	// }

	//Get MC points
	fMCHits = (TClonesArray*) ioman->GetObject("LMDPoint");
	if (!fMCHits) {
		std::cout << "-W- PndLmdDigiQTask::Init: " << "No LMDPoint" << " array!"
				<< std::endl;
		return kERROR;
	}

	//Get MC tracks
	fMCTracks = (TClonesArray*) ioman->GetObject("MCTrack");
	if (!fMCTracks) {
		std::cout << "-W- PndLmdDigiQTask::Init: " << "No MCTrack" << " array!"
				<< std::endl;
		return kERROR;
	}

	//Get digis
	fDigis = (TClonesArray*) ioman->GetObject("LMDPixelDigis");
	if (!fDigis) {
		std::cout << "-W- PndLmdDigiQTask::Init: " << "No LMDPixelDigis"
				<< " array!" << std::endl;
		return kERROR;
	}

	fDigiQ = new TClonesArray("PndLmdDigiQ");
	ioman->Register("LMDPixelDigisQ", "DigiQ", fDigiQ, kTRUE);

	//FairRun* fRun = FairRun::Instance(); //[R.K. 01/2017] unused variable?
	//FairRuntimeDb* rtdb = fRun->GetRuntimeDb(); //[R.K. 01/2017] unused variable

	return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PndLmdDigiQTask::Exec(Option_t*) {
	FairRootManager* ioman = FairRootManager::Instance();
	double glEvTime = ioman->GetEventTime();
	fDigiQ->Delete();
	//const int nMCHits = fMCHits->GetEntriesFast(); //[R.K. 01/2017] unused variable
	const int nDigis = fDigis->GetEntriesFast();
	const int nParticles = fMCTracks->GetEntriesFast();

	/// Set elastic/inelastic flag ----------------------------------------------------
	bool elfl = false;
	int sumID = 0;
	//int TotCharge=0; //[R.K. 01/2017] unused variable
	for (Int_t iN = 0; iN < nParticles; iN++) {

		PndMCTrack *mctrk = (PndMCTrack*) fMCTracks->At(iN);
		//int glPDG = mctrk->GetPdgCode(); //[R.K. 01/2017] unused variable
		Int_t mcID = mctrk->GetPdgCode();
		int motherid = mctrk->GetMotherID();
		if (motherid < 0) {
			sumID += fabs(mcID);
		}
	}
	if (sumID == 4424)
		elfl = true;
	///------------------------------------------------------------------------------

	for (Int_t i = 0; i < nDigis; i++) {
		PndSdsDigiPixel* DigiPoint = (PndSdsDigiPixel*) (fDigis->At(i)); // read digi hit
		TClonesArray& clref = *fDigiQ;
		Int_t size = clref.GetEntriesFast();
		PndLmdDigiQ *digiq = new (clref[size]) PndLmdDigiQ(*DigiPoint, elfl);
		int nmchits = DigiPoint->GetNIndices(); // number of PndSdsMCPoint(s) contributing to digi
		int sensorID = DigiPoint->GetSensorID();
		auto const& digi_info(lmd_geo_helper.getHitLocationInfo(sensorID));

		for (Int_t j = 0; j < nmchits; j++) {
			int mcind = DigiPoint->GetIndex(j);
			PndSdsMCPoint* MCPoint = (PndSdsMCPoint*) (fMCHits->At(mcind));
			int MCtrk = MCPoint->GetTrackID();
			PndMCTrack *mctrk = (PndMCTrack*) fMCTracks->At(MCtrk);
			int glPDG = mctrk->GetPdgCode(); // barp: -2212
			digiq->SetMCtrkID(MCtrk);
			digiq->SetPDG(glPDG);
			digiq->SetPlane(digi_info.plane);
			digiq->SetHalf(digi_info.detector_half);
			digiq->SetModule(digi_info.module);
			digiq->SetSide(digi_info.module_side);
			digiq->SetEvT(glEvTime);
			int movID = mctrk->GetMotherID(); // primary: <0
			TVector3 MomMC = mctrk->GetMomentum();
			double thMC = MomMC.Theta();
			digiq->SetThMC(thMC);
			if (glPDG == -2212 && movID < 0 && elfl)
				digiq->SetFlSig();
			else
				digiq->SetFlBkg();
		}
	}
	if (fVerbose > 2)
		cout << "PndLmdDigiQTask::Exec END!" << endl;
	fEventNr++;
}

void PndLmdDigiQTask::Finish() {
}
ClassImp(PndLmdDigiQTask);
