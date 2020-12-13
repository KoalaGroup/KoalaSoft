#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void fit_tof(const char* infile,
             const char* dirname = "tof_spectrum",
             const char* suffix = "tof",
             const char* geoFile = "geo_standard.root",
             double loffset = 0,
             double zoffset_si1 = 0, double zoffset_si2 = 0, double zoffset_ge1 = 0, double zoffset_ge2 = 0
             )
{
  TStopwatch timer;

  //
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  auto distances = getChannelDistances(geoFile,loffset,zoffset); // flight distance of recoil particle
  auto positions = getChannelGlobalPosition(geoFile,zoffset); // strip position along z-axis

  //
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name, "Update");

  auto hdir = getDirectory(filein, dirname);
  auto h1s_ptr = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);

  // 
  std::map<Int_t, double> FittedTofs;
  std::map<Int_t, double> FittedTofErrors;
  std::map<Int_t, double> FittedSigmas;
  std::map<Int_t, double> FittedSigmaErrors;
  std::map<Int_t, double> PeakTofs;

  ParameterList<double> OutputParameters;
  auto& output_means = addValueContainer(OutputParameters, "Mean");
  auto& output_mean_errs = addValueContainer(OutputParameters, "Err(Mean)");
  auto& output_sigmas = addValueContainer(OutputParameters, "Sigma");
  auto& output_sigma_errs = addValueContainer(OutputParameters, "Err(Sigma)");
  auto& output_distances = addValueContainer(OutputParameters, "Distance");
  auto& output_positions = addValueContainer(OutputParameters, "Position");

  // fit
  auto encoder = KoaMapEncoder::Instance();
  auto fitPeak = [&] ()
                 {
                   // config the search paramters
                   Int_t search_maxpeaks=1;
                   auto ip_id = encoder->EncodeChannelID(0, 12);

                   // loop through all hists
                   for ( auto& hist : h1s_ptr ) {
                     auto id = hist.first;
                     auto h1 = hist.second;
                     Int_t det_id, ch_id;
                     ch_id = encoder->DecodeChannelID(id, det_id);

                     if(id < ip_id )
                       continue;

                     //
                     TSpectrum s(search_maxpeaks);
                     Int_t npeaks;
                     npeaks = s.Search(h1, 0.5, "", 0.3);

                     // fit window in sigma
                     double fit_window[4]={1,2,3,2};

                     if(npeaks>0) {
                       Double_t *xpeaks = s.GetPositionX();
                       PeakTofs.emplace(id, xpeaks[0]);
                       auto result = h1->Fit("gaus", "qs", "", xpeaks[0]-3, xpeaks[0]+3);

                       // first fit to get rough estimation
                       auto sigma = result->Parameter(2);
                       h1->GetXaxis()->SetRangeUser(xpeaks[0]-10*sigma, xpeaks[0]+10*sigma);
                       result = h1->Fit("gaus", "qs", "", xpeaks[0]-3*sigma, xpeaks[0]+1.5*sigma);

                       double mean = result->Parameter(1);
                       double sigma_fitted = result->Parameter(2);
                       double mean_err = result->ParError(1);
                       double sigma_err = result->ParError(2);

                       output_means.emplace(id, mean);
                       output_mean_errs.emplace(id, mean_err);
                       output_sigmas.emplace(id, sigma_fitted);
                       output_sigma_errs.emplace(id, sigma_err);
                     }
                   }
                 };
  fitPeak();

  //
  TMultiGraph* mg_tof = new TMultiGraph();
  mg_tof->SetName("mg_tof");
  mg_tof->SetTitle("Fitted TOF");
  auto graphs_tof = bookGraphByRecDetectorId("tof","Fitted TOF",8);
  for(auto& graph: graphs_tof) {
    mg_tof->Add(graph.second);
  }

  TMultiGraph* mg_resolution = new TMultiGraph();
  mg_resolution->SetName("mg_resolution");
  mg_resolution->SetTitle("Fitted TOF Sigma");
  auto graphs_resolution = bookGraphByRecDetectorId("resolution","Fitted TOF Sigma",8);
  for(auto& graph: graphs_resolution) {
    mg_resolution->Add(graph.second);
  }

  TMultiGraph* mg_correlation = new TMultiGraph();
  mg_correlation->SetName("mg_correlation");
  mg_correlation->SetTitle("TOF VS Sigma");
  auto graphs_correlation = bookGraphByRecDetectorId("correlation","TOF VS Sigma",8);
  for(auto& graph: graphs_correlation) {
    mg_correlation->Add(graph.second);
  }

  // filling
  Int_t index[4] = {0} ;
  Int_t global_index = 0;
  for(auto item: output_means)
  {
    auto id = item.first;
    auto mean = item.second;
    auto sigma = output_sigmas[id];
    auto l = distances[id];
    auto z = positions[id];

    output_distances.emplace(id, l);
    output_positions.emplace(id, z);

    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    graphs_tof[det_id]->SetPoint(index[det_id], z, mean);
    graphs_resolution[det_id]->SetPoint(index[det_id], z, sigma);
    graphs_correlation[det_id]->SetPoint(index[det_id], mean, sigma);

    index[det_id]++;
  }

  //
  TString outdir_name = dirname;
  outdir_name.Append("_fitted");
  auto hDirOut = getDirectory(filein, outdir_name.Data());
  writeHistos<TH1D*>(hDirOut, h1s_ptr);

  hDirOut->WriteTObject( mg_tof, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_tof,"WriteDelete");

  hDirOut->WriteTObject( mg_resolution, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_resolution,"WriteDelete");

  hDirOut->WriteTObject( mg_correlation, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_correlation,"WriteDelete");

  //
  TString outfile_pdf(infile);
  outfile_pdf.ReplaceAll(".root","_tof_fitted.pdf");
  printHistos<TH1D*>(h1s_ptr, outfile_pdf.Data());

  TString outfile_txt(infile);
  outfile_txt.ReplaceAll(".root","_tof_fitted.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  delete filein;

  //
  timer.Stop();
  timer.Print();
}
