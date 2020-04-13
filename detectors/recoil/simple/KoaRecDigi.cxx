#include "KoaRecDigi.h"

KoaRecDigi::KoaRecDigi() :
  fIndex(),
  fDetID(-1),
  fCharge(-1.)
{
}

KoaRecDigi::KoaRecDigi(std::vector<Int_t> index, Int_t detID, Double_t charge):
  fIndex(), fDetID(detID), fCharge(charge)
{ 
	AddIndex(index);
}

KoaRecDigi::KoaRecDigi(Int_t index, Int_t detID, Double_t charge):
  fIndex(), fDetID(detID), fCharge(charge)
{
	AddIndex(index);
}

ClassImp(KoaRecDigi);
