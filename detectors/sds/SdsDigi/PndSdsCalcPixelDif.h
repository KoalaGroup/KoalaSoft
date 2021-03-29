#ifndef PNDSDSCALCPIXELDIF_H
#define PNDSDSCALCPIXELDIF_H

#include "PndSdsPixel.h"
#include "FairGeoVector.h"
#include <iostream>
#include <vector>
//#include <XYVector.h>
//#include "CLHEP/Vector/TwoVector.h"
//! Calculates the pixels (digis) fired from a particle hitting the sensor
/**
 *  @author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 *  @author Ralf Kliemt, Uni Bonn
 * This class gets as an input the point where the particle enters the sensor,
 * where it leaves the sensor and the deposited energy. It calculates the track
 * of the particle between these two points and determines the pixels lying on the
 * track. The total energy of the particle is then distributed acording to a gaussian widened path
 * to the pixels. The output is a vector<PndSdsPixel> of the fired sensor pixels
 * with the energy deposited in the pixels.
 * If a noise value is given a gausian distributed energy with a sigma of (noise) is added (or substracted) to
 * the energy deposited in one pixel.
 * If a threshold value is given all pixels with energies below threshold are ignored
 */

class PndSdsPixelDigiPar;

class PndSdsCalcPixelDif
  {
  public:
		///Default constructor
		PndSdsCalcPixelDif();

	  ///Main constructor
	  ///@param w width of sensor pixel [cm]
	  ///@param l length of sensor pixel [cm]
    ///@param qspread charge cloud gaussian width
	  ///@param threshold discriminator threshold of pixel [e]
	  ///@param noise total noise of pixel [e]
	  PndSdsCalcPixelDif(Double_t w, Double_t l, Double_t qspread = 0, Double_t threshold = 0, Double_t noise = 0,Double_t nrows=10, Double_t ncols=10);
	  PndSdsCalcPixelDif(const PndSdsPixelDigiPar& digi_par);

	  ///Main function to calculate the vector<PndSdsPixel> of fired pixel
	  std::vector<PndSdsPixel> GetPixels (Double_t inx, Double_t iny,
                                        Double_t outx, Double_t outy,
                                        Double_t energy);

    Int_t GetPixelsAlternative(Double_t inx, Double_t iny,
                               Double_t outx, Double_t outy,
                               Double_t energy, std::vector<Int_t>& cols, std::vector<Int_t>& rows,
                               std::vector<Double_t>& charges);

	  void SetVerboseLevel(Int_t level){ fVerboseLevel = level;};
	  std::ostream& operator<<(std::ostream& out);

  private:
    Double_t ChargeFromEloss(Double_t eloss) const {return eloss/(3.61e-9);}
    void InjectPixelCharge(Int_t col, Int_t row, Double_t charge);

		std::vector<PndSdsPixel> fPixels;
    PndSdsPixel fActivePixel;

		Double_t fPixelSizeX;
		Double_t fPixelSizeY;
		Double_t fRows;
		Double_t fCols;
		Double_t fThreshold;
		Double_t fNoise;
    Double_t fQspread;
		Double_t fEnergy;

    Int_t fVerboseLevel;

  };

#endif
