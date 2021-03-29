#include "KoaHistUtility.h"
#include "KoaTextUtility.h"

using namespace KoaUtility;

void integrateTofE(const char* filename,
                   const char* dirname = "cluster_vs_tof",
                   const char* suffix = "cluster_vs_tof",
                   double p0=450, double p1=79.25, double p2=-0.898,
                   double win_low = -200, double win_middle = -20, double win_high = 20
                   )
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  auto hdir = getDirectory(f, dirname);
  auto hist = getHistosByRecTdcChannelId<TH2D>(hdir, suffix);
  auto htotal = (TH2D*)hdir->Get(Form("h2_%s", suffix));

  // range function
  auto fTofE = new TF1("fTofE", "[0]+[1]*TMath::Power(x,-0.5)+[2]*TMath::Power(x,-1.5)", 0.05, 7);
  fTofE->SetParameters(p0, p1, p2);

  //
  ParameterList<double> Parameters;
  auto& output_elastic = addValueContainer(Parameters, "elastic");
  auto& output_lower = addValueContainer(Parameters, "lower");
  auto& output_percent = addValueContainer(Parameters, "percent");

  auto integral = [&](TH2D* h2, double low, double high){
                    auto xbins = h2->GetNbinsX();
                    auto ybins = h2->GetNbinsY();
                    TAxis *x_ax = h2->GetXaxis();
                    TAxis *y_ax = h2->GetYaxis();
                    long sum = 0;
                    for(int x=1;x<xbins+1;x++){
                      auto energy = x_ax->GetBinCenter(x); // in MeV
                      auto tof_calc = fTofE->Eval(energy); // ns
                      auto tof_low = tof_calc + low;
                      auto tof_high = tof_calc + high;
                      for(int y=1;y<ybins+1;y++){
                        auto tof = y_ax->GetBinCenter(y); // in MeV
                        auto value = h2->GetBinContent(x, y);
                        if(tof > tof_low && tof < tof_high)
                          sum += value;
                      }
                    }
                    return sum;
                  };

  for(auto it: hist){
    auto id = it.first;
    auto h2 = it.second;
    auto sum_lower = integral(h2, win_low, win_middle);
    auto sum_elasitc = integral(h2, win_middle, win_high);
    output_elastic.emplace(id, sum_elasitc);
    output_lower.emplace(id, sum_lower);
    output_percent.emplace(id, (double)sum_lower/sum_elasitc);
  }

  auto total_elastic = integral(htotal, win_middle, win_high);
  auto total_lower = integral(htotal, win_low, win_middle);
  std::cout << "lower/elastic: " << total_lower << "/" << total_elastic
            << "(" << (double)total_lower/total_elastic << ")" << std::endl;

  // output
  TString outfilename(filename);
  outfilename.ReplaceAll(".root",Form("_%s_integral.txt",suffix));
  printValueList<double>(Parameters, outfilename.Data());

  //
  delete f;

  // timer stop
  timer.Stop();
  timer.Print();
}
