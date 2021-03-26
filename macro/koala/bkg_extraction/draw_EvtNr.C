#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void draw_EvtNt(
                const char* filename,
                const char* outfilename,
                const char* dirname,
                double mom,
                // const char* solid_angle_filename = "SolidAngle.txt",
                const char* geoFile = "geo_standard.root",
                double zoffset_si1 = 0.18, double zoffset_si2 = 0.13, double zoffset_ge1 = 0.12, double zoffset_ge2 = 0.12

)
{
  ////////////////////////////////////////
  // Preparation
  ////////////////////////////////////////

  Double_t fProtonMass = 0.938272081;

  // Map encoder
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  // elastic scattering kinematic calculator
  auto calculator = new KoaElasticCalculator(mom);

  // Detector position correction applied to imput geometry model
  // double zoffset[4] = {0.18, 0.13, 0.12, 0.12}; // in cm
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm

  // Retrieve the strips/channels z-pos, alpha, expected-energy
  auto CalculatedEnergies = getChannelEnergies(mom, geoFile,yoffset,zoffset);
  auto DeltaTs = getChannelDeltaT(mom,geoFile,yoffset,zoffset);
  auto Positions = getChannelGlobalPosition(geoFile, zoffset);
  
  auto geoHandler = getGeometryHandler(geoFile);
  auto ChToStripMap = geoHandler->GetChIdToStripIds();

  ////////////////////////////////////////
  // Read in fitted event number
  ////////////////////////////////////////

  ValueContainer<double> evtNr;
  ValueContainer<double> evtNr_err;
  ValueContainer<double> mean;
  ValueContainer<double> mean_err;

  auto fit_params = readParameterList<double>(filename);

  auto it = findValueContainer(fit_params, "EvtNr");
  if( it == fit_params.end() ) {
    cout << "EvtNr not available in config file: " << filename << endl;
    return;
  }
  evtNr = it->second;

  it = findValueContainer(fit_params, "CB_mean");
  if( it == fit_params.end() ) {
    cout << "CB_mean not available in config file: " << filename << endl;
    return;
  }
  mean = it->second;

  it = findValueContainer(fit_params, "Err(EvtNr)");
  if( it == fit_params.end() ) {
    cout << "Err(EvtNr) not available in config file: " << filename << endl;
    return;
  }
  evtNr_err = it->second;

  it = findValueContainer(fit_params, "Err(CB_mean)");
  if( it == fit_params.end() ) {
    cout << "Err(CB_mean) not available in config file: " << filename << endl;
    return;
  }
  mean_err = it->second;

  ////////////////////////////////////////
  // Output Parameters
  ////////////////////////////////////////

  ParameterList<double> ChannelParams;
  auto& output_energy = addValueContainer(ChannelParams, "Energy");
  auto& output_N = addValueContainer(ChannelParams, "N");
  auto& output_dN = addValueContainer(ChannelParams, "N/StripNr");
  auto& output_t = addValueContainer(ChannelParams, "t");
  auto& output_dNdt = addValueContainer(ChannelParams, "dN/dt");

  ////////////////////////////////////////
  // Book graphs
  ////////////////////////////////////////
  TMultiGraph* mg_N = new TMultiGraph();
  mg_N->SetName("mg_N");
  mg_N->SetTitle("Counts VS Energy; E (MeV); N");
  auto graphs_N = bookGraphByRecDetectorId("N","Counts VS Energy; E(MeV);N",20, 0.6);
  for(auto& graph: graphs_N) {
    mg_N->Add(&graph.second);
  }

  TMultiGraph* mg_dN = new TMultiGraph();
  mg_dN->SetName("mg_dN");
  mg_dN->SetTitle("Average Counts VS Energy ; E (MeV); dN/NrStrips");
  auto graphs_dN = bookGraphByRecDetectorId("dN","Average Counts VS Energy;E (Mev);dN/NrStrips",20, 0.6);
  for(auto& graph: graphs_dN) {
    mg_dN->Add(&graph.second);
  }

  // TMultiGraph* mg_dNdOmega = new TMultiGraph();
  // mg_dNdOmega->SetName("mg_dNdOmega");
  // mg_dNdOmega->SetTitle("dN/d#Omega VS Energy; E (MeV); dN/d#Omega");
  // auto graphs_dNdOmega = bookGraphByRecDetectorId("dNdOmega","dN/d#Omega VS Energy;E (MeV);dN/d#Omega",20, 0.6);
  // for(auto& graph: graphs_dNdOmega) {
  //   mg_dNdOmega->Add(&graph.second);
  // }

  TMultiGraph* mg_dNdt = new TMultiGraph();
  mg_dNdt->SetName("mg_dNdt");
  mg_dNdt->SetTitle("dN/dt VS |t|;|t| (GeV/c)^2;dN/dt");
  auto graphs_dNdt = bookGraphByRecDetectorId("dNdt","dN/dt VS |t|; |t| (GeV/c)^2; dN/dt", 20, 0.6);
  for(auto& graph: graphs_dNdt) {
    mg_dNdt->Add(&graph.second);
  }

  ////////////////////////////////////////
  // Fill graphs
  ////////////////////////////////////////

  Int_t index[4] = {0} ;
  for(auto item: evtNr) {
    auto id = item.first;
    auto evt = item.second;

    auto nr_strips = ChToStripMap[id].size();
    auto dt = DeltaTs[id];
    auto t = 2*fProtonMass*mean[id]/1000.;
    auto t_err = 2*fProtonMass*mean_err[id]/1000;

    // fill output paramters
    output_energy.emplace(id, mean[id]);
    output_N.emplace(id, evt);
    output_dN.emplace(id, evt/nr_strips);
    output_dNdt.emplace(id, evt/dt);
    output_t.emplace(id, t);

    //
    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    graphs_N[det_id].SetPoint(index[det_id], mean[id], evt);
    graphs_N[det_id].SetPointError(index[det_id], mean_err[id], evtNr_err[id]);

    graphs_dN[det_id].SetPoint(index[det_id], mean[id], evt/nr_strips);
    graphs_dN[det_id].SetPointError(index[det_id], mean_err[id], evtNr_err[id]/nr_strips);

    graphs_dNdt[det_id].SetPoint(index[det_id], t, evt/dt);
    graphs_dNdt[det_id].SetPointError(index[det_id], t_err, evtNr_err[id]/dt);

    index[det_id]++;
  }

  ////////////////////////////////////////
  // Save graphs
  ////////////////////////////////////////

  auto fileout = TFile::Open(outfilename,"update");
  auto dirout = getDirectory(fileout, dirname);


  dirout->WriteTObject( mg_N, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dirout, graphs_N, "WriteDelete");

  dirout->WriteTObject( mg_dN, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dirout, graphs_dN, "WriteDelete");

  dirout->WriteTObject( mg_dNdt, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dirout, graphs_dNdt, "WriteDelete");

// txt
  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".txt", Form("_Normalized.txt"));
  printValueList<double>(ChannelParams, outfile_txt.Data());

//
  delete fileout;
}
