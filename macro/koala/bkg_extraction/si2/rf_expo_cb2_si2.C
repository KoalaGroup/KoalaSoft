#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "fill_expo_cb2_workspace_si2.cxx"

using namespace KoaUtility;
using namespace RooFit;
using namespace std;

//////////////////////
void rf_expo_cb2_si2(const char* infile,
                     const char* configFile = "./rf_expo_cb2_config_si2.txt",
                     const char* dirname = "rec_cluster_energy_FirstHit",
                     const char* suffix = "cluster_energy_firstHit"
                     )

{
  TStopwatch timer;

  ////////////////////////////////////////
  // Preparation
  ////////////////////////////////////////

  // Map encoder
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  int tdc_id = encoder->EncodeChannelID(1,37);

  ////////////////////////////////////////
  // Read in the fitting config params
  ////////////////////////////////////////

  ValueContainer<double> cb_mean;
  ValueContainer<double> cb_sigma;
  ValueContainer<double> cb_alpha1, cb_n1;
  ValueContainer<double> cb_alpha2, cb_n2;
  ValueContainer<double> expo_lambda;
  ValueContainer<double> range_limit;

  auto read_config = [&]() {
                       auto fit_params = readParameterList<double>(configFile);

                       auto it = findValueContainer(fit_params, "CB_mean");
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

                       it = findValueContainer(fit_params, "Expo_lambda");
                       if( it == fit_params.end() ) {
                         cout << "Expo_lambda not available in config file: " << configFile << endl;
                         return;
                       }
                       expo_lambda = it->second;

                       it = findValueContainer(fit_params, "Range_limit");
                       if( it == fit_params.end() ) {
                         cout << "Range_limit not available in config file: " << configFile << endl;
                         return;
                       }
                       range_limit = it->second;
                     };

  read_config();

  ////////////////////////////////////////
  // Read in the histograms
  ////////////////////////////////////////
  TString infile_name = gSystem->ExpandPathName(infile);
  auto filein = TFile::Open(infile_name,"Update");

  // naming pattern
  HistoPtr1D h1s_ptr;
  auto hdir_energy = getDirectory(filein, dirname);
  h1s_ptr = getHistosByChannelId<TH1D>(hdir_energy, suffix);

  ////////////////////////////////////////
  // Fitting with CB2Shape based on number
  // of strips in each channel
  ////////////////////////////////////////

  // Map containers for fitting results, with channel id as key
  ParameterList<double> ChannelParams;
  auto& output_avg_mean = addValueContainer(ChannelParams, "CB_mean");
  auto& output_avg_sigma = addValueContainer(ChannelParams, "CB_sigma");
  auto& output_cb_alpha1 = addValueContainer(ChannelParams, "CB_alpha1");
  auto& output_cb_alpha2 = addValueContainer(ChannelParams, "CB_alpha2");
  auto& output_cb_n1 = addValueContainer(ChannelParams, "CB_n1");
  auto& output_cb_n2 = addValueContainer(ChannelParams, "CB_n2");
  auto& output_expo_lambda = addValueContainer(ChannelParams, "Expo_lambda");
  auto& output_range_limit = addValueContainer(ChannelParams, "Range_limit");
  auto& output_evt = addValueContainer(ChannelParams, "EvtNr");
  auto& output_avg_mean_err = addValueContainer(ChannelParams, "Err(CB_mean)");
  auto& output_evt_err = addValueContainer(ChannelParams, "Err(EvtNr)");
  auto& output_chi2ndf = addValueContainer(ChannelParams, "chi2/ndf");

  // Map containers for class objects
  std::map<Int_t, RooWorkspace> ws;
  std::map<Int_t, RooFitResult> rf_result;
  std::map<Int_t, TCanvas> canvas;

  auto fit_expo_cb2 = [&] ()
                      {
                         // Print Canvases to PDF
                        TString outfile_pdf(infile_name);
                        outfile_pdf.ReplaceAll(".root", Form("_%s_FitExpoCB2.pdf", dirname));

                        TCanvas *can = new TCanvas("canvas","Fitting using CB2Shape", 1000, 1000);
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

                          /**********************************************************************/
                           // Histogram preparation
                           /**********************************************************************/
                           // rebin
                          if( tdc_id >= id)
                            hist->Rebin(10);
                          else
                            hist->Rebin(2);

                           // get the observed events in fit range
                          double ig_low = cb_mean[id]-15*cb_sigma[id];
                          double ig_high = cb_mean[id]+15*cb_sigma[id];

                          auto bin_low = hist->GetXaxis()->FindBin(ig_low);
                          auto bin_high = hist->GetXaxis()->FindBin(ig_high);
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

                          fill_expo_cb2_workspace(w,
                                                  cb_mean[id],
                                                  cb_sigma[id], cb_alpha1[id], cb_alpha2[id], cb_n1[id], cb_n2[id],
                                                  expo_lambda[id],
                                                  range_limit[id],
                                                  ntotal);
                          w.Print();
                          std::cout << "Fit channel: " << volName.Data() << "_" << ch+1 << std::endl;

                          // retrieve vars and p.d.fs from workspace
                          RooRealVar* energy = w.var("energy");
                          auto model = w.pdf("model");

                          std::cout << "Peak Energy: " << cb_mean[id] << std::endl;

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
                          model->plotOn(frame, Range("drawRange"), LineColor(kBlue));

                          // Get chi2
                          auto chi2_over_ndf = frame->chiSquare(6);
                          output_chi2ndf.emplace(id, chi2_over_ndf);

                          // Get residual
                          RooHist *hpull = frame->pullHist();
                          hpull->SetMarkerSize(0.5);
                          RooHist *hresid = frame->residHist();
                          hresid->SetMarkerSize(0.5);

                          // Add pull histo to frame2
                          RooPlot *frame2 = energy->frame(Title("Pull Distribution"));
                          frame2->addPlotable(hpull, "P");
                          RooPlot *frame3 = energy->frame(Title("Residual Distribution"));
                          frame3->addPlotable(hresid, "P");

                          // Get correlation matrix of the floating parameters
                          TH2 *hcorr = r->correlationHist();

                          // Draw all frames on a canvas
                          model->plotOn(frame, Components("bkg_model"), LineStyle(kDashed), LineColor(kGreen), Range("drawRange"));

                          canvas.emplace(std::piecewise_construct,
                                         std::forward_as_tuple(id),
                                         std::forward_as_tuple(Form("c_%s_%d",volName.Data(),ch+1),
                                                               Form("Double-sided CrystalBall Fitting"),
                                                               1000, 1000));
                          canvas[id].Divide(2,2);
                          canvas[id].cd(1);
                          gPad->SetLeftMargin(0.15);
                          gPad->SetLogy();
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
                          gPad->SetLogy();
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
                          RooRealVar* mean  = w.var("cb_m0");
                          RooRealVar* sigma = w.var("cb_sigma");
                          output_avg_mean.emplace(id, mean->getVal());
                          output_avg_mean_err.emplace(id, mean->getError());
                          output_avg_sigma.emplace(id, sigma->getVal());

                          RooRealVar* nelastic = w.var("nelastic");
                          output_evt.emplace(id, nelastic->getVal());
                          output_evt_err.emplace(id, nelastic->getError());

                          RooRealVar* tmp = w.var("cb_alpha1");
                          output_cb_alpha1.emplace(id, tmp->getVal());
                          tmp = w.var("cb_alpha2");
                          output_cb_alpha2.emplace(id, tmp->getVal());
                          tmp = w.var("cb_n1");
                          output_cb_n1.emplace(id, tmp->getVal());
                          tmp = w.var("cb_n2");
                          output_cb_n2.emplace(id, tmp->getVal());
                          tmp = w.var("expo_lambda");
                          output_expo_lambda.emplace(id, tmp->getVal());

                          output_range_limit.emplace(id, range_limit[id]);

                          std::cout << "End Fit channel: " << volName.Data() << "_" << ch+1 << std::endl;
                        }

                        // close PDF file
                        can->Print(Form("%s]",outfile_pdf.Data()));
                        delete can;
                      };

  fit_expo_cb2();

  ////////////////////////////////////////
  // Save Workspaces and RooFitResult to ROOT file, with one directory for each channel
  ////////////////////////////////////////
  auto hDirOut = getDirectory(filein, Form("%s_FitExpoCB2", dirname));

  for(auto& item : ws){
    auto id = item.first;
    auto& w = item.second;

    // hDirOut->WriteTObject(&w, "", "WriteDelete");
    hDirOut->WriteTObject(&canvas[id], "", "WriteDelete");
    // hDirOut->WriteTObject(&rf_result[id], "", "WriteDelete");
  }

  ////////////////////////////////////////
  // Save Parameters to TXT
  ////////////////////////////////////////
  TString outfile_channel_txt(infile_name);
  outfile_channel_txt.ReplaceAll(".root", Form("_%s_FitExpoCB2.txt", dirname));
  printValueList<double>(ChannelParams, outfile_channel_txt.Data());

  ////////////////////////////////////////
  // Clean up
  ////////////////////////////////////////
  delete filein;

  //
  timer.Stop();
  timer.Print();
}
