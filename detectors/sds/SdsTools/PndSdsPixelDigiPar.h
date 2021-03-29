//
// C++ Interface: PndSdsPixelDigiPar
//
#ifndef PNDSDSPIXELDIGIPAR_H
#define PNDSDSPIXELDIGIPAR_H

#include <TVector2.h>
#include "FairParGenericSet.h"
#include "FairParamList.h"

#include <iostream>

//! Digitization Parameter Class for SDS-Pixel part

class PndSdsPixelDigiPar : public FairParGenericSet
  {
    public :
    PndSdsPixelDigiPar (const char* name="PndSdsParTest",
                        const char* title="PndSds pixel digi parameter",
                        const char* context="TestDefaultContext");
    ~PndSdsPixelDigiPar(void){};
    void clear(void){};
    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);
    
    virtual void Print (std::ostream& out = std::cout) const;
    virtual void print(){Print();}

    friend std::ostream& operator<<(std::ostream& out, const PndSdsPixelDigiPar& dt){
    	dt.Print(out);
    	return out;
    }
   
    Double_t GetXPitch()        const {return fDimX;}
    Double_t GetYPitch()        const {return fDimY;}
    Double_t GetThreshold()     const {return fThreshold;}
    Double_t GetNoise()         const {return fNoise;}
    Double_t GetQCloudSigma()   const {return fCSigma;}
    Int_t GetFECols()           const {return fFeCols;}
    Int_t GetFERows()           const {return fFeRows;}
    Int_t GetMaxFEperCol()      const {return fMaxFEperCol;}
    Int_t GetMaxFEperRow()      const {return fMaxFEperRow;}
    Double_t GetClustRadius()   const {return fRadius;}
    Double_t GetFeBusClock()    const {return fFeBusClock;}
    Double_t GetTimeStep()		const {return (1./fFeBusClock * 1000.);} ///< Time step of one clock cycle in ns
    Int_t GetChargeConvMethod() const  {return fChargeConvMethod;}
    Double_t GetPixelSorterCellWidth() const {return fPixelSorterCellWidth;}
    Int_t GetPixelSorterNumberOfCells() const {return fPixelSorterNumberOfCells;}
    
    void SetXPitch(Double_t x)        {fDimX = x;}
    void SetYPitch(Double_t x)        {fDimY = x;}
    void SetThreshold(Double_t x)     {fThreshold = x;}
    void SetNoise(Double_t x)         {fNoise = x;}
    void SetQCloudSigma(Double_t x)   {fCSigma = x;}
    void SetFECols(Int_t x)           {fFeCols = x;}
    void SetFERows(Int_t x)           {fFeRows = x;}
    void SetMaxFEperCol(Int_t x)      {fMaxFEperCol = x;}
    void SetMaxFEperRow(Int_t x)      {fMaxFEperRow = x;}
    void SetClustRadius(Double_t x)   {fRadius=x;}
    void SetFeBusClock(Double_t x)      {fFeBusClock = x;}
    void SetChargeConvMethod(Int_t x) {fChargeConvMethod = x;}

    void SetPixelSorterCellWidth(Double_t x) {fPixelSorterCellWidth = x;}
    void SetPixelSorterNumberOfCells(Int_t x) {fPixelSorterNumberOfCells=x;}
    
  private:
    // Pixel Parameters
    Int_t fFeCols;            // Colums read per Frontend 
    Int_t fFeRows;            // Rows read per Frontend
    Int_t fMaxFEperCol;       // maximum number of front-end chip per column on a sensor
    Int_t fMaxFEperRow;       // maximum number of front-end chip per row on a sensor
    Double_t fDimX;           // Pixel cell size X
    Double_t fDimY;           // Pixel cell size Y
    Double_t fRadius;         // Clusterfinder search radius (channel numbers)
    Double_t fThreshold;      // Discriminator Threshold (electrons)
    Double_t fNoise;          // Gaussian electronics noise including threshold dispersion (electrons)
    Double_t fCSigma;         // Gaussian charge cloud smearing
    Double_t fFeBusClock;   // Frontend bus clock to determin noise rate
    Int_t fChargeConvMethod;	// 0: ideal conversion; 1: TOT calculation
    Double_t fPixelSorterCellWidth;	// Parameter for TimeStamp Sorter
    Int_t fPixelSorterNumberOfCells; // Parameter for TimeStamp Sorter
    //Text_t fSensName;         // Sensor name
    //Text_t fFeName;           // Frontend name
    
    
    ClassDef(PndSdsPixelDigiPar,5);
  };

#endif /*!PNDSDSSTRIPDIGIPAR_H*/
