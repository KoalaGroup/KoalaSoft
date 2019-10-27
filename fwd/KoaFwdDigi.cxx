#include "KoaFwdDigi.h"

KoaFwdDigi::KoaFwdDigi() :
  fIndex(),
  fDetID(-1),
  fCharge(-1.)
{
}

KoaFwdDigi::KoaFwdDigi(std::vector<Int_t> index, Int_t detID, Double_t charge):
  fIndex(), fDetID(detID), fCharge(charge)
{ 
	AddIndex(index);
}

KoaFwdDigi::KoaFwdDigi(Int_t index, Int_t detID, Double_t charge):
  fIndex(), fDetID(detID), fCharge(charge)
{
	AddIndex(index);
}

ClassImp(KoaFwdDigi);
