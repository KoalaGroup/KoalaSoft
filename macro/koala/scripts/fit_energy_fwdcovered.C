#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void fit_energy_fwdcovered(const char* infile,
                           double mom = 2.2,
                           const char* dirname = "rec_cluster_energy_FirstHit_fwdhit_TimeValid",
                           const char* suffix = "cluster_energy_firstHit_fwdhit_TimeValid",
                           const char* geoFile = "geo_standard.root",
                           int ip_ch = 12,
                           double loffset = 0,
                           double zoffset_si1 = 0.18, double zoffset_si2 = 0.13, double zoffset_ge1 = 0.14, double zoffset_ge2 = 0.14
                           )
{
  TStopwatch timer;

  // geoometry 
  TFile* fgeo=new TFile(geoFile);
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  KoaGeoHandler* geoHandler = new KoaGeoHandler(kFALSE);

  // zoffset_si1 = 0.18; zoffset_si2 = 0.13; zoffset_ge1 = 0.14;zoffset_ge2 = 0.14;
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] ={0};
  auto distances = getChannelDistances(geoFile,loffset,zoffset); // flight distance of recoil particle
  auto positions = getChannelGlobalPosition(geoFile,zoffset); // strip position along z-axis
  auto alphas = getChannelAlphas(geoFile, yoffset, zoffset);

  auto calculator = new KoaElasticCalculator(mom);
  Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));
  calculator->SetRecDistance(rec_distance);
  Double_t fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc1"));
  calculator->SetFwdDistance(fwd_distance);
  Double_t fwd_low, fwd_high, temp;
  geoHandler->GetDetBoundaryByName("SensorSc1", fwd_low, temp);
  geoHandler->GetDetBoundaryByName("SensorSc2", temp, fwd_high);
  Double_t si1_low, si1_high;
  geoHandler->GetDetBoundaryByName("SensorSi1", si1_low, si1_high);
  Double_t si2_low, si2_high;
  geoHandler->GetDetBoundaryByName("SensorSi2", si2_low, si2_high);
  Double_t rec_low, rec_high;
  rec_low = calculator->GetRecZByFwdX(fwd_low);
  rec_high = calculator->GetRecZByFwdX(fwd_high);

  std::map<Int_t, double> CalculatedEnergies;
  for(auto item: positions ){
    auto id = item.first;
    auto pos = item.second;
    if(pos>0){
      auto energy = calculator->GetEnergyByAlpha(alphas[id]);
      CalculatedEnergies.emplace(id, energy);
    }
  }

  // get the range id of fwd covered Si1 and Si2
  auto encoder = KoaMapEncoder::Instance();

  Double_t global_pos[3] = {-rec_distance, 0, rec_low/10.};
  Int_t id_temp;
  Int_t id_si1_low = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);

  global_pos[2] = rec_high/10.;
  Int_t id_si1_high = 47;
  if ( rec_high/10 < si1_high ) {
    id_si1_high = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 0), id_temp);
  }
  Int_t id_si2_low = 0, id_si2_high = -2;
  if ( rec_high/10 < si2_low ) {
    id_si2_low = -2;
  }
  else {
    id_si2_high = encoder->DecodeChannelID(geoHandler->RecGlobalPositionToDetCh(global_pos, 1), id_temp);
  }

  //
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name, "Update");

  auto hdir = getDirectory(filein, dirname);
  auto h1s_ptr = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);

  // 
  std::map<Int_t, double> FittedEnergy;
  std::map<Int_t, double> FittedEnergyError;
  std::map<Int_t, double> FittedSigmas;
  std::map<Int_t, double> FittedSigmaErrors;
  std::map<Int_t, double> PeakEnergy;

  ParameterList<double> OutputParameters;
  auto& output_peaks = addValueContainer(OutputParameters, "Peak");
  auto& output_means = addValueContainer(OutputParameters, "Mean");
  auto& output_mean_errs = addValueContainer(OutputParameters, "Err(Mean)");
  auto& output_sigmas = addValueContainer(OutputParameters, "Sigma");
  auto& output_sigma_errs = addValueContainer(OutputParameters, "Err(Sigma)");
  auto& output_distances = addValueContainer(OutputParameters, "Distance");
  auto& output_positions = addValueContainer(OutputParameters, "Position");
  auto& output_alphas = addValueContainer(OutputParameters, "Alpha");

  // fit
  auto fitPeak = [&] ()
                 {
                   // config the search paramters
                   Int_t search_maxpeaks=1;
                   auto ip_id = encoder->EncodeChannelID(0, ip_ch);
                   auto si1_thersh_id = encoder->EncodeChannelID(0, ip_ch+10);

                   // loop through all hists
                   for ( auto& hist : h1s_ptr ) {
                     auto id = hist.first;
                     auto h1 = hist.second;
                     h1->SetLineColor(kBlack);

                     Int_t det_id, ch_id;
                     ch_id = encoder->DecodeChannelID(id, det_id);
                     auto cal_e = CalculatedEnergies[id];

                     if(id < ip_id )
                       continue;

                     if(det_id==0 && (ch_id < id_si1_low || ch_id > id_si1_high))
                       continue;
                     if(det_id==1 && (ch_id < id_si2_low || ch_id > id_si2_high))
                       continue;

                     //
                     TSpectrum s(search_maxpeaks);
                     Int_t npeaks;
                     if(cal_e < 1){
                       h1->GetXaxis()->SetRangeUser(0.05, 2.5);
                       npeaks = s.Search(h1, 0.1, "", 0.5);
                     }
                     else if (cal_e < 3) {
                       h1->GetXaxis()->SetRangeUser(0.5, 4);
                       npeaks = s.Search(h1, 0.1, "", 0.5);
                     }
                     else{
                       if((cal_e-4) < 1)
                         h1->GetXaxis()->SetRangeUser(1, CalculatedEnergies[id]+5);
                       else
                         h1->GetXaxis()->SetRangeUser(CalculatedEnergies[id]-4, CalculatedEnergies[id]+5);
                       // h1->GetXaxis()->SetRangeUser(3,70);
                       npeaks = s.Search(h1, 0.3, "", 0.5);
                     }

                     // fit window in sigma
                     double fit_window[4]={0.04, 0.08, 0.12, 0.12};

                     if(npeaks>0) {
                       Double_t *xpeaks = s.GetPositionX();
                       PeakEnergy.emplace(id, xpeaks[0]);
                       auto result = h1->Fit("gaus", "qs", "", xpeaks[0]-fit_window[det_id], xpeaks[0]+fit_window[det_id]);

                       // first fit to get rough estimation
                       auto sigma = result->Parameter(2);
                       h1->GetXaxis()->SetRangeUser(xpeaks[0]-10*sigma, xpeaks[0]+7*sigma);
                       if(id < si1_thersh_id)
                         result = h1->Fit("gaus", "qs", "", xpeaks[0]-sigma, xpeaks[0]+3*sigma);
                       else
                         result = h1->Fit("gaus", "qs", "", xpeaks[0]-2*sigma, xpeaks[0]+4*sigma);

                       double mean = result->Parameter(1);
                       double sigma_fitted = result->Parameter(2);
                       double mean_err = result->ParError(1);
                       double sigma_err = result->ParError(2);

                       output_peaks.emplace(id, xpeaks[0]);
                       output_means.emplace(id, mean);
                       output_mean_errs.emplace(id, mean_err);
                       output_sigmas.emplace(id, sigma_fitted);
                       output_sigma_errs.emplace(id, sigma_err);
                     }
                   }
                 };
  fitPeak();

  //
  TMultiGraph* mg_calc_vs_fitted = new TMultiGraph();
  mg_calc_vs_fitted->SetName("mg_calc_vs_fitted");
  mg_calc_vs_fitted->SetTitle("Fitted Cluster Energy;Calculated Energy (MeV);Fitted Energy (MeV)");
  auto graphs_calc_vs_fitted = bookGraphByRecDetectorId("calc_Vs_fitted","Cluster Energy (Calculated VS Fitted)",8);
  for(auto& graph: graphs_calc_vs_fitted) {
    mg_calc_vs_fitted->Add(graph.second);
  }

  TMultiGraph* mg_correlation = new TMultiGraph();
  mg_correlation->SetName("mg_correlation");
  mg_correlation->SetTitle("Energy VS Sigma;Energy (MeV);#sigma (MeV)");
  auto graphs_correlation = bookGraphByRecDetectorId("correlation","Mean VS Sigma",8);
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
    auto alpha = alphas[id];
    auto energy = CalculatedEnergies[id];

    output_distances.emplace(id, l);
    output_positions.emplace(id, z);
    output_alphas.emplace(id, alpha);

    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    graphs_calc_vs_fitted[det_id]->SetPoint(index[det_id], energy, mean);
    graphs_correlation[det_id]->SetPoint(index[det_id], mean, sigma);

    index[det_id]++;
  }

  //
  TString outdir_name = dirname;
  outdir_name.Append("_fitted");
  auto hDirOut = getDirectory(filein, outdir_name.Data());
  writeHistos<TH1D*>(hDirOut, h1s_ptr);

  hDirOut->WriteTObject( mg_calc_vs_fitted, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_calc_vs_fitted,"WriteDelete");

  hDirOut->WriteTObject( mg_correlation, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_correlation,"WriteDelete");

  //
  TString outfile_pdf(infile);
  outfile_pdf.ReplaceAll(".root","_energy_fwdcovered_fitted.pdf");
  printHistos<TH1D*>(h1s_ptr, outfile_pdf.Data());

  TString outfile_txt(infile);
  outfile_txt.ReplaceAll(".root","_energy_fwdcovered_fitted.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  delete filein;
  delete fgeo;

  //
  timer.Stop();
  timer.Print();
}
