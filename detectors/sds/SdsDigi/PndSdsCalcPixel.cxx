#include "PndSdsCalcPixel.h"
#include <cmath>
#include "TRandom.h"


PndSdsCalcPixel::PndSdsCalcPixel() :
  fPixels(),
  fPixelWidth(0.),
  fPixelLength(0.),
  fThreshold(0.),
  fNoise(0.),
  fEnergy(0.),
  fVerboseLevel(0),
  fQuad(kQuadUNDEF),
  fNextPixel(kPixelUNDEF),
  fIn(),
  fOut(),
  fDir(),
  fPos(),
  fCon(),
  fActivePixel(),
  fCperL(-1),
  fStop(false)
{
}

PndSdsCalcPixel::PndSdsCalcPixel(Double_t w, Double_t l, Double_t threshold, Double_t noise) :
  fPixels(),
  fPixelWidth(w),
  fPixelLength(l),
  fThreshold(threshold),
  fNoise(noise),
  fEnergy(0.),
  fVerboseLevel(0),
  fQuad(kQuadUNDEF),
  fNextPixel(kPixelUNDEF),
  fIn(),
  fOut(),
  fDir(),
  fPos(),
  fCon(),
  fActivePixel(),
  fCperL(-1),
  fStop(false)
{}

Int_t PndSdsCalcPixel::GetPixelsAlternative(Double_t inx, Double_t iny,
                                            Double_t outx, Double_t outy,
                                            Double_t energy, 
                                            std::vector<Int_t>& cols, std::vector<Int_t>& rows,
                                            std::vector<Double_t>& charges)
{
  std::vector<PndSdsPixel> pixels = GetPixels(inx,iny,outx,outy,energy);
  Int_t npix=pixels.size();
  for(Int_t i=0;i<npix;i++)
  { 
    if(fVerboseLevel>2) Info("PndSdsCalcPixel::GetPixelsAlternative()","pass this pixel: i=%i, c=%i, r=%i, q=%f",i,pixels[i].GetCol(),pixels[i].GetRow(),pixels[i].GetCharge());
    cols.push_back(pixels[i].GetCol());
    rows.push_back(pixels[i].GetRow());
    charges.push_back(pixels[i].GetCharge());
  }
  return npix;
}


std::vector<PndSdsPixel> PndSdsCalcPixel::GetPixels(Double_t inx, Double_t iny,
                                                    Double_t outx, Double_t outy,
                                                    Double_t energy)
{
  fPixels.clear();
  fIn.setXYZ(inx, iny, 0);
  fOut.setXYZ(outx, outy, 0);
  
  fDir = fOut - fIn;
  fPos = fIn;
  if (fDir.length() < 0.001){   //1 m
    CalcStartPixel();
    fActivePixel.SetCharge(energy/(3.61e-9));
    fPixels.push_back(fActivePixel);
    return fPixels;
  }
  //  CalcConMatrix(); //fCon berechnen
  //  ApplyConMatrix(); //fCon anwenden
  if (fVerboseLevel > 1){
    std::cout << "Converted Vectors: " << std::endl;
    std::cout << fIn << fOut << fDir << fPos << std::endl;
  }
  CalcQuadrant();
  CalcCperL(energy);
  
  CalcStartPixel();
  
  fStop = false;
  while (fStop != true){
    CalcPixel();
    Int_t col = fActivePixel.GetCol();
    Int_t row = fActivePixel.GetRow();
    switch (fNextPixel) {
      case kU : fActivePixel.SetRow(++row); break;
      case kD : fActivePixel.SetRow(--row); break;
      case kL : fActivePixel.SetCol(--col); break;
      case kR : fActivePixel.SetCol(++col); break;
      case kPixelUNDEF : std::cout << "PndSdsCalcPixel::GetPixels no next pixel."<<std::endl; break;
    }
    fActivePixel.SetCharge(-1.0);
  }
  
  //  ConvertPixels(); //fCon rueckgaengig
  return fPixels;
}
void PndSdsCalcPixel::CalcConMatrix()
{
  if (fIn.getX() < 0)
    fCon.setX(-1);
  else fCon.setX(1);
  if (fIn.getY() < 0)
    fCon.setY(-1);
  else fCon.setY(1);
}

void PndSdsCalcPixel::ApplyConMatrix()
{
  fIn.setX(fCon.getX() * fIn.getX());
  fIn.setY(fCon.getY() * fIn.getY());
  
  fOut.setX(fCon.getX() * fOut.getX());
  fOut.setY(fCon.getY() * fOut.getY());
  
  fPos.setX(fCon.getX() * fPos.getX());
  fPos.setY(fCon.getY() * fPos.getY());
  
  fDir.setX(fCon.getX() * fDir.getX());
  fDir.setY(fCon.getY() * fDir.getY());
  
}

void PndSdsCalcPixel::CalcQuadrant()
{
  if (fDir.getX() > 0)
    if (fDir.getY() > 0)
      fQuad = kUR;
    else
      fQuad = kDR;
    else if (fDir.getY() > 0)
      fQuad = kUL;
    else
      fQuad = kDL;
  
  if (fVerboseLevel > 1){
    std::cout << "CalcQuadrant: " << fQuad << std::endl;
  }
}

void PndSdsCalcPixel::CalcCperL(Double_t Energy)
{
  Double_t Charge = Energy / (3.61e-9);
  fCperL = Charge / fDir.length();  
}

void PndSdsCalcPixel::CalcStartPixel ()
{
  Int_t col = Int_t(fIn.getX() / fPixelLength);
  Int_t row = Int_t(fIn.getY() / fPixelWidth);
  fActivePixel.SetCol(col);
  fActivePixel.SetRow(row);
}

void PndSdsCalcPixel::CalcPixel()
{
  Double_t borderX = 0;
  Double_t borderY = 0;
  FairGeoVector OutPoint;
  bool xBeforeY = false;
  
  /*  if ( fabs(fDir.getX()) < 1e-8 ) {
   xBeforeY = false;
   borderY = fPixelWidth * (fActivePixel.GetRow()+1);
   }
   else  if ( fabs(fDir.getY()) < 1e-8 ) {
   xBeforeY = true;
   borderX = fPixelWidth
   }
   else  switch (fQuad){
   */
  switch (fQuad){
    case kUR : borderX = fPixelLength * (fActivePixel.GetCol()+1);
      borderY = fPixelWidth  * (fActivePixel.GetRow()+1);
      if ( fabs(fDir.getX()) < 1e-8 ) xBeforeY = false;
      else if ( ( (borderX - fPos.getX()) * fDir.getY() / fDir.getX() )+fPos.getY() < borderY)
        xBeforeY = true;
      else xBeforeY = false;
      break;
    case kUL : borderX = fPixelLength * (fActivePixel.GetCol());
      borderY = fPixelWidth  * (fActivePixel.GetRow()+1);
      if ( fabs(fDir.getX()) < 1e-8 ) xBeforeY = false;
      else if ( ( (borderX - fPos.getX()) * fDir.getY() / fDir.getX() )+fPos.getY() < borderY)
        xBeforeY = true;
      else xBeforeY = false;
      break;
    case kDL : borderX = fPixelLength * (fActivePixel.GetCol());
      borderY = fPixelWidth  * (fActivePixel.GetRow());
      if ( fabs(fDir.getX()) < 1e-8 ) xBeforeY = false;
      else if ( ( (borderX - fPos.getX()) * fDir.getY() / fDir.getX() )+fPos.getY() > borderY)
        xBeforeY = true;
      else xBeforeY = false;
      break;
    case kDR : borderX = fPixelLength * (fActivePixel.GetCol()+1);
      borderY = fPixelWidth  * (fActivePixel.GetRow());
      if ( fabs(fDir.getX()) < 1e-8 ) xBeforeY = false;
      else if ( ( (borderX - fPos.getX()) * fDir.getY() / fDir.getX() )+fPos.getY() > borderY)
        xBeforeY = true;
      else xBeforeY = false;
      break;
    case kQuadUNDEF : std::cout<<"PndSdsCalcPixel::CalcPixel : Quadrant not defined!"<<std::endl;
      //default : ErrMsg(fatal) << " Quadrant not defined! " << endmsg;
  }
  
  if ( xBeforeY ) { //Is borderX reached berfore borderY
    OutPoint.setXYZ(borderX, ((borderX-fPos.getX())*fDir.getY()/fDir.getX())+fPos.getY(),0);
    
    if (fQuad == kUR || fQuad == kDR)
      fNextPixel = kR;
    else fNextPixel = kL;
  }
  else {
    OutPoint.setXYZ(((borderY-fPos.getY())*fDir.getX()/fDir.getY())+fPos.getX(), borderY,0);
    
    if (fQuad == kUR || fQuad == kUL)
      fNextPixel = kU;
    else fNextPixel = kD;
  } 
  //  ErrMsg(warning) << " OutPoint: " << OutPoint << endmsg;
  
  
  if ((OutPoint - fPos).length() > (fOut - fPos).length()){
    fStop = true;
    OutPoint = fOut;
  }
  
  
  Double_t depCharge = (OutPoint - fPos).length() * fCperL;
  if (fVerboseLevel > 1){
    printf("len: %g, cperL: %g, depCharge w/o noise: %g\n",(OutPoint - fPos).length(),fCperL,depCharge);
  }
  
  // noise smearing and discriminator threshold cut
  Double_t smearedCharge = SmearCharge(depCharge);
  if (smearedCharge<=fThreshold) return;
  
  fPos = OutPoint;
  fActivePixel.SetCharge(smearedCharge);
  
  
  fPixels.push_back(fActivePixel);
  
  if (fVerboseLevel > 1){
    std::cout << fActivePixel << std::endl;
  }
  
}

void PndSdsCalcPixel::ConvertPixels()
{
  Int_t col, row;
  for (UInt_t i = 0; i < fPixels.size(); i++){
    col = fPixels[i].GetCol();
    row = fPixels[i].GetRow();
    fPixels[i].SetCol(Int_t(col * fCon.getX()));
    fPixels[i].SetRow(Int_t(row * fCon.getY()));
  }
}

std::ostream& PndSdsCalcPixel::operator<<(std::ostream& out)
{
  out << "PixelWidth: " << fPixelWidth << " PixelLength: " <<
  fPixelLength << std::endl;
  
  return out;
}

//______________________________________________________________________________
Double_t PndSdsCalcPixel::SmearCharge(Double_t charge)
{
  Double_t smeared = gRandom->Gaus(charge,fNoise);
  if (fVerboseLevel > 3) std::cout<<" charge = "<<charge<<", smeared = "<<smeared<<std::endl;
  return smeared;
}

