// -------------------------------------------------------------------------
// -----                PndSdsIdealClusterTask source file             -----
// -------------------------------------------------------------------------


#include "TClonesArray.h"
#include "TArrayD.h"
#include "TGeoManager.h"

#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairGeoNode.h"
#include "FairGeoVector.h"

#include "PndStringSeparator.h"

#include "PndSdsIdealClusterTask.h"
#include "PndSdsMCPoint.h"
// #include "PndSdsHit.h"
#include "PndSdsCalcPixel.h"
//#include "PndSdsCalcFePixel.h"
#include "PndSdsDigiPixel.h"
// #include "PndSdsPixelCluster.h"
#include "PndSdsClusterPixel.h"


// -----   Default constructor   -------------------------------------------
PndSdsIdealClusterTask::PndSdsIdealClusterTask() :
  PndSdsTask("SDS Clustertisation Task"),
      fDigiArray(NULL),
      fClustBranchName(""),
      fClusterType(-1),
      fClusterArray(NULL),
      fHitArray(NULL),
      fGeoH(PndGeoHandling::Instance()),
      fRadius(0),
      fFEcolumns(0),
      fFErows(0),
      fGeoFile(""),
      finder(NULL),
      mapping(NULL)
{
  //TGeoManager* geoMan;// = new TGeoManager("geoMan","geoMan");
  //geoMan = gGeoManager;
  //fGeoH = PndGeoHandling::Instance();
	SetPersistency(kTRUE);
}

PndSdsIdealClusterTask::PndSdsIdealClusterTask(Double_t radius, Int_t FEcolumns, Int_t FErows, TString geoFile) :
  PndSdsTask("SDS Clustertisation Task"),
      fDigiArray(NULL),
      fClustBranchName(""),
      fClusterType(-1),
      fClusterArray(NULL),
      fHitArray(NULL),
      fGeoH(PndGeoHandling::Instance()),
      fRadius(radius),
      fFEcolumns(FEcolumns),
      fFErows(FErows),
      fGeoFile(geoFile),
      finder(NULL),
      mapping(NULL)
{
  //TGeoManager* geoMan;// = new TGeoManager("geoMan","geoMan");
  //geoMan = gGeoManager;
  //fGeoH = PndGeoHandling::Instance();
	SetPersistency(kTRUE);
}

// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
PndSdsIdealClusterTask::~PndSdsIdealClusterTask()
{
}
// -------------------------------------------------------------------------

// -----   Initialization  of Parameter Containers -------------------------
void PndSdsIdealClusterTask::SetParContainers()
{
	fGeoH->SetParContainers();
}

InitStatus PndSdsIdealClusterTask::ReInit()
{
  InitStatus stat=kSUCCESS; //kERROR;
  return stat;
}

// -----   Public method Init   --------------------------------------------
InitStatus PndSdsIdealClusterTask::Init()
{

  SetBranchNames();
  SetInBranchId();

  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman )
    {
      std::cout << "-E- PndSdsIdealClusterTask::Init: "
     << "RootManager not instantiated!" << std::endl;
      return kFATAL;
    }

  // Get input array
  fDigiArray = (TClonesArray*) ioman->GetObject(fInBranchName);

  if ( ! fDigiArray )
    {
      std::cout << "-W- PndSdsIdealClusterTask::Init: "
     << "No SDSDigi array!" << std::endl;
      return kERROR;
  }

  fClusterArray = new TClonesArray("PndSdsClusterPixel");
  ioman->Register(fClustBranchName, fFolderName, fClusterArray, GetPersistency());

  fHitArray = new TClonesArray("PndSdsHit");
  ioman->Register(fOutBranchName , fFolderName, fHitArray, GetPersistency());

  mapping = new PndSdsChargeWeightedPixelMapping(fGeoH);
  finder = new PndSdsIdealPixelClusterFinder();
  mapping->SetVerbose(fVerbose);
  finder->SetVerbose(fVerbose);

  std::cout << "-I- PndSdsIdealClusterTask: Initialisation successfull" << std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------



// -----   Public method Exec   --------------------------------------------
void PndSdsIdealClusterTask::Exec(Option_t*)
{
  std::vector<PndSdsDigiPixel> DigiPixelArray;
  // Reset output array
  if ( ! fClusterArray )
    Fatal("Exec", "No ClusterArray");
  fClusterArray->Delete();

  if ( ! fHitArray )
    Fatal("Exec", "No HitArray");
  fHitArray->Delete();

  Int_t
    nPoints = fDigiArray->GetEntriesFast();

  for (Int_t iPoint = 0; iPoint < nPoints; iPoint++){
	PndSdsDigiPixel myDigi = *(PndSdsDigiPixel*)(fDigiArray->At(iPoint));
	DigiPixelArray.push_back(myDigi);
  }

  std::vector< std::vector< Int_t> > clusters = finder->GetClusters(DigiPixelArray);
  std::cout << clusters.size() << std::endl;
  for (UInt_t i = 0; i < clusters.size(); i++)
  {
	new((*fClusterArray)[i]) PndSdsClusterPixel(fClusterType, clusters[i]);
  }

 for (UInt_t i = 0; i < clusters.size(); i++){
	std::cout << clusters[i].size() << " " << std::endl;
	std::vector<PndSdsDigiPixel> clusterArray;
	for (UInt_t j=0;j < clusters[i].size();j++)
		clusterArray.push_back(DigiPixelArray[clusters[i][j]]);
	PndSdsHit myCluster = mapping->GetCluster(clusterArray);
	myCluster.SetClusterIndex(FairRootManager::Instance()->GetBranchId(fClustBranchName), i);
	std::cout << "ClusterData: " << std::endl;
	myCluster.Print();
	new ((*fHitArray)[i]) PndSdsHit(myCluster);
  }
  std::cout << std::endl;

  return;

}

ClassImp(PndSdsIdealClusterTask);

