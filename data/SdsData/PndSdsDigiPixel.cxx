#include "PndSdsDigiPixel.h"

PndSdsDigiPixel::PndSdsDigiPixel() : PndSdsDigi(),
fCol(-1),
fRow(-1)
{
}

PndSdsDigiPixel::PndSdsDigiPixel(std::vector<Int_t> index, Int_t detID, Int_t sensorID, Int_t fe, Int_t col, Int_t row, Double_t charge, Double_t timeStamp):
PndSdsDigi(index, detID, sensorID, fe, charge, timeStamp),
fCol(col),
fRow(row)
{
}

ClassImp(PndSdsDigiPixel);
