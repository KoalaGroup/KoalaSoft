// -------------------------------------------------------------------------
// -----                PndLmdHybridHitProducer source file             -----
// -------------------------------------------------------------------------


#include "PndLmdHybridHitProducer.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsIdealChargeConversion.h"
#include "FairRuntimeDb.h"
#include "FairRun.h"

// -----   Default constructor   -------------------------------------------
PndLmdHybridHitProducer::PndLmdHybridHitProducer() :
  PndSdsHybridHitProducer("LMD Hybrid Hit Producer")
{
  fPixelHits = 0;
  fEventNr = 0;
  fOverwriteParams = kFALSE;
  fPersistance = kTRUE;
  fDigiPixelMCInfo = kFALSE;
  if(fVerbose>2) std::cout << "LMD Hybrid Digi Producer created, Parameters will be taken from RTDB" << std::endl;

}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
PndLmdHybridHitProducer::~PndLmdHybridHitProducer()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus PndLmdHybridHitProducer::Init()
{
	InitStatus status = PndSdsHybridHitProducer::Init();
	if (fDigiPar->GetChargeConvMethod() == 0){
		if(fVerbose>0) Info("Init()","ideal charge conversion");
		fChargeConverter = new PndSdsIdealChargeConversion(fDigiPar->GetNoise());
	}
	else if (fDigiPar->GetChargeConvMethod() == 1){
		if(fVerbose>0) Info("Init()","use TOT charge conversion");
		fChargeConverter = new PndSdsTotChargeConversion(
			fTotDigiPar->GetChargingTime(),
			fTotDigiPar->GetConstCurrent(),
			fDigiPar->GetThreshold(),
			fTotDigiPar->GetClockFrequency(),
			fVerbose);
	}
	else Fatal ("Init()","charge conversion method not defined!");
	if(fVerbose>0) Info("Init","Intialisation successfull");
	return status;
}

// -----   Initialization  of Parameter Containers -------------------------
void PndLmdHybridHitProducer::SetParContainers()
{
  // called before Init()
  // Get Base Container
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  fDigiPar = (PndSdsPixelDigiPar*)(rtdb->getContainer("LMDPixelDigiPar"));
  // fTotDigiPar = (PndSdsTotDigiPar*)(rtdb->getContainer("SDSPixelTotDigiPar"));
  PndSdsHybridHitProducer::SetParContainers();
}

// -------------------------------------------------------------------------
void PndLmdHybridHitProducer::SetBranchNames(TString inBranchname, TString outBranchname, TString folderName)
{
  fInBranchName = inBranchname;
  fOutBranchName = outBranchname;
  fFolderName = folderName;
  SetInBranchId();
}

// -------------------------------------------------------------------------
void PndLmdHybridHitProducer::SetBranchNames()
{
  if(fVerbose>1) Info("SetBranchNames","Set Lmd Pixel names.");
  fInBranchName = "LMDPoint";
  fOutBranchName = "LMDPixelDigis";
  fFolderName = "pndsim";
  SetInBranchId();
}

ClassImp(PndLmdHybridHitProducer);
