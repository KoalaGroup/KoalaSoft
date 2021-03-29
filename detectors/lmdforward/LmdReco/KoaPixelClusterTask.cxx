// -------------------------------------------------------------------------
// -----                KoaPixelClusterTasksource file             -----
// -------------------------------------------------------------------------

#include "KoaPixelClusterTask.h"
#include "KoaChargeWeightedPixelMapping.h"
#include "PndLmdContFact.h"
#include "KoaSimplePixelClusterFinder.h"
#include "PndSdsClusterPixel.h"
#include "PndSdsPixelDigiPar.h"

// FAIR
#include "FairBaseParSet.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "TLorentzVector.h"

// -----   Default constructor   -------------------------------------------
KoaPixelClusterTask::KoaPixelClusterTask()
    : PndSdsPixelClusterTask("LMD Clustertisation Task") {
  SetPersistency(kTRUE);
  // flagMS = true;
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
KoaPixelClusterTask::~KoaPixelClusterTask() {
	if (fBackMapping != 0)
		delete fBackMapping;
	if (fClusterFinder != 0)
		delete fClusterFinder;
	if (fFunctor != 0)
		delete fFunctor;

	if (fStartFunctor != 0)
		delete fStartFunctor;
	if (fGeoH != 0)
		delete fGeoH;
}
// -------------------------------------------------------------------------

InitStatus KoaPixelClusterTask::Init() {
	SetBranchNames();

	SetBackMapping();
	SetClusterFinder();

	FairRootManager* ioman = FairRootManager::Instance();

	if (!ioman) {
		std::cout << "-E- PndSdsPixelClusterTask::Init: " << "RootManager not instantiated!"
		        << std::endl;
		return kFATAL;
	}

	// Get input array
	fDigiArray = (TClonesArray*) ioman->GetObject(fInBranchName);
	//
	if (!fDigiArray) {
		std::cout << "-E- PndSdsPixelClusterTask::Init: " << "No SDSDigi array!" << std::endl;
		return kERROR;
	}

  fClusterArray = ioman->Register(fClustBranchName, "PndSdsClusterPixel",
                                  fFolderName, GetPersistency());

  fHitArray =
      ioman->Register(fOutBranchName, "PndSdsHit", fFolderName, GetPersistency());

	SetInBranchId();

	fFunctor = new TimeGap();
	fStartFunctor = new StopTime();

	if (fVerbose > 1)
		fDigiPar->Print();

	fGeoH->SetVerbose(fVerbose);

	std::cout << "-I- PndSdsPixelClusterTask: Initialisation successfull" << std::endl;
	return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Initialization  of Parameter Containers -------------------------
void KoaPixelClusterTask::SetParContainers() {
	std::cout << "KoaPixelClusterTask::SetParContainers() " << std::endl;
	// Get Base Container
	ana = FairRun::Instance();
	rtdb = ana->GetRuntimeDb();
	fDigiPar = (PndSdsPixelDigiPar*) (rtdb->getContainer("KOAPixelDigiPar"));
	//	rtdb->getContainer("SDSPixelTotDigiPar");

	PndLmdContFact* themdcontfact = (PndLmdContFact*) rtdb->getContFactory("PndLmdContFact");
	// read params for lumi alignment
	TList* theAlignLMDContNames = themdcontfact->GetAlignParNames();
	Info("SetParContainers()", "AlignLMD The container names list contains %i entries",
	        theAlignLMDContNames->GetEntries());
	TIter cfAlIter(theAlignLMDContNames);
	while (TObjString* contname = (TObjString*) cfAlIter()) {
		TString parsetname = contname->String();
		Info("SetParContainers()", "%s", parsetname.Data());
	}
	// //
	PndSdsPixelClusterTask::SetParContainers();
}

void KoaPixelClusterTask::SetBackMapping() {
	// at Init() stage we already have fGeoH filled with the parameters
	fBackMapping = new KoaChargeWeightedPixelMapping(fGeoH, fVerbose);
}

void KoaPixelClusterTask::SetClusterFinder() {
	std::cout << "KoaPixelClusterTask::SetClusterFinder() " << std::endl;
	fClusterFinder = new KoaSimplePixelClusterFinder(fVerbose);
}

// -----   Manula I/O folders/branches
// ----------------------------------------------------
void KoaPixelClusterTask::SetBranchNames(TString inBranchname, TString outHitBranchname,
        TString outClustBranchname, TString folderName) {
	fInBranchName = inBranchname;
	fOutBranchName = outHitBranchname;
	fClustBranchName = outClustBranchname;
	fFolderName = folderName;
}

// -----   Default I/O folder/branches
// ----------------------------------------------------
void KoaPixelClusterTask::SetBranchNames() {
  if (FairRunAna::Instance()->IsTimeStamp())
    fInBranchName = "KOALASortedPixelDigis";
  else
    fInBranchName = "KoalaPixelDigis";
  fOutBranchName = "KoalaHitsPixel";
  fClustBranchName = "KoalaPixelClusterCand";
  fFolderName = "pndsim";
}

// -----   Public method Exec   --------------------------------------------
void KoaPixelClusterTask::Exec(Option_t*) {
	// std::cout<<" fEventNr = "<< fEventNr<<std::endl;
	// Reset output array
	fClusterArray = FairRootManager::Instance()->GetTClonesArray(fClustBranchName);
	if (!fClusterArray)
		Fatal("Exec", "No ClusterArray");
	fClusterArray->Delete();

	fHitArray = FairRootManager::Instance()->GetTClonesArray(fOutBranchName);
	if (!fHitArray)
		Fatal("Exec", "No HitArray");
	fHitArray->Delete();

	std::vector<PndSdsDigiPixel> DigiPixelArray;
	DigiPixelArray.clear();

	Double_t EventTime = FairRootManager::Instance()->GetEventTime();

	if (fVerbose > 0)
		std::cout << "-I- PndSdsPixelClusterTask::Exec EventTime: " << EventTime << std::endl;

	// Get input array
	if (FairRunAna::Instance()->IsTimeStamp()) {
		fDigiArray->Clear();
		fDigiArray = FairRootManager::Instance()->GetData(fInBranchName, fStartFunctor, EventTime + 10);
	} else
		fDigiArray = (TClonesArray*) FairRootManager::Instance()->GetObject(fInBranchName);

	Int_t nPoints = fDigiArray->GetEntriesFast();

	// convert from TClonesArray to a std::vector
	for (Int_t iPoint = 0; iPoint < nPoints; iPoint++) {
		PndSdsDigiPixel myDigi = *(PndSdsDigiPixel*) (fDigiArray->At(iPoint));
		DigiPixelArray.push_back(myDigi);
		myDigi.Clear();
	}
	// Retrieve the calculated clusters with the chosen clusterfinder
	std::vector<std::vector<Int_t> > clusters = fClusterFinder->GetClusters(DigiPixelArray);
	if (fVerbose > 1)
		std::cout << " -I-  PndSdsPixelClusterTask::Exec(): We have " << clusters.size()
		        << " pixel clusters" << std::endl;
	// store the list
	for (UInt_t i = 0; i < clusters.size(); i++) {
		PndSdsClusterPixel* tempCluster = new ((*fClusterArray)[i]) PndSdsClusterPixel(fInBranchId,
		        clusters[i]);
		if (FairRunAna::Instance()->IsTimeStamp()) {
			tempCluster->ResetLinks();
			for (UInt_t j = 0; j < clusters[i].size(); j++) {
				PndSdsDigiPixel* tempDigi = (PndSdsDigiPixel*) fDigiArray->At(clusters[i][j]);
				tempCluster->AddLink(FairLink(tempDigi->GetEntryNr()));
				tempDigi->Clear();
			}
		}
	}

	// do the backmapping with charge-weight
	for (UInt_t i = 0; i < clusters.size(); i++) {
		//    if(fVerbose>2) std::cout << clusters[i].size() << " " << std::endl;
		std::vector<PndSdsDigiPixel> clusterArray;
		for (UInt_t j = 0; j < clusters[i].size(); j++) {  // convert
			clusterArray.push_back(DigiPixelArray[clusters[i][j]]);
		}

		// mapping with the choosen back mapping
		// Int_t iHits = fHitArray->GetEntriesFast(); //[R.K. 01/2017] unused
		// variable
		//      PndSdsHit *myHit = new((*fHitArray)[iHits])
		//      PndSdsHit(fBackMapping->GetCluster(clusterArray));
		PndSdsHit myHit = fBackMapping->GetCluster(clusterArray);
		clusterArray.clear();
		myHit.SetClusterIndex(fClusterType, i, 0, fEventNr);
		TVector3 hitPos = myHit.GetPosition();
		TMatrixD hitCov = myHit.GetCov();
		Double_t hitE = myHit.GetEloss();
		// hitCov(0,0) = 5.29e-06; //assuming hit resolution for x-y 23 mkm
		// hitCov(1,1) = 5.29e-06; //assuming hit resolution for x-y 23 mkm
		hitCov(0, 0) = 2.25e-06;  // assuming hit resolution for x-y 15 mkm
		hitCov(1, 1) = 2.25e-06;  // assuming hit resolution for x-y 15 mkm
		hitCov(2, 2) = 4.28489999999999954e-08;  // assuming hit resolution for z
		                                         // 2.07 mkm NB: isn't used in Trk
		                                         // rec.

		// //Add multiple scattering error ---------------
		// if(flagMS){
		// 	//	TVector3 hitPos = myHit.GetPosition();
		// 	TVector3
		// hitErr(sqrt(hitCov[0][0]),sqrt(hitCov[1][1]),sqrt(hitCov[2][2]));
		// 	TVector3 hitErrMSadd = AddMSErr(hitPos, hitErr);
		// 	hitCov[0][0] = TMath::Power(hitErrMSadd.X(),2);
		// 	hitCov[1][1] = TMath::Power(hitErrMSadd.Y(),2);
		// 	hitCov[2][2] = TMath::Power(hitErrMSadd.Z(),2);
		// }
		// cout<<"!!!!!!!!!"<<endl;
		// hitCov.Print();
		// cout<<"!!!!!!!!!"<<endl;
		myHit.SetCov(hitCov);  // save value
		myHit.SetDx(sqrt(hitCov[0][0]));
		myHit.SetDy(sqrt(hitCov[1][1]));
		myHit.SetDz(sqrt(hitCov[2][2]));

		if (fVerbose > 0) {
			std::cout << " -I-  PndSdsPixelClusterTask::Exec(): Calculated Hit(LUMI "
					"frame): " << std::endl;
			myHit.Print();
#if (ROOT_VERSION_CODE >= ROOT_VERSION(5, 34, 10))
			((FairMultiLinkedData_Interface) (myHit)).Print();
#else
			((FairMultiLinkedData)(myHit)).Print();
#endif
		}
		TClonesArray& clref = *fHitArray;
		Int_t size = clref.GetEntriesFast();
		new (clref[size]) PndSdsHit(myHit);  // PndSdsHit *freshHit =  //[R.K.03/2017] unused variable
		// myHit.Delete();
		//      myHit.Clear();
		//      std::cout<<"fHitArray.size() = "<<sizeof(*fHitArray)<<std::endl;
	}
	clusters.clear();
	DigiPixelArray.clear();
	if (fVerbose > 1)
		std::cout << std::endl;

	if (fVerbose > 1) {
		std::cout << "-I- KoaPixelClusterTask: " << fClusterArray->GetEntriesFast()
		        << " Sds Clusters and " << fHitArray->GetEntriesFast() << " Hits calculated."
		        << std::endl;
	}
	fEventNr++;
	fHitArray->Sort();

	// fDigiArray->Delete();

	// std::cout<<"lmddim.size() = "<<sizeof(*lmddim)<<std::endl;

	//  std::cout<<"DigiPixelArray.size() = "<<DigiPixelArray.size()<< std::endl;
	// FinishEvent();
	//  std::cout<<"size() = "<<sizeof(*this)<<std::endl;
	return;
}

void KoaPixelClusterTask::FinishEvent() {
	if (fDigiArray != NULL)
		fDigiArray->Delete();
	if (fHitArray != NULL)
		fHitArray->Delete();
	if (fClusterArray != NULL)
		fClusterArray->Delete();
	FinishEvents();
	// std::cout << "-I- KoaPixelClusterTask: FinishEvent()" << std::endl;
}

ClassImp(KoaPixelClusterTask);
