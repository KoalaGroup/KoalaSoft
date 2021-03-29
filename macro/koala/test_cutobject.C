#include "KoaCutObject.h"

using namespace KoaUtility;

void writeObject()
{
  auto f = TFile::Open("cutobject.root", "recreate");
  if (!f) std::cout << "can't open file\n";

  // KoaFwdTimeCut tcut(9,2,3,5,0,0);
  KoaFwdTimeCut *tcut = new KoaFwdTimeCut(9,2,3,5,0,0);
  // f->WriteObject(&tcut,"fwdTimeCut");
  f->WriteObjectAny(tcut,"KoaFwdTimeCut","fwdTimeCut");

  delete tcut;
  delete f;
}

void readObject()
{
  auto f = TFile::Open("cutobject.root");
  if (!f) std::cout << "can't open file\n";

  KoaFwdTimeCut* tcut;
  // auto tcut = f->Get<KoaFwdTimeCut>("fwdTimeCut"); // not available in 6.16
  f->GetObject("fwdTimeCut", tcut);
  if ( !tcut ) std::cout << "can't get object\n";
  else tcut->Print();

  delete f;
}
