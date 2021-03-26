double tof_energy_imp(double* x, double *p){
  KoaElasticCalculator calculator(p[0], p[1], p[2]);

  double alpha = calculator.GetAlphaByEnergy(x[0]);
  double tof_rec = calculator.GetRecTOFByAlpha(alpha);
  double tof_fwd = calculator.GetFwdTOFByAlpha(alpha);
  return tof_rec-tof_fwd+p[3];
}

double energy_tof_corrected_imp(double*x, double *p){
  KoaElasticCalculator calculator(p[0], p[1], p[2]);
  TF1* fTofE = new TF1("fTofE",tof_energy_imp, 0, 5);
  fTofE->SetParameter(0, p[0]);
  fTofE->SetParameter(1, p[1]);
  fTofE->SetParameter(2, p[2]);
  fTofE->SetParameter(3, p[3]);
  fTofE->SetNpx(1400);

  auto e = fTofE->GetX(x[0]);
  auto beta_2_inv = (938+e)*(938+e)/((938+e)*(938+e)-938*938);
  return p[4]+p[5]*beta_2_inv+e;
}

void fit_ETof(const char* filename,
              const char* dirname = "TofE",
              const char* graphname = "gr_TofE",
              double mom = 2.2,
              double tof_offset = 473.5,
              double e_low = 0.1,
              double e_high = 4)
{
  auto fin = TFile::Open(filename, "update");
  auto dir = (TDirectory*)fin->Get(dirname);

  TGraph* gr = nullptr;
  if(!dir){
    dir = fin;
    gr = new TGraph();
    gr->SetName(Form("gr_%s", graphname));
    gr->SetMarkerStyle(20);
    gr->SetMarkerSize(0.4);
    gr->SetMarkerColor(kBlack);

    auto h2 = (TH2D*)fin->Get(graphname);
    auto pf = h2->ProfileY();
    int npx = pf->GetNbinsX();
    int gindex = 0;
    for(int i=1;i<=npx;i++){
      auto evtnr = pf->GetBinEntries(i);
      auto tof = pf->GetBinCenter(i);
      auto e = pf->GetBinContent(i);

      if(evtnr > 20){
        gr->SetPoint(gindex, tof, e);
        gindex++;
      }
    }
    dir->WriteTObject(gr,"", "WriteDelete");
  }
  else{
    gr = (TGraph*)dir->Get(graphname);
  }

  TGraph* gr_ETof = new TGraph();
  gr_ETof->SetName(Form("gr_ETof_%s", graphname));
  gr_ETof->SetMarkerStyle(20);
  gr_ETof->SetMarkerSize(0.4);
  gr_ETof->SetMarkerColor(kBlack);
  auto npt = gr->GetN();
  auto x = gr->GetX();
  auto y = gr->GetY();
  for(int i=0;i<npt;i++){
    gr_ETof->SetPoint(i, y[i], x[i]);
  }


  //
  TF1 *f_tof_energy = new TF1("f_tof_energy", tof_energy_imp, e_low, e_high, 4);
  f_tof_energy->SetParName(0, "Beam Momentum (GeV)");
  f_tof_energy->SetParameter(0, mom);
  f_tof_energy->SetParLimits(0, mom, mom);
  f_tof_energy->SetParName(1, "Recoil Distance (cm)");
  f_tof_energy->SetParameter(1, 90.4);
  f_tof_energy->SetParLimits(1, 85, 95);
  f_tof_energy->SetParName(2, "Fwd Distance (cm)");
  f_tof_energy->SetParameter(2, 460);
  f_tof_energy->SetParLimits(2, 440, 480);
  f_tof_energy->SetParName(3, "TOF offset (ns)");
  f_tof_energy->SetParameter(3, tof_offset);
  f_tof_energy->SetParLimits(3, 460, 500);
  f_tof_energy->SetNpx(1400);
  dir->WriteTObject(f_tof_energy,"", "WriteDelete");

  //
  // TF1* f_energy_tof_corrected = new TF1("f_energy_tof_corrected", energy_tof_corrected_imp,450, 750,6);
  TF1* f_energy_tof_corrected = new TF1("f_energy_tof_corrected",
                                        "[&](double* x, double* p){return p[0]+p[1]*(TMath::Power(938+f_tof_energy->GetX(x[0]),2))/(TMath::Power(938+f_tof_energy->GetX(x[0]),2)-938*938);}",450, 750, 2);
  f_energy_tof_corrected->SetParName(0, "p0 for correction");
  f_energy_tof_corrected->SetParameter(0, 0.002);
  f_energy_tof_corrected->SetParName(1, "p1 for correction");
  f_energy_tof_corrected->SetParameter(1, -1.8e-5);
  // f_energy_tof_corrected->SetParName(0, "Beam Momentum (GeV)");
  // f_energy_tof_corrected->SetParameter(0, mom);
  // f_energy_tof_corrected->SetParLimits(0, mom, mom);
  // f_energy_tof_corrected->SetParName(1, "Recoil Distance (cm)");
  // f_energy_tof_corrected->SetParameter(1, 90.4);
  // f_energy_tof_corrected->SetParLimits(1, 85, 95);
  // f_energy_tof_corrected->SetParName(2, "Fwd Distance (cm)");
  // f_energy_tof_corrected->SetParameter(2, 460);
  // f_energy_tof_corrected->SetParLimits(2, 440, 480);
  // f_energy_tof_corrected->SetParName(3, "TOF offset (ns)");
  // f_energy_tof_corrected->SetParameter(3, tof_offset);
  // f_energy_tof_corrected->SetParLimits(3, 460, 500);
  // f_energy_tof_corrected->SetParName(4, "p0 for correction");
  // f_energy_tof_corrected->SetParameter(4, 0.002);
  // f_energy_tof_corrected->SetParName(5, "p1 for correction");
  // f_energy_tof_corrected->SetParameter(5, -1.8e-5);
  f_energy_tof_corrected->SetNpx(1400);

  //
  TGraph* gr_ediff = new TGraph();
  gr_ediff->SetName(Form("gr_ediff_%s", graphname));
  gr_ediff->SetMarkerStyle(20);
  gr_ediff->SetMarkerSize(0.4);
  gr_ediff->SetMarkerColor(kBlack);
  npt = gr->GetN();
  x = gr->GetX();
  y = gr->GetY();
  for(int i=0;i<npt;i++){
    auto e_theory = f_tof_energy->GetX(y[i]);
    gr_ediff->SetPoint(i, e_theory, e_theory-x[i]);
  }
  dir->WriteTObject(gr_ediff,"", "WriteDelete");

  //
  TCanvas c;
  TString pdffilename(filename);
  pdffilename.ReplaceAll(".root","_fit.pdf");
  c.Print(Form("%s[", pdffilename.Data()));

  gr->Draw("AP");
  f_tof_energy->Draw("same");
  c.Print(Form("%s", pdffilename.Data()));

  // gr->Fit(f_tof_energy,"", "", 0.3,4);
  gr->Draw("AP");
  f_tof_energy->Draw("same");
  c.Print(Form("%s", pdffilename.Data()));

  gr_ETof->Fit(f_energy_tof_corrected,"", "", 450,750);
  gr_ETof->Draw("AP");
  f_energy_tof_corrected->Draw("same");
  c.Print(Form("%s", pdffilename.Data()));

  c.Print(Form("%s]", pdffilename.Data()));


  delete fin;
}
