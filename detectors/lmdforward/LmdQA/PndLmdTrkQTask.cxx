// -------------------------------------------------------------------------
// -----              PndLmdTrkQTask source file                -----
// -----            Created 18/06/13  by A.Karavdina          -----
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

#include "PndLmdTrkQTask.h"
#include "LmdMC/PndLmdGeometryHelper.h"

// // -----   Default constructor   -------------------------------------------
// PndLmdTrkQTask::PndLmdTrkQTask() : FairTask("Track Quality  Task for PANDA Lmd"), fEventNr(0)
// {
// }
// // -------------------------------------------------------------------------

PndLmdTrkQTask::PndLmdTrkQTask(Double_t pBeam, TString geaneBranch,
		TString trackBranch) :
		FairTask("Track Quality Task for PANDA Lmd"), fEventNr(0) {
	fWriteAllMC = false;
	fPbeam = pBeam;
	fGeaneName = geaneBranch;
	fTrackBranchName = trackBranch;
	//cout<<"Beam Momentum for particle with PDGid#"<<fPDGid<<" this run is "<<fPbeam<<endl;
	// vtx = IP;
	// cout<<"Interaction Point:"<<endl;
	// vtx.Print();
}

// -----   Destructor   ----------------------------------------------------
PndLmdTrkQTask::~PndLmdTrkQTask() {
}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdTrkQTask::Init() {

	// Get RootManager
	FairRootManager* ioman = FairRootManager::Instance();
	if (!ioman) {
		std::cout << "-E- PndLmdTrkQTask::Init: " << "RootManager not instantiated!"
				<< std::endl;
		return kFATAL;
	}

	// fMCHeader = (TClonesArray*) ioman->GetObject("MCEventHeader.");
	// if ( !fMCHeader)	{
	//   std::cout << "-W- PndLmdTrkQTask::Init: "<< "No MCEventHeader "<<" object!" << std::endl;
	//   return kERROR;
	// }

	//Get MC points
	fMCHits = (TClonesArray*) ioman->GetObject("LMDPoint");
	if (!fMCHits) {
		std::cout << "-W- PndLmdTrkQTask::Init: " << "No LMDPoint" << " array!"
				<< std::endl;
		return kERROR;
	}

	//Get MC tracks
	fMCTracks = (TClonesArray*) ioman->GetObject("MCTrack");
	if (!fMCTracks) {
		std::cout << "-W- PndLmdTrkQTask::Init: " << "No MCTrack" << " array!"
				<< std::endl;
		return kERROR;
	}

	//Get rec. hits
	fRecHits = (TClonesArray*) ioman->GetObject("LMDHitsMerged");
	if (!fRecHits) {
		std::cout << "-W- PndLmdTrkQTask::Init: " << "No LMDHitsMerged" << " array!"
				<< std::endl;
		return kERROR;
	}
	//Get trk cand
	fRecCandTracks = (TClonesArray*) ioman->GetObject("LMDTrackCand");
	if (!fRecCandTracks) {
		std::cout << "-W- PndLmdTrkQTask::Init: " << "No LMDTrackCand" << " array!"
				<< std::endl;
		return kERROR;
	}
	//Get rec.tracks before back propagation
	fRecTracks = (TClonesArray*) ioman->GetObject(fTrackBranchName);
	if (!fRecTracks) {
		std::cout << "-W- PndLmdTrkQTask::Init: " << "No LMDPndTrackFilt"
				<< " array!" << std::endl;
		return kERROR;
	}

	//Get rec.tracks after back propagation
	//  fRecBPTracks = (TClonesArray*) ioman->GetObject("GeaneTrackFinal");//use raw reconstructed data
	//  fRecBPTracks = (TClonesArray*) ioman->GetObject("LMDCleanTrack");//use cleaned data
	fRecBPTracks = (TClonesArray*) ioman->GetObject(fGeaneName);
	if (!fRecBPTracks) {
		std::cout << "-W- PndLmdTrkQTask::Init: " << "No GeaneTrackFinal"
				<< " array!" << std::endl;
		return kERROR;
	}

	fTrackQ = new TClonesArray("PndLmdTrackQ");
	ioman->Register("LMDTrackQ", "TrkQ", fTrackQ, kTRUE);

	// fDetName = new TClonesArray("TObjString");
	// ioman->Register("DetName", "TrkQ", fDetName, kTRUE);

	// fGeoH = PndGeoHandling::Instance();
	//FairRun* fRun = FairRun::Instance(); //[R.K. 01/2017] unused variable?
	//FairRuntimeDb* rtdb = fRun->GetRuntimeDb(); //[R.K. 01/2017] unused variable
	//  TDatabasePDG *fdbPDG = TDatabasePDG::Instance();
	//  fdbPDG = TDatabasePDG::Instance();

	return kSUCCESS;
}
// -------------------------------------------------------------------------
// void PndLmdTrkQTask::SetParContainers()
// {
// }

// -----   Public method Exec   --------------------------------------------
void PndLmdTrkQTask::Exec(Option_t*) {

	fTrackQ->Delete();
	// fDetName->Delete();

	Double_t glXrecLMD, glYrecLMD, glZrecLMD, glThetarecLMD, glPhirecLMD;
	Double_t glXrec, glYrec, glZrec, glThetarec, glPhirec, glMomrec;
	Double_t glXmc, glYmc, glZmc, glThetamc, glPhimc, glMommc;
	Double_t glXmcLMD, glYmcLMD, glZmcLMD, glThetamcLMD, glPhimcLMD, glMommcLMD;
	Int_t trkRECStatus;
	Int_t trkMCStatus;
	Double_t glchi2;
	int glPDG;
	int glNumMChits;
	int glNumDoubleMChits;

	int glModule, glHalf;
	FairRootManager* ioman = FairRootManager::Instance();
	//  double glEvTime = FairRootManager::Instance()->GetEventTime();
	double glEvTime = ioman->GetEventTime();
	// FairMCEventHeader* iomchead = (FairMCEventHeader*) ioman->GetObject("MCEventHeader");
	// FairMCEventHeader* mcevhead = (FairMCEventHeader*) fMCHeader->At(0);
	// int glEvID = mcevhead->GetEventID();
	// cout<<"this is event # "<<glEvID<<endl;
	double glTrkTime;

	const int nGeaneTrks = fRecBPTracks->GetEntriesFast();
	const int nParticles = fMCTracks->GetEntriesFast();
	const int numTrk = fRecTracks->GetEntriesFast();
	const int nRecHits = fRecHits->GetEntriesFast();
	const int nMCHits = fMCHits->GetEntriesFast();

	const int nTrkCandidates = fRecCandTracks->GetEntriesFast();
	//const int nRecTrks = fRecTracks->GetEntriesFast(); //[R.K. 01/2017] unused variable

	if (fVerbose > 0)
		cout << "%%%%%! Event #" << fEventNr << " has " << nParticles
				<< " true particles, " << " out of it " << nRecHits << " hits, "
				<< nTrkCandidates << " trk-cands, " << numTrk << " tracks and "
				<< nGeaneTrks << " geane Trks!" << endl;

	/// Set signal/bkg flag ----------------------------------------------------
	int sumID = 0;
	//int TotCharge=0; //[R.K. 01/2017] unused variable
	for (Int_t iN = 0; iN < nParticles; iN++) {
		PndMCTrack *mctrk = (PndMCTrack*) fMCTracks->At(iN);
		glPDG = mctrk->GetPdgCode();
		Int_t mcID = mctrk->GetPdgCode();
		int motherid = mctrk->GetMotherID();
		if (motherid < 0 && fabs(mcID) < 1e5) {
			sumID += fabs(mcID);
		}
		// TParticlePDG *fParticle = fdbPDG->GetParticle(mcID);
		// Double_t  fCharge = fParticle->Charge();
		// TotCharge += fCharge;
	}
	///------------------------------------------------------------------------------

	/// Chech how many MC hits has MC trk ----------------------------
	int MCtksSIMhits[nParticles];
	int MCDoubleHits[nParticles];
	for (int imctrk = 0; imctrk < nParticles; imctrk++) {
		MCtksSIMhits[imctrk] = 0;
		MCDoubleHits[imctrk] = 0;
	}
	for (int imc = 0; imc < nMCHits; imc++) {
		PndSdsMCPoint* MCPoint = (PndSdsMCPoint*) (fMCHits->At(imc));
		int MCtrk = MCPoint->GetTrackID();
		MCtksSIMhits[MCtrk]++;
	}
	///------------------------------------------------------------------------------

	/// Chech how many REC hits has MC trk ----------------------------

	int MCtksREChits[nParticles];
	// const int nSize = 2e4;
	// int MCtksREChits[nSize];//add arbitrary number of fake trks due to noise hits
	for (int imctrk = 0; imctrk < nParticles; imctrk++) {
		MCtksREChits[imctrk] = 0;
	}
	if (fVerbose > 7)
		cout << "    ** ALL REChits are made from MChits: " << endl; //start MC hit content
	//bool fMCnegative = false; //[R.K. 01/2017] unused variable
	for (int irec = 0; irec < nRecHits; irec++) {
		PndSdsMergedHit* myHit = (PndSdsMergedHit*) (fRecHits->At(irec));
		int mcrefbot = myHit->GetSecondMCHit();
		int MCtrkidbot, MCtrkidtop;
		if (mcrefbot > 0) {
			PndSdsMCPoint* MCPointBot = (PndSdsMCPoint*) (fMCHits->At(mcrefbot));
			int MCtrkid = MCPointBot->GetTrackID();

			MCtksREChits[MCtrkid]++;
			MCtrkidbot = MCtrkid;
			if (fVerbose > 7)
				cout << " " << MCtrkid << "(MChitID=" << mcrefbot << ",z="
						<< MCPointBot->GetZ() << ")";
		}
		int mcreftop = myHit->GetRefIndex();
		if (mcreftop > 0) {
			PndSdsMCPoint* MCPointTop = (PndSdsMCPoint*) (fMCHits->At(mcreftop));
			int MCtrkid = MCPointTop->GetTrackID();

			MCtksREChits[MCtrkid]++;
			MCtrkidtop = MCtrkid;
			if (fVerbose > 7)
				cout << " " << MCtrkid << "(MChitID=" << mcreftop << ",z="
						<< MCPointTop->GetZ() << ")";
		}
		if (mcreftop > 0 && mcrefbot > 0) {
			if (MCtrkidtop == MCtrkidbot) {
				MCDoubleHits[MCtrkidbot]++;
			} else {
				if (fVerbose > 7)
					cout << "  REChit No." << irec << "contain MCid: " << MCtrkidtop
							<< ", " << MCtrkidbot << " !" << endl;
			}
		}
		// if(fVerbose>7)
		//   cout<<" "<<endl;//next hit content
	}
	// if(fMCnegative){
	//   if(fVerbose>7) cout<<"bad event, skip it!"<<endl;
	// }
	// if(fMCnegative) continue;
	///------------------------------------------------------------------------------

	///Compare trk-cand vs. trk-fit -----------------------------
	// TNtuple *ntupTrkFit = new TNtuple("ntupTrkFit","Info about reconstructed trks: trk-cand vs. trk after fit","xtc:ytc:ztc:thtc:phitc:xtf:ytf:ztf:thtf:phitf:chi2");
	for (Int_t iN = 0; iN < nGeaneTrks; iN++) { // loop over all reconstructed trks
		//dummy values
		glXrecLMD = -9999;
		glYrecLMD = -9999;
		glZrecLMD = -9999;
		glThetarecLMD = -9999;
		glPhirecLMD = -9999;
		glXrec = -9999;
		glYrec = -9999;
		glZrec = -9999;
		glThetarec = -9999;
		glPhirec = -9999;
		glMomrec = -9999;
		glXmc = -9999;
		glYmc = -9999;
		glZmc = -9999;
		glThetamc = -9999;
		glPhimc = -9999;
		glMommc = -9999;
		glXmcLMD = -9999;
		glYmcLMD = -9999;
		glZmcLMD = -9999;
		glThetamcLMD = -9999;
		glPhimcLMD = -9999;
		glMommcLMD = -9999;
		trkRECStatus = -9999;
		trkMCStatus = -9999;
		glchi2 = -9999;
		glPDG = -9999;
		glNumMChits = -9999;
		glNumDoubleMChits = -9999;

		PndTrack *trkpnd = (PndTrack*) fRecTracks->At(iN);
		//double chi2 = trkpnd->GetChi2(); //[R.K. 01/2017] unused variable
		FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();
		TVector3 PosRecLMD(fFittedTrkP.GetX(), fFittedTrkP.GetY(),
				fFittedTrkP.GetZ());
		TVector3 MomRecLMD(fFittedTrkP.GetPx(), fFittedTrkP.GetPy(),
				fFittedTrkP.GetPz());
		MomRecLMD *= fPbeam / MomRecLMD.Mag();

		int candID = trkpnd->GetRefIndex();
		//      cout<<"candID = "<<candID<<endl;
		PndTrackCand *trkcand = (PndTrackCand*) fRecCandTracks->At(candID);
		/// Obtain first approximation
		const int numPts = trkcand->GetNHits(); //read how many points in this track
		PndTrackCandHit theHit1 = trkcand->GetSortedHit(0); //get 1st hit
		Int_t index1 = theHit1.GetHitId();
		PndSdsHit* Hit1sds = (PndSdsHit*) fRecHits->At(index1);
		TVector3 posSeed = Hit1sds->GetPosition();
		PndTrackCandHit theHit2 = trkcand->GetSortedHit(numPts - 1); //get last hit
		Int_t index2 = theHit2.GetHitId();
		PndSdsHit* Hit2sds = (PndSdsHit*) fRecHits->At(index2);
		TVector3 pos2 = Hit2sds->GetPosition();
		TVector3 MomRecCandLMD = pos2 - posSeed;
		MomRecCandLMD *= fPbeam / MomRecCandLMD.Mag();
		// TVector3 PosRecCandLMD = trkcand->getPosSeed();
		// TVector3 MomRecCandLMD = trkcand->getDirSeed();
		// MomRecCandLMD *=fPbeam/MomRecCandLMD.Mag();
	}
	///-------------------------------------------------------------------

	/// Set MC ID for each track ----------------------------------------------------
	//Int_t nRecGEANEtrk = 0; //[R.K. 01/2017] unused variable
	int MCtrk[nParticles]; //Number of participation this MCid in rec.tracks
	int RECtrkMCid[nGeaneTrks]; //Assignment MC id to REC trk;
	for (int nk = 0; nk < nParticles; nk++)
		MCtrk[nk] = 0;
	bool goodTrk[nGeaneTrks];
	bool ghostTrk[nGeaneTrks];
	for (Int_t iN = 0; iN < nGeaneTrks; iN++) {
		goodTrk[iN] = false;
		ghostTrk[iN] = false;
		RECtrkMCid[iN] = -1;
	}

	//int goodRectrk=0;//for missed trk-search //[R.K. 01/2017] unused variable
	for (Int_t iN = 0; iN < nGeaneTrks; iN++) { // loop over all reconstructed trks
		FairTrackParH *fRes = (FairTrackParH*) fRecBPTracks->At(iN);
		TVector3 PosRec = fRes->GetPosition();
		Double_t lyambda = fRes->GetLambda();
		if (lyambda == 0) {
			cout << "GEANE didn't propagate trk No." << iN << "!" << endl;
		}

		PndTrack *trkpnd = (PndTrack*) fRecTracks->At(iN);
		//double chi2 = trkpnd->GetChi2(); //[R.K. 01/2017] unused variable
		int candID = trkpnd->GetRefIndex();
		//if(fVerbose>5) cout<<"candID = "<<candID<<endl;
		PndTrackCand *trkcand = (PndTrackCand*) fRecCandTracks->At(candID);
		const int Ntrkcandhits = trkcand->GetNHits();
		//    PndSdsMCPoint* MCPointHit;
		int MCtrkID[Ntrkcandhits]; //arrray of hits MCid
		for (Int_t iHit = 0; iHit < Ntrkcandhits; iHit++) {
			MCtrkID[iHit] = 9999;
		}
		Int_t diffIDs = 1;

		///Matching between MC & Rec on hits level-----------------------------------
		//bool emergExit=false; //[R.K. 01/2017] unused variable
		if (fVerbose > 7)
			cout << "    *** REChits in trk (with " << Ntrkcandhits
					<< " hits) are made from MChits: " << endl;     //start MC hit content
		for (Int_t iHit = 0; iHit < Ntrkcandhits; iHit++) { // loop over rec.hits
			if (fVerbose > 7)
				cout << "No." << iHit << ": ";
			PndTrackCandHit candhit = (PndTrackCandHit) (trkcand->GetSortedHit(iHit));
			Int_t hitID = candhit.GetHitId();
			PndSdsMergedHit* myHit = (PndSdsMergedHit*) (fRecHits->At(hitID));
			int mcrefbot = myHit->GetSecondMCHit();
			//bool badpxbot=false; //[R.K. 01/2017] unused variable
			//bool badpxtop=false; //[R.K. 01/2017] unused variable
			if (mcrefbot >= 0) {
				PndSdsMCPoint* MCPointBot = (PndSdsMCPoint*) (fMCHits->At(mcrefbot));
				int MCtrkid = MCPointBot->GetTrackID();
				if (MCtrkid < 0) {
					//emergExit=true; //[R.K. 01/2017] unused variable
					if (fVerbose > 7)
						cout << " " << MCtrkid << "!!!";
					break;	//TODO: how it is possible???
				}
				//	  if(MCtrkid>-1)
				MCtrkID[iHit] = MCtrkid;
				if (fVerbose > 7)
					cout << " " << MCtrkid;
			} else {
				//badpxbot=true; //[R.K. 01/2017] unused variable
				if (fVerbose > 7)
					cout << " Ooops,  mcrefbot = " << mcrefbot;
			}
			int mcreftop = myHit->GetRefIndex();

			if (mcreftop >= 0) {
				// if(fVerbose>5)
				//   cout<<", "<<mcreftop<<")";
				PndSdsMCPoint* MCPointTop = (PndSdsMCPoint*) (fMCHits->At(mcreftop));
				int MCtrkid = MCPointTop->GetTrackID();
				if (MCtrkid < 0) {
					//emergExit=true; //[R.K. 01/2017] unused variable
					if (fVerbose > 7)
						cout << " " << MCtrkid << "!!!";
					break;	  //TODO: how it is possible???
				}
				//	  if(MCtrkid>-1)
				MCtrkID[iHit] = MCtrkid;
				if (fVerbose > 7)
					cout << " " << MCtrkid;
			} else {
				//badpxtop=true; //[R.K. 01/2017] unused variable
				if (fVerbose > 7)
					cout << " Ooops,  mcreftop = " << mcreftop;
			}

			if (fVerbose > 7)
				cout << " " << endl;	  //next hit content
		}
		//   if(emergExit) continue;

		//   Sorting MC IDs ----------------------------------------
		//TODO: sort it by c++ function
		Int_t k, x;
		//bool ch=false; //Was element changed?  //[R.K. 01/2017] unused variable
		Int_t nch = 0; //How many times?
		for (Int_t n = 0; n < Ntrkcandhits; n++) { // n - current position
			k = n;
			x = MCtrkID[n];
			for (Int_t m = n + 1; m < Ntrkcandhits; m++)	// find the least element
				if (MCtrkID[m] < x) {
					k = m;
					x = MCtrkID[m];	        // k - index for the least element
					//ch=true;  //[R.K. 01/2017] unused variable
					nch++;
				}
			MCtrkID[k] = MCtrkID[n];
			MCtrkID[n] = x; // change position between the least and current elements
		}
		///--------------------------------------------------------------------------

		/// Counting number of diff MC ids ----------------------------------------
		Int_t prevID = MCtrkID[0];
		for (int nk = 0; nk < nParticles; nk++) {
			if (MCtrkID[0] == nk)
				MCtrk[nk] = MCtrk[nk] + 1;
		}
		diffIDs = 1;
		for (Int_t n = 1; n < Ntrkcandhits; n++) {
			if (MCtrkID[n] > 9998)
				break;
			if (prevID < MCtrkID[n]) {
				diffIDs++;
				prevID = MCtrkID[n];
				for (int nk = 0; nk < nParticles; nk++) {
					if (MCtrkID[n] == nk)
						MCtrk[nk] = MCtrk[nk] + 1;
				}
			}
		}

		///------------------------------------------------------------------------

		/// Set track quality: good or ghost? and assign MC id to rec trk ---------
		if (diffIDs < 2) {
			RECtrkMCid[iN] = MCtrkID[0];
			//	cout<<"MCtrkID[0] = "<<MCtrkID[0]<<endl;
			if (MCtrkID[0] < 9999)
				goodTrk[iN] = true;
			else {
				goodTrk[iN] = false;
				ghostTrk[iN] = true;
			}
		} else {
			vector<int> countMC_IDs(diffIDs);
			for (int kn = 0; kn < diffIDs; kn++) {
				countMC_IDs[kn] = 0;
			}

			prevID = MCtrkID[0];
			int diffCount = 0;
			for (Int_t n = 0; n < Ntrkcandhits; n++) {
				//	  cout<<"MCtrkID[n] = "<<MCtrkID[n]<<endl;
				if (MCtrkID[n] > 9998) { //Trk from noise hits
					goodTrk[iN] = false;
					ghostTrk[iN] = true;
					//	    break;
				}

				if (prevID < MCtrkID[n]) {
					diffCount++;
					prevID = MCtrkID[n];
				}
				countMC_IDs[diffCount]++;
			}
			//	if(fVerbose>1)	cout<<""<<endl;
			int maxID = countMC_IDs[0];
			int posIDmax = 0;
			for (int kn = 0; kn < diffIDs; kn++) {
				if (fVerbose > 3)
					cout << "countMC_IDs[" << kn << "]=" << countMC_IDs[kn]
							<< " 0.65*Ntrkcandhits = " << 0.65 * Ntrkcandhits << endl;
				if (countMC_IDs[kn] > 0.65 * Ntrkcandhits) { //more then 65% of hits come from the same MC id
					goodTrk[iN] = true;
					ghostTrk[iN] = false;
				} else {
					if (!goodTrk[iN]) {
						ghostTrk[iN] = true;
						//	      cout<<" aaaaa!"<<iN<< " is ghost trk !aaaa"<<endl;
					}
				}

				if (countMC_IDs[kn] > maxID) {
					maxID = countMC_IDs[kn];
					posIDmax = kn;
				}
			}
			prevID = MCtrkID[0];
			diffCount = 0;
			for (Int_t n = 0; n < Ntrkcandhits; n++) {
				if (diffCount == posIDmax)
					RECtrkMCid[iN] = prevID;
				if (prevID < MCtrkID[n]) {
					diffCount++;
					prevID = MCtrkID[n];
				}
			}
		}
		///------------------------------------------------------------------------

		// /// Comporision MC, trk-candidates and REConstructed tracks --------------------------------------------

		// if(diffIDs>-1){ // All tracks

		// 	/// Read MC track parameters ----------------------------------------------------------
		// 	int MCidforREC = RECtrkMCid[iN];
		// 	PndMCTrack *mctrk =(PndMCTrack*) fMCTracks->At(MCidforREC);
		// 	Int_t mcID = mctrk->GetPdgCode();
		// 	//	glPDG = mctrk->GetPdgCode();
		// 	TVector3 MomMC = mctrk->GetMomentum();
		// 	Double_t thetaMC = MomMC.Theta();
		// 	Double_t phiMC = MomMC.Phi();
		// 	///------------------------------------------------------------------------------------

		// 	/// Read track-parameters after back-propagation ---------------------------------------
		// 	//TODO: problem with covarance matrix in FairTrackParH???
		// 	Double_t CovGEANELAB[6][6];
		// 	fRes->GetMARSCov(CovGEANELAB);
		// 	Double_t errX = fRes->GetDX();
		// 	Double_t errY = fRes->GetDY();
		// 	Double_t errZ = fRes->GetDZ();

		// 	Double_t errPx = fRes->GetDPx();
		// 	Double_t errPy = fRes->GetDPy();
		// 	Double_t errPz = fRes->GetDPz();
		// 	TVector3 errMomBP(errPx,errPy,errPz);

		// 	Double_t thetaBP = TMath::Pi()/2. - lyambda;
		// 	Double_t err_lyambda = fRes->GetDLambda();
		// 	if(err_lyambda==0) err_lyambda = errMomBP.Theta();
		// 	// Double_t err_lyambda = errMom.Theta();
		// 	Double_t phiBP = fRes->GetPhi();
		// 	Double_t err_phi = fRes->GetDPhi();
		// 	if(err_phi==0) err_phi=errMomBP.Phi();
		// 	Double_t errMomRecBP = fRes->GetDQp();
		// 	TVector3 MomRecBP = fRes->GetMomentum();

		// 	///==================================
		// }
		// ///-------------------------------------------------------------------------------------
	}

	/// (II) missed\ghost tracks are defined on hits information
	/// GHOST ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	///check repeated assignment to one MC trk (maybe one MC trk rec. trk was assigned  to several REC trk) ---------------------------------
	//NB: it's only quantity and _ NOT_ quality check. 1st REC trk will be called GOOD and 2nd and others GHOST
	int RECassigMC[nGeaneTrks]; //how many time MCid from this RECtrk met in other RECtrks
	for (Int_t iN = 0; iN < nGeaneTrks; iN++)
		RECassigMC[iN] = 1;

	for (Int_t iN = 0; iN < nGeaneTrks; iN++) {
		int mc_i = RECtrkMCid[iN];
		for (Int_t jN = (iN + 1); jN < nGeaneTrks; jN++) {
			int mc_j = RECtrkMCid[jN];
			if (mc_i == mc_j) {
				RECassigMC[iN]++;
				if (fVerbose > 3)
					cout << "GHOST?!: rec.trks #" << iN << " and #" << jN
							<< "were assigned to one MC trk =|" << endl;
			}
		}
	}
	///END check repeated assignment to one MC trk ------------------------------------------------------------------------------------------------------------------

	int goodRecII = 0, ghostRecI = 0, ghostRecII = 0;
	for (Int_t iN = 0; iN < nGeaneTrks; iN++) { //ghost/good trk determination

		int trkType = -1;
		if (RECassigMC[iN] > 1) { //one RECtrk was already called GOOD for this MCid -> all next are GHOSTs
			goodTrk[iN] = false;
			ghostTrk[iN] = true;
			trkType = +2;
			ghostRecI++;
		}

		if (goodTrk[iN]) {
			if (fVerbose > 7)
				cout << "... RECtrk#" << iN << " was defined as GOOD ..." << endl;
			goodRecII++;
			trkType = 0;
		}
		if (ghostTrk[iN]) {
			if (fVerbose > 7)
				cout << "... RECtrk#" << iN << " was defined as GHOST ..." << endl;
			if (trkType < 0) {
				trkType = +1;
				ghostRecII++;
			}
		}
		if (trkType < 0) {
			cout << "Ooops, RECtrk isn't GOOD and isn't GHOST!!!" << endl;
			trkType = -10;
		}
		//    if(trkType<0) continue; //GEANE didn't propagate this track
		FairTrackParH *fRes = (FairTrackParH*) fRecBPTracks->At(iN);
		Double_t lyambda = fRes->GetLambda();
		if (lyambda == 0)
			trkType = -100; //Trk was not back-propagated!
		//	cout<<"GEANE didn't propagate "<<iN<<" trk!"<<endl;
		Double_t thetaBP = TMath::Pi() / 2. - lyambda;
		Double_t phiBP = fRes->GetPhi();
		TVector3 MomRecBP = fRes->GetMomentum();
		TVector3 PosBP = fRes->GetPosition();

		//Fill tree with rec vs. mc trk info ------------------------------------------------
		glXrec = PosBP.X();
		glYrec = PosBP.Y();
		glZrec = PosBP.Z();
		glThetarec = thetaBP;
		glPhirec = phiBP;
		glMomrec = MomRecBP.Mag();
		Double_t errX = fRes->GetDX();
		Double_t errY = fRes->GetDY();
		Double_t errZ = fRes->GetDZ();

		Double_t errPx = fRes->GetDPx();
		Double_t errPy = fRes->GetDPy();
		Double_t errPz = fRes->GetDPz();
		TVector3 errMomBP(errPx, errPy, errPz);

		Double_t err_lyambda = fRes->GetDLambda();
		//	if(err_lyambda==0) err_lyambda = errMomBP.Theta();
		Double_t err_phi = fRes->GetDPhi();

		PndTrack *trkpnd = (PndTrack*) fRecTracks->At(iN);
		glchi2 = trkpnd->GetChi2();
		FairTrackParP fFittedTrkP = trkpnd->GetParamFirst();
		TVector3 PosRecLMD(fFittedTrkP.GetX(), fFittedTrkP.GetY(),
				fFittedTrkP.GetZ());
		TVector3 MomRecLMD(fFittedTrkP.GetPx(), fFittedTrkP.GetPy(),
				fFittedTrkP.GetPz());
		MomRecLMD *= fPbeam / MomRecLMD.Mag();
		glXrecLMD = PosRecLMD.X();
		glYrecLMD = PosRecLMD.Y();
		glZrecLMD = PosRecLMD.Z();
		glThetarecLMD = MomRecLMD.Theta();
		glPhirecLMD = MomRecLMD.Phi();
		trkRECStatus = trkType;
		int candID = trkpnd->GetRefIndex();
		PndTrackCand *trkcand = (PndTrackCand*) fRecCandTracks->At(candID);
		PndTrackCandHit candhit = (PndTrackCandHit) (trkcand->GetSortedHit(0));	//1st hit info
		Int_t hitID = candhit.GetHitId();
		PndSdsMergedHit* myHit = (PndSdsMergedHit*) (fRecHits->At(hitID));
		int sensorID = myHit->GetSensorID();

		auto& lmd_geo_helper(PndLmdGeometryHelper::getInstance());
		auto const& digi_info(lmd_geo_helper.getHitLocationInfo(sensorID));
		glModule = digi_info.module;
		glHalf = digi_info.detector_half;
		glTrkTime = myHit->GetTimeStamp();
		//TODO: include info from GetTimeStampError()

		// if(trkType>0){ //TODO: ghost-doubled trks has MC trk!!!
		// 	//	int MCidforREC = RECtrkMCid[iN];

		// 	// glXmc= -9999; glYmc =-9999; glZmc = -9999; glThetamc =-9999; glPhimc = -9999; glMommc = -9999;
		// 	// glXmcLMD = -9999; glYmcLMD =-9999; glZmcLMD = -9999; glThetamcLMD =-9999; glPhimcLMD = -9999; glMommcLMD = -9999;
		// 	// glNumMChits = -9999;  glNumDoubleMChits  = -9999; //	glEvTime = -9999;
		// 	// trkMCStatus = -9999;
		// 	// glPDG = -9999;
		// }
		// else{

		// }
		int MCidforREC = RECtrkMCid[iN];
		//	if(!goodTrk[iN]) continue;
		//cout<<" MCidforREC = "<<MCidforREC<<endl;
		if (MCidforREC > 9998) {
			glXmc = -9999;
			glYmc = -9999;
			glZmc = -9999;
			glThetamc = -9999;
			glPhimc = -9999;
			glMommc = -9999;
			glXmcLMD = -9999;
			glYmcLMD = -9999;
			glZmcLMD = -9999;
			glThetamcLMD = -9999;
			glPhimcLMD = -9999;
			glMommcLMD = -9999;
			glNumMChits = -9999;
			glNumDoubleMChits = -9999; //	glEvTime = -9999;
			trkMCStatus = -9999;
			glPDG = -9999;
		} else {
			PndMCTrack *mctrk = (PndMCTrack*) fMCTracks->At(MCidforREC);
			glPDG = mctrk->GetPdgCode();
			//	glEvTime = mctrk->GetStartTime(); //this gives start time of trk, doesn't matter since all el. pbar start in IP
			TVector3 MomMC = mctrk->GetMomentum();
			glThetamc = MomMC.Theta();
			glPhimc = MomMC.Phi();
			glMommc = MomMC.Mag();
			TVector3 StartMC = mctrk->GetStartVertex();
			glXmc = StartMC.X();
			glYmc = StartMC.Y();
			glZmc = StartMC.Z();
			int movID = mctrk->GetMotherID();
			trkMCStatus = movID;
			// if(movID<0) trkMCStatus=1;
			// else
			//   trkMCStatus=0;
			glNumMChits = MCtksSIMhits[MCidforREC];
			glNumDoubleMChits = MCDoubleHits[MCidforREC];

			// //Get MC info in LMD

			int mcrefbot = myHit->GetSecondMCHit();
			int mcreftop = myHit->GetRefIndex();
			if (fVerbose > 0) {
				cout << "mcrefbot = " << mcrefbot << " mcreftop = " << mcreftop << endl;
			}
			PndSdsMCPoint* MCPointHit;
			if (mcreftop >= 0) {
				MCPointHit = (PndSdsMCPoint*) (fMCHits->At(mcreftop));
			} else {
				if (mcrefbot >= 0)
					MCPointHit = (PndSdsMCPoint*) (fMCHits->At(mcrefbot));
				else
					MCPointHit = NULL;
			}
			if (MCPointHit != NULL) {
				TVector3 PosMClmd = MCPointHit->GetPosition();

				double pxTrue = MCPointHit->GetPx();
				double pyTrue = MCPointHit->GetPy();
				double pzTrue = MCPointHit->GetPz();
				TVector3 MomMClmd(pxTrue, pyTrue, pzTrue);
				glXmcLMD = PosMClmd.X();
				glYmcLMD = PosMClmd.Y();
				glZmcLMD = PosMClmd.Z();
				glThetamcLMD = MomMClmd.Theta();
				glPhimcLMD = MomMClmd.Phi();
				glMommcLMD = MomMClmd.Mag();
			} else {	// Noise MC hit
				// glXmcLMD = -9999;      glYmcLMD = -9999;      glZmcLMD = -9999;
				// glThetamcLMD = -9999;  glPhimcLMD = -9999;  glMommcLMD = -9999;
				glXmc = -9999;
				glYmc = -9999;
				glZmc = -9999;
				glThetamc = -9999;
				glPhimc = -9999;
				glMommc = -9999;
				glXmcLMD = -9999;
				glYmcLMD = -9999;
				glZmcLMD = -9999;
				glThetamcLMD = -9999;
				glPhimcLMD = -9999;
				glMommcLMD = -9999;
				glNumMChits = -9999;
				glNumDoubleMChits = -9999; //	glEvTime = -9999;
				trkMCStatus = -99; //1st rec hit = Noise MC hit TODO: check if all hits of this rec.trk are noise ones
				glPDG = -99; //1st rec hit = Noise MC hit
			}
		}
		//    tRECMCtrks->Fill();
		PndLmdTrackQ *trkqlmd =
				new ((*fTrackQ)[fTrackQ->GetEntriesFast()]) PndLmdTrackQ(glMommc);

		trkqlmd->SetTrkRecStatus(trkRECStatus);
		trkqlmd->SetSecondary(trkMCStatus);
		trkqlmd->SetPDGcode(glPDG);
		trkqlmd->SetLMDpoint(glXrecLMD, glYrecLMD, glZrecLMD);
		trkqlmd->SetLMDdir(glThetarecLMD, glPhirecLMD);
		trkqlmd->SetLMDchi2(glchi2);
		trkqlmd->SetIPpoint(glXrec, glYrec, glZrec);
		trkqlmd->SetIPmom(glThetarec, glPhirec, glMomrec);
		trkqlmd->SetIPerrpoint(errX, errY, errZ);
		trkqlmd->SetIPerrmom(err_lyambda, err_phi, errMomBP.Mag());

		trkqlmd->SetMCpoint(glXmc, glYmc, glZmc);
		trkqlmd->SetMCmom(glThetamc, glPhimc, glMommc);
		//     trkqlmd->SetSecondary(trkMCStatus);
		trkqlmd->SetNumMChits(glNumMChits);
		trkqlmd->SetNumDoubleMChits(glNumDoubleMChits);
		trkqlmd->SetMCpointLMD(glXmcLMD, glYmcLMD, glZmcLMD);
		trkqlmd->SetMCmomLMD(glThetamcLMD, glPhimcLMD, glMommcLMD);
		//      trkqlmd->SetTotEvCharge(TotCharge);
		trkqlmd->SetSumEvPDG(sumID);
		trkqlmd->SetEvMCMulti(nParticles);
		trkqlmd->SetEvRECMulti(nGeaneTrks);
		trkqlmd->SetEvTime(glEvTime);
		trkqlmd->SetTrkTime(glTrkTime);
		trkqlmd->SetModule(glModule);
		trkqlmd->SetHalf(glHalf);
		//(end) Fill tree with rec vs. mc trk info ---------------------------------------

	}
	///END GHOST--------------------------------------------------------------------------------------------------------------------------------------------------------------------

	/// MISSED ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	if ((nParticles - goodRecII) > 0) { //missed trks

		int nMCmissedTrkSearch = 0;
		int nMCmissedLossHits = 0;
		for (int imc = 0; imc < nParticles; imc++) { //MC trks
			bool missTrk = true;
			for (int irec = 0; irec < nGeaneTrks; irec++) { //RECids assigment
				int mc_comp = RECtrkMCid[irec];
				if (mc_comp == imc && goodTrk[irec])
					missTrk = false;
			}
			PndMCTrack *mctrk = (PndMCTrack*) fMCTracks->At(imc);
			int movID = mctrk->GetMotherID();
			TVector3 MomMC = mctrk->GetMomentum();
			TVector3 PosMC = mctrk->GetStartVertex();
			glXmc = PosMC.X();
			glYmc = PosMC.Y();
			glZmc = PosMC.Z();
			glThetamc = MomMC.Theta();
			glPhimc = MomMC.Phi();
			glMommc = MomMC.Mag();

			int trkQ = 0;
			/// if MC trk was missed, justify why
			int minHits = MCDoubleHits[imc] + 2;
			if (MCDoubleHits[imc] == 4)
				minHits -= 1;

			if (missTrk) {
				if (MCtksREChits[imc] > minHits) { //missed during trk-search
					if (fVerbose > 7) {
						cout << " --- MCtrk#" << imc
								<< " was defined as MISSED during trk-search (#MChits="
								<< MCtksREChits[imc] << " with limit>" << minHits << ")"
								<< endl;
						if (MCDoubleHits[imc] > 0)
							cout << "         NB:this MCtrk contains " << MCDoubleHits[imc]
									<< " double hits!" << endl;
					}
					trkQ = -1;
					nMCmissedTrkSearch++;
				} else { //missed due to small amount of hits
					if (MCtksREChits[imc] > 0) { // if MCtksREChits[imc]==0 trk is out of measurment range
						//	    if(MCtksREChits[imc]>0){// if MCtksREChits[imc]==0 trk is out of measurment range
						nMCmissedLossHits++;
						trkQ = -2;
						if (fVerbose > 7)
							cout << " --- MCtrk#" << imc
									<< " was defined as MISSED due to little amount of hits (#MChits="
									<< MCtksREChits[imc] << " with limit>" << minHits << ")"
									<< endl;
						int hitArr = -1;
						//     cout<<"nMCHits = "<<nMCHits<<endl;
						for (int imhc = 0; imhc < nMCHits; imhc++) {//find corresponding MC hit for this MC trk
							PndSdsMCPoint* MCPoint = (PndSdsMCPoint*) (fMCHits->At(imhc));
							int MCtrkID = MCPoint->GetTrackID();
							//	cout<<"MCtrkID = "<<MCtrkID<<" imc = "<<imc<<endl;
							if (MCtrkID == imc) {
								hitArr = imhc;
								break;
							}
						}
						if (hitArr > 0) {
							PndSdsMCPoint* MCPointHit = (PndSdsMCPoint*) (fMCHits->At(hitArr));
							TVector3 PosMClmd = MCPointHit->GetPosition();
							double pxTrue = MCPointHit->GetPx();
							double pyTrue = MCPointHit->GetPy();
							double pzTrue = MCPointHit->GetPz();
							TVector3 MomMClmd(pxTrue, pyTrue, pzTrue);
							glXmcLMD = PosMClmd.X();
							glYmcLMD = PosMClmd.Y();
							glZmcLMD = PosMClmd.Z();
							glThetamcLMD = MomMClmd.Theta();
							glPhimcLMD = MomMClmd.Phi();
							glMommcLMD = MomMClmd.Mag();
						} else {
							trkQ = -3;
							glXmcLMD = -9999;
							glYmcLMD = -9999;
							glZmcLMD = -9999;
							glThetamcLMD = -9999;
							glPhimcLMD = -9999;
							glMommcLMD = -9999;
						}
					} else {
						trkQ = -3;
						glXmcLMD = -9999;
						glYmcLMD = -9999;
						glZmcLMD = -9999;
						glThetamcLMD = -9999;
						glPhimcLMD = -9999;
						glMommcLMD = -9999;
					}
				}
				//	  cout<<"trk was marked ad missed, reason trkQ="<<trkQ<<endl;

				//Fill tree with rec vs. mc trk info for missed trks ------------------------------------------------
				glXrec = -9999;
				glYrec = -9999;
				glZrec = -9999;
				glThetarec = -9999;
				glPhirec = -9999;
				glXrecLMD = -9999;
				glYrecLMD = -9999;
				glZrecLMD = -9999;
				glThetarecLMD = -9999;
				glPhirecLMD = -9999;
				glMomrec = -9999;
				glchi2 = -9999;
				glTrkTime = -9999;
				trkRECStatus = trkQ;

				trkMCStatus = movID;
				glPDG = mctrk->GetPdgCode();
				//	  glEvTime = mctrk->GetStartTime();
				// if(movID<0) trkMCStatus=0;
				// if(movID>=0) trkMCStatus=+1;
				//	  tRECMCtrks->Fill();
				if (!fWriteAllMC && trkRECStatus == -3) {
				} else {
					TClonesArray& clref = *fTrackQ;
					Int_t size = clref.GetEntriesFast();
					PndLmdTrackQ *trkqlmd = new (clref[size]) PndLmdTrackQ(glMommc);
					trkqlmd->SetTrkRecStatus(trkRECStatus);
					trkqlmd->SetSecondary(trkMCStatus);
					trkqlmd->SetPDGcode(glPDG);
					trkqlmd->SetLMDpoint(glXrecLMD, glYrecLMD, glZrecLMD);
					trkqlmd->SetLMDdir(glThetarecLMD, glPhirecLMD);
					trkqlmd->SetLMDchi2(glchi2);
					trkqlmd->SetIPpoint(glXrec, glYrec, glZrec);
					trkqlmd->SetIPmom(glThetarec, glPhirec, glMomrec);
					trkqlmd->SetMCpoint(glXmc, glYmc, glZmc);
					trkqlmd->SetMCmom(glThetamc, glPhimc, glMommc);
					//   trkqlmd->SetSecondary(trkMCStatus);
					trkqlmd->SetIPerrpoint(-9999, -9999, -9999);
					trkqlmd->SetIPerrmom(-9999, -9999, -9999);
					trkqlmd->SetNumMChits(MCtksREChits[imc]);
					trkqlmd->SetNumDoubleMChits(MCDoubleHits[imc]);
					//    cout<<"glXmcLMD = "<<glXmcLMD<<endl;
					trkqlmd->SetMCpointLMD(glXmcLMD, glYmcLMD, glZmcLMD);
					trkqlmd->SetMCmomLMD(glThetamcLMD, glPhimcLMD, glMommcLMD);
					//    cout<<"glPhimcLMD = "<<glPhimcLMD<<endl;
					//	    trkqlmd->SetTotEvCharge(TotCharge);
					trkqlmd->SetSumEvPDG(sumID);
					trkqlmd->SetEvMCMulti(nParticles);
					trkqlmd->SetEvRECMulti(nGeaneTrks);
					trkqlmd->SetEvTime(glEvTime);
					trkqlmd->SetTrkTime(glTrkTime);
					trkqlmd->SetModule(glModule);
					trkqlmd->SetHalf(glHalf);
				}
				//(end) Fill tree with rec vs. mc trk info for missed trks ---------------------------------------
			}
		}
	}

	if (fVerbose > 2)
		cout << "PndLmdTrkQTask::Exec END!" << endl;
	fEventNr++;
}

void PndLmdTrkQTask::Finish() {
}
ClassImp(PndLmdTrkQTask);
