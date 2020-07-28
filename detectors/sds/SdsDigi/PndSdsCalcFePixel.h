#ifndef PNDSDSCALCFEPIXEL_H
#define PNDSDSCALCFEPIXEL_H

#include <vector>
#include "PndSdsPixel.h"
#include "TVector3.h"

class PndSdsPixelDigiPar;

//! Class to calculate the position of digis on a front-end from the digis on a sensor
/** @author T.Stockmanns <t.stockmanns@fz-juelich.de>
 *
 * This class calculates the column, row and front-end number of a digi
 * from the column, row number on a sensor and vice versa
 */

class PndSdsCalcFePixel
  {
    public :
	///Default constructor
	PndSdsCalcFePixel();
	///Main constructor
	PndSdsCalcFePixel(const PndSdsPixelDigiPar& digi_par);
	~PndSdsCalcFePixel();
    
    /*void SetNCols(Int_t ncols){fNcols = ncols;};
    void SetNRows(Int_t nrows){fNrows = nrows;};
    void SetMaxFE(Int_t maxFE){fMaxFEperCol = maxFE;};
    Int_t GetNCols() const { return fNcols;};
    Int_t GetNRows() const { return fNrows;};
    Int_t GetMaxFE() const { return fMaxFEperCol;};*/

    ///Main function to calculate front-end hits
    std::vector<PndSdsPixel> CalcFEHits(const std::vector<PndSdsPixel>& sensor_hits);
    
    ///Main function to calculate sensor hits
    void CalcSensorColRow(Int_t& col, Int_t& row, const Int_t fe) const;
  protected : 
    Int_t fNcols;       /// number of columns on a front-end chip
    Int_t fNrows;       /// nrows number of rows on a front-end chip
    Int_t fMaxFEperCol; /// maximum number of front-end chip per column on a sensor
    Int_t fMaxFEperRow; /// maximum number of front-end chip per row on a sensor
  };


#endif /*PNDSDSCALCFEPIXEL_H*/
