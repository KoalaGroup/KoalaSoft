#include "KoaGraphUtility.h"

using namespace KoaUtility;

void compareClusterDigiEnergy(
    const char* clusterFile,
    const char* digiFile
                              )
{
  // cluster
  auto cluster_params = readParameterList<double>(clusterFile);

  auto it = findValueContainer(cluster_params, "Mean");
  auto cluster_energy = it->second;
  it = findValueContainer(cluster_params, "Position");
  auto cluster_position = it->second;

  // digi
  auto digi_params = readParameterList<double>(digiFile);

  it = findValueContainer(digi_params, "Mean");
  auto digi_energy = it->second;
  it = findValueContainer(digi_params, "Position");
  auto digi_position = it->second;

  //
  TMultiGraph* mg_diff_value = new TMultiGraph();
  mg_diff_value->SetName("mg_diff");
  mg_diff_value->SetTitle("Energy discrepancy between cluster and digi energy");
  auto graphs_diff_value = bookGraphByRecDetectorId("diff_value","Energy discrepancy between cluster and digi energy",8);
  for(auto& graph: graphs_diff_value) {
    mg_diff_value->Add(graph.second);
  }

  auto gr_diff = new TGraph();
  gr_diff->SetName("gr_diff_ClusterVsDigi");
  gr_diff->SetTitle("Energy discrepancy between cluster and digi energy;Z(cm);E_{cluster} - E_{digi} (MeV)");
  gr_diff->SetMarkerStyle(8);
  gr_diff->SetMarkerSize(1);

  auto encoder = KoaMapEncoder::Instance();

  int global_index = 0;
  Int_t index[4] = {0} ;
  for(auto item: cluster_energy)
  {
    auto id = item.first;
    auto cluster_e = item.second;
    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    auto search = digi_energy.find(id);
    if(search == digi_energy.end())
      continue;

    auto digi_e = digi_energy[id];
    auto z_pos = cluster_position[id];

    gr_diff->SetPoint(global_index++, z_pos, cluster_e - digi_e);
    graphs_diff_value[det_id]->SetPoint(index[det_id]++, z_pos, cluster_e - digi_e);
  }

  auto c = new TCanvas();
  mg_diff_value->Draw("AP");
}
