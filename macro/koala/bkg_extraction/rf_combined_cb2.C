#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"
#include "fill_combined_cb2_workspace.cxx"

using namespace KoaUtility;
using namespace RooFit;
using namespace std;

// sort multiple vectors together
template <typename T, typename Compare>
std::vector<std::size_t> sort_permutation(
    const std::vector<T>& vec,
    Compare compare)
{
  std::vector<std::size_t> p(vec.size());
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(),
            [&](std::size_t i, std::size_t j){ return compare(vec[i], vec[j]); });
  return p;
}

template <typename T>
std::vector<T> apply_permutation(
    const std::vector<T>& vec,
    const std::vector<std::size_t>& p)
{
  std::vector<T> sorted_vec(vec.size());
  std::transform(p.begin(), p.end(), sorted_vec.begin(),
                 [&](std::size_t i){ return vec[i]; });
  return sorted_vec;
}

template <typename T>
void apply_permutation_in_place(
    std::vector<T>& vec,
    const std::vector<std::size_t>& p)
{
  std::vector<bool> done(vec.size());
  for (std::size_t i = 0; i < vec.size(); ++i)
  {
    if (done[i])
    {
      continue;
    }
    done[i] = true;
    std::size_t prev_j = i;
    std::size_t j = p[i];
    while (i != j)
    {
      std::swap(vec[prev_j], vec[j]);
      done[j] = true;
      prev_j = j;
      j = p[j];
    }
  }
}

//////////////////////
void rf_combined_cb2(const char* infile,
                     const char* configFile = "./rf_combined_cb2_config.txt",
                     const char* strip_configFile = "./rf_combined_cb2_strips_config.txt",
                     const char* geoFile="../calib_para/geo_standard.root",
                     const char* dirname = "rec_cluster_energy_FirstHit",
                     const char* suffix = "cluster_energy_firstHit",
                     bool useGeometry = false,
                     Double_t mom = 2.6,
                     double zoffset_si1 = 0.18, double zoffset_si2 = 0.13, double zoffset_ge1 = 0.12, double zoffset_ge2 = 0.12
                     )

{
  TStopwatch timer;

  ////////////////////////////////////////
  // Preparation
  ////////////////////////////////////////

  // Map encoder
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  int tdc_id = encoder->EncodeChannelID(1,37);

  // Retrieve the map from ch id to strip ids. Some ch may correspond to multiple strips
  auto geoHandler = getGeometryHandler(geoFile);
  auto ChToStripMap = geoHandler->GetChIdToStripIds();

  // get strip-mapped mean init values
  ValueContainer<double> strip_mean;
  if(useGeometry) {
    double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
    double yoffset[4] = {0, 0, 0, 0}; // in cm
    strip_mean = getStripEnergies(mom, geoFile,yoffset,zoffset);
  }
  else {
    auto strip_params = readParameterList<double>(strip_configFile);

    auto it = findValueContainer(strip_params, "Mean");
    if( it == strip_params.end() ) {
      cout << "Mean not available in config file: " << strip_configFile << endl;
      return;
    }
    strip_mean = it->second;
  }

  ////////////////////////////////////////
  // Read in the fitting config params
  ////////////////////////////////////////

  ValueContainer<double> rg_low, rg_high;
  ValueContainer<double> cb_mean;
  ValueContainer<double> cb_sigma;
  ValueContainer<double> cb_alpha1, cb_n1;
  ValueContainer<double> cb_alpha2, cb_n2;
  ValueContainer<double> expo1, expo2;
  ValueContainer<double> mpv, mpv_sigma;
  ValueContainer<double> frac_expo1, frac_mip, frac_elastic;

  auto read_config = [&]() {
                       auto fit_params = readParameterList<double>(configFile);

                       auto it = findValueContainer(fit_params, "Range_low");
                       if( it == fit_params.end() ) {
                         cout << "Range_low not available in config file: " << configFile << endl;
                         return;
                       }
                       rg_low = it->second;

                       it = findValueContainer(fit_params, "Range_high");
                       if( it == fit_params.end() ) {
                         cout << "Range_high not available in config file: " << configFile << endl;
                         return;
                       }
                       rg_high = it->second;

                       it = findValueContainer(fit_params, "CB_mean");
                       if( it == fit_params.end() ) {
                         cout << "CB_mean not available in config file: " << configFile << endl;
                         return;
                       }
                       cb_mean = it->second;

                       it = findValueContainer(fit_params, "CB_sigma");
                       if( it == fit_params.end() ) {
                         cout << "CB_sigma not available in config file: " << configFile << endl;
                         return;
                       }
                       cb_sigma = it->second;

                       it = findValueContainer(fit_params, "CB_alpha1");
                       if( it == fit_params.end() ) {
                         cout << "CB_alpha1 not available in config file: " << configFile << endl;
                         return;
                       }
                       cb_alpha1 = it->second;

                       it = findValueContainer(fit_params, "CB_alpha2");
                       if( it == fit_params.end() ) {
                         cout << "CB_alpha2 not available in config file: " << configFile << endl;
                         return;
                       }
                       cb_alpha2 = it->second;

                       it = findValueContainer(fit_params, "CB_n1");
                       if( it == fit_params.end() ) {
                         cout << "CB_n1 not available in config file: " << configFile << endl;
                         return;
                       }
                       cb_n1 = it->second;

                       it = findValueContainer(fit_params, "CB_n2");
                       if( it == fit_params.end() ) {
                         cout << "CB_n2 not available in config file: " << configFile << endl;
                         return;
                       }
                       cb_n2 = it->second;

                       it = findValueContainer(fit_params, "Expo1");
                       if( it == fit_params.end() ) {
                         cout << "Expo1 not available in config file: " << configFile << endl;
                         return;
                       }
                       expo1 = it->second;

                       it = findValueContainer(fit_params, "Expo2");
                       if( it == fit_params.end() ) {
                         cout << "Expo2 not available in config file: " << configFile << endl;
                         return;
                       }
                       expo2 = it->second;

                       it = findValueContainer(fit_params, "MPV");
                       if( it == fit_params.end() ) {
                         cout << "MPV not available in config file: " << configFile << endl;
                         return;
                       }
                       mpv = it->second;

                       it = findValueContainer(fit_params, "Mpv_sigma");
                       if( it == fit_params.end() ) {
                         cout << "Mpv_sigma not available in config file: " << configFile << endl;
                         return;
                       }
                       mpv_sigma = it->second;

                       it = findValueContainer(fit_params, "Frac_expo1");
                       if( it == fit_params.end() ) {
                         cout << "Frac_expo1 not available in config file: " << configFile << endl;
                         return;
                       }
                       frac_expo1 = it->second;

                       it = findValueContainer(fit_params, "Frac_mip");
                       if( it == fit_params.end() ) {
                         cout << "Frac_mip not available in config file: " << configFile << endl;
                         return;
                       }
                       frac_mip = it->second;

                       it = findValueContainer(fit_params, "Frac_elastic");
                       if( it == fit_params.end() ) {
                         cout << "Frac_elastic not available in config file: " << configFile << endl;
                         return;
                       }
                       frac_elastic = it->second;
                     };

  read_config();

  ////////////////////////////////////////
  // Read in the histograms
  ////////////////////////////////////////
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name,"Update");

  // naming pattern
  auto hdir_energy = getDirectory(filein, dirname);
  auto h1s_ptr = getHistosByChannelId<TH1D>(hdir_energy, suffix);

  ////////////////////////////////////////
  // Fitting with CB2Shape based on number
  // of strips in each channel
  ////////////////////////////////////////

  // Map containers for fitting results, with strip id as key
  ParameterList<double> StripParams;
  auto& output_init_mean = addValueContainer(StripParams, "Init_mean");
  auto& output_mean = addValueContainer(StripParams, "Mean");
  auto& output_sigma = addValueContainer(StripParams, "Sigma");
  auto& output_stripevt = addValueContainer(StripParams, "EvtNr");

  // Map containers for fitting results, with channel id as key
  ParameterList<double> ChannelParams;
  auto& output_range_low = addValueContainer(ChannelParams, "Range_low");
  auto& output_range_high = addValueContainer(ChannelParams, "Range_high");
  auto& output_avg_mean = addValueContainer(ChannelParams, "CB_mean");
  auto& output_avg_sigma = addValueContainer(ChannelParams, "CB_sigma");
  auto& output_cb_alpha1 = addValueContainer(ChannelParams, "CB_alpha1");
  auto& output_cb_alpha2 = addValueContainer(ChannelParams, "CB_alpha2");
  auto& output_cb_n1 = addValueContainer(ChannelParams, "CB_n1");
  auto& output_cb_n2 = addValueContainer(ChannelParams, "CB_n2");
  auto& output_expo1 = addValueContainer(ChannelParams, "Expo1");
  auto& output_expo2 = addValueContainer(ChannelParams, "Expo2");
  auto& output_mpv = addValueContainer(ChannelParams, "MPV");
  auto& output_mpv_sigma = addValueContainer(ChannelParams, "Mpv_sigma");
  auto& output_frac_expo1 = addValueContainer(ChannelParams, "Frac_expo1");
  auto& output_frac_mip = addValueContainer(ChannelParams, "Frac_mip");
  auto& output_frac_elastic = addValueContainer(ChannelParams, "Frac_elastic");
  auto& output_evt = addValueContainer(ChannelParams, "EvtNr");
  auto& output_avg_mean_err = addValueContainer(ChannelParams, "Err(CB_mean)");
  auto& output_evt_err = addValueContainer(ChannelParams, "Err(EvtNr)");
  auto& output_chi2ndf = addValueContainer(ChannelParams, "chi2/ndf");

  // Map containers for class objects
  std::map<Int_t, RooWorkspace> ws;
  std::map<Int_t, RooFitResult> rf_result;
  std::map<Int_t, TCanvas> canvas;

  auto fit_combined_cb2 = [&] ()
                          {
                            // Print Canvases to PDF
                            TString outfile_pdf(infile_name);
                            outfile_pdf.ReplaceAll(".root", Form("_%s_FitCombinedCB2.pdf", dirname));

                            TCanvas *can = new TCanvas("canvas","Fitting using CB2Shape", 1500, 500);
                            can->Divide(2,2);
                            can->Print(Form("%s[",outfile_pdf.Data()));

                            // loop through all hists
                            for ( auto& item : h1s_ptr ) {
                              auto id = item.first;
                              auto hist = item.second;

                              TString volName;
                              Int_t ch = encoder->DecodeChannelID(id, volName);
                              volName.ReplaceAll("Sensor", "");

                              // ignore channels on the edges, partly-deposit and malfuntioning
                              if (id == encoder->EncodeChannelID(0,47) ||
                                  id == encoder->EncodeChannelID(1,0) ||
                                  id == encoder->EncodeChannelID(1,63) ||
                                  id == encoder->EncodeChannelID(2,0) ||
                                  id == encoder->EncodeChannelID(2,31)  ||
                                  id == encoder->EncodeChannelID(3,0)  ||
                                  id == encoder->EncodeChannelID(3,31) 
                                  )
                                continue;

                              auto search = cb_mean.find(id);
                              if(search == cb_mean.end()) continue;

                              // retrieve the number of strips in the channel
                              auto strip_ids = ChToStripMap[id];
                              auto nr_strips = strip_ids.size();

                              /**********************************************************************/
                              // Histogram preparation
                              /**********************************************************************/
                              // rebin
                              if( tdc_id >= id)
                                hist->Rebin(5);
                              else
                                hist->Rebin(3);

                              // get the observed events in fit range
                              auto bin_low = hist->GetXaxis()->FindBin(rg_low[id]);
                              auto bin_high = hist->GetXaxis()->FindBin(rg_high[id]);
                              double ntotal = hist->Integral(bin_low, bin_high);

                              /**********************************************************************/
                              // Define the workspace
                              /**********************************************************************/

                              // fill in the fit model
                              ws.emplace(std::piecewise_construct,
                                         std::forward_as_tuple(id),
                                         std::forward_as_tuple(Form("ws_%s_%d", volName.Data(), ch+1),
                                                               Form("RooWorkspace of %s_%d", volName.Data(), ch+1)));
                              RooWorkspace& w = ws[id];

                              fill_combined_cb2_workspace(w, nr_strips,
                                                          rg_low[id], rg_high[id],
                                                          cb_mean[id],
                                                          cb_sigma[id], cb_alpha1[id], cb_alpha2[id], cb_n1[id], cb_n2[id],
                                                          expo1[id], expo2[id],
                                                          mpv[id], mpv_sigma[id],
                                                          frac_expo1[id], frac_mip[id], frac_elastic[id],
                                                          ntotal);
                              std::cout << "Fit channel: " << volName.Data() << "_" << ch+1 << std::endl;

                              // retrieve vars and p.d.fs from workspace
                              RooRealVar* energy = w.var("energy");

                              auto model = w.pdf("model");

                              // set init value for elastic peak centers
                              if(nr_strips>1){
                                double strip_sigma = cb_sigma[id]/TMath::Sqrt(nr_strips);
                                for(int i=0;i<nr_strips;i++){
                                  RooRealVar* cb_m0 = w.var(Form("cb_m0_%d",i+1));
                                  cb_m0->setVal(strip_mean[strip_ids[i]]);
                                  cb_m0->setRange(strip_mean[strip_ids[i]]-3*strip_sigma,
                                                  strip_mean[strip_ids[i]]+3*strip_sigma);
                                  std::cout << "strip_mean: " << strip_mean[strip_ids[i]] << std::endl;
                                }
                              }

                              // init and fill in the data set
                              std::cout << "Import data: " << volName.Data() << "_" << ch+1 << std::endl;

                              RooDataHist dh("dh", Form("%s_%d", volName.Data(), ch+1), *energy, Import(*hist));
                              w.import(dh);

                              /**********************************************************************/
                              // Fitting
                              /**********************************************************************/
                              std::cout << "Fitting: " << volName.Data() << "_" << ch+1 << std::endl;

                              RooFitResult* r = model->fitTo(dh, Range("fitRange"), Save());
                              r->SetName(Form("rf_result_%s_%d", volName.Data(), ch+1));

                              /**********************************************************************/
                              // Drawing
                              /**********************************************************************/
                              RooPlot *frame = energy->frame(Title(Form( "Fitting of %s_%d", volName.Data(), ch+1 )));
                              dh.plotOn(frame, MarkerSize(0.5));
                              model->plotOn(frame, VisualizeError(*r));
                              model->plotOn(frame, Range("fitRange"), LineColor(kBlue));
                              // model.paramOn(frame, Layout(0.55));

                              // Get chi2
                              auto chi2_over_ndf = frame->chiSquare(15+(nr_strips-1)*2);

                              // Get residual
                              RooHist *hpull = frame->pullHist();
                              hpull->SetMarkerSize(0.5);
                              RooHist *hresid = frame->residHist();
                              hresid->SetMarkerSize(0.5);

                              // Get correlation matrix of the floating parameters
                              TH2 *hcorr = r->correlationHist();

                              // Add other components to the frame
                              model->plotOn(frame, Components("bkg_mip"), LineStyle(kDashed), LineColor(kMagenta), Range(0, 60.));
                              model->plotOn(frame, Components("bkg_model"), LineStyle(kDashed), LineColor(kGreen), Range(0, 60.));
                              switch (nr_strips) {
                              case 1: {
                                model->plotOn(frame, Components("elastic_model"), LineStyle(kDotted), LineColor(kRed), Range(0, 60.));
                                break;
                              }
                              case 2: {
                                model->plotOn(frame, Components("cb1"), LineStyle(kDotted), LineColor(kRed), Range(0, 60.));
                                model->plotOn(frame, Components("cb2"), LineStyle(kDotted), LineColor(kRed), Range(0, 60.));
                                break;
                              }
                              case 3: {
                                model->plotOn(frame, Components("cb1"), LineStyle(kDotted), LineColor(kRed), Range(0, 60.));
                                model->plotOn(frame, Components("cb2"), LineStyle(kDotted), LineColor(kRed), Range(0, 60.));
                                model->plotOn(frame, Components("cb3"), LineStyle(kDotted), LineColor(kRed), Range(0, 60.));
                                break;
                              }
                              default:
                                break;
                              }

                              // Add pull histo to frame2
                              RooPlot *frame2 = energy->frame(Title("Pull Distribution"));
                              frame2->addPlotable(hpull, "P");
                              RooPlot *frame3 = energy->frame(Title("Residual Distribution"));
                              frame3->addPlotable(hresid, "P");

                              // Draw all frames on a canvas
                              canvas.emplace(std::piecewise_construct,
                                             std::forward_as_tuple(id),
                                             std::forward_as_tuple(Form("c_%s_%d",volName.Data(),ch+1),
                                                                   Form("Double-sided CrystalBall Fitting"),
                                                                   1000, 1000));
                              canvas[id].Divide(2,2);
                              canvas[id].cd(1);
                              gPad->SetLeftMargin(0.15);
                              frame->GetYaxis()->SetTitleOffset(1.8);
                              frame->Draw();

                              canvas[id].cd(2);
                              gPad->SetLeftMargin(0.1);
                              frame2->Draw();

                              canvas[id].cd(3);
                              gPad->SetLeftMargin(0.2);
                              hcorr->GetYaxis()->SetTitleOffset(1.4);
                              gStyle->SetOptStat(0);
                              hcorr->Draw("colz");

                              canvas[id].cd(4);
                              gPad->SetLeftMargin(0.1);
                              frame3->Draw();

                              // for printing to pdf file
                              can->cd(1);
                              gPad->SetLeftMargin(0.15);
                              frame->GetYaxis()->SetTitleOffset(1.8);
                              frame->Draw();

                              can->cd(2);
                              gPad->SetLeftMargin(0.1);
                              frame2->Draw();

                              can->cd(3);
                              gPad->SetLeftMargin(0.2);
                              hcorr->GetYaxis()->SetTitleOffset(1.4);
                              gStyle->SetOptStat(0);
                              hcorr->Draw("colz");

                              can->cd(4);
                              gPad->SetLeftMargin(0.1);
                              frame3->Draw();

                              can->Print(Form("%s",outfile_pdf.Data()));

                              /**********************************************************************/
                              // Save results
                              /**********************************************************************/

                              rf_result.emplace(std::piecewise_construct,
                                                std::forward_as_tuple(id),
                                                std::forward_as_tuple(*r));

                              // fit params for each strip
                              RooRealVar* nelastic = w.var("nelastic");

                              std::vector<double> means, sigmas, mean_errs, sigma_errs, events;
                              for(int i=0;i<nr_strips;i++){
                                RooRealVar* mean  = w.var(Form("cb_m0_%d",i+1));
                                RooRealVar* sigma = w.var("cb_sigma");

                                means.emplace_back(mean->getVal());
                                mean_errs.emplace_back(mean->getError());
                                sigmas.emplace_back(sigma->getVal());
                                sigma_errs.emplace_back(sigma->getError());
                              }

                              switch (nr_strips) {
                              case 1: {
                                events.emplace_back(nelastic->getVal());
                                break;
                              }
                              default: {
                                double last_frac = 1;
                                for(int i = 0; i<(nr_strips-1); i++) {
                                  RooRealVar* var = w.var(Form("frac_cb%d",i+1));
                                  events.emplace_back(var->getVal()*nelastic->getVal());
                                  last_frac -= var->getVal();
                                }
                                events.emplace_back(last_frac*nelastic->getVal());
                                break;
                              }
                              }

                              // order the means as sequence
                              auto p = sort_permutation<double>(means,
                                                                [](double const& a, double const& b){return a < b;} );
                              apply_permutation_in_place(means, p);
                              apply_permutation_in_place(sigmas, p);
                              apply_permutation_in_place(mean_errs, p);
                              apply_permutation_in_place(sigma_errs, p);
                              apply_permutation_in_place(events, p);

                              // save the fit values into output containers
                              for(int i=0;i<nr_strips;i++){
                                auto strip_id = strip_ids[i];

                                output_init_mean.emplace(strip_id, strip_mean[strip_id]);
                                output_mean.emplace(strip_id, means[i]);
                                output_sigma.emplace(strip_id, sigmas[i]);
                                output_stripevt.emplace(strip_id, events[i]);
                              }

                              // fit params for each channel
                              output_evt.emplace(id, nelastic->getVal());
                              output_evt_err.emplace(id, nelastic->getError());
                              output_chi2ndf.emplace(id, chi2_over_ndf);

                              output_avg_mean.emplace(id, TMath::Mean(means.begin(), means.end()));
                              output_range_low.emplace(id, rg_low[id]);
                              output_range_high.emplace(id, rg_high[id]);

                              double avg_sigma = 0;
                              double avg_sigma_err = 0, avg_mean_err = 0;
                              int index = 0;
                              for(auto item: sigmas){
                                avg_sigma += item*item;
                                avg_sigma_err += sigma_errs[index]*sigma_errs[index];
                                avg_mean_err += mean_errs[index]*mean_errs[index];
                                index++;
                              }
                              avg_sigma = TMath::Sqrt(avg_sigma/sigmas.size());
                              avg_mean_err = TMath::Sqrt(avg_mean_err)/nr_strips;
                              avg_sigma_err = TMath::Sqrt(avg_sigma_err)/nr_strips;

                              output_avg_sigma.emplace(id, avg_sigma);
                              output_avg_mean_err.emplace(id, avg_mean_err);

                              RooRealVar* tmp = w.var("mpv");
                              output_mpv.emplace(id, tmp->getVal());
                              tmp = w.var("mpv_sigma");
                              output_mpv_sigma.emplace(id, tmp->getVal());

                              tmp = w.var("expo1");
                              output_expo1.emplace(id, tmp->getVal());
                              tmp = w.var("expo2");
                              output_expo2.emplace(id, tmp->getVal());

                              tmp = w.var("cb_alpha1");
                              output_cb_alpha1.emplace(id, tmp->getVal());
                              tmp = w.var("cb_alpha2");
                              output_cb_alpha2.emplace(id, tmp->getVal());
                              tmp = w.var("cb_n1");
                              output_cb_n1.emplace(id, tmp->getVal());
                              tmp = w.var("cb_n2");
                              output_cb_n2.emplace(id, tmp->getVal());

                              tmp = w.var("frac_expo1");
                              output_frac_expo1.emplace(id, tmp->getVal());
                              tmp = w.var("frac_mip");
                              output_frac_mip.emplace(id, tmp->getVal());
                              RooRealVar* nbkg = w.var("nbkg");
                              output_frac_elastic.emplace(id, nelastic->getVal()/(nelastic->getVal()+nbkg->getVal()));

                              std::cout << "End Fit channel: " << volName.Data() << "_" << ch+1 << std::endl;
                            }

                            // close PDF file
                            can->Print(Form("%s]",outfile_pdf.Data()));
                            delete can;
                          };

  fit_combined_cb2();

  ////////////////////////////////////////
  // Save Workspaces and RooFitResult to ROOT file, with one directory for each channel
  ////////////////////////////////////////
  auto hDirOut = getDirectory(filein, Form("%s_FitCombinedCB2", dirname));

  for(auto& item : ws){
    auto id = item.first;
    auto& w = item.second;

    // hDirOut->WriteTObject(&w, "", "WriteDelete");
    hDirOut->WriteTObject(&canvas[id], "", "WriteDelete");
    hDirOut->WriteTObject(&rf_result[id], "", "WriteDelete");
  }

  ////////////////////////////////////////
  // Save Parameters to TXT
  ////////////////////////////////////////
  TString outfile_strip_txt(infile_name);
  outfile_strip_txt.ReplaceAll(".root", Form("_%s_FitCombinedCB2_Strips.txt", dirname));
  printValueList<double>(StripParams, outfile_strip_txt.Data());

  TString outfile_channel_txt(infile_name);
  outfile_channel_txt.ReplaceAll(".root", Form("_%s_FitCombinedCB2_Channels.txt", dirname));
  printValueList<double>(ChannelParams, outfile_channel_txt.Data());

  ////////////////////////////////////////
  // Clean up
  ////////////////////////////////////////
  delete filein;

  //
  timer.Stop();
  timer.Print();
}
