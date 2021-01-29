
#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void fit_mip_ge1ge2(
                    const char* filename,
                    const char* dirname = "no_expo1_Ge1Ge2",
                    const char* suffix = "noexpo"
                    )
{
  //
  auto encoder = KoaMapEncoder::Instance();
  auto ge1_id_start = encoder->EncodeChannelID(2,0);
  auto ge2_id_start = encoder->EncodeChannelID(3,0);

  double mpv_init[2] =   {2.0, 6.9};
  double sigma_init[2] = {0.3, 1.0};
  double fit_low[2] =  {1.5, 5.2};
  double fit_high[2] = {2.5, 7.5};

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByChannelId<TH1D>(hdir, suffix);
  delete fin;
  
  //
  auto htemp = h1s[ge1_id_start];
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
                   int det_id;
                   auto ch = encoder->DecodeChannelID(id,det_id);

                   // search mip peak
                   h1->SetAxisRange(mpv_init[det_id-2]-3*sigma_init[det_id-2],
                                    mpv_init[det_id-2]+5*sigma_init[det_id-2]);
                   TSpectrum s(1);
                   int np = s.Search(h1, 0.5, "", 0.5);
                   auto xpeaks = s.GetPositionX();
                   if(np == 1)
                     output_peak.emplace(id, xpeaks[0]);

                   // fit mip with landau
                   h1->Fit("landau", "q", "", fit_low[det_id-2], fit_high[det_id-2]);
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

    if (id < ge1_id_start) continue;

    fit_mip(id, hist);
  }

  //
  TString outfilename(filename);
  auto fout = TFile::Open(outfilename, "update");
  auto dir_out = getDirectory(fout, "no_mip_Ge1Ge2");
  writeHistos<TH1D>(dir_out, hsub);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", "_FitMip_Ge1Ge2.pdf");
  printHistos<TH1D*>(h1s, pdffilename.Data(), "", true);

  pdffilename.ReplaceAll("FitMip", "NoMip");
  printHistos<TH1D>(hsub, pdffilename.Data(), "", true);

  TString outfile_txt(filename);
  outfile_txt.ReplaceAll(".root","_FitMip_Ge1Ge2.txt");
  printValueList<double>(OutputParameters, outfile_txt.Data());

  //
  delete fout;
}
