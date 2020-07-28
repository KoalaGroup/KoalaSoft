#include "PndSdsCalcFePixel.h"
#include "PndSdsPixelDigiPar.h"

PndSdsCalcFePixel::PndSdsCalcFePixel() :
		fNcols(1), fNrows(1), fMaxFEperCol(1), fMaxFEperRow(1) {
}

PndSdsCalcFePixel::PndSdsCalcFePixel(const PndSdsPixelDigiPar& digi_par) :
		fNcols(digi_par.GetFECols()), fNrows(digi_par.GetFERows()), fMaxFEperCol(digi_par.GetMaxFEperCol()), fMaxFEperRow(
		    digi_par.GetMaxFEperRow()) {
}

PndSdsCalcFePixel::~PndSdsCalcFePixel() {
}

std::vector<PndSdsPixel> PndSdsCalcFePixel::CalcFEHits(const std::vector<PndSdsPixel>& sensor_hits) {
	Int_t col, row, fe, fe_row, fe_col;
	std::vector<PndSdsPixel> result;
	for (auto const& sensor_hit : sensor_hits) {
		col = sensor_hit.GetCol();
		row = sensor_hit.GetRow();
		fe_col = col / fNcols;
		if (fMaxFEperCol > fe_col) {
			col -= fe_col * fNcols;
			fe = fe_col;
		}
		fe_row = row / fNrows;
		if (fMaxFEperRow > fe_row) {
			fe += fMaxFEperCol * (fe_row);
			row -= fe_row * fNrows;
		}
		PndSdsPixel myPixel(sensor_hit.GetSensorID(), fe, col, row, sensor_hit.GetCharge());
		myPixel.SetAddNoise(sensor_hit.GetAddNoise());
		result.push_back(myPixel);
	}
	return result;
}

void PndSdsCalcFePixel::CalcSensorColRow(Int_t& col, Int_t& row, const Int_t fe) const {
	Int_t fe_row = fe / fMaxFEperCol;
	Int_t fe_col = fe % fMaxFEperCol;
	row = row + fe_row * fNrows;
	col = col + fe_col * fNcols;
	return;
}
