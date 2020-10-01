// #include "TFile.h"
// #include "TTree.h"
// #include "KoaEmsRawEvent.h"
// #include <map>
// #include <fstream>
// #include <iterator>

using namespace std;

void export_ems(const char* finname, const char* foutname)
{
  TFile* fin=new TFile(finname);

  // Retrieve the EMS raw event tree
  TTree* tin=(TTree*)fin->Get("Ems");
  KoaEmsRawEvent* evt = nullptr;
  tin->SetBranchAddress("KoaEmsRawEvent", &evt);

  // Retrieve the scalor channel mapping
  map<string,int>* ScalorChMap = nullptr;
  fin->GetObject("ScalorChMap", ScalorChMap);

  // Define output columns
  ofstream fout;
  fout.open(foutname);
  fout<<"Time_s, Time_us, Event, ";

  for(auto it = ScalorChMap->begin(); it != ScalorChMap->end(); it++){
    auto name = it->first;
    auto ch   = it->second;

    fout << name;
    if(next(it) != ScalorChMap->end()){
      fout << ", ";
    }
    cout << name << " (" << ch << ")" << endl;
  }
  fout << endl;

  // Export EMS data
  int entries=tin->GetEntries();
  for(int entry=0;entry<entries;entry++){
    tin->GetEntry(entry);

    //
    fout << evt->Second << ", " << evt->Usecond << ", " << evt->EventNr << ", ";

    for(auto it = ScalorChMap->begin(); it != ScalorChMap->end(); it++) {
      fout << evt->Scalor[it->second];
      if(next(it) != ScalorChMap->end()){
        fout << ", ";
      }
    }
    fout << endl;
  }
  cout << "EMS events: " << entries << endl;

  // Clean up
  delete fin;
  fout.close();
}
