// #include "TFile.h"
// #include "TTree.h"
// #include "KoaEmsRawEvent.h"
// #include <map>
// #include <fstream>
// #include <iterator>
#include "KoaUtility.h"

using namespace KoaUtility;
using namespace std;

void export_ems(const char* finname,
                const char* elistFileName = nullptr,
                const char* edirName = "/",
                const char* elistName = "rate_elist"
                )
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
  TString foutname = finname;
  if(elistFileName) {
    foutname.ReplaceAll("_EmsRawEvent.root","_scalor_selected.csv");
  }
  else{
    foutname.ReplaceAll("_EmsRawEvent.root","_scalor.csv");
  }

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

  // retrieve elist
  TFile* felist = nullptr;
  TDirectory* eDir = nullptr;
  TEventList* eList = nullptr;
  if ( elistFileName ) {
    felist = new TFile(elistFileName);
    eDir = getDirectory(felist, edirName);
    eList = getObject<TEventList>(eDir, elistName);
  }

  // Export EMS data
  Long_t entries = tin->GetEntries();
  if ( elistFileName ) {
    entries = eList->GetN();
  }

  for(int entry=0;entry<entries;entry++){
    if ( elistFileName ) {
      auto tree_index = eList->GetEntry(entry);
      tin->GetEntry(tree_index);
    }
    else {
      tin->GetEntry(entry);
    }

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
