#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void apply_solidAngle(const char* countsFile,
                      const char* solidAngleFile,
                      const char* outfile,
                      double mom,
                      const char* geoFile,
                      double zoffset_si1 = 0, double zoffset_si2 = 0, double zoffset_ge1 = 0, double zoffset_ge2 = 0,
                      double scale_factor = 1
                      )
{
  TStopwatch timer;
  
  // get delta 4-momentum transfer for each strip
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm

  auto DeltaTs = getChannelDeltaT(mom,geoFile,yoffset,zoffset);

  // input counts
  auto counts_params = readParameterList<double>(countsFile);

  auto it = findValueContainer(counts_params, "Alpha");
  auto alphas = it->second;
  it = findValueContainer(counts_params, "|t|");
  auto t_means = it->second;
  it = findValueContainer(counts_params, "Err(|t|)");
  auto t_errs = it->second;
  it = findValueContainer(counts_params, "Count");
  auto counts = it->second;

  // input solid angles
  auto solidAngle_params = readParameterList<double>(solidAngleFile);

  it = findValueContainer(solidAngle_params, "SolidAngle");
  auto solid_angles = it->second;

  // output parameters
  ParameterList<double> OutParameters;
  auto& output_alphas = addValueContainer(OutParameters, "Alpha");
  auto& output_t = addValueContainer(OutParameters, "|t|");
  auto& output_dNdt = addValueContainer(OutParameters, "dN/dt");
  auto& output_dNdOmega = addValueContainer(OutParameters, "dN/dOmega");
  auto& output_counts = addValueContainer(OutParameters, "Count");
  auto& output_dt = addValueContainer(OutParameters, "dt");
  auto& output_solidAngle = addValueContainer(OutParameters, "SolidAngle");
  auto& output_factor = addValueContainer(OutParameters, "ScaleFactor");
  auto& output_t_errs = addValueContainer(OutParameters, "Err(|t|)");

  //
  TMultiGraph* mg_dNdOmega = new TMultiGraph();
  mg_dNdOmega->SetName("mg_dN/dOmega");
  mg_dNdOmega->SetTitle("dN/dOmega VS |t|;|t| (GeV/c)^2;dN/dOmega");
  auto graphs_dNdOmega = bookGraphByRecDetectorId("dN/dOmega","dN/dOmega VS |t|",8);
  for(auto& graph: graphs_dNdOmega) {
    mg_dNdOmega->Add(graph.second);
  }

  TMultiGraph* mg_dNdt = new TMultiGraph();
  mg_dNdt->SetName("mg_dN/dt");
  mg_dNdt->SetTitle("dN/dt VS |t|;|t| (GeV/c)^2;dN/dt");
  auto graphs_dNdt = bookGraphByRecDetectorId("dN/dt","dN/dt VS |t|",8);
  for(auto& graph: graphs_dNdt) {
    mg_dNdt->Add(graph.second);
  }

  TMultiGraph* mg_N = new TMultiGraph();
  mg_N->SetName("mg_N");
  mg_N->SetTitle("Counts VS Alpha");
  auto graphs_N = bookGraphByRecDetectorId("N","Counts VS Alpha",8);
  for(auto& graph: graphs_N) {
    mg_N->Add(graph.second);
  }

  TMultiGraph* mg_dOmega = new TMultiGraph();
  mg_dOmega->SetName("mg_dOmega");
  mg_dOmega->SetTitle("SolidAngle VS #alpha");
  auto graphs_dOmega = bookGraphByRecDetectorId("dOmega","SolidAngle VS #alpha",8);
  for(auto& graph: graphs_dOmega) {
    mg_dOmega->Add(graph.second);
  }

  //
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  Int_t index[4] = {0} ;
  for(auto item: alphas) {
    auto id = item.first;

    auto alpha = item.second;
    auto t_mean = t_means[id];
    auto t_err = t_errs[id];
    auto count = counts[id];
    auto solid_angle = solid_angles[id];
    auto dt = DeltaTs[id];

    //
    if(alpha < 0) {
      continue;
    }

    //
    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    output_alphas.emplace(id, alpha);
    output_t.emplace(id, t_mean);
    output_counts.emplace(id, count);
    output_dt.emplace(id, dt);
    output_solidAngle.emplace(id, solid_angle);
    output_factor.emplace(id, scale_factor);
    output_t_errs.emplace(id, t_err);
    output_dNdOmega.emplace(id, count/solid_angle);
    output_dNdt.emplace(id, count/dt);

    graphs_dNdOmega[det_id]->SetPoint(index[det_id], t_mean, output_dNdOmega[id]);
    graphs_dNdt[det_id]->SetPoint(index[det_id], t_mean, output_dNdt[id]);
    graphs_N[det_id]->SetPoint(index[det_id], alpha , output_counts[id]);
    graphs_dOmega[det_id]->SetPoint(index[det_id], alpha , output_solidAngle[id]);

    index[det_id]++;
  }

  // output
  printValueList<double>(OutParameters, outfile);

  TString outfile_root(outfile);
  outfile_root.ReplaceAll(".txt",".root");
  auto fout = new TFile(outfile_root,"update");

  auto hDirOut = getDirectory(fout, "dNdOmega");
  hDirOut->WriteTObject( mg_dNdOmega,"", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_dNdOmega, "WriteDelete");

  hDirOut = getDirectory(fout, "dNdt");
  hDirOut->WriteTObject( mg_dNdt,"", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_dNdt, "WriteDelete");

  hDirOut = getDirectory(fout, "N");
  hDirOut->WriteTObject( mg_N,"", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_N, "WriteDelete");

  hDirOut = getDirectory(fout, "SolidAngle");
  hDirOut->WriteTObject( mg_dOmega,"", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_dOmega, "WriteDelete");

  //
  delete fout;

  //
  timer.Stop();
  timer.Print();
}
