#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;
using namespace std;

void correct_energy_difference(const char* param_file,
                               double mom,
                               const char* geoFile,
                               double zoffset_si1 = 0.18, double zoffset_si2 = 0.13, double zoffset_ge1 = 0.13, double zoffset_ge2 = 0.13,
                               double yoffset_si1 = 0, double yoffset_si2=0, double yoffset_ge1=0, double yoffset_ge2=0,
                               bool useLowerLimit = true
                               )
{
  // correct function: deltaE vs E_fitted
  TF1 fsi1("fsi1", "-54.8*x+48.052+16.3*x*x",0,2);
  TF1 fsi2("fsi2", "-54.8*x+48.052+16.3*x*x",0,2);

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
  std::map<Int_t, double> CalculatedEnergies;

  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] = {yoffset_si1, yoffset_si2, yoffset_ge1, yoffset_ge2}; // in cm
  // auto Positions = getChannelGlobalPosition(geoFile, zoffset);
  auto Alphas = getChannelAlphas(geoFile, yoffset, zoffset);

  for(auto item: e){
    auto id = item.first;
    auto energy = calculator->GetEnergyByAlpha(Alphas[id]);
    CalculatedEnergies.emplace(id, energy);
  }

  //
  TGraphErrors* graph_calculated = new TGraphErrors();
  graph_calculated->SetName("graph_calculated");
  graph_calculated->SetTitle("Energy VS Recoil Angle (Calculated);#alpha (#circ);Energy (MeV)");
  graph_calculated->SetMarkerColor(kBlue);
  graph_calculated->SetMarkerStyle(22);
  graph_calculated->SetMarkerSize(0.6);
  TGraphErrors* graph_corrected = new TGraphErrors();
  graph_corrected->SetName("graph_corrected");
  graph_corrected->SetTitle("Energy VS Recoil Angle (Corrected);#alpha (#circ);Energy (MeV)");
  graph_corrected->SetMarkerColor(kRed);
  graph_corrected->SetMarkerStyle(20);
  graph_corrected->SetMarkerSize(0.6);

  TMultiGraph* mg=new TMultiGraph();
  mg->SetName("mg_energy_vs_alpha");
  mg->SetTitle("Energy VS Recoil Angle;#alpha (#circ);Energy (MeV)");
  mg->Add(graph_calculated, "P");
  mg->Add(graph_corrected, "P");

  //
  TMultiGraph* mg_diff = new TMultiGraph();
  mg_diff->SetName("mg_relativeDiff_vs_alpha");
  mg_diff->SetTitle("Relative Difference between Fitted and Calculated Energy;#alpha (#cirec);#Delta E/E");
  auto graphs_diff = bookGraphByRecDetectorId("relativeDiff_vs_alpha","Relative Difference between Fitted and Calculated Energy;#alpha (#circ);#Delta E/E",8, 0.6);
  for(auto& graph: graphs_diff) {
    mg_diff->Add(&graph.second);
  }

  TMultiGraph* mg_diff_value = new TMultiGraph();
  mg_diff_value->SetName("mg_diff_vs_alpha");
  mg_diff_value->SetTitle("Difference between Fitted and Calculated Energy;#alpha (#circ);#Delta E (MeV)");
  auto graphs_diff_value = bookGraphByRecDetectorId("diff_vs_alpha","Difference between Fitted and Calculated Energy;#alpha (#circ);#Delta E (MeV)",8, 0.6);
  for(auto& graph: graphs_diff_value) {
    mg_diff_value->Add(&graph.second);
  }

  TGraphErrors* graph_diff = new TGraphErrors();
  graph_diff->SetName("graph_relativeDiff_vs_alpha");
  graph_diff->SetTitle("Relative Difference between Fitted and Calculated Energy;#alpha (#circ);#Delta E/E");
  graph_diff->SetMarkerColor(kBlue);
  graph_diff->SetMarkerStyle(8);
  graph_diff->SetMarkerSize(1);

  TGraphErrors* graph_diff_value = new TGraphErrors();
  graph_diff_value->SetName("graph_diff_vs_alpha");
  graph_diff_value->SetTitle("Difference between Fitted and Calculated Energy;#alpha (#circ);#Delta E (MeV)");
  graph_diff_value->SetMarkerColor(kBlack);
  graph_diff_value->SetMarkerStyle(8);
  graph_diff_value->SetMarkerSize(1);

  //
  auto encoder = KoaMapEncoder::Instance();
  int lower_id = encoder->EncodeChannelID(0, 17);
  Int_t index[4] = {0} ;
  Int_t global_index = 0;
  for(auto item: e){
    auto id = item.first;
    auto fitted = item.second;
    auto fitted_err = e_err[id];
    auto calculated = CalculatedEnergies[id];
    auto alpha = Alphas[id];

    if(useLowerLimit && id < lower_id) continue;

    //
    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);
    if(calculated < 2.){
      if(det_id == 0){
        fitted += fsi1.Eval(fitted)/1000.;
      }
      else if(det_id == 1) {
        fitted += fsi2.Eval(fitted)/1000.;
      }
    }

    //
    graph_corrected->SetPoint(global_index, alpha, fitted);
    graph_corrected->SetPointError(global_index, 0, fitted_err);
    graph_calculated->SetPoint(global_index, alpha, calculated);

    graph_diff->SetPoint(global_index, alpha, (fitted-calculated)/calculated);
    graph_diff_value->SetPoint(global_index, alpha, fitted-calculated);

    graphs_diff[det_id].SetPoint(index[det_id], alpha, (fitted-calculated)/calculated);
    graphs_diff_value[det_id].SetPoint(index[det_id], alpha, (fitted-calculated));

    //
    global_index++;
    index[det_id]++;
  }

  //
  TString outfile_root(param_file);
  outfile_root.ReplaceAll(".txt",".root");
  auto fout = TFile::Open(outfile_root, "update");
  auto dir_out = getDirectory(fout, Form("ecorrected_zoffset_%.3f_%.3f_%.3f_%.3f", zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2));

  dir_out->WriteTObject( graph_corrected, "", "WriteDelete");
  dir_out->WriteTObject( graph_calculated, "", "WriteDelete");
  dir_out->WriteTObject( mg, "", "WriteDelete");

  dir_out->WriteTObject( graph_diff, "", "WriteDelete");
  dir_out->WriteTObject( graph_diff_value, "", "WriteDelete");

  dir_out->WriteTObject( mg_diff, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dir_out, graphs_diff,"WriteDelete");

  dir_out->WriteTObject( mg_diff_value, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dir_out, graphs_diff_value, "WriteDelete");

  //
  delete fout;
}
