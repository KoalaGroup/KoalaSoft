#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;
using namespace std;

void compute_z_difference(const char* param_file,
                          double mom,
                          const char* geoFile,
                          double zoffset_si1 = 0., double zoffset_si2 = 0., double zoffset_ge1 = 0., double zoffset_ge2 = 0.,
                          bool useLowerLimit = true
                          )
{
  // read in fitting parameter of CB_mean and associated error from aggregated results
  ValueContainer<double> e;
  ValueContainer<double> e_err;

  auto fit_params = readParameterList<double>(param_file);
  auto it = findValueContainer(fit_params, "Energy");
  if( it == fit_params.end() ) {
    cout << "Energy not available in config file: " << param_file << endl;
    return;
  }
  e = it->second;

  it = findValueContainer(fit_params, "Energy(Error)");
  if( it == fit_params.end() ) {
    cout << "Energy(Error) not available in config file: " << param_file << endl;
    return;
  }
  e_err = it->second;

  //
  auto calculator = new KoaElasticCalculator(mom);
  std::map<Int_t, double> CalculatedPositions;

  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm
  auto Positions = getChannelGlobalPosition(geoFile, zoffset);

  for(auto item: e){
    auto id = item.first;
    auto z = calculator->GetRecZByEnergy(item.second); // in mm
    CalculatedPositions.emplace(id, z);
  }

  //
  TMultiGraph* mg_diff_value = new TMultiGraph();
  mg_diff_value->SetName("mg_diff_vs_z");
  mg_diff_value->SetTitle("Difference between Energy-deduced Z and Model-deduced Z;Z (cm);Z_{energy}-Z_{model} (mm)");
  auto graphs_diff_value = bookGraphByRecDetectorId("diff_vs_z","Difference between Energy-deduced Z and Model-deduced Z;Z (cm);Z_{energy}-Z_{model} (mm)",8, 0.6);
  for(auto& graph: graphs_diff_value) {
    mg_diff_value->Add(&graph.second);
  }

  TGraphErrors* gr_diff_value = new TGraphErrors();
  gr_diff_value->SetName("gr_diff_vs_z");
  gr_diff_value->SetTitle("Difference between Energy-deduced Z and Model-deduced Z;Z (cm);Z_{energy}-Z_{model} (mm)");
  gr_diff_value->SetMarkerColor(kBlack);
  gr_diff_value->SetMarkerStyle(8);
  gr_diff_value->SetMarkerSize(0.6);

  auto h1_diff = bookH1dByDetectorId("zdiff", "Difference between Energy-deduced Z and Model-deduced Z;Z_{energy}-Z_{model} (mm)",
                                     100,-2,3);
 
  //
  auto encoder = KoaMapEncoder::Instance();
  int lower_id = encoder->EncodeChannelID(0, 17);

  Int_t index[4] = {0} ;
  Int_t global_index = 0;
  for(auto item: e){
    auto id = item.first;
    // auto fitted_err = e_err[id];
    auto calculated = CalculatedPositions[id]; // in mm
    auto z_model = 10*Positions[id]; // in mm

    if(useLowerLimit && id < lower_id) continue;

    //
    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    //
    graphs_diff_value[det_id].SetPoint(index[det_id], z_model, calculated-z_model);
    h1_diff[det_id].Fill(calculated-z_model);

    gr_diff_value->SetPoint(global_index, z_model, calculated-z_model);

    //
    global_index++;
    index[det_id]++;
  }

  //
  TString outfile_pdf(param_file);
  outfile_pdf.ReplaceAll(".txt", Form("_zdiff_%.3f_%.3f_%.3f_%.3f.pdf", zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2));
  printGraphs<TGraphErrors>(graphs_diff_value, outfile_pdf.Data());

  TString outfile_root(param_file);
  outfile_root.ReplaceAll(".txt",".root");
  auto fout = TFile::Open(outfile_root, "update");
  auto dir_out = getDirectory(fout, Form("zdiff_%.3f_%.3f_%.3f_%.3f", zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2));

  dir_out->WriteTObject( gr_diff_value, "", "WriteDelete");
  dir_out->WriteTObject( mg_diff_value, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dir_out, graphs_diff_value, "WriteDelete");

  writeHistos<TH1D>(dir_out, h1_diff);

  //
  delete fout;
}
