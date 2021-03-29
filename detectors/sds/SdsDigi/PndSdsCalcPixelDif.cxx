#include "PndSdsCalcPixelDif.h"
#include "PndSdsPixelDigiPar.h"
#include <sstream>
#include <cmath>
#include "TRandom.h"
#include <map>

PndSdsCalcPixelDif::PndSdsCalcPixelDif() :
		fPixels(), fActivePixel(), fPixelSizeX(0.), fPixelSizeY(0.), fRows(0.), fCols(0.), fThreshold(0.), fNoise(
		    0.), fQspread(0.), fEnergy(0.), fVerboseLevel(0) {
}

PndSdsCalcPixelDif::PndSdsCalcPixelDif(const PndSdsPixelDigiPar& digi_par) :
		fPixels(), fActivePixel(), fPixelSizeX(digi_par.GetXPitch()), fPixelSizeY(digi_par.GetYPitch()), fRows(
		    digi_par.GetFERows() * digi_par.GetMaxFEperRow()), fCols(
		    digi_par.GetFECols() * digi_par.GetMaxFEperCol()), fThreshold(digi_par.GetThreshold()), fNoise(
		    digi_par.GetNoise()), fQspread(digi_par.GetQCloudSigma()), fEnergy(0.), fVerboseLevel(0) {
}

PndSdsCalcPixelDif::PndSdsCalcPixelDif(Double_t lx, Double_t ly, Double_t qspread,Double_t threshold, Double_t noise, Double_t nrows, Double_t ncols) :
    fPixels(),
    fActivePixel(),
		fPixelSizeX(lx),
		fPixelSizeY(ly),
    fRows(nrows),
    fCols(ncols),
		fThreshold(threshold),
		fNoise(noise),
    fQspread(qspread),
		fEnergy(0.),
    fVerboseLevel(0)
{}

Int_t PndSdsCalcPixelDif::GetPixelsAlternative(Double_t inx, Double_t iny, Double_t outx, Double_t outy,
    Double_t energy, std::vector<Int_t>& cols, std::vector<Int_t>& rows,
    std::vector<Double_t>& charges) {
	std::vector<PndSdsPixel> pixels = GetPixels(inx, iny, outx, outy, energy);
	Int_t npix = pixels.size();
	for (Int_t i = 0; i < npix; i++) {
		if (fVerboseLevel > 2) Info("PndSdsCalcPixelDif::GetPixelsAlternative()",
		    "pass this pixel: i=%i, c=%i, r=%i, q=%f", i, pixels[i].GetCol(), pixels[i].GetRow(),
		    pixels[i].GetCharge());
		cols.push_back(pixels[i].GetCol());
		rows.push_back(pixels[i].GetRow());
		charges.push_back(pixels[i].GetCharge());
	}
	return npix;
}

std::vector<PndSdsPixel> PndSdsCalcPixelDif::GetPixels(Double_t inx, Double_t iny, Double_t outx,
    Double_t outy, Double_t dE) {
	fPixels.clear();
	if (0 >= fPixelSizeX || 0 >= fPixelSizeY) {
		Error("PndSdsCalcPixelDif::GetPixels()", "Invalid Pixel sizes: fPixelSizeX=%g,fPixelSizeY=%g",
		    fPixelSizeX, fPixelSizeY);
		return fPixels;
	}

	// determine box digis which can get charge
	double max_charge_diffusion_distance(3.0 * fQspread);
	double min_x(inx);
	double max_x(outx);
	if (outx < inx) {
		min_x = outx;
		max_x = inx;
	}
	double min_y(iny);
	double max_y(outy);
	if (outy < iny) {
		min_y = outy;
		max_y = iny;
	}
	min_x -= max_charge_diffusion_distance;
	min_y -= max_charge_diffusion_distance;
	max_x += max_charge_diffusion_distance;
	max_y += max_charge_diffusion_distance;

	double track_dx = outx - inx;
	double track_dy = outy - iny;
	unsigned int cols(
	    ((unsigned int) std::fabs(max_x / fPixelSizeX)) - ((unsigned int) std::fabs(min_x / fPixelSizeX))
	        + 1);
	unsigned int rows(
	    ((unsigned int) std::fabs(max_y / fPixelSizeX)) - ((unsigned int) std::fabs(min_y / fPixelSizeY))
	        + 1);
	// we gain a lot of speed by using a fixed vector
	// and using a fixed mapping between row+col and vector index
	int start_col(min_x / fPixelSizeX);
	int start_row(min_y / fPixelSizeY);
	double difx = 0, dify = 0;
	int row = 0, col = 0;
	double t = 0;
	std::vector<int> hitstorage(cols * rows, 0);
	double Q = ChargeFromEloss(dE);  // in electrons
	unsigned int samples(Q);  // sample amount (can be chosen independent of charge electrons Q)
	// do hit&miss mc sampling, if we have more than 1 possible cell
	if (hitstorage.size() == 1) {
		InjectPixelCharge(start_col, start_row, Q);
	}
	else {
		for (unsigned int i = 0; i < samples; ++i) {
			t = gRandom->Rndm();
			difx = gRandom->Gaus(0, fQspread);
			dify = gRandom->Gaus(0, fQspread);
			// if the electron diffused outside of the boundary just ignore it
			if (std::abs(difx) > max_charge_diffusion_distance
			    || std::abs(dify) > max_charge_diffusion_distance) continue;
			col = (inx + t * track_dx + difx) / fPixelSizeX;
			row = (iny + t * track_dy + dify) / fPixelSizeY;
			hitstorage[(row - start_row) * cols + (col - start_col)]++;
		}
		// distribute electrons based on the distribution from the hit&miss
		for (unsigned int i = 0; i < hitstorage.size(); ++i) {
			if (hitstorage[i] > 0) {
				row = i / cols + start_row;
				col = i % cols + start_col;
				InjectPixelCharge(col, row, Q * hitstorage[i] / samples);
			}
		}
	}
	return fPixels;
}

//______________________________________________________________________________
void PndSdsCalcPixelDif::InjectPixelCharge(Int_t col, Int_t row, Double_t charge) {
	// cut if out of range
	if (col < 0 || row < 0 || col > fCols || row > fRows) {
		if (fVerboseLevel > 2) {
			std::stringstream ss;
			ss << " (col=" << col << ",row=" << row << " values exceed sensor boundaries: cols=[0-" << fCols
			    << "] rows=[0-" << fRows << "]";
			Info("PndSdsCalcPixelDif::PndSdsCalcPixelDif::InjectPixelCharge:", ss.str().c_str());
		}
	}
	Double_t smearedCharge = gRandom->Gaus(charge, fNoise);
	if (fVerboseLevel > 3) std::cout << " charge = " << charge << ", smeared = " << smearedCharge
	    << std::endl;
	if (smearedCharge > fThreshold) {
		if (fVerboseLevel > 3) Info("PndSdsCalcPixelDif::InjectPixelCharge", "col=%i, row=%i,charge=%f", col,
		    row, charge);
		fActivePixel.SetCol(col);  // x axis
		fActivePixel.SetRow(row);  // y axis
		fActivePixel.SetCharge(smearedCharge);
		fPixels.push_back(fActivePixel);  // fActivePixel content will be copied
	}
	return;
}

//______________________________________________________________________________
std::ostream& PndSdsCalcPixelDif::operator<<(std::ostream& out) {
	out << "fPixelSizeX: " << fPixelSizeX << " fPixelSizeY: " << fPixelSizeY << std::endl;

	return out;
}

