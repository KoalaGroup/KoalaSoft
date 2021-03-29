// -------------------------------------------------------------------------
// -----                LumiHybridHitProducer source file             -----
// -------------------------------------------------------------------------


#include "LumiHybridHitProducer.h"
#include "PndSdsPixelDigiPar.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsIdealChargeConversion.h"
#include "FairRuntimeDb.h"
#include "FairRun.h"

// -----   Default constructor   -------------------------------------------
LumiHybridHitProducer::LumiHybridHitProducer() :
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
LumiHybridHitProducer::~LumiHybridHitProducer()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus LumiHybridHitProducer::Init()
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
void LumiHybridHitProducer::SetParContainers()
{
  // called before Init()
  // Get Base Container
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  fDigiPar = (PndSdsPixelDigiPar*)(rtdb->getContainer("SDSPixelDigiPar"));
  // fTotDigiPar = (PndSdsTotDigiPar*)(rtdb->getContainer("SDSPixelTotDigiPar"));
  PndSdsHybridHitProducer::SetParContainers();
}

// -------------------------------------------------------------------------
void LumiHybridHitProducer::SetBranchNames(TString inBranchname, TString outBranchname, TString folderName)
{
  fInBranchName = inBranchname;
  fOutBranchName = outBranchname;
  fFolderName = folderName;
  SetInBranchId();
}

// -------------------------------------------------------------------------
void LumiHybridHitProducer::SetBranchNames()
{
  if(fVerbose>1) Info("SetBranchNames","Set Lmd Pixel names.");
  fInBranchName = "KoalaLMDPoint";
  fOutBranchName = "LMDPixelDigis";
  fFolderName = "pndsim";
  SetInBranchId();
}

ClassImp(LumiHybridHitProducer);
