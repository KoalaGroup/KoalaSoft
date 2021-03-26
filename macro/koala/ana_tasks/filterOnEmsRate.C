#include "KoaUtility.h"

using namespace KoaUtility;

void filterOnEmsRate(const char* digifile,
                     const char* ratefile,
                     const char* elistfile
                     )
{
  // the selected ems rate events
  auto frate = new TFile(ratefile);
  auto trate = (TTree*)frate->Get("EMS_Rates_Selected");

  trate->BuildIndex("Second", "Usecond");

  // the digi file with KoaRawEvent tree
  auto fin = new TFile(digifile);
  auto tin = (TTree*)fin->Get("koalasim");
  KoaRawEvent* evt = nullptr;
  tin->SetBranchAddress("KoaRawEvent", &evt);

  // the output elist
  TEventList elist("ems_rate_selected", "Events based on Rate selection");

  // event loop based on selected rate keys : Second, Usecond
  int entries=tin->GetEntries();
  for(int entry=0;entry<entries;entry++){
    tin->GetEntry(entry);

    //
    if(trate->GetEntryNumberWithIndex(evt->Second, evt->Usecond) > -1) {
      elist.Enter(entry);
    }
  }
  std::cout << elist.GetN()/(Double32_t)entries << "\t" << elist.GetN() << "\t" << entries
            << "\t" << digifile << std::endl;

  // output
  auto fout = new TFile(elistfile, "update");
  TDirectory* edir = getDirectory(fout, "rate");
  edir->WriteTObject(&elist, "", "Overwrite");

  //
  delete frate, fin, fout;
}
