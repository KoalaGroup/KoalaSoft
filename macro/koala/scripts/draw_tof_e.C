#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void draw_tof_e(const char* toffile = "tof.txt",
                const char* energyfile = "energy.txt",
                const char* outfile = "tof_e.root"
                )
{
  auto tof_params = readParameterList<double>(toffile);
  auto it = findValueContainer(tof_params, "Mean");
  auto tofs = it->second;
  
  auto energy_params = readParameterList<double>(energyfile);
  it = findValueContainer(energy_params, "Mean");
  auto energies = it->second;

  TMultiGraph* mg_tof_e = new TMultiGraph();
  mg_tof_e->SetName("mg_tof_e");
  mg_tof_e->SetTitle("TOF-E");
  auto graphs_tof_e = bookGraphByRecDetectorId("tof_e","TOF-E",8);
  for(auto& graph: graphs_tof_e) {
    mg_tof_e->Add(graph.second);
  }

  // filling
  auto encoder = KoaMapEncoder::Instance();

  Int_t index[4] = {0} ;
  Int_t global_index = 0;
  for(auto item: tofs)
  {
    auto id = item.first;
    auto tof = item.second;

    auto search = energies.find(id);
    if (search == energies.end() )
      continue;

    auto e = energies[id];

    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    graphs_tof_e[det_id]->SetPoint(index[det_id], e, tof);

    index[det_id]++;
  }

  auto fout = TFile::Open(outfile, "update");
  fout->WriteTObject( mg_tof_e, "", "WriteDelete");
  writeGraphs<TGraph*>(fout, graphs_tof_e,"WriteDelete");
}
