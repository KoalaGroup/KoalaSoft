#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"

using namespace KoaUtility;

double tof_energy_imp(double* x, double *p){
  KoaElasticCalculator calculator(p[0], p[1], p[2]);

  double alpha = calculator.GetAlphaByEnergy(x[0]);
  double tof_rec = calculator.GetRecTOFByAlpha(alpha);
  double tof_fwd = calculator.GetFwdTOFByAlpha(alpha);
  return tof_rec-tof_fwd;
}

void resolution_TofE_StripCorrection(const char* filename,
                                     // double tof_offset = 480,
                                     const char* cut_filename,
                                     const char* dirname = "TofE_Individual_-5.0_5.0",
                                     const char* suffix = "TofE",
                                     const char* cut_dirname = "TofE_profile_MoreThan10Evts",
                                     double e_low = 0.05, double e_high=2., double e_step=0.02,
                                     double tof_low = 500, double tof_high = 700, double tof_step = 1
                                     )
{
  auto fin = TFile::Open(filename, "update");
  TDirectory* hdir = getDirectory(fin, dirname);
  auto h2map = getHistosByRecTdcChannelId<TH2D>(hdir, suffix);

  //
  auto fgraph = TFile::Open(cut_filename);
  auto gdir = getDirectory(fgraph, cut_dirname);
  auto gr_mean = getGraphsByRecTdcChannelId(gdir, "mean");
  auto gr_mean_inv = bookGraphByRecTdcChannelId("mean_inv","TOF VS E", kBlack, 20, 0.4);
  for(auto item: gr_mean){
    auto id = item.first;
    auto gr = item.second;
    auto npoints = gr->GetN();
    double* e = gr->GetX();
    double* tof = gr->GetY();
    for(int i=0;i<npoints;i++){
      gr_mean_inv[id].SetPoint(i, tof[i], e[i]);
    }
  }

  //
  auto gr_energy_resolution = bookGraphByRecTdcChannelId("energy_resolution", "E VS #sigma_{E};E (MeV); #sigma_{E} (MeV)", kBlack, 20, 0.4);
  auto gr_tof_resolution = bookGraphByRecTdcChannelId("tof_resolution", "E VS #sigma_{TOF};E (MeV); #sigma_{TOF} (ns)", kBlack, 20, 0.4);

  TH1D h1_energy("h1_energy","Energy Resolutions",100, 0, 0.5);
  TH1D h1_tof("h1_tof","TOF Resolutions",100, 1, 10);

  //
  std::map<int, double> e_means;
  std::map<int, double> e_sigmas;
  std::map<int, double> tof_means;
  std::map<int, double> tof_sigmas;
  double e_mean_buffer, e_sigma_buffer, tof_mean_buffer, tof_sigma_buffer;

  auto fit_energy = [&](TH1D* hist) -> bool
                    {
                      TSpectrum s(1);
                      auto npeaks = s.Search(hist, 0.04, "", 0.5);

                     if(npeaks>0) {
                       Double_t *xpeaks = s.GetPositionX();
                       auto sigma = hist->GetRMS();
                       auto result = hist->Fit("gaus", "qs", "", xpeaks[0]-0.04, xpeaks[0]+0.04);

                       // first fit to get rough estimation
                       sigma = result->Parameter(2);
                       hist->GetXaxis()->SetRangeUser(xpeaks[0]-10*sigma, xpeaks[0]+7*sigma);
                       result = hist->Fit("gaus", "qs", "", xpeaks[0]-sigma, xpeaks[0]+2*sigma);

                       //
                       if(TMath::Abs(xpeaks[0]-result->Parameter(1)) < 0.05) {
                         // e_mean_buffer = result->Parameter(1);
                         e_mean_buffer = xpeaks[0];
                         e_sigma_buffer = result->Parameter(2);
                         return true;
                       }
                     }
                     return false;
                    };

  auto fit_tof = [&](TH1D* hist) -> bool
                 {
                   TSpectrum s(1);
                   auto npeaks = s.Search(hist, 2.0, "", 0.4);

                   if(npeaks>0) {
                     Double_t *xpeaks = s.GetPositionX();
                     auto sigma = hist->GetRMS();
                     auto result = hist->Fit("gaus", "qs", "", xpeaks[0]-2, xpeaks[0]+2);

                     // first fit to get rough estimation
                     sigma = result->Parameter(2);
                     hist->GetXaxis()->SetRangeUser(xpeaks[0]-10*sigma, xpeaks[0]+7*sigma);
                     result = hist->Fit("gaus", "qs", "", xpeaks[0]-sigma, xpeaks[0]+2*sigma);

                     //
                     if(TMath::Abs(xpeaks[0]-result->Parameter(1)) < 2) {
                       // tof_mean_buffer = result->Parameter(1);
                       tof_mean_buffer = xpeaks[0];
                       tof_sigma_buffer = result->Parameter(2);
                       return true;
                     }
                   }
                   return false;
                 };

  // Energy Division
  for(auto item: h2map){
    auto id = item.first;
    auto h2 = item.second;
    auto xaxis = h2->GetXaxis();
    auto yaxis = h2->GetYaxis();
    auto& gr_resolution = gr_energy_resolution[id];

    int e_nr = (e_high-e_low)/e_step;
    int gindex = 0;
    for(int i=0;i<e_nr;i++){
      auto x_low = e_low+i*e_step;
      auto y_high = gr_mean[id]->Eval(x_low);
      auto x_high = x_low+e_step;
      auto y_low = gr_mean[id]->Eval(x_high);

      //
      auto ybin_low = yaxis->FindBin(y_low);
      auto ybin_high = yaxis->FindBin(y_high);

      //
      auto h_energy = h2->ProjectionX(Form("h_energy_%d",i+1), ybin_low, ybin_high);

      if(fit_energy(h_energy)){
        gr_resolution.SetPoint(gindex, e_mean_buffer, e_sigma_buffer);
        h1_energy.Fill(e_sigma_buffer);
        gindex++;
      }
    }
  }

  // TOF Division
  for(auto item: h2map){
    auto id = item.first;
    auto h2 = item.second;
    auto xaxis = h2->GetXaxis();
    auto yaxis = h2->GetYaxis();
    auto& gr_resolution = gr_tof_resolution[id];

    int tof_nr = (tof_high-tof_low)/tof_step;
    int gindex = 0;
    for(int i=0;i<tof_nr;i++){
      auto y_low = tof_low+i*tof_step;
      auto x_high = gr_mean_inv[id].Eval(y_low);
      auto y_high = y_low+tof_step;
      auto x_low = gr_mean_inv[id].Eval(y_high);

      //
      auto xbin_low = xaxis->FindBin(x_low);
      auto xbin_high = xaxis->FindBin(x_high);

      //
      auto h_tof = h2->ProjectionY(Form("h_tof_%d",i+1), xbin_low, xbin_high);

      if(fit_tof(h_tof)){
        gr_resolution.SetPoint(gindex, gr_mean_inv[id].Eval(tof_mean_buffer), tof_sigma_buffer);
        h1_tof.Fill(tof_sigma_buffer);
        gindex++;
      }
    }
  }

  //
  auto dir_out = getDirectory(fin, "Resolution");
  dir_out->WriteTObject(&h1_energy, "", "WriteDelete");
  dir_out->WriteTObject(&h1_tof, "", "WriteDelete");
  writeGraphs<TGraphErrors>(dir_out, gr_energy_resolution);
  writeGraphs<TGraphErrors>(dir_out, gr_tof_resolution);

  //
  delete fin;
}
