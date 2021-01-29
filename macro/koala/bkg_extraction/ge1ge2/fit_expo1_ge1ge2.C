#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void fit_expo1_ge1_ge2(
                       const char* filename,
                       const char* bkg_filename,
                       const char* dirname = "rec_cluster_energy_FirstHit",
                       const char* suffix = "cluster_energy_firstHit"
                       )
{
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByChannelId<TH1D>(hdir, suffix);

  auto encoder = KoaMapEncoder::Instance();
  auto ge1_id_start = encoder->EncodeChannelID(2,0);
  auto ge1_id_stop = encoder->EncodeChannelID(2,28);
  auto ge2_id_start = encoder->EncodeChannelID(3,0);
  auto ge2_id_stop = encoder->EncodeChannelID(3,16);

  double fit_low[4] = {1.05, 1.2,  1.8, 2.4};
  double fit_high[4] = {1.3, 1.4, 4.0, 3.9};

  // book output histograms
  auto htemp = h1s[ge1_id_start];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByChannelId("noexpo","Substract exponential bkg1",
                                 xbins, xlow, xup, kBlue);

  // book output parameters
  ParameterList<double> OutputParameters;
  auto& output_p0 = addValueContainer(OutputParameters, "Expo_p0");
  auto& output_p1 = addValueContainer(OutputParameters, "Expo_lambda");

  //
  auto fit_expo = [&](int id, TH1D* h1, double low, double high)
                  {
                    h1->Fit("expo", "q", "", low, high);
                    auto fexpo = (TF1*)h1->GetFunction("expo");
                    fexpo->SetRange(0,xup);
                    fexpo->SetNpx(1000);
                    output_p0.emplace(id, fexpo->GetParameter(0));
                    output_p1.emplace(id, fexpo->GetParameter(1));

                    xaxis = hsub[id].GetXaxis();
                    xbins = hsub[id].GetNbinsX();
                    for(int i=1;i<xbins;i++){
                      auto x = xaxis->GetBinCenter(i);
                      auto y = h1->GetBinContent(i);
                      auto calc = fexpo->Eval(x);
                      if(x > low)
                        hsub[id].SetBinContent(i, y-calc);
                    }
                  };

  for(auto item: h1s){
    auto id = item.first;
    auto hist = item.second;
    // hist->Rebin(2);

    if( id < ge1_id_start ) continue;

    // fit with expo
    if(id < ge1_id_stop) {
      fit_expo(id, hist, fit_low[0], fit_high[0]);
    }
    else if (id < ge2_id_start) {
      fit_expo(id, hist, fit_low[1], fit_high[1]);
    }
    else if (id < ge2_id_stop) {
      fit_expo(id, hist, fit_low[2], fit_high[2]);
    }
    else {
      int det_id;
      auto ch = encoder->DecodeChannelID(id,det_id);
      if(ch == 24 || ch == 29)
        fit_expo(id, hist, 2.7, 4.5);
      else
        fit_expo(id, hist, fit_low[3], fit_high[3]);
    }
  }

  //
  TString outfilename(bkg_filename);
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, "no_expo1_Ge1Ge2");
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(bkg_filename);
  pdffilename.ReplaceAll(".root", "_BkgNoExpo_Ge1Ge2.pdf");
  printHistos<TH1D>(hsub, pdffilename.Data(), "", true);
  pdffilename.ReplaceAll("_BkgNoExpo","_BkgExpoFit");
  printHistos<TH1D*>(h1s, pdffilename.Data(), "", true);

  TString outfile_txt(bkg_filename);
  outfile_txt.ReplaceAll(".root","_BkgExpoFit_Ge1Ge2.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  delete fin, fout;
}
