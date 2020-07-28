#include "PndLmdDigiQ.h"

PndLmdDigiQ::PndLmdDigiQ() : PndSdsDigiPixel()
{
  fSigfl = true;
  fPDG = -1;
}


PndLmdDigiQ::PndLmdDigiQ(const PndSdsDigiPixel &digiIn, bool sigfl):PndSdsDigiPixel(digiIn)
{
  fSigfl = sigfl;
  fPDG = -1;
}


ClassImp(PndLmdDigiQ);
