
#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void fit_mip_si1si2(
                    const char* filename,
                    const char* dirname = "no_expo1_Si1Si2",
                    const char* suffix = "noexpo"
                    )
{
  //
  double mpv_init=0.37;
  double sigma_init=0.05;
  double fit_low=0.25;
  double fit_high = 0.45;

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);
  delete fin;
  
  //
  auto htemp = h1s[0];
  auto xbins = htemp->GetNbinsX();
  auto xaxis = htemp->GetXaxis();
  auto xlow = xaxis->GetBinLowEdge(1);
  auto xup = xaxis->GetBinUpEdge(xbins);
  auto hsub = bookH1dByChannelId("nomip","Substract MIP bkg",
                                 xbins, xlow, xup, kBlack);

  // book output parameters
  ParameterList<double> OutputParameters;
  auto& output_peak = addValueContainer(OutputParameters, "Peak");
  auto& output_mpv = addValueContainer(OutputParameters, "MPV");
  auto& output_sigma = addValueContainer(OutputParameters, "Sigma");
  // auto& output_evt = addValueContainer(OutputParameters, "EvtNr");

  //
  auto fit_mip = [&] (int id, TH1D* h1)
                 {
                   // search mip peak
                   h1->SetAxisRange(mpv_init-3*sigma_init,
                                    mpv_init+5*sigma_init);
                   TSpectrum s(1);
                   int np = s.Search(h1, 0.5, "", 0.5);
                   auto xpeaks = s.GetPositionX();
                   if(np == 1)
                     output_peak.emplace(id, xpeaks[0]);

                   // fit mip with landau
                   h1->Fit("landau", "q", "", fit_low, fit_high);
                   auto flandau = (TF1*)h1->GetFunction("landau");
                   flandau->SetRange(0,xup);
                   flandau->SetNpx(1000);
                   output_mpv.emplace(id, flandau->GetParameter(1));
                   output_sigma.emplace(id, flandau->GetParameter(2));

                   // substract mip
                   h1->SetAxisRange(xlow, xup);
                   xaxis = hsub[id].GetXaxis();
                   xbins = hsub[id].GetNbinsX();
                   for(int i=1;i<xbins;i++){
                     auto x = xaxis->GetBinCenter(i);
                     auto y = h1->GetBinContent(i);
                     auto calc = flandau->Eval(x);
                     hsub[id].SetBinContent(i, y-calc);
                   }
                 };

  //
  for(auto item: h1s) {
    auto id = item.first;
    auto hist = item.second;

    fit_mip(id, hist);
  }

  //
  TString outfilename(filename);
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, "no_mip_Si1Si2");
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", "_FitMip_Si1Si2.pdf");
  printHistos<TH1D*>(h1s, pdffilename.Data(), "", true);

  pdffilename.ReplaceAll("FitMip", "NoMip");
  printHistos<TH1D>(hsub, pdffilename.Data(), "", true);

  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_FitMip_Si1Si2.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  delete fout;
}
