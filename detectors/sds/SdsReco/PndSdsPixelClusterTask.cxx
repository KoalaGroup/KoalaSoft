// -------------------------------------------------------------------------
// -----                PndSdsPixelClusterTasksource file             -----
// -------------------------------------------------------------------------


#include "TClonesArray.h"
#include "TArrayD.h"
#include "TGeoManager.h"

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairGeoNode.h"
#include "FairGeoVector.h"
#include "FairEventHeader.h"

#include "PndStringSeparator.h"

#include "PndSdsPixelClusterTask.h"
#include "PndSdsMCPoint.h"
#include "PndSdsCalcPixel.h"
//#include "PndSdsCalcFePixel.h"
#include "PndSdsDigiPixel.h"
// #include "PndSdsPixelCluster.h"
#include "PndSdsClusterPixel.h"
#include "PndGeoHandling.h"

#include "PndSdsSimplePixelClusterFinder.h"
#include "PndSdsChargeWeightedPixelMapping.h"
#include "PndSdsFESimple.h"

#if (ROOT_VERSION_CODE >= ROOT_VERSION(5,34,10))
  #include "FairMultiLinkedData_Interface.h"
#endif

// -----   Default constructor   -------------------------------------------
PndSdsPixelClusterTask::PndSdsPixelClusterTask() :
PndSdsTask("SDS Clustertisation Task"),
      fUseNoiseSuppression(kTRUE),
      fFEModel(NULL),
      fDigiArray(NULL),
      fDigiPar(NULL),
      fChargeConverter(NULL),
      fGeoH(NULL),
      fClustBranchName(""),
      fClusterArray(NULL),
      fHitArray(NULL),
      fEventHeader(0),
      fFunctor(NULL),
      fStartFunctor(NULL), 
      fClusterType(-1),
      fEventNr(0),
      fClusterFinder(NULL),
      fBackMapping(NULL)
{
	SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------

// -----   Named constructor   ---------------------------------------------
PndSdsPixelClusterTask::PndSdsPixelClusterTask(const char* name) :
PndSdsTask(name),
      fUseNoiseSuppression(kTRUE),
      fFEModel(NULL),
      fDigiArray(NULL),
      fDigiPar(NULL),
      fChargeConverter(NULL),
      fGeoH(NULL),
      fClustBranchName(""),
      fClusterArray(NULL),
      fHitArray(NULL),
      fEventHeader(0),
      fFunctor(NULL),
      fStartFunctor(NULL), 
      fClusterType(-1),
      fEventNr(0),
      fClusterFinder(NULL),
      fBackMapping(NULL)
{
	SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
PndSdsPixelClusterTask::~PndSdsPixelClusterTask()
{
	if (fBackMapping != 0) delete fBackMapping;
	if (fClusterFinder != 0) delete fClusterFinder;
	if (fFunctor != 0) delete fFunctor;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PndSdsPixelClusterTask::InitMQ(TList* tempList) {
  LOG(INFO) << "********************************************** PixelFindHits::InitMQ()" << FairLogger::endl;
//  fDigiPar = (PndSdsPixelDigiPar*)tempList->FindObject(fParName.Data());

  fHitArray = new TClonesArray("PndSdsHit",10000);
  fHitArray->SetName("MVDHitsPixel");
  fClusterArray = new TClonesArray("PndSdsClusterPixel", 10000);
  fClusterArray->SetName("MVDPixelCluster");

  SetClusterFinderMQ(tempList);
  SetBackMappingMQ(tempList);

  return;
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void   PndSdsPixelClusterTask::ExecMQ(TList* inputList,TList* outputList) {
  //  LOG(INFO) << "********************************************** PixelFindHits::ExecMQ(" << inputList->GetName() << "," << outputList->GetName() << "), Event " << fTNofEvents << FairLogger::endl;
  //  LOG(INFO) << "********************************************** PixelFindHits::ExecMQ(), Event " << fTNofEvents << FairLogger::endl;
//  inputList->Print();
  fDigiArray = (TClonesArray*) inputList->FindObject("PndSdsDigiPixels");
  fEventHeader = (FairEventHeader*) inputList->FindObject("EventHeader.");
  LOG(INFO) << "DigiArray: " << fDigiArray->GetEntriesFast() << FairLogger::endl;


  outputList->Add(fClusterArray);
  outputList->Add(fHitArray);
  Exec("");
  return;
}
// -------------------------------------------------------------------------

void PndSdsPixelClusterTask::GetParList(TList* ) {  //tempList //[R.K.03/2017] unused variable(s)
}

// -----   Initialization  of Parameter Containers -------------------------
void PndSdsPixelClusterTask::SetParContainers()
{
  if ( fGeoH == NULL ) {
    fGeoH = PndGeoHandling::Instance();
  }
  fGeoH->SetParContainers();
  if( ! fDigiPar) Fatal("SetParContainers","No digitization parameters specified");
  if(fVerbose>1) Info("SetParContainers","done.");
  return;
}


// -----   Initialization  of Parameter Containers -------------------------

InitStatus PndSdsPixelClusterTask::ReInit()
{
  
  /*
   FairRun* ana = FairRun::Instance();
   FairRuntimeDb* rtdb=ana->GetRuntimeDb();
   fGeoPar=(PndSdsGeoPar*)(rtdb->getContainer("PndSdsGeoPar"));
   
   return kSUCCESS;
   */
  
  return kSUCCESS; // TODO: Fill in sense here...
}

// -----   Public method Init   --------------------------------------------
InitStatus PndSdsPixelClusterTask::Init()
{
  SetBranchNames();

  SetBackMapping();
  SetClusterFinder();
  
  FairRootManager* ioman = FairRootManager::Instance();
  
  if ( ! ioman )
  {
    std::cout << "-E- PndSdsPixelClusterTask::Init: "
    << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }
  

  // Get input array
  fDigiArray = (TClonesArray*) ioman->GetObject(fInBranchName);
//
  if ( ! fDigiArray )
  {
    std::cout << "-E- PndSdsPixelClusterTask::Init: "
    << "No SDSDigi array!" << std::endl;
    return kERROR;
  }
  
  fClusterArray = ioman->Register(fClustBranchName, "PndSdsClusterPixel", fFolderName, GetPersistency());

  fHitArray =  ioman->Register(fOutBranchName, "PndSdsHit", fFolderName, GetPersistency());
  
  SetInBranchId();

  fFunctor = new TimeGap();
  fStartFunctor = new StopTime();
//  fFEModel = new PndSdsFESimple();


  if(fVerbose>1) fDigiPar->Print();
  
  std::cout << "-I- PndSdsPixelClusterTask: Initialisation successfull" << std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------



// -----   Public method Exec   --------------------------------------------
void PndSdsPixelClusterTask::Exec(Option_t*)
{
  std::vector<PndSdsDigiPixel> DigiPixelArray;
//  // Reset output array
  if ( ! fClusterArray ) Fatal("Exec", "No ClusterArray");

  fGeoH->SetVerbose(fVerbose);

  //Double_t eventTime = 0; //[R.K. 01/2017] unused variable
  Int_t entryNumber = -1;
  if (fEventHeader != 0){
	  //eventTime = fEventHeader->GetEventTime(); //[R.K. 01/2017] unused variable
	  entryNumber = fEventHeader->GetMCEntryNumber();
  }
  else {
	  //eventTime = FairRootManager::Instance()->GetEventTime(); //[R.K. 01/2017] unused variable
	  entryNumber = FairRootManager::Instance()->GetEntryNr();
  }

//   if(fVerbose>0)
//	   std::cout << "-I- PndSdsPixelClusterTask::Exec EventNumber: " << fEventNr << " EventTime: " <<  EventTime << std::endl;

    if (FairRunAna::Instance() != 0 && FairRunAna::Instance()->IsTimeStamp()){
    	if(fVerbose>0)  std::cout << "TimeStepPixel: " << fDigiPar->GetTimeStep();
    	fDigiArray = FairRootManager::Instance()->GetData(fInBranchName, fFunctor, fDigiPar->GetTimeStep() * 2);
    }

  if ( ! fHitArray ) Fatal("Exec", "No HitArray");

  //Int_t nPoints = fDigiArray->GetEntriesFast();
//  if (fVerbose > 1)
//	  std::cout << "Points in DigiArray: " << nPoints << std::endl;

  // convert from TClonesArray to a std::vector

  DigiPixelArray = ConvertAndFilter(fDigiArray);

  // Retrieve the calculated clusters with the chosen clusterfinder
  std::vector< std::vector< Int_t> > clusters = fClusterFinder->GetClusters(DigiPixelArray);
//  if(fVerbose>1)
//	  std::cout << " -I-  PndSdsPixelClusterTask::Exec(): We have "<<clusters.size()<<" pixel clusters" << std::endl;

  // Get rid of noise hits with a single digi in cluster and minimum charge
  if (fUseNoiseSuppression) {
	  UInt_t clusterSize = clusters.size();
	  for (UInt_t i = 0 ; i < clusterSize; i++)
	  {
		  if (clusters[i].size() == 1){
			  PndSdsDigiPixel tempDigi = DigiPixelArray[clusters[i][0]];
			  if (tempDigi.GetCharge() < 40){
				  if (fVerbose > 2) std::cout << "-I-  PndSdsPixelClusterTask::Exec():Erased cluster with digi " << tempDigi << std::endl;
				  clusters.erase(clusters.begin() + i);
				  i--;
				  clusterSize = clusters.size();
			  }
		  }
	  }
  }

  // store the list
  if(fVerbose > 2) std::cout << "Cluster Size after Erase: " << clusters.size() << std::endl;
  for (UInt_t i = 0; i < clusters.size(); i++)
  {

    PndSdsClusterPixel* tempCluster = new((*fClusterArray)[i]) PndSdsClusterPixel(fInBranchId, clusters[i]);

    if (FairRunAna::Instance() != 0 && FairRunAna::Instance()->IsTimeStamp()){
		tempCluster->ResetLinks();
		for (UInt_t j = 0; j < clusters[i].size(); j++){
			PndSdsDigiPixel* tempDigi = (PndSdsDigiPixel*)fDigiArray->At(clusters[i][j]);
			tempCluster->AddInterfaceData(tempDigi);
		}
    }

    std::vector<PndSdsDigiPixel> clusterArray;
	for (UInt_t j=0;j < clusters[i].size();j++)
	{ // convert
	  clusterArray.push_back(DigiPixelArray[clusters[i][j]]);
	}

	// mapping with the chosen back mapping
	PndSdsHit myHit = fBackMapping->GetCluster(clusterArray);
	myHit.SetClusterIndex(fClusterType,i, -1, entryNumber);

 //   myHit.SetCharge(myHit.GetCharge());
//	if(fVerbose>0){
//	  std::cout << " -I-  PndSdsPixelClusterTask::Exec(): Calculated Hit: " << std::endl;
//	  myHit.Print();
//#if (ROOT_VERSION_CODE >= ROOT_VERSION(5,34,10))
//	  ((FairMultiLinkedData_Interface)(myHit)).Print();
//#else
//	  ((FairMultiLinkedData)(myHit)).Print();
//#endif
//	}
	new ((*fHitArray)[i]) PndSdsHit(myHit);
  }



  if(fVerbose>1)std::cout << std::endl;

  if(fVerbose>1){
    std::cout << "-I- PndSdsPixelClusterTask: " << fClusterArray->GetEntriesFast()
    << " Sds Clusters and " << fHitArray->GetEntriesFast()<<" Hits calculated." << std::endl;
  }
  fEventNr++;
  fHitArray->Sort();
  return;
  
}

std::vector<PndSdsDigiPixel> PndSdsPixelClusterTask::ConvertAndFilter(TClonesArray* digidata)
{
	std::vector<PndSdsDigiPixel> result;
	for (Int_t iPoint = 0; iPoint < digidata->GetEntriesFast(); iPoint++){				// Just conversion
		PndSdsDigiPixel myDigi = *(PndSdsDigiPixel*)(digidata->At(iPoint));
		result.push_back(myDigi);
	}
	return result;
}

void PndSdsPixelClusterTask::FinishEvent(){

	if (fDigiArray != NULL) 	fDigiArray->Delete();
	if (fHitArray != NULL) 		fHitArray->Delete();
	if (fClusterArray != NULL) 	fClusterArray->Delete();
}

ClassImp(PndSdsPixelClusterTask);

