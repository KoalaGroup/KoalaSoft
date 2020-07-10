#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void calc_energy_MultiGaussian(const char* infile,
                               Double_t mom = 2.6,
                               const char* geoFile="../calib_para/geo_standard.root",
                               const char* dirname = "elastic_events",
                               const char* suffix = "cluster_energy_elastic",
                               bool separateRegion = false,
                               int rangeId_si1 = 35, int rangeid_si2 = 6,
                               int ip_ch = 13,
                               Double_t pedestal = 0, // pedestal in sim digi task in keV
                               bool useAlpha = false,
                               double zoffset_si1 = 0, double zoffset_si2 = 0, double zoffset_ge1 = 0, double zoffset_ge2 = 0
                               )

{
  TStopwatch timer;

  //
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  auto calculator = new KoaElasticCalculator(mom);

  // IP id config
  Int_t ip_id = encoder->EncodeChannelID(0,ip_ch);

  // double zoffset[4] = {0.18, 0.13, 0.12, 0.12}; // in cm
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm

  auto Positions = getStripGlobalPosition(geoFile,zoffset);
  auto Alphas = getStripAlphas(geoFile,yoffset,zoffset);
  auto CalculatedEnergies = getStripEnergies(mom, geoFile,yoffset,zoffset);
  auto ChannelAlphas = getChannelAlphas(geoFile, yoffset, zoffset);

  auto geoHandler = getGeometryHandler(geoFile);
  auto ChToStripMap = geoHandler->GetChIdToStripIds();
  // delete geoHandler;

  ////////////////////////////////////////
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name,"Update");

  TString hdir_name(dirname);
  TString hname_suffix(suffix);

  TString hdir_cut_name = hdir_name + "_fwdhit_TimeValid";
  TString hname_cut_suffix = hname_suffix + "_fwdhit_TimeValid";

  HistoPtr1D h1s_ptr;
  // readHist
  auto readHist = [&] (Int_t sepid_si1, Int_t sepid_si2)
                  {
                    //
                    auto hdir_energy = getDirectory(filein, hdir_name.Data());
                    auto hist_energy = getHistosByChannelId<TH1D>(hdir_energy, hname_suffix.Data());

                    auto hdir_energy_cut = getDirectory(filein, hdir_cut_name.Data());
                    auto hist_energy_cut = getHistosByChannelId<TH1D>(hdir_energy_cut, hname_cut_suffix.Data());

                    //
                    std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
                    Int_t rangeids[4];
                    rangeids[0] = encoder->EncodeChannelID(0, sepid_si1);
                    rangeids[1] = encoder->EncodeChannelID(1, sepid_si2);
                    rangeids[2] = -1;
                    rangeids[3] = -1;

                    for ( auto& ChID : ChIDs ) {
                      if ( separateRegion ) {
                        Int_t det_id, ch_id;
                        ch_id = encoder->DecodeChannelID(ChID, det_id);

                        if (ChID < rangeids[det_id]){
                          h1s_ptr.emplace(ChID, hist_energy_cut[ChID]);
                        }
                        else{
                          h1s_ptr.emplace(ChID, hist_energy[ChID]);
                        }
                      }
                      else{
                        h1s_ptr.emplace(ChID, hist_energy[ChID]);
                      }
                    }

                    return true;
                  };

  if (separateRegion)
    readHist(rangeId_si1, rangeid_si2);
  else {
    auto hdir_energy = getDirectory(filein, hdir_name.Data());
    h1s_ptr = getHistosByChannelId<TH1D>(hdir_energy, hname_suffix.Data());
  }

  ////////////////////////////////////////
  std::map<Int_t, double> FittedEnergies;
  std::map<Int_t, double> FittedEnergyErrors;
  std::map<Int_t, double> FittedSigmas;
  std::map<Int_t, double> FittedSigmaErrors;

  auto searchPeaks = [&] ()
                     {
                       // loop through all hists
                       for ( auto& item : h1s_ptr ) {
                         auto id = item.first;
                         auto hist = item.second;

                         if ( id < ip_id || ChannelAlphas[id] < 0 )
                           continue;

                         if (id == encoder->EncodeChannelID(0,47) ||
                             id == encoder->EncodeChannelID(1,0) ||
                             id == encoder->EncodeChannelID(1,63) ||
                             id == encoder->EncodeChannelID(2,0) ||
                             id == encoder->EncodeChannelID(2,31)  ||
                             id == encoder->EncodeChannelID(3,0)  ||
                             id == encoder->EncodeChannelID(3,31)  ||
                             // ignore partly-deposit
                             id == encoder->EncodeChannelID(2,27) ||
                             id == encoder->EncodeChannelID(2,28) ||
                             id == encoder->EncodeChannelID(2,29) ||
                             id == encoder->EncodeChannelID(2,30) ||
                             id == encoder->EncodeChannelID(2,31) ||
                             id == encoder->EncodeChannelID(3,28) ||
                             id == encoder->EncodeChannelID(3,29) ||
                             id == encoder->EncodeChannelID(3,30) ||
                             id == encoder->EncodeChannelID(3,31) ||
                             // ignore malfuntion
                             id == encoder->EncodeChannelID(3,21) ||
                             id == encoder->EncodeChannelID(3,22)
                             )
                           continue;

                         //
                         auto strip_ids = ChToStripMap[id];
                         auto nr_strips = strip_ids.size();

                         TF1* ffit = nullptr;
                         switch (nr_strips) {
                           case 1: {
                             auto low = CalculatedEnergies[strip_ids[0]] - 3*0.2;
                             auto high = CalculatedEnergies[strip_ids[0]] + 3*0.2;
                             hist->GetXaxis()->SetRangeUser(low, high);
                             double integral = hist->Integral();
                             auto rms = hist->GetRMS();

                             low = CalculatedEnergies[strip_ids[0]] - 5*rms;
                             high = CalculatedEnergies[strip_ids[0]] + 5*rms;
                             hist->GetXaxis()->SetRangeUser(low, high);

                             ffit = new TF1("ffit", "gaus(0)", low+3*rms, high);
                             ffit->SetParameter(0, integral);
                             ffit->SetParameter(1, CalculatedEnergies[strip_ids[0]]);
                             ffit->SetParameter(2, rms);
                             break;
                           }
                           case 2: {
                             auto low = CalculatedEnergies[strip_ids[0]] - 5*0.2;
                             auto high = CalculatedEnergies[strip_ids[1]] + 5*0.2;
                             hist->GetXaxis()->SetRangeUser(low, high);
                             double integral = hist->Integral();
                             auto rms = hist->GetRMS()/TMath::Sqrt(2);

                             low = CalculatedEnergies[strip_ids[0]] - 5*rms;
                             high = CalculatedEnergies[strip_ids[1]] + 5*rms;
                             hist->GetXaxis()->SetRangeUser(low, high);

                             auto result1 = hist->Fit("gaus","qs+", "", CalculatedEnergies[strip_ids[0]]-3*rms,CalculatedEnergies[strip_ids[0]]+rms);
                             auto result2 = hist->Fit("gaus","qs+", "", CalculatedEnergies[strip_ids[1]]-rms,CalculatedEnergies[strip_ids[1]]+3*rms);
            
                             ffit = new TF1("ffit", "gaus(0)+gaus(3)", low, high);
                             ffit->SetParameter(0, result1->Parameter(0));
                             ffit->SetParameter(1, result1->Parameter(1));
                             ffit->SetParameter(2, result1->Parameter(2));

                             ffit->SetParameter(3, result2->Parameter(0));
                             ffit->SetParameter(4, result2->Parameter(1));
                             ffit->SetParameter(5, result2->Parameter(2));

                             break;
                           }
                           case 3: {
                             auto low = CalculatedEnergies[strip_ids[0]] - 5*0.2;
                             auto high = CalculatedEnergies[strip_ids[2]] + 5*0.2;
                             hist->GetXaxis()->SetRangeUser(low, high);
                             double integral = hist->Integral();
                             auto rms = hist->GetRMS()/TMath::Sqrt(3);

                             low = CalculatedEnergies[strip_ids[0]] - 5*rms;
                             high = CalculatedEnergies[strip_ids[2]] + 5*rms;
                             hist->GetXaxis()->SetRangeUser(low, high);

                             auto result1 = hist->Fit("gaus","qs+", "", CalculatedEnergies[strip_ids[0]]-3*rms,CalculatedEnergies[strip_ids[0]]+rms);
                             auto result2 = hist->Fit("gaus","qs+", "", CalculatedEnergies[strip_ids[2]]-rms,CalculatedEnergies[strip_ids[2]]+3*rms);

                             ffit = new TF1("ffit", "gaus(0)+gaus(3)+gaus(6)", low, high);

                             ffit->SetParameter(0, result1->Parameter(0));
                             ffit->SetParameter(1, result1->Parameter(1));
                             ffit->SetParameter(2, result1->Parameter(2));

                             // triple gaussian form
                             auto p0 = (result2->Parameter(0)+result1->Parameter(0))/2;
                             auto p1 = CalculatedEnergies[strip_ids[1]];
                             auto p2 = rms;
                             ffit->SetParameter(3, p0);
                             ffit->SetParameter(4, p1);
                             ffit->SetParameter(5, p2);

                             ffit->SetParameter(6, result2->Parameter(0));
                             ffit->SetParameter(7, result2->Parameter(1));
                             ffit->SetParameter(8, result2->Parameter(2));

                             break;
                           }
                           default:
                             break;
                         }

                         auto fit_result = hist->Fit(ffit,"qsr");
                         Int_t fit_status = fit_result;

                         //
                         if(!fit_status) {
                           int index=0;
                           for(auto strip_id: strip_ids){
                             double mean = fit_result->Parameter(1+3*index);
                             double sigma_fitted = fit_result->Parameter(2+3*index);
                             double mean_err = fit_result->ParError(1+3*index);
                             double sigma_err = fit_result->ParError(2+3*index);

                             FittedEnergies.emplace(strip_id, mean-pedestal/1000.);
                             FittedEnergyErrors.emplace(strip_id, mean_err);
                             FittedSigmas.emplace(strip_id, sigma_fitted);
                             FittedSigmaErrors.emplace(strip_id, sigma_err);

                             index++;
                           }
                         }
                       }
                     };

  searchPeaks();

  //////////////////
  TGraph* graph_calculated = new TGraph();
  graph_calculated->SetName("graph_calculated");
  graph_calculated->SetTitle("Position VS Energy");
  graph_calculated->SetMarkerColor(kBlue);
  graph_calculated->SetMarkerStyle(22);
  graph_calculated->SetMarkerSize(0.6);
  TGraph* graph_calibrated = new TGraph();
  graph_calibrated->SetName("graph_calibrated");
  graph_calibrated->SetTitle("Position VS Energy");
  graph_calibrated->SetMarkerColor(kRed);
  graph_calibrated->SetMarkerStyle(20);
  graph_calibrated->SetMarkerSize(0.6);

  TMultiGraph* mg=new TMultiGraph();
  mg->SetName("graph_position_vs_energy");
  mg->SetTitle("Position VS Energy");
  mg->Add(graph_calculated, "P");
  mg->Add(graph_calibrated, "P");

  //
  TMultiGraph* mg_diff = new TMultiGraph();
  mg_diff->SetName("mg_diff");
  mg_diff->SetTitle("Fitted Energy Relative Variance");
  auto graphs_diff = bookGraphByRecDetectorId("diff","Fitted Energy Relative Variance",8);
  for(auto& graph: graphs_diff) {
    mg_diff->Add(graph.second);
  }

  TMultiGraph* mg_diff_value = new TMultiGraph();
  mg_diff_value->SetName("mg_diff_value");
  mg_diff_value->SetTitle("Fitted Energy Absolute Variance");
  auto graphs_diff_value = bookGraphByRecDetectorId("diff_value","Fitted Energy Absolute Variance",8);
  for(auto& graph: graphs_diff_value) {
    mg_diff_value->Add(graph.second);
  }

  TGraph* graph_diff = new TGraph();
  graph_diff->SetName("graph_diff");
  graph_diff->SetTitle("Fitted Energy Relative Variance");
  graph_diff->SetMarkerColor(kBlue);
  graph_diff->SetMarkerStyle(8);
  graph_diff->SetMarkerSize(1);

  TGraph* graph_diff_value = new TGraph();
  graph_diff_value->SetName("graph_diff_value");
  graph_diff_value->SetTitle("Fitted Energy Absolute Variance");
  graph_diff_value->SetMarkerColor(kBlack);
  graph_diff_value->SetMarkerStyle(8);
  graph_diff_value->SetMarkerSize(1);

  // output parameters
  ParameterList<double> EnergyParameters;
  auto& output_postions = addValueContainer(EnergyParameters, "Position");
  auto& output_alphas = addValueContainer(EnergyParameters, "Alpha");
  auto& output_calculated = addValueContainer(EnergyParameters, "Calculated");
  auto& output_mean = addValueContainer(EnergyParameters, "Mean");
  auto& output_sigma = addValueContainer(EnergyParameters, "Sigma");
  auto& output_mean_err = addValueContainer(EnergyParameters, "Err(mean)");
  auto& output_sigma_err = addValueContainer(EnergyParameters, "Err(sigma)");

  Int_t index[4] = {0} ;
  Int_t global_index = 0;
  for( auto& energy : FittedEnergies ) {
    auto id = energy.first;
    auto fitted_value = energy.second;
    auto calc_value = CalculatedEnergies[id];

    Int_t det_id, ch_id;
    ch_id = encoder->DecodeChannelID(id, det_id);

    if(Positions[id]>0 &&
       // ignore edges
       // id != encoder->EncodeChannelID(0,47) &&
       // id != encoder->EncodeChannelID(1,0) &&
       // id != encoder->EncodeChannelID(1,63) &&
       // id != encoder->EncodeChannelID(2,0) &&
       // id != encoder->EncodeChannelID(2,31) &&
       // id != encoder->EncodeChannelID(3,0) &&
       // id != encoder->EncodeChannelID(3,31) &&
       // // ignore partly-deposit
       // id != encoder->EncodeChannelID(2,27) &&
       // id != encoder->EncodeChannelID(2,28) &&
       // id != encoder->EncodeChannelID(2,29) &&
       // id != encoder->EncodeChannelID(2,30) &&
       // id != encoder->EncodeChannelID(2,31) &&
       // id != encoder->EncodeChannelID(3,28) &&
       // id != encoder->EncodeChannelID(3,29) &&
       // id != encoder->EncodeChannelID(3,30) &&
       // id != encoder->EncodeChannelID(3,31) &&
       // // ignore malfuntion
       // id != encoder->EncodeChannelID(3,21) &&
       // id != encoder->EncodeChannelID(3,22) &&
       CalculatedEnergies[id] > 0 
       )
    {

      double xpos;
      if(!useAlpha) {
        xpos = Positions[id];
      }
      else{
        xpos = Alphas[id];
      }

      //
      output_postions.emplace(id, Positions[id]);
      output_alphas.emplace(id, Alphas[id]);
      output_calculated.emplace(id, calc_value);
      output_mean.emplace(id, fitted_value);
      output_mean_err.emplace(id, FittedEnergyErrors[id]);
      output_sigma.emplace(id, FittedSigmas[id]);
      output_sigma_err.emplace(id, FittedSigmaErrors[id]);

      //
      graph_calibrated->SetPoint(global_index, xpos, fitted_value);
      graph_calculated->SetPoint(global_index, xpos, calc_value);

      graph_diff->SetPoint(global_index, xpos, (fitted_value-calc_value)/calc_value);
      graph_diff_value->SetPoint(global_index, xpos, fitted_value-calc_value);

      graphs_diff[det_id]->SetPoint(index[det_id], xpos, (fitted_value-calc_value)/calc_value);
      graphs_diff_value[det_id]->SetPoint(index[det_id], xpos, (fitted_value-calc_value));

      //
      index[det_id]++;
      global_index++;
    }
  }

  // output
  TString outdir_name = hdir_name;
  outdir_name.Append("_fitted_MultiGaussian");
  auto hDirOut = getDirectory(filein, outdir_name.Data());
  writeHistos<TH1D*>(hDirOut, h1s_ptr);

  hDirOut->WriteTObject( graph_calibrated, "", "WriteDelete");
  hDirOut->WriteTObject( graph_calculated, "", "WriteDelete");
  hDirOut->WriteTObject( mg, "", "WriteDelete");

  hDirOut->WriteTObject( graph_diff, "", "WriteDelete");
  hDirOut->WriteTObject( graph_diff_value, "", "WriteDelete");

  hDirOut->WriteTObject( mg_diff, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_diff,"WriteDelete");

  hDirOut->WriteTObject( mg_diff_value, "", "WriteDelete");
  writeGraphs<TGraph*>(hDirOut, graphs_diff_value, "WriteDelete");

  TString outfile_pdf(infile_name);
  outfile_pdf.ReplaceAll(".root", Form("_%s_fitted_MultiGaussian.pdf", hdir_name.Data()));
  printH1Ds(h1s_ptr, outfile_pdf.Data());

  //
  TString outfile_txt(infile_name);
  outfile_txt.ReplaceAll(".root", Form("_%s_fitted_MultiGaussian.txt", hdir_name.Data()));
  printValueList<double>(EnergyParameters, outfile_txt.Data());

  //
  delete filein;
  delete calculator;

  //
  timer.Stop();
  timer.Print();
}
