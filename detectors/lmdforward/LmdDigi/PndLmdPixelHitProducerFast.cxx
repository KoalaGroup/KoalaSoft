// -------------------------------------------------------------------------
// -----               PndLmdPixelHitProducerFast source file             -----
// -------------------------------------------------------------------------


#include "TClonesArray.h"
#include "TMath.h"

#include "FairRootManager.h"
#include "PndLmdPixelHitProducerFast.h"
#include "PndSdsHit.h"
#include "PndSdsMCPoint.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"


// -----   Default constructor   -------------------------------------------
PndLmdPixelHitProducerFast::PndLmdPixelHitProducerFast() :
PndSdsTask("Fast LMD Hit Producer")
{
  fPixelSizeX=0.005; //to round MC-Hit x-position
  fPixelSizeY=0.005; //to round MC-Hit y-position
  SetPersistency(kTRUE);
}

PndLmdPixelHitProducerFast::PndLmdPixelHitProducerFast(Double_t pixelx, Double_t pixely) :
PndSdsTask("Fast LMD Hit Producer"), fPixelSizeX(pixelx), fPixelSizeY(pixely)
{
	SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------

// -----   Named constructor   -------------------------------------------
PndLmdPixelHitProducerFast::PndLmdPixelHitProducerFast(const char* name) :
PndSdsTask(name)
{
  fPixelSizeX=0.005; //to round MC-Hit x-position
  fPixelSizeY=0.005; //to round MC-Hit y-position
  SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndLmdPixelHitProducerFast::~PndLmdPixelHitProducerFast()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdPixelHitProducerFast::Init()
{
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();

  SetBranchNames();

  if ( ! ioman )
    {
      std::cout << "-E- PndLmdPixelHitProducerFast::Init: "
	   << "RootManager not instantiated!" << std::endl;
      return kFATAL;
    }

  // Get input array
  fPointArray = (TClonesArray*) ioman->GetObject(fInBranchName);

  if ( ! fPointArray )
    {
      std::cout << "-W- PndLmdPixelHitProducerFast::Init: "
	   << "No SDSPoint array!" << std::endl;
      return kERROR;
  }


  // Create and register output array
  fHitArray = new TClonesArray("PndSdsHit");
  ioman->Register(fOutBranchName, fFolderName, fHitArray, GetPersistency());

  std::cout << "-I- PndLmdPixelHitProducerFast: Intialisation successfull" << std::endl;
  return kSUCCESS;
}
// -------------------------------------------------------------------------
void PndLmdPixelHitProducerFast::SetParContainers()
{
  // Get Base Container
  //FairRun* ana = FairRun::Instance();
  //FairRuntimeDb* rtdb=ana->GetRuntimeDb();
 // fGeoPar = (PndSdsGeoPar*)(rtdb->getContainer("PndSdsGeoPar"));

}

void PndLmdPixelHitProducerFast::SetBranchNames(TString inBranchname, TString outBranchname, TString folderName)
{
  fInBranchName = inBranchname;
  fOutBranchName = outBranchname;
  fFolderName = folderName;
}


void PndLmdPixelHitProducerFast::SetBranchNames()
{
  fInBranchName = "LMDPoint";
  fOutBranchName = "LMDHit";
  fFolderName = "PndLmd";
}


// -----   Public method Exec   --------------------------------------------
void PndLmdPixelHitProducerFast::Exec(Option_t*)
{
  // Reset output array
  if ( ! fHitArray )
    Fatal("Exec", "No HitArray");

  fHitArray->Delete();

  // Declare some variables
  PndSdsMCPoint *point = 0;

  Int_t
    detID = 0;       // Detector ID
    //trackID = 0;     // Track index //[R.K.03/2017] unused variable

  TVector3
    pos, dpos;       // Position and error vectors

  // Loop over PndSdsMCPoints
  Int_t
    nPoints = fPointArray->GetEntriesFast();

  for (Int_t iPoint = 0; iPoint < nPoints; iPoint++)
    {
      point = (PndSdsMCPoint*) fPointArray->At(iPoint);
	//std::cout << " Fast Hit Producer -Point-: " << point << std::endl;
      if ( ! point)
	continue;

      // Detector ID
      detID = point->GetDetectorID();

      // MCTrack ID
      //trackID = point->GetTrackID(); //[R.K.03/2017] unused variable

     TVector3
	position(fPixelSizeX*TMath::Nint(point->GetX()/fPixelSizeX), fPixelSizeY*TMath::Nint(point->GetY()/fPixelSizeY), point->GetZ());
	dpos.SetXYZ(0.005,0.005,0.005);


      // Create new hit
      PndSdsHit* myHit = new ((*fHitArray)[iPoint]) PndSdsHit(detID, point->GetSensorID(), position, dpos, -1, point->GetEnergyLoss(),1, iPoint);
      myHit->SetClusterIndex(fInBranchId, iPoint);
     // 	std::cout << "Hit created for module: " << point->GetDetName() << std::endl;



    }   // Loop over MCPoints

  // Event summary
  //std::cout << "-I- PndLmdPixelHitProducerFast: " << nPoints << " PndSdsMCPoints, "
  //     << nPoints << " Hits created." << std::endl;

}
// -------------------------------------------------------------------------


ClassImp(PndLmdPixelHitProducerFast)
