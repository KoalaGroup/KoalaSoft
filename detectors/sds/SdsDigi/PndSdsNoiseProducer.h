// -------------------------------------------------------------------------
// -----                PndSdsNoiseProducer header file                -----
// -----                  Created 01.07.08  by R.Kliemt                -----
// -------------------------------------------------------------------------


/** PndSdsNoiseProducer.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The Noise Producer adds fake hits to silicon sensor channels (strips and
 ** Pixels)
 **/


#ifndef PNDSDSNOISEPRODUCER_H
#define PNDSDSNOISEPRODUCER_H

#include "PndSdsTask.h"

#include <vector>

#include "TRandom.h"
//#include "PndSdsGeoPar.h"
#include "PndGeoHandling.h"
#include "PndSdsStripDigiPar.h"
#include "PndSdsPixelDigiPar.h"
#include "KoaDetectorList.h"
#include "TString.h"

class TClonesArray;

class PndSdsNoiseProducer : public PndSdsTask
{
 public:

  /** Default constructor **/
  PndSdsNoiseProducer();

  PndSdsNoiseProducer(PndSdsNoiseProducer& other):
      PndSdsTask(),
      fBranchNameStrip(other.fBranchNameStrip),
      fBranchNamePixel(other.fBranchNamePixel),
      fDigiStripArray(other.fDigiStripArray),
      fDigiPixelArray(other.fDigiPixelArray),
      fDigiParRect(other.fDigiParRect),
      fDigiParTrap(other.fDigiParTrap),
      fDigiParPix(other.fDigiParPix),
      fMCPointType(other.fMCPointType),
      fGeoH(other.fGeoH),
      fPixelIds4(other.fPixelIds4),
      fPixelIds6(other.fPixelIds6),
      fPixelIds8(other.fPixelIds8),
      fPixelIds12(other.fPixelIds12),
      fStripRectIds(other.fStripRectIds),
      fStripTrapIds(other.fStripTrapIds),
      fNoiseSpread(other.fNoiseSpread),
      fThreshold(other.fThreshold),
      fIonizationEnergy(other.fIonizationEnergy)
  {};
  
  /** Destructor **/
  virtual ~PndSdsNoiseProducer();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();

  /** pure virtual method SetBranchNames
   **
   ** called by Init()
   ** function to set individual branch names
   **/
  virtual void SetBranchNames()=0;
  virtual void SetMCPointType() = 0;

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  Double_t CalcDistFraction(Double_t spread, Double_t threshold);
//   Int_t CalcChanWhite(Int_t chanleft, Double_t frac);
  Int_t CalcChargeAboveThreshold(Double_t spread, Double_t threshold);
  void AddDigiStrip(Int_t &iStrip, Int_t iPoint, Int_t sensorID, Int_t fe, Int_t chan, Double_t charge);
  void AddDigiPixel(Int_t &noisies, Int_t iPoint, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge);

  void DiveDownNode(TGeoNode *fN);
  void FillSensorLists();
//   void Finish();

  
  PndSdsNoiseProducer& operator=(PndSdsNoiseProducer& other)
  {
    if(this != &other) // protect against invalid self-assignment
    {
      fBranchNameStrip=other.fBranchNameStrip;
      fBranchNamePixel=other.fBranchNamePixel;
      fDigiStripArray=other.fDigiStripArray;
      fDigiPixelArray=other.fDigiPixelArray;
      fDigiParRect=other.fDigiParRect;
      fDigiParTrap=other.fDigiParTrap;
      fDigiParPix=other.fDigiParPix;
      fMCPointType=other.fMCPointType;
      fGeoH=other.fGeoH;
      fPixelIds4=other.fPixelIds4;
      fPixelIds6=other.fPixelIds6;
      fPixelIds8=other.fPixelIds8;
      fPixelIds12=other.fPixelIds12;
      fStripRectIds=other.fStripRectIds;
      fStripTrapIds=other.fStripTrapIds;
      fNoiseSpread=other.fNoiseSpread;
      fThreshold=other.fThreshold;
      fIonizationEnergy=other.fIonizationEnergy;
    }
    return *this;
  }

 protected:
  TString fBranchNameStrip;
  TString fBranchNamePixel;
  /** In-Output array of PndSdsDigis **/
  TClonesArray* fDigiStripArray;
  TClonesArray* fDigiPixelArray;

  /** Parameter Containers **/
  PndSdsStripDigiPar* fDigiParRect;
  PndSdsStripDigiPar* fDigiParTrap;
  PndSdsPixelDigiPar* fDigiParPix;

  fDetectorType fMCPointType;

  PndGeoHandling* fGeoH;      //! Geometry name handling

  std::vector<Int_t> fPixelIds4;
  std::vector<Int_t> fPixelIds6;
  std::vector<Int_t> fPixelIds8;
  std::vector<Int_t> fPixelIds12;
  std::vector<Int_t> fStripRectIds;
  std::vector<Int_t> fStripTrapIds;

  Int_t fNoiseSpread;
  Int_t fThreshold;

  Double_t fIonizationEnergy; // electrons per GeV (Panda unified units)
//   void Register();
//   void Reset();
//   void ProduceHits();

  ClassDef(PndSdsNoiseProducer,1);

};

#endif
