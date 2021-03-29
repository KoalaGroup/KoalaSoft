#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"
#include "fill_histpdf_bkg_workspace.cxx"

using namespace KoaUtility;
using namespace RooFit;
using namespace std;

//////////////////////
void rf_bkg_substraction(const char* infile,
                         const char* bkg_filename,
                         const char* configFile = "./rf_histpdf_cb2_config.txt",
                         const char* dirname = "Energy_All_Individual_-5.0_5.0",
                         const char* suffix = "Energy_All",
                         const char* bkg_dirname = "Energy_All_NoElastic",
                         const char* bkg_suffix = "noelastic",
                         const char* elastic_dirname = "Energy_Individual_-5.0_5.0",
                         const char* elastic_suffix = "Energy",
                         int si1_ch_low = 28, int si1_ch_high = 30,
                         int si2_ch_low = 2, int si2_ch_high = 4
                         )

{
  TStopwatch timer;

  ////////////////////////////////////////
  // Preparation
  ////////////////////////////////////////

  // Map encoder
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();

  ////////////////////////////////////////
  // Read in the fitting config params
  ////////////////////////////////////////

  ValueContainer<double> rg_low, rg_high;
  ValueContainer<double> rg_start;
  ValueContainer<double> cb_mean;
  ValueContainer<double> cb_sigma;
  ValueContainer<double> energy_offset;

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

                       it = findValueContainer(fit_params, "Range_start");
                       if( it == fit_params.end() ) {
                         cout << "Range_start not available in config file: " << configFile << endl;
                         return;
                       }
                       rg_start = it->second;

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

                       it = findValueContainer(fit_params, "Energy_offset(keV)");
                       if( it == fit_params.end() ) {
                         cout << "Energy_offset not available in config file: " << configFile << endl;
                         return;
                       }
                       energy_offset = it->second;
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
  h1s_ptr = getHistosByRecTdcChannelId<TH1D>(hdir_energy, suffix);

  hdir_energy = getDirectory(filein, elastic_dirname);
  auto hist_tofe_elastic = getHistosByRecTdcChannelId<TH1D>(hdir_energy, elastic_suffix);

  auto htemp = h1s_ptr[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hist_out = bookH1dByRecTdcChannelId("nobkg","No HistPdf Background",
                                           xbins, xlow, xup);

  // shift the histograms
  double bin_width = 1000*(xup-xlow)/xbins; // in keV
  for(auto item: h1s_ptr){
    auto id = item.first;
    auto h1 = item.second;

    shiftHisto(h1, (int)(energy_offset[id]/bin_width));
    shiftHisto(hist_tofe_elastic[id], (int)(energy_offset[id]/bin_width));
  }

  // bkg reference histograms
  auto filebkg = TFile::Open(bkg_filename);
  auto hdir_bkg = getDirectory(filebkg, bkg_dirname);
  auto hbkg = getHistosByRecTdcChannelId<TH1D>(hdir_bkg, bkg_suffix);
  delete filebkg;

  auto id = encoder->EncodeChannelID(0, si1_ch_low-1);
  TH1D* hbkg_si1 = (TH1D*)hbkg[id]->Clone("hbkg_si1");
  for(int i = si1_ch_low; i < si1_ch_high; i++){
    auto id = encoder->EncodeChannelID(0, i);
    hbkg_si1->Add(hbkg[id],1);
  }
  // hbkg_si1->Rebin(5);

  id = encoder->EncodeChannelID(1, si2_ch_low-1);
  TH1D* hbkg_si2 = (TH1D*)hbkg[id]->Clone("hbkg_si2");
  for(int i = si2_ch_low; i < si2_ch_high; i++){
    auto id = encoder->EncodeChannelID(1, i);
    hbkg_si2->Add(hbkg[id],1);
  }
  // hbkg_si2->Rebin(5);

  ////////////////////////////////////////
  // Fitting with CB2Shape based on number
  // of strips in each channel
  ////////////////////////////////////////

  // Map containers for fitting results, with channel id as key
  ParameterList<double> ChannelParams;
  auto& output_range_low = addValueContainer(ChannelParams, "Range_low");
  auto& output_range_high = addValueContainer(ChannelParams, "Range_high");
  auto& output_range_start = addValueContainer(ChannelParams, "Range_start");
  auto& output_avg_mean = addValueContainer(ChannelParams, "CB_mean");
  auto& output_avg_sigma = addValueContainer(ChannelParams, "CB_sigma");
  auto& output_energy_shift = addValueContainer(ChannelParams, "Energy_offset(keV)");
  auto& output_evt = addValueContainer(ChannelParams, "EvtNr");
  auto& output_chi2ndf = addValueContainer(ChannelParams, "chi2/ndf");

  // Map containers for class objects
  std::map<Int_t, RooWorkspace> ws;
  std::map<Int_t, RooFitResult> rf_result;
  std::map<Int_t, TCanvas> canvas;
  std::map<Int_t, TCanvas> canvas2;

  auto substract_bkg = [&] ()
                       {
                         // Print Canvases to PDF
                         TString outfile_pdf(infile_name);
                         outfile_pdf.ReplaceAll(".root", Form("_%s_SubstractBkgHistPdf.pdf",dirname));

                         TCanvas *can = new TCanvas("canvas","Substract HistPdf Background", 1000, 1000);
                         can->Divide(2,2);
                         can->Print(Form("%s[",outfile_pdf.Data()));

                         // loop through all hists
                         for ( auto& item : h1s_ptr ) {
                           auto id = item.first;
                           auto hist = item.second;

                           TString volName;
                           Int_t ch = encoder->DecodeChannelID(id, volName);
                           volName.ReplaceAll("Sensor", "");

                           // select different background template for Si1 and Si2
                           TH1D* hbkg_ref = nullptr;
                           if(volName == "Si1") hbkg_ref = hbkg_si1;
                           else if(volName == "Si2") hbkg_ref = hbkg_si2;

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
                           if(cb_mean[id] < 1.6) {
                             hist->Rebin(2);
                             hist_tofe_elastic[id]->Rebin(2);
                             hist_out[id].Rebin(2);
                           }
                           else{
                             hist->Rebin(8);
                             hist_tofe_elastic[id]->Rebin(8);
                             hist_out[id].Rebin(8);
                           }

                           /**********************************************************************/
                           // Define the workspace
                           /**********************************************************************/

                           // fill in the fit model
                           ws.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(id),
                                      std::forward_as_tuple(Form("ws_%s_%d", volName.Data(), ch+1),
                                                            Form("RooWorkspace of %s_%d", volName.Data(), ch+1)));
                           RooWorkspace& w = ws[id];

                           fill_histpdf_bkg_workspace(w,
                                                      hbkg_ref,
                                                      rg_low[id], rg_high[id],
                                                      rg_start[id],
                                                      cb_mean[id],
                                                      cb_sigma[id]
                                                      );
                           w.Print();
                           std::cout << "Fit channel: " << volName.Data() << "_" << ch+1 << std::endl;

                           // retrieve vars and p.d.fs from workspace
                           RooRealVar* energy = w.var("energy");
                           auto model = w.pdf("model");

                           // RooRealVar* cb_m0 = w.var("cb_m0");
                           std::cout << "Peak Energy: " << cb_mean[id] << std::endl;

                           // init and fill in the data set
                           std::cout << "Import data: " << volName.Data() << "_" << ch+1 << std::endl;

                           RooDataHist dh("dh", Form("%s_%d", volName.Data(), ch+1), *energy, Import(*hist));
                           w.import(dh);

                           // estimate bkg evt nr
                           auto bin_low = hist->GetXaxis()->FindBin(0.12);
                           auto bin_high = hist->GetXaxis()->FindBin(6);
                           double nbkg = hist->Integral(bin_low, bin_high);
                           RooRealVar* n_bkg = w.var("nbkg");
                           n_bkg->setVal(nbkg);
                           n_bkg->setRange(0, nbkg);

                           /**********************************************************************/
                           // Fitting the background
                           /**********************************************************************/
                           std::cout << "Fitting: " << volName.Data() << "_" << ch+1 << std::endl;

                           RooFitResult* r = model->fitTo(dh, Range("fitRange"), Save());
                           r->SetName(Form("rf_result_%s_%d", volName.Data(), ch+1));

                           // get the residual plot
                           RooPlot *frame_res = energy->frame(Title("Background Substracted"));
                           dh.plotOn(frame_res, MarkerSize(0.5), Range("drawRange"));
                           model->plotOn(frame_res, LineColor(kRed), Range("drawRange"));
                           RooHist *helastic = frame_res->residHist();
                           helastic->SetMarkerSize(0.5);

                           auto ig_low = cb_mean[id] - 7*cb_sigma[id];
                           auto ig_high = cb_mean[id] + 7*cb_sigma[id];
                           if(ig_low < 0.12)
                             ig_low = 0.12;
                           auto nelastic = helastic->getFitRangeNEvt(ig_low, ig_high);
                           output_evt.emplace(id, nelastic);

                           // convert RooHist to TH1D
                           auto n = helastic->GetN();
                           auto x = helastic->GetX();
                           auto y = helastic->GetY();
                           for(int i=0;i<n;i++){
                             auto bin = hist_out[id].GetXaxis()->FindBin(x[i]);
                             hist_out[id].SetBinContent(bin, y[i]);
                           }

                           /**********************************************************************/
                           // Drawing
                           /**********************************************************************/
                           RooPlot *frame = energy->frame(Title(Form( "Fitting background of %s_%d", volName.Data(), ch+1 )), Range(0.02, 0.15));
                           dh.plotOn(frame, MarkerSize(0.5), Range(0.02, 0.15));
                           model->plotOn(frame, VisualizeError(*r));
                           model->plotOn(frame, Range(0.02, 0.15), LineColor(kRed));

                           RooPlot *frame2 = energy->frame(Title("Pull Distribution"), Range("fitRange"));
                           dh.plotOn(frame2, MarkerSize(0.5), Range("fitRange"));
                           model->plotOn(frame2, LineColor(kRed), Range("fitRange"));

                           // Get chi2
                           auto chi2_over_ndf = frame2->chiSquare(1);
                           output_chi2ndf.emplace(id, chi2_over_ndf);

                           RooHist *hpull = frame2->pullHist();
                           hpull->SetMarkerSize(0.5);
                           RooHist *hresid = frame2->residHist();
                           hresid->SetMarkerSize(0.5);

                           RooPlot *frame3 = energy->frame(Title("Residual Distribution") ,Range("fitRange"));
                           frame3->addPlotable(hresid, "P");

                           RooPlot *frame4 = energy->frame(Title("Background Substracted"), Range(ig_low, ig_high));
                           frame4->addPlotable(helastic, "P");

                           RooPlot *frame5 = energy->frame(Title("Background Substracted"), Range("fitRange"));
                           frame5->addPlotable(hpull, "P");

                           // Draw all frames on a canvas
                           canvas.emplace(std::piecewise_construct,
                                          std::forward_as_tuple(id),
                                          std::forward_as_tuple(Form("c_%s_%d",volName.Data(),ch+1),
                                                                Form("HistPdf + Double-sided CrystalBall Fitting"),
                                                                1000, 1000));
                           canvas[id].Divide(2,2);
                           canvas[id].cd(1);
                           gPad->SetLeftMargin(0.15);
                           frame->GetYaxis()->SetTitleOffset(1.8);
                           frame->Draw();

                           canvas[id].cd(2);
                           gPad->SetLeftMargin(0.1);
                           frame5->Draw();

                           canvas[id].cd(3);
                           gPad->SetLeftMargin(0.2);
                           hist_tofe_elastic[id]->SetLineColor(kBlue);
                           hist_tofe_elastic[id]->SetLineWidth(3);
                           frame4->Draw();
                           hist_tofe_elastic[id]->Draw("same");

                           canvas[id].cd(4);
                           gPad->SetLeftMargin(0.1);
                           frame3->Draw();

                           canvas2.emplace(std::piecewise_construct,
                                           std::forward_as_tuple(id),
                                           std::forward_as_tuple(Form("c2_%s_%d",volName.Data(),ch+1),
                                                                 Form("HistPdf + Double-sided CrystalBall Fitting"), 600, 600));
                           canvas2[id].cd();
                           hist_tofe_elastic[id]->SetLineColor(kBlue);
                           hist_tofe_elastic[id]->SetLineWidth(3);
                           frame4->Draw();
                           hist_tofe_elastic[id]->Draw("same");

                           // for printing to pdf file
                           can->cd(1);
                           gPad->SetLeftMargin(0.15);
                           // gPad->SetLogy();
                           frame->GetYaxis()->SetTitleOffset(1.8);
                           frame->Draw();

                           can->cd(2);
                           gPad->SetLeftMargin(0.1);
                           frame5->Draw();

                           can->cd(3);
                           gPad->SetLeftMargin(0.2);
                           frame4->Draw();
                           hist_tofe_elastic[id]->Draw("same");

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

                           output_avg_mean.emplace(id, cb_mean[id]);
                           output_avg_sigma.emplace(id, cb_sigma[id]);

                           output_range_low.emplace(id, rg_low[id]);
                           output_range_high.emplace(id, rg_high[id]);
                           output_range_start.emplace(id, rg_start[id]);
                           output_energy_shift.emplace(id, energy_offset[id]);

                           std::cout << "End Fit channel: " << volName.Data() << "_" << ch+1 << std::endl;
                         }

                         // close PDF file
                         can->Print(Form("%s]",outfile_pdf.Data()));
                         delete can;
                       };

  substract_bkg();

  ////////////////////////////////////////
  // Save Workspaces and RooFitResult to ROOT file, with one directory for each channel
  ////////////////////////////////////////
  auto hDirOut = getDirectory(filein, Form("%s_SubstractBkgHistPdf", dirname));

  for(auto& item : ws){
    auto id = item.first;
    auto& w = item.second;

    // hDirOut->WriteTObject(&w, "", "WriteDelete");
    hDirOut->WriteTObject(&canvas[id], "", "WriteDelete");
    hDirOut->WriteTObject(&canvas2[id], "", "WriteDelete");
  }
  writeHistos<TH1D>(hDirOut, hist_out);

  ////////////////////////////////////////
  // Save Parameters to TXT
  ////////////////////////////////////////
  TString outfile_channel_txt(infile_name);
  outfile_channel_txt.ReplaceAll(".root", Form("_%s_SubstractBkgHistPdf.txt", dirname));
  printValueList<double>(ChannelParams, outfile_channel_txt.Data());

  ////////////////////////////////////////
  // Clean up
  ////////////////////////////////////////
  delete filein;

  //
  timer.Stop();
  timer.Print();
}
