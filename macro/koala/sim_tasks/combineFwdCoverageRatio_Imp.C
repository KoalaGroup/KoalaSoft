#include "KoaHistUtility.h"

using namespace KoaUtility;
using namespace std;

void combineFwdCoverageRatio_Imp(
                                 map<string, double> list_file,
                                 const char* outfilename,
                                 const char* dirname
)
{
  // output txt paramaeters
  ParameterList<double> CountsParameter;
  auto& output_total = addValueContainer(CountsParameter, "Total");
  auto& output_covered = addValueContainer(CountsParameter, "FwdCovered");
  auto& output_ratio = addValueContainer(CountsParameter, "Ratio");
  
  auto encoder = KoaMapEncoder::Instance();
  auto ChIDs = encoder->GetRecChIDs();
  for(auto id: ChIDs) {
    output_total.emplace(id, 0);
    output_covered.emplace(id, 0);
  }

  // output hist
  int nbins = 300;
  double xlow =0;
  double xhigh = 3;

  auto h1_total = bookH1dByDetectorId("total","Event Counts (Total);E (MeV); EvtNr",
                                      nbins, xlow, xhigh);
  auto h1_covered = bookH1dByDetectorId("covered","Event Counts (Fwd Covered);E (MeV); EvtNr",
                                        nbins, xlow, xhigh);
  //
  auto fill_new_events = [&] (string filename, double fraction)
                         {
                           auto fin = TFile::Open(filename.data());
                           auto hdir = getDirectory(fin, dirname);
                           auto htotal = getHistosByDetectorId<TH1D>(hdir, "total");
                           auto hcovered = getHistosByDetectorId<TH1D>(hdir, "covered");

                           for(auto item: h1_total){
                             auto id = item.first;
                             h1_total[id].Add(htotal[id],fraction);
                             h1_covered[id].Add(hcovered[id],fraction);
                           }
                           delete fin;
                         };

  //
  for(auto item: list_file){
    fill_new_events(item.first, item.second);
  }

  // output efficiency
  Int_t RecIdRange[2];
  encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  map<int, TEfficiency*> eff;
  for(auto sensor : ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    TString volName = encoder->DetectorIDToVolName(sensor);
    volName.ReplaceAll("Sensor", "");

    eff[sensor] = new TEfficiency(h1_covered[sensor], h1_total[sensor]);
    eff[sensor]->SetName(Form("ratio_%s",volName.Data()));
    eff[sensor]->SetTitle(Form("Ratio of Fwd-Covered Events (%s); E (MeV);Ratio", volName.Data()));
    eff[sensor]->SetStatisticOption(TEfficiency::kFAC);
    eff[sensor]->SetConfidenceLevel(0.95);
    eff[sensor]->SetFillColor(kBlue);
    eff[sensor]->SetFillStyle(3005);
    eff[sensor]->SetMarkerColor(kBlue);
    eff[sensor]->SetMarkerStyle(20);
    eff[sensor]->SetMarkerSize(0.3);
  }

  //
  TString outputfilename(outfilename);
  auto fout = TFile::Open(outputfilename.Data(), "update");
  auto dirout = getDirectory(fout, dirname);
  writeHistos<TH1D>(dirout, h1_covered);
  writeHistos<TH1D>(dirout, h1_total);

  for(auto sensor : ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    dirout->WriteTObject(eff[sensor],"","WriteDelete");
  }

  //
  delete fout;
}
