// -------------------------------------------------------------------------
// -----               PndSdsHitProducerIdeal source file             -----
// -------------------------------------------------------------------------


#include "TClonesArray.h"

#include "FairRootManager.h"
#include "PndSdsHitProducerIdeal.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"


// -----   Default constructor   -------------------------------------------
PndSdsHitProducerIdeal::PndSdsHitProducerIdeal() :
PndSdsTask("Ideal SDS Hit Producer"),
fPointArray(NULL),
fHitArray(NULL)
{
	SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------

// -----   Named constructor   -------------------------------------------
PndSdsHitProducerIdeal::PndSdsHitProducerIdeal(const char* name) :
PndSdsTask(name),
fPointArray(),
fHitArray()
{
	SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndSdsHitProducerIdeal::~PndSdsHitProducerIdeal()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus PndSdsHitProducerIdeal::Init()
{
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();

  SetBranchNames();

  if ( ! ioman )
    {
      std::cout << "-E- PndSdsHitProducerIdeal::Init: "
	   << "RootManager not instantiated!" << std::endl;
      return kFATAL;
    }

  // Get input array
  fPointArray = (TClonesArray*) ioman->GetObject(fInBranchName);

  if ( ! fPointArray )
    {
      std::cout << "-W- PndSdsHitProducerIdeal::Init: "
	   << "No SDSPoint array!" << std::endl;
      return kERROR;
  }


  // Create and register output array
  fHitArray = new TClonesArray("PndSdsHit");
  ioman->Register(fOutBranchName, fFolderName, fHitArray, GetPersistency());

  std::cout << "-I- PndSdsHitProducerIdeal: Intialisation successfull" << std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndSdsHitProducerIdeal::SetParContainers()
{
  // Get Base Container
  //FairRun* ana = FairRun::Instance();
  //FairRuntimeDb* rtdb=ana->GetRuntimeDb();
 // fGeoPar = (PndSdsGeoPar*)(rtdb->getContainer("PndSdsGeoPar"));

}


// -----   Public method Exec   --------------------------------------------
void PndSdsHitProducerIdeal::Exec(Option_t*)
{
  // Reset output array
  if ( ! fHitArray )
    Fatal("Exec", "No HitArray");

  fHitArray->Delete();

  // Declare some variables
  PndSdsMCPoint *point = 0;

  Int_t
    detID = 0;      // Detector ID
    //trackID = 0;     // Track index //[R.K. 01/2017] unused variable

  TVector3
    pos, dpos;       // Position and error vectors

  // Loop over PndSdsMCPoints
  Int_t
    nPoints = fPointArray->GetEntriesFast();

  for (Int_t iPoint = 0; iPoint < nPoints; iPoint++)
    {
      point = (PndSdsMCPoint*) fPointArray->At(iPoint);
//	std::cout << " Ideal Hit Producer -Point-: " << point << std::endl;
      if ( ! point)
	continue;

      // Detector ID
      detID = point->GetDetectorID();

      // MCTrack ID
      //trackID = point->GetTrackID(); //[R.K. 01/2017] unused variable

     TVector3
	position(point->GetX(), point->GetY(), point->GetZ());
	dpos.SetXYZ(0.005,0.005,0.005);


      // Create new hit
      PndSdsHit* myHit = new ((*fHitArray)[iPoint]) PndSdsHit(detID, point->GetSensorID(), position, dpos, -1, point->GetEnergyLoss(),1, iPoint);
      myHit->SetClusterIndex(fInBranchId, iPoint);
      //	std::cout << "Hit created for module: " << point->GetDetName() << std::endl;



    }   // Loop over MCPoints

  // Event summary
//  std::cout << "-I- PndSdsHitProducerIdeal: " << nPoints << " PndSdsMCPoints, "
 //      << nPoints << " Hits created." << std::endl;

}
// -------------------------------------------------------------------------


ClassImp(PndSdsHitProducerIdeal)
