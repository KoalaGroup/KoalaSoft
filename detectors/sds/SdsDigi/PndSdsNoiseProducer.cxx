// -------------------------------------------------------------------------
// -----                PndSdsNoiseProducer source file                -----
// -----                  Created 01.07.08  by R.Kliemt                -----
// -------------------------------------------------------------------------


#include "TClonesArray.h"
#include "TGeoNode.h"

#include "FairRootManager.h"
#include "FairGeoVolume.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairGeoNode.h"
#include "FairMCEventHeader.h"

#include "PndSdsNoiseProducer.h"
#include "PndSdsMCPoint.h"
#include "PndSdsDigiPixel.h"

#include "KoaDetectorList.h"

// -----   Default constructor   -------------------------------------------
PndSdsNoiseProducer::PndSdsNoiseProducer() :
PndSdsTask("Charge Noise Producer"),
fBranchNameStrip(""),
fBranchNamePixel(""),
fDigiStripArray(NULL),
fDigiPixelArray(NULL),
fDigiParRect(NULL),
fDigiParTrap(NULL),
fDigiParPix(NULL),
fMCPointType(), // Not used???
fGeoH(NULL),
fPixelIds4(),
fPixelIds6(),
fPixelIds8(),
fPixelIds12(),
fStripRectIds(),
fStripTrapIds(),
fNoiseSpread(0),
fThreshold(0),
fIonizationEnergy(1.)
{
	SetPersistency(kTRUE);
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
PndSdsNoiseProducer::~PndSdsNoiseProducer()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus PndSdsNoiseProducer::Init()
{
  SetBranchNames();
  
  // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  
  if ( ! ioman )
  {
    std::cout << "-E- PndSdsNoiseProducer::Init: RootManager not instantiated!" << std::endl;
    return kFATAL;
  }
  
  // Get input array
  fDigiStripArray = FairRootManager::Instance()->GetTClonesArray(fBranchNameStrip);
  if ( ! fDigiStripArray )  {
    std::cout << "-W- PndSdsNoiseProducer::Init: No "<<fBranchNameStrip<<" array!" << std::endl;
    std::cout << "    Create a new one." << std::endl;
    ioman->Register(fBranchNameStrip, "PndSdsDigiStrip", fFolderName, GetPersistency());
  }
  
  fDigiPixelArray = FairRootManager::Instance()->GetTClonesArray(fBranchNamePixel);
  if ( ! fDigiPixelArray )     {
    std::cout << "-W- PndSdsNoiseProducer::Init: No "<<fBranchNamePixel<<" array!" << std::endl;
    std::cout << "    Create a new one." << std::endl;
    ioman->Register(fBranchNamePixel, "PndSdsDigiPixel", fFolderName, GetPersistency());
  }
  
  
  // Retrieve a map between the active geometry nodes and their interpretation
  //  TGeoNode* topnode = gGeoManager->GetTopNode();
  //  for (Int_t n=0; n<topnode->GetNdaughters();n++)
  //  {
  //    gGeoManager->CdDown(n);
  //    TGeoNode* node = gGeoManager->GetCurrentNode();
  //    TString nodeName = node->GetName();
  //    if(nodeName.BeginsWith(fFolderName))
  //    {
  //      DiveDownNode(node);
  //      break;
  //    }
  //    gGeoManager->CdUp();
  //  }
  
  FillSensorLists();
  if(fVerbose>1)
  {
    std::cout <<"-I- PndSdsNoiseProducer: Registered Sensors: "
    <<fStripRectIds.size()<<"xStripRect "
    <<fStripTrapIds.size()<<"xStripTrap "
    <<fPixelIds4.size()<<"xPixel"
    <<std::endl;
  }
  std::cout << "-I- PndSdsNoiseProducer: Intialisation successfull" << std::endl;
  
  
  return kSUCCESS;
  
}

void PndSdsNoiseProducer::FillSensorLists()
{
	TObjArray* sensorNames = fGeoH->GetSensorNames();
	for (int i = 0; i < sensorNames->GetEntries(); i++){
		TString volname = ((TObjString*)(sensorNames->At(i)))->GetString();
		if(volname.Contains("Active"))
		{
		  if(volname.Contains("Rect")) fStripRectIds.push_back(i);
		  if(volname.Contains("Trap")) fStripTrapIds.push_back(i);
		  if(volname.Contains("Pixel"))
		  {
        if(volname.Contains("4x1")) fPixelIds4.push_back(i);
        if(volname.Contains("6x1")) fPixelIds6.push_back(i);
        if(volname.Contains("4x2")) fPixelIds8.push_back(i);
        if(volname.Contains("6x2")) fPixelIds12.push_back(i);
		  }
		}
	}
}

void PndSdsNoiseProducer::DiveDownNode(TGeoNode *){ //nodeMother //[R.K.03/2017] unused variable(s)
  //  for (Int_t Nod=0; Nod<nodeMother->GetNdaughters();Nod++)
  //  {
  //    gGeoManager->CdDown(Nod);
  //    TGeoNode *aNode = gGeoManager->GetCurrentNode();
  //    if(aNode->GetNdaughters()>0) DiveDownNode(aNode);
  //    TString volname = gGeoManager->GetPath();
  //    if(volname.Contains("Active"))
  //    {
  //      if(volname.Contains("Rect")) fStripRectIds.push_back(fGeoH->GetID(volname));
  //      if(volname.Contains("Trap")) fStripTrapIds.push_back(fGeoH->GetID(volname));
  //      if(volname.Contains("Pixel"))
  //      {
  //        if(volname.Contains("4x1")) fPixelIds4.push_back(fGeoH->GetID(volname));
  //        if(volname.Contains("6x1")) fPixelIds6.push_back(fGeoH->GetID(volname));
  //        if(volname.Contains("4x2")) fPixelIds8.push_back(fGeoH->GetID(volname));
  //        if(volname.Contains("6x2")) fPixelIds12.push_back(fGeoH->GetID(volname));
  //      }
  //    }
  //    gGeoManager->CdUp();
  //  }
}

// -------------------------------------------------------------------------
void PndSdsNoiseProducer::SetParContainers()
{
  if ( fGeoH == NULL )
    fGeoH = PndGeoHandling::Instance();

  fGeoH->SetParContainers();

  // Get Base Container
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  // fGeoPar = (PndSdsGeoPar*)(rtdb->getContainer("PndSdsGeoPar"));
  fDigiParRect = (PndSdsStripDigiPar*)(rtdb->getContainer("MVDStripDigiParRect"));
  fDigiParTrap = (PndSdsStripDigiPar*)(rtdb->getContainer("MVDStripDigiParTrap"));
  fDigiParPix  = (PndSdsPixelDigiPar*)(rtdb->getContainer("MVDPixelDigiPar"));
  Info("SetParContainers","done.");
}


// -----   Public method Exec   --------------------------------------------
void PndSdsNoiseProducer::Exec(Option_t*)
{
  fGeoH->SetVerbose(fVerbose);
  //   TObjArray* activeSensors = fGeoPar->GetGeoSensitiveNodes();
  Int_t nrCh=0,rnd=0,
  nrFE=0,sens=0,
  nrSensors=0,fe=0,
  chanmax=0,chan=0,
  col=0,row=0,
  // iStrip=0,
  chanwhite=0,
  //iPix=0,
  charge=0,
  nNoisyStripRects=0,
  nNoisyStripTraps=0,
  nNoisyPixels=0;
  Double_t xfrac=0.;
  Int_t did;
  
  // *** Strip Rect ***
  // how many channels left?
  nrCh = fDigiParRect->GetNrFECh();
  nrFE = fDigiParRect->GetNrBotFE() + fDigiParRect->GetNrTopFE();
  nrSensors = fStripRectIds.size();
  chanmax = nrCh * nrFE * nrSensors;
  // Get Number of Channels fired from noise
  xfrac = CalcDistFraction(fDigiParRect->GetNoise(),fDigiParRect->GetThreshold());
  chanwhite = gRandom->Poisson(xfrac*chanmax);
  if(fVerbose>1) std::cout << "-I- PndSdsNoiseProducer: RECT xfrac = " << xfrac
    << " leading to " << chanwhite << " noisy digis of " << chanmax
    << " total channels" << std::endl;
  for(Int_t i = 0;i < chanwhite;i++)
  {
    // randomize the channel numbers & sensors
    rnd = gRandom->Integer(chanmax);
    sens = rnd/(nrFE*nrCh);
    rnd = rnd % (nrFE*nrCh);
    fe = rnd/nrCh; //will populate
    chan = rnd % nrCh;
    // calculate a charge deposit above threshold
    charge = CalcChargeAboveThreshold(fDigiParRect->GetNoise(),fDigiParRect->GetThreshold());
    did = fStripRectIds[sens];
    AddDigiStrip(nNoisyStripRects,-1,did,fe,chan,charge);
  }
  
  // *** Strip Trapezoids ***
  nrCh = fDigiParTrap->GetNrFECh();
  nrFE = fDigiParTrap->GetNrBotFE() + fDigiParTrap->GetNrTopFE();
  nrSensors = fStripTrapIds.size();
  chanmax = nrCh * nrFE * nrSensors;
  xfrac = CalcDistFraction(fDigiParTrap->GetNoise(),fDigiParTrap->GetThreshold());
  chanwhite = gRandom->Poisson(xfrac*chanmax);
  if(fVerbose>1) std::cout << "-I- PndSdsNoiseProducer: TRAP xfrac = " << xfrac
    << " leading to " << chanwhite << " noisy digis of " << chanmax
    << " total channels" << std::endl;
  for(Int_t i = 0;i < chanwhite;i++)
  {
    rnd = gRandom->Integer(chanmax);
    sens = rnd/(nrFE*nrCh);
    rnd = rnd % (nrFE*nrCh);
    fe = rnd/nrCh;
    chan = rnd % nrCh;
    charge = CalcChargeAboveThreshold(fDigiParTrap->GetNoise(),fDigiParTrap->GetThreshold());
    did = fStripTrapIds[sens];
    AddDigiStrip(nNoisyStripTraps,-1,did,fe,chan,charge);
  }
  
  // *** Pixel Sensors ***
  nrCh = fDigiParPix->GetFECols()*fDigiParPix->GetFERows();
  nrFE = 4*fPixelIds4.size() + 6*fPixelIds6.size() + 8*fPixelIds8.size() + 12*fPixelIds12.size();
  chanmax = nrCh * nrFE;
  xfrac = CalcDistFraction(fDigiParPix->GetNoise(),fDigiParPix->GetThreshold());
  chanwhite = gRandom->Poisson(xfrac*chanmax);
  if(fVerbose>1) std::cout << "-I- PndSdsNoiseProducer: PIXEL xfrac = " << xfrac
    << " leading to " << chanwhite << " noisy digis of " << chanmax
    << " total channels" << std::endl;
  for(Int_t i = 0;i < chanwhite;i++)
  {
    charge = CalcChargeAboveThreshold(fDigiParPix->GetNoise(),fDigiParPix->GetThreshold());
    rnd = gRandom->Integer(chanmax);
    chan = rnd%nrCh;
    col = chan%fDigiParPix->GetFECols();
    row = chan/fDigiParPix->GetFECols();
    fe  = rnd/nrCh;
    if(fe >= (Int_t)(4*fPixelIds4.size() + 6*fPixelIds6.size() + 8*fPixelIds8.size()) )
    {
      fe = fe - 4*fPixelIds4.size() - 6*fPixelIds6.size() - 8*fPixelIds8.size();
      sens = fe/12;
      did = fPixelIds12[sens];
      fe = fe%12;
      if(fe>6) fe=fe-6+10; //0-9 one row of FE, 10-19 2nd row of FE
    } else if(fe >= (Int_t)(4*fPixelIds4.size() + 6*fPixelIds6.size()) )
    {
      fe = fe - 4*fPixelIds4.size() - 6*fPixelIds6.size();
      sens = fe/8;
      did = fPixelIds8[sens];
      fe = fe%8;
      if(fe>4) fe=fe-4+10; //0-9 one row of FE, 10-19 2nd row of FE
    } else if( fe >= (Int_t)(4*fPixelIds4.size()) )
    {
      fe = fe -4*fPixelIds4.size();
      sens = fe/6;
      did = fPixelIds6[sens];
      fe = fe%6;
    } else
    {
      sens = fe/4;
      did = fPixelIds4[sens];
      fe = fe%4;
    }
    
    AddDigiPixel(nNoisyPixels,-1,did,fe,col,row,charge);
  }
  
  // *** The End ***
  if(fVerbose>0)
  {
    std::cout <<"-I- PndSdsNoiseProducer: Noise produced\t"
    <<nNoisyStripRects <<"xStripRect\t"
    <<nNoisyStripTraps <<"xStripTrap\t"
    <<nNoisyPixels <<"xPixels"<<std::endl;
  }
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
Double_t PndSdsNoiseProducer::CalcDistFraction(Double_t spread, Double_t threshold)
{
  // mean fraction of fireing digis
  return 0.5*TMath::Erfc( threshold / (TMath::Sqrt2()*spread) );
}

// Int_t PndSdsNoiseProducer::CalcChanWhite(Int_t chanleft, Double_t frac)
// {
//   Int_t temp=0;
//   // random number of firing digis around the mean fraction
//   temp = gRandom->Poisson(frac*chanleft);
//   return (Int_t)temp;
// }

Int_t PndSdsNoiseProducer::CalcChargeAboveThreshold(Double_t spread,Double_t threshold)
{
  // only the charge ABOVE the threshold counts
  // get maximum y value of gauss tail
  // calculate a random charge according to that tails distribution
  Double_t temp=0.;
  temp = TMath::Gaus(threshold,0,spread);
  temp = gRandom->Uniform(0.,temp);
  temp = -2.*spread*spread*log(temp);
  temp = sqrt(temp);
  return (Int_t)temp;
}
// -------------------------------------------------------------------------
void PndSdsNoiseProducer::AddDigiPixel(Int_t &noisies, Int_t iPoint, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge)
{
  Bool_t found = kFALSE;
  Int_t detID = -1;
  fDigiPixelArray = FairRootManager::Instance()->GetTClonesArray(fBranchNamePixel);
  Int_t iPix = fDigiPixelArray->GetEntriesFast();
  PndSdsDigiPixel* aDigi = 0;
  for(Int_t kstr = 0; kstr < iPix && found == kFALSE; kstr++)
  {
    aDigi = (PndSdsDigiPixel*)fDigiPixelArray->At(kstr);
    if ( aDigi->GetDetID() == detID &&
        aDigi->GetSensorID() == sensorID &&
        aDigi->GetFE() == fe &&
        aDigi->GetPixelColumn() == col &&
        aDigi->GetPixelRow() == row )
    {
      aDigi->AddCharge(charge);
      aDigi->AddIndex(iPoint);
      found = kTRUE;
    }
  }
  if(found == kFALSE){
	  std::vector<Int_t> indices;
	  indices.push_back(iPoint);
	  FairMCEventHeader* MCevtHeader = (FairMCEventHeader*)FairRootManager::Instance()->GetObject("MCEventHeader.");

    new ((*fDigiPixelArray)[iPix]) PndSdsDigiPixel(indices,detID,sensorID,fe,col,row,charge, MCevtHeader->GetT()) ;
    noisies++;
    if(fVerbose>2) std::cout
      << " -I- PndSdsNoiseProducer: Added Pixel Digi at: FE=" << fe
      << ", col|row = ("<<col<<"|"<<row<< "), charge=" << charge<< " e"
      << ", in sensor \n" << sensorID <<std::endl;
    
  }
}
// -------------------------------------------------------------------------


ClassImp(PndSdsNoiseProducer)
