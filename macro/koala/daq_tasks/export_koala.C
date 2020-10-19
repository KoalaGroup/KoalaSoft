// #include "TFile.h"
// #include "TTree.h"
// #include "KoaRawEvent.h"
// #include <map>
// #include <fstream>
// #include <iterator>

using namespace std;

void export_koala(const char* finname, const char* foutname)
{
  TFile* fin=new TFile(finname);

  // Retrieve the KOALA Raw raw event tree
  TTree* tin=(TTree*)fin->Get("koalasim");
  KoaRawEvent* evt = nullptr;
  tin->SetBranchAddress("KoaRawEvent", &evt);

  // Define output columns
  ofstream fout;
  fout.open(foutname);
  fout<<"Time_s, Time_us" << endl;

  // Export KOALA Raw data
  int entries=tin->GetEntries();
  for(int entry=0;entry<entries;entry++){
    tin->GetEntry(entry);

    //
    fout << (int)evt->Second << ", " << (int)evt->Usecond << endl;
  }
  cout << "KOALA Raw events: " << entries << endl;

  // Clean up
  delete fin;
  fout.close();
}
