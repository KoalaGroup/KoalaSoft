void fit_target_profile(const char* filename,
                        double zoffset_si1 = 0,
                        double zoffset_si2 = 0
                        )
{
  auto fin = TFile::Open(filename);
  auto dir = (TDirectory*)fin->Get(Form("profile_si1_%.2f_si2_%.2f", zoffset_si1, zoffset_si2));
  auto gr = (TGraph*)dir->Get("gr_strip_si1");

  auto npts = gr->GetN();
  auto x = gr->GetX();
  auto y = gr->GetY();

  double x_low, x_high;
  auto find_range = [&](){
    double thresh = 1000;
    x_low = -100; x_high = 100;
    for(int i = 0; i < npts; i++){
      if(y[i] > 1000 && x_low == -100) x_low = x[i];
      if(y[i] < 1000 && x_low != -100) x_high = x[i];
    }
    std::cout << "Fit range: " << x_low << ", " << x_high <<std::endl;
  };

  TF1* ffit = new TF1("bigaus", "[0]*([1]*TMath::Gaus(x, [2],[3])+(1.-[1])*TMath::Gaus(x,[2], [4]))", x_low-10, x_high+10);
  ffit->SetParName(0, "A");
  ffit->SetParameter(0, 800e3);
  ffit->SetParLimits(0, 1e5, 1e6);
  ffit->SetParName(1, "frac1");
  ffit->SetParameter(1, 0.6);
  ffit->SetParLimits(1, 0.4, 1.);
  ffit->SetParName(2, "z0");
  ffit->SetParameter(2, 1.5);
  ffit->SetParLimits(2, -3, 2.1);
  ffit->SetParName(3, "#sigma_{1}");
  ffit->SetParameter(3, 2);
  ffit->SetParLimits(3, 0.5, 3);
  ffit->SetParName(4, "#sigma_{2}");
  ffit->SetParameter(4, 4);
  ffit->SetParLimits(4, 0, 8);
  /* ffit->SetParName(5, "pol1 p0"); */
  /* ffit->SetParameter(5, 4000); */
  /* ffit->SetParLimits(5, 0, 4500); */
  /* ffit->SetParName(6, "pol1 p1"); */
  /* ffit->SetParameter(6, 0.); */
  /* ffit->SetParLimits(6, -0.1, 0.1); */

  gr->Fit(ffit,"","",x_low,x_high);

  /* TF1* ffit = new TF1("biexp", "[0]*TMath::LaplaceDist(x,[1],[2])+[3]",-40,60); */
  /* ffit->SetParameter(0, 800e3); */
  /* ffit->SetParLimits(0, 200e3, 1e7); */
  /* ffit->SetParameter(1, 1.5); */
  /* ffit->SetParLimits(1, 1., 2.1); */
  /* ffit->SetParameter(2, 2); */
  /* ffit->SetParLimits(2, 0.1, 8); */
  /* ffit->SetParameter(3, 2000); */
  /* ffit->SetParLimits(3, 1000, 4000); */

  /* gr->Fit(ffit,"","",fit_low,fit_high); */

  /* TF1* ffit = new TF1("breit_wigner", "[0]*TMath::BreitWigner(x,[1],[2])+[3]",-40,60); */
  /* ffit->SetParameter(0, 800e3); */
  /* ffit->SetParLimits(0, 200e3, 1e7); */
  /* ffit->SetParameter(1, 0); */
  /* ffit->SetParLimits(1, 0., 2.1); */
  /* ffit->SetParameter(2, 2); */
  /* ffit->SetParLimits(2, 0.1, 8); */
  /* ffit->SetParameter(3, 2000); */
  /* ffit->SetParLimits(3, 1000, 4000); */

  /* gr->Fit(ffit,"","",fit_low,fit_high); */

  /* auto gr_residual = new TGraph(); */
  /* gr_residual->SetMarkerStyle(20); */
  /* gr_residual->SetMarkerSize(0.6); */

  /* auto gr_pull = new TGraph(); */
  /* gr_pull->SetMarkerStyle(20); */
  /* gr_pull->SetMarkerSize(0.6); */

  /* auto npt = gr->GetN(); */
  /* auto x = gr->GetX(); */
  /* auto y = gr->GetY(); */
  /* for(int i =0;i<npt;i++){ */
  /*   gr_residual->SetPoint(i, x[i], y[i]-ffit->Eval(x[i])); */
  /*   gr_pull->SetPoint(i, x[i], (y[i]-ffit->Eval(x[i]))/TMath::Sqrt(y[i])); */
  /* } */

  //
  TCanvas *c = new TCanvas("c", "c", 500, 500);
  /* c->Divide(2,1); */
  /* c->cd(1); */
  gr->Draw("AP");

  /* c->cd(2); */
  /* /\* gr_residual->Draw("AP"); *\/ */
  /* gr_pull->Draw("AP"); */

  //
  double max = ffit->GetMaximum();
  double max_x = ffit->GetParameter(2);
  double fwhm= ffit->GetX(max/2, max_x, max_x+10) - ffit->GetX(max/2., max_x-10,max_x);
  double percent_width = ffit->GetX(max*0.1, max_x, max_x+20) - ffit->GetX(max*0.1, max_x-20 ,max_x);
  std::cout << "MAX: " << ffit->GetMaximum() << "\t FWHM: "  << fwhm << "\t 10% width: " << percent_width << std::endl;
}
