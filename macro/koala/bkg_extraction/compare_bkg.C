#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

void compare_bkg(
                 const char* filename,
                 const char* ref_filename,
                 const char* bkg_filename,
                 const char* sensor = "Si1",
                 int ref_ch = 29,
                 const char* prefix = "noelastic_vs_noelastic",
                 double rg_low = 0.12, double rg_high = 6,
                 const char* dirname = "Energy_All_NoElastic",
                 const char* suffix = "noelastic",
                 const char* ref_dirname = "Energy_All_NoElastic",
                 const char* ref_suffix = "noelastic"
)
{
  // get ref ch id
  auto encoder = KoaMapEncoder::Instance();
  auto ref_id = encoder->EncodeChannelID(Form("Sensor%s", sensor), ref_ch-1);

  //
  auto fin = TFile::Open(filename);
  auto hdir = getDirectory(fin, dirname);
  auto h1s = getHistosByRecTdcChannelId<TH1D>(hdir, suffix);
  delete fin;

  //
  auto fref = TFile::Open(ref_filename);
  hdir = getDirectory(fref, ref_dirname);
  auto href = getHistosByRecTdcChannelId<TH1D>(hdir, ref_suffix);
  delete fref;

  // rebin
  int rebin = 5;
  for(auto item: h1s){
    auto id = item.first;
    auto hist = item.second;
    hist->Rebin(rebin);
    href[id]->Rebin(rebin);
  }

  //
  auto gr_qq = bookGraphByRecTdcChannelId("qq",
                                          Form("Q-Q plot, Ref: %s_%d", sensor, ref_ch),
                                          kBlack, 20, 0.5
                                          );
  auto gr_qq_diff = bookGraphByRecTdcChannelId("qq_diff",
                                               Form("Q-Q Diff plot, Ref: %s_%d", sensor, ref_ch),
                                               kBlack, 20, 0.5
                                               );
  auto gr_res = bookGraphByRecTdcChannelId("res",
                                          Form("Residual (Chi2Test), Ref: %s_%d", sensor, ref_ch),
                                          kBlack, 20, 0.5
                                          );

  //
  auto get_qqplot = [&] ()
                    {
                      int nprob = 50;
                      auto prob = new double[nprob];
                      for(int i =0 ;i<(nprob-1); i++) prob[i] = double(i+1)/nprob;

                      for(auto item: h1s){
                        auto id = item.first;
                        auto hist = item.second;

                        gr_qq[id].Set(nprob);
                        auto x = gr_qq[id].GetX();
                        auto y = gr_qq[id].GetY();

                        auto np = href[ref_id]->GetQuantiles(nprob, x, prob);
                        hist->GetQuantiles(nprob, y, prob);
                        for(int i=0;i<np;i++){
                          gr_qq_diff[id].SetPoint(i, x[i], y[i]-x[i]);
                        }
                      }
                    };

  auto get_resplot = [&] ()
                     {
                       // chi2test normalized residual distribution
                       href[ref_id]->SetAxisRange(rg_low, rg_high, "X");
                       auto xaxis = href[ref_id]->GetXaxis();
                       auto bin_low = xaxis->FindBin(rg_low);
                       auto bin_high = xaxis->FindBin(rg_high);
                       auto res = new double[bin_high-bin_low+1];

                       for(auto item: h1s) {
                         auto id = item.first;
                         auto hist = item.second;

                         hist->SetAxisRange(rg_low, rg_high, "X");
                         auto p_val = hist->Chi2Test(href[ref_id], "UU P", res);
                         int index =0 ;
                         for(int i=bin_low;i<=bin_high;i++){
                           auto x = xaxis->GetBinCenter(i);
                           gr_res[id].SetPoint(index++, x, res[i-bin_low]);
                         }
                       }
                     };

  //
  get_qqplot();
  get_resplot();

  // output
  auto fout = TFile::Open(bkg_filename, "update");
  auto dir_out = getDirectory(fout, Form("qqplot_%s_Ref_%s_%d", prefix, sensor, ref_ch));
  writeGraphs(dir_out, gr_qq);
  writeGraphs(dir_out, gr_qq_diff);

  dir_out = getDirectory(fout, Form("chi2test_%s_Ref_%s_%d", prefix, sensor, ref_ch));
  writeGraphs(dir_out, gr_res);

  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root", Form("_qqplot_%s_Ref_%s_%d.pdf",prefix,sensor, ref_ch));
  printGraphs(gr_qq, pdffilename.Data());
  pdffilename.ReplaceAll("qqplot", "qqdiff");
  printGraphs(gr_qq_diff, pdffilename.Data());

  pdffilename.ReplaceAll("qqdiff", "chi2test");
  printGraphs(gr_res, pdffilename.Data());

  //
  delete fout;
}
