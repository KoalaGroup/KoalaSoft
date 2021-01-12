#include "KoaHistUtility.h"

using namespace KoaUtility;

void draw_TofE_profile(const char* filename,
                       const char* dirname,
                       const char* hname,
                       double e_low = 0.05, double e_high=2., double e_step=0.02,
                       double tof_low = 500, double tof_high = 700, double tof_step = 1,
                       double p0=450, double p1=79.25, double p2=-0.898
                       )
{
  auto fin = TFile::Open(filename, "update");
  TDirectory* dir = (TDirectory*)fin->Get(dirname);
  TH2D* h2_TofE = (TH2D*)dir->Get(hname);
  TAxis* xaxis = h2_TofE->GetXaxis();
  TAxis* yaxis = h2_TofE->GetYaxis();

  // range function
  auto fTofE = new TF1("fTofE", "[0]+[1]*TMath::Power(x,-0.5)+[2]*TMath::Power(x,-1.5)", 0.05, 10);
  fTofE->SetNpx(1000);
  fTofE->SetParameters(p0, p1, p2);

  //
  std::map<int, TH1D*> energy_hists;
  std::map<int, TH1D*> tof_hists;

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
  int e_nr = (e_high-e_low)/e_step;
  int gindex = 0;
  for(int i=0;i<e_nr;i++){
    auto x_low = e_low+i*e_step;
    auto y_high = fTofE->Eval(x_low);
    auto x_high = x_low+e_step;
    auto y_low = fTofE->Eval(x_high);

    //
    auto xbin_low = xaxis->FindBin(x_low);
    auto xbin_high = xaxis->FindBin(x_high);
    auto ybin_low = yaxis->FindBin(y_low);
    auto ybin_high = yaxis->FindBin(y_high);

    //
    auto h_energy = h2_TofE->ProjectionX(Form("h_energy_%d",i+1), ybin_low, ybin_high);
    auto h_tof = h2_TofE->ProjectionY(Form("h_tof_%d",i+1), xbin_low, xbin_high);

    if(fit_energy(h_energy) && fit_tof(h_tof)){
      e_means.emplace(gindex, e_mean_buffer);
      e_sigmas.emplace(gindex, e_sigma_buffer);
      tof_means.emplace(gindex, tof_mean_buffer);
      tof_sigmas.emplace(gindex, tof_sigma_buffer);
      gindex++;
    }

    energy_hists.emplace(i, h_energy);
    tof_hists.emplace(i, h_tof);
  }

  // output
  TGraph *gr_TofE = new TGraph();
  gr_TofE->SetName("gr_TofE");
  gr_TofE->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gr_TofE->SetLineWidth(0);
  gr_TofE->SetMarkerSize(0.8);
  gr_TofE->SetMarkerStyle(20);
  TGraphErrors *gre_TofE = new TGraphErrors();
  gre_TofE->SetName("gre_TofE");
  gre_TofE->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gre_TofE->SetLineWidth(0);
  gre_TofE->SetMarkerSize(0.8);
  gre_TofE->SetMarkerStyle(20);
  TGraph *gr_E_TofSigma = new TGraph();
  gr_E_TofSigma->SetName("gr_E_TofSigma");
  gr_E_TofSigma->SetTitle("Energy VS Sigma(TOF);E (MeV);#sigma_{TOF} (ns)");
  gr_E_TofSigma->SetLineWidth(0);
  gr_E_TofSigma->SetMarkerSize(0.8);
  gr_E_TofSigma->SetMarkerStyle(20);
  TGraph *gr_E_ESigma = new TGraph();
  gr_E_ESigma->SetName("gr_E_ESigma");
  gr_E_ESigma->SetTitle("Energy VS Sigma(E);E (MeV);#sigma_{E} (MeV)");
  gr_E_ESigma->SetLineWidth(0);
  gr_E_ESigma->SetMarkerSize(0.8);
  gr_E_ESigma->SetMarkerStyle(20);

  std::ofstream ftxt(gSystem->ExpandPathName(Form("%s_%.0fkeV_%.0fps_EDiv.txt",hname,e_step*1000,tof_step*1000)));
  if(!ftxt.is_open()){
    std::cout << "Can't open txt out file \n";
    return;
  }
  ftxt << std::setw(6) << std::left << "Index" ;
  ftxt << std::setw(12) << std::left << "E_mean" ;
  ftxt << std::setw(12) << std::left << "E_err" ;
  ftxt << std::setw(12) << std::left << "Tof_mean" ;
  ftxt << std::setw(12) << std::left << "Tof_err" << std::endl;
  for(auto item: e_means){
    auto index = item.first;

    //
    ftxt << std::setw(6) << std::left << index;
    ftxt << std::setw(12) << std::left << e_means[index];
    ftxt << std::setw(12) << std::left << e_sigmas[index];
    ftxt << std::setw(12) << std::left << tof_means[index];
    ftxt << std::setw(12) << std::left << tof_sigmas[index]<< std::endl;

    //
    gr_TofE->SetPoint(index, e_means[index], tof_means[index]);
    gr_E_TofSigma->SetPoint(index, e_means[index], tof_sigmas[index]);
    gr_E_ESigma->SetPoint(index, e_means[index], e_sigmas[index]);

    gre_TofE->SetPoint(index, e_means[index], tof_means[index]);
    gre_TofE->SetPointError(index, 0, 5*tof_sigmas[index]);
  }
  ftxt.close();

  //
  TString outfile_EDiv_energy_pdf(Form("%s_%.0fkeV_%.0fps_EDiv_energy.pdf",hname,e_step*1000,tof_step*1000));
  printHistos<TH1D*>(energy_hists, outfile_EDiv_energy_pdf.Data());
  TString outfile_EDiv_tof_pdf(Form("%s_%.0fkeV_%.0fps_EDiv_tof.pdf",hname,e_step*1000,tof_step*1000));
  printHistos<TH1D*>(tof_hists, outfile_EDiv_tof_pdf.Data());

  TDirectory* out_dir = getDirectory(fin, Form("%s_%0.fkeV_%.0fps_EDiv", hname, e_step*1000,tof_step*1000));
  out_dir->WriteTObject(gr_TofE, "", "WriteDelete");
  out_dir->WriteTObject(gre_TofE, "", "WriteDelete");
  out_dir->WriteTObject(gr_E_TofSigma, "", "WriteDelete");
  out_dir->WriteTObject(gr_E_ESigma, "", "WriteDelete");
  delete gr_TofE;
  delete gr_E_TofSigma;
  delete gr_E_ESigma;

  /********************************************/
  // TOF Division
  energy_hists.clear();
  tof_hists.clear();

  e_means.clear();
  e_sigmas.clear();
  tof_means.clear();
  tof_sigmas.clear();

  gr_TofE = new TGraph();
  gr_TofE->SetName("gr_TofE");
  gr_TofE->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gr_TofE->SetLineWidth(0);
  gr_TofE->SetMarkerSize(0.8);
  gr_TofE->SetMarkerStyle(20);

  gre_TofE = new TGraphErrors();
  gre_TofE->SetName("gre_TofE");
  gre_TofE->SetTitle("TOF-E;E (MeV);TOF (ns)");
  gre_TofE->SetLineWidth(0);
  gre_TofE->SetMarkerSize(0.8);
  gre_TofE->SetMarkerStyle(20);

  gr_E_TofSigma = new TGraph();
  gr_E_TofSigma->SetName("gr_E_TofSigma");
  gr_E_TofSigma->SetTitle("Energy VS Sigma(TOF);E (MeV);#sigma_{TOF} (ns)");
  gr_E_TofSigma->SetLineWidth(0);
  gr_E_TofSigma->SetMarkerSize(0.8);
  gr_E_TofSigma->SetMarkerStyle(20);

  gr_E_ESigma = new TGraph();
  gr_E_ESigma->SetName("gr_E_ESigma");
  gr_E_ESigma->SetTitle("Energy VS Sigma(E);E (MeV);#sigma_{E} (MeV)");
  gr_E_ESigma->SetLineWidth(0);
  gr_E_ESigma->SetMarkerSize(0.8);
  gr_E_ESigma->SetMarkerStyle(20);

  //
  int tof_nr = (tof_high - tof_low)/tof_step;
  gindex = 0 ;
  for(int i=0;i<tof_nr;i++){
    auto y_low = tof_low + i*tof_step;
    auto y_high = y_low + tof_step;
    auto x_high = fTofE->GetX(y_low);
    auto x_low = fTofE->GetX(y_high);

    //
    auto xbin_low = xaxis->FindBin(x_low);
    auto xbin_high = xaxis->FindBin(x_high);
    auto ybin_low = yaxis->FindBin(y_low);
    auto ybin_high = yaxis->FindBin(y_high);

    //
    auto h_energy = h2_TofE->ProjectionX(Form("h_energy_%d",i+1), ybin_low, ybin_high);
    auto h_tof = h2_TofE->ProjectionY(Form("h_tof_%d",i+1), xbin_low, xbin_high);

    if(fit_energy(h_energy) && fit_tof(h_tof)){
      e_means.emplace(gindex, e_mean_buffer);
      e_sigmas.emplace(gindex, e_sigma_buffer);
      tof_means.emplace(gindex, tof_mean_buffer);
      tof_sigmas.emplace(gindex, tof_sigma_buffer);
      gindex++;
    }

    energy_hists.emplace(i, h_energy);
    tof_hists.emplace(i, h_tof);
  }

  //
  ftxt.open(gSystem->ExpandPathName(Form("%s_%.0fkeV_%.0fps_TofDiv.txt",hname,e_step*1000,tof_step*1000)));
  if(!ftxt.is_open()){
    std::cout << "Can't open txt out file \n";
    return;
  }
  ftxt << std::setw(6) << std::left << "Index" ;
  ftxt << std::setw(12) << std::left << "E_mean" ;
  ftxt << std::setw(12) << std::left << "E_err" ;
  ftxt << std::setw(12) << std::left << "Tof_mean" ;
  ftxt << std::setw(12) << std::left << "Tof_err" << std::endl;
  for(auto item: e_means){
    auto index = item.first;

    //
    ftxt << std::setw(6) << std::left << index;
    ftxt << std::setw(12) << std::left << e_means[index];
    ftxt << std::setw(12) << std::left << e_sigmas[index];
    ftxt << std::setw(12) << std::left << tof_means[index];
    ftxt << std::setw(12) << std::left << tof_sigmas[index]<< std::endl;

    //
    gr_TofE->SetPoint(index, e_means[index], tof_means[index]);
    gr_E_TofSigma->SetPoint(index, e_means[index], tof_sigmas[index]);
    gr_E_ESigma->SetPoint(index, e_means[index], e_sigmas[index]);

    gre_TofE->SetPoint(index, e_means[index], tof_means[index]);
    gre_TofE->SetPointError(index, 0, 5*tof_sigmas[index]);
  }
  ftxt.close();

  TString outfile_TofDiv_energy_pdf(Form("%s_%.0fkeV_%.0fps_TofDiv_energy.pdf",hname,e_step*1000,tof_step*1000));
  printHistos<TH1D*>(energy_hists, outfile_TofDiv_energy_pdf.Data());
  TString outfile_TofDiv_tof_pdf(Form("%s_%.0fkeV_%.0fps_TofDiv_tof.pdf",hname,e_step*1000,tof_step*1000));
  printHistos<TH1D*>(tof_hists, outfile_TofDiv_tof_pdf.Data());

  out_dir = getDirectory(fin, Form("%s_%0.fkeV_%.0fps_TofDiv", hname, e_step*1000,tof_step*1000));
  out_dir->WriteTObject(gr_TofE, "", "WriteDelete");
  out_dir->WriteTObject(gre_TofE, "", "WriteDelete");
  out_dir->WriteTObject(gr_E_TofSigma, "", "WriteDelete");
  out_dir->WriteTObject(gr_E_ESigma, "", "WriteDelete");
  delete gr_TofE;
  delete gr_E_TofSigma;
  delete gr_E_ESigma;

  //
  delete fin;
}
