#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;
using namespace std;

void draw_fit_parameters(const char* param_file,
                         bool useLowerLimit = true,
                         int lower_ch = 21
                         )
{
    auto fit_params = readParameterList<double>(param_file);

    auto it = findValueContainer(fit_params, "Energy");
    if( it == fit_params.end() ) {
      cout << "Energy not available in config param_file: " << param_file << endl;
      return;
    }
    auto energy = it->second;

    it = findValueContainer(fit_params, "Sigma");
    if( it == fit_params.end() ) {
      cout << "CB_sigma not available in config param_file: " << param_file << endl;
      return;
    }
    auto sigma = it->second;

    it = findValueContainer(fit_params, "CB_alpha1");
    if( it == fit_params.end() ) {
      cout << "CB_alpha1 not available in config param_file: " << param_file << endl;
      return;
    }
    auto cb_alpha1 = it->second;

    it = findValueContainer(fit_params, "CB_alpha2");
    if( it == fit_params.end() ) {
      cout << "CB_alpha2 not available in config param_file: " << param_file << endl;
      return;
    }
    auto cb_alpha2 = it->second;

    it = findValueContainer(fit_params, "CB_n1");
    if( it == fit_params.end() ) {
      cout << "CB_n1 not available in config param_file: " << param_file << endl;
      return;
    }
    auto cb_n1 = it->second;

    it = findValueContainer(fit_params, "CB_n2");
    if( it == fit_params.end() ) {
      cout << "CB_n2 not available in config param_file: " << param_file << endl;
      return;
    }
    auto cb_n2 = it->second;

    //
    TMultiGraph* mg_sigma = new TMultiGraph();
    mg_sigma->SetName("mg_sigma");
    mg_sigma->SetTitle("Fitting Paramater: CB sigma;E (MeV);#sigma");
    auto gr_sigma = bookGraphByRecDetectorId("sigma","Fitting Paramater: CB sigma;E (MeV);#sigma",8, 0.6);
    for(auto& graph: gr_sigma) {
      mg_sigma->Add(&graph.second);
    }

    TMultiGraph* mg_alpha1 = new TMultiGraph();
    mg_alpha1->SetName("mg_alpha1");
    mg_alpha1->SetTitle("Fitting Paramater: CB #alpha_{leading};E (MeV);#alpha_{leading}");
    auto gr_alpha1 = bookGraphByRecDetectorId("alpha1","Fitting Paramater: CB #alpha_{leading};E (MeV);#alpha_{leading}",8, 0.6);
    for(auto& graph: gr_alpha1) {
      mg_alpha1->Add(&graph.second);
    }

    TMultiGraph* mg_alpha2 = new TMultiGraph();
    mg_alpha2->SetName("mg_alpha2");
    mg_alpha2->SetTitle("Fitting Paramater: CB #alpha_{trail};E (MeV);#alpha_{trail}");
    auto gr_alpha2 = bookGraphByRecDetectorId("alpha2","Fitting Paramater: CB #alpha_{trail};E (MeV);#alpha_{trail}",8, 0.6);
    for(auto& graph: gr_alpha2) {
      mg_alpha2->Add(&graph.second);
    }

    TMultiGraph* mg_n1 = new TMultiGraph();
    mg_n1->SetName("mg_n1");
    mg_n1->SetTitle("Fitting Paramater: CB n_{leading};E (MeV);n_{leading}");
    auto gr_n1 = bookGraphByRecDetectorId("n1","Fitting Paramater: CB n_{leading};E (MeV);n_{leading}",8, 0.6);
    for(auto& graph: gr_n1) {
      mg_n1->Add(&graph.second);
    }

    TMultiGraph* mg_n2 = new TMultiGraph();
    mg_n2->SetName("mg_n2");
    mg_n2->SetTitle("Fitting Paramater: CB n_{trail};E (MeV);n_{trail}");
    auto gr_n2 = bookGraphByRecDetectorId("n2","Fitting Paramater: CB n_{trail};E (MeV);n_{trail}",8, 0.6);
    for(auto& graph: gr_n2) {
      mg_n2->Add(&graph.second);
    }

    //
    auto encoder = KoaMapEncoder::Instance();
    int lower_id = encoder->EncodeChannelID(0, lower_ch-1);

    Int_t index[4] = {0} ;
    Int_t global_index = 0;
    for(auto item: energy){
      auto id = item.first;
      auto e = item.second;

      if(useLowerLimit && id < lower_id) continue;

      //
      Int_t det_id, ch_id;
      ch_id = encoder->DecodeChannelID(id, det_id);

      gr_sigma[det_id].SetPoint(index[det_id], e, sigma[id]);
      gr_alpha1[det_id].SetPoint(index[det_id], e, cb_alpha1[id]);
      gr_alpha2[det_id].SetPoint(index[det_id], e, cb_alpha2[id]);
      gr_n1[det_id].SetPoint(index[det_id], e, cb_n1[id]);
      gr_n2[det_id].SetPoint(index[det_id], e, cb_n2[id]);

      //
      index[det_id]++;
    }

    TString outfile_root(param_file);
    outfile_root.ReplaceAll(".txt",".root");
    auto fout = TFile::Open(outfile_root, "update");
    auto dir_out = getDirectory(fout, "cb_parameters");

    dir_out->WriteTObject( mg_sigma, "", "WriteDelete");
    writeGraphs<TGraphErrors>(dir_out, gr_sigma, "WriteDelete");
    dir_out->WriteTObject( mg_alpha1, "", "WriteDelete");
    writeGraphs<TGraphErrors>(dir_out, gr_alpha1, "WriteDelete");
    dir_out->WriteTObject( mg_alpha2, "", "WriteDelete");
    writeGraphs<TGraphErrors>(dir_out, gr_alpha2, "WriteDelete");
    dir_out->WriteTObject( mg_n1, "", "WriteDelete");
    writeGraphs<TGraphErrors>(dir_out, gr_n1, "WriteDelete");
    dir_out->WriteTObject( mg_n2, "", "WriteDelete");
    writeGraphs<TGraphErrors>(dir_out, gr_n2, "WriteDelete");

    delete fout;
}
