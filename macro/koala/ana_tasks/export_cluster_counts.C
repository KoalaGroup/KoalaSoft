#include <map>

using namespace std;

void export_cluster_counts(const char* clustercounts_file)
{
  TFile* fin=new TFile(clustercounts_file);

  // Retrieve the KOALA Raw raw event tree
  TTree* tin=(TTree*)fin->Get("ClusterSumCount");
  Long64_t sec, usec;
  tin->SetBranchAddress("Second", &sec);
  tin->SetBranchAddress("Usecond", &usec);
  std::map<int, Long_t> *sum_counts = nullptr;
  tin->SetBranchAddress("ClusterSumCount", &sum_counts);

  // Define output columns
  ofstream fout;
  TString foutname(clustercounts_file);
  foutname.ReplaceAll("_counts.root", "_sum_counts.csv");
  fout.open(foutname.Data());

  fout<<"Time_s, Time_us, ";
  tin->GetEntry(0);
  auto encoder = KoaMapEncoder::Instance();
  for(auto it = sum_counts->begin(); it != sum_counts->end(); it++){
    auto id = it->first;
    TString volName;
    Int_t ch = encoder->DecodeChannelID(id, volName);
    volName.ReplaceAll("Sensor", "");
    volName.Append(Form("_%d",ch+1));

    fout << volName.Data();
    if (next(it) != sum_counts->end()) {
      fout << ", ";
    }
    else {
      fout << endl;
    }
  }

  // Export
  int entries=tin->GetEntries();
  for(int entry=0;entry<entries;entry++){
    tin->GetEntry(entry);

    //
    fout << sec << ", " << usec << ", ";
    for(auto it = sum_counts->begin(); it != sum_counts->end(); it++){
      fout << it->second;
      if (next(it) != sum_counts->end()) {
        fout << ", ";
      }
      else {
        fout << endl;
      }
    }
  }
  cout << "KOALA entries: " << entries << endl;

  // Clean up
  delete fin;
  fout.close();
}
