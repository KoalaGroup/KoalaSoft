double tof_energy_imp(double* x, double *p){
  KoaElasticCalculator calculator(p[0], p[1], p[2]);

  double alpha = calculator.GetAlphaByEnergy(x[0]);
  double tof_rec = calculator.GetRecTOFByAlpha(alpha);
  double tof_fwd = calculator.GetFwdTOFByAlpha(alpha);
  return tof_rec-tof_fwd+p[3];
}

void fit_TofE(const char* filename,
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
    auto pf = h2->ProfileX();
    int npx = pf->GetNbinsX();
    int gindex = 0;
    for(int i=1;i<=npx;i++){
      auto evtnr = pf->GetBinEntries(i);
      auto e = pf->GetBinCenter(i);
      auto tof = pf->GetBinContent(i);

      if(evtnr > 20){
        gr->SetPoint(gindex, e, tof);
        gindex++;
      }
    }
    dir->WriteTObject(gr,"", "WriteDelete");
  }
  else{
    gr = (TGraph*)dir->Get(graphname);
  }

  //
  TF1 *f_tof_energy = new TF1("ffit_tof_energy", tof_energy_imp, e_low, e_high, 4);
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
  TGraph* gr_ediff = new TGraph();
  gr_ediff->SetName(Form("gr_ediff_%s", graphname));
  gr_ediff->SetMarkerStyle(20);
  gr_ediff->SetMarkerSize(0.4);
  gr_ediff->SetMarkerColor(kBlack);
  auto npt = gr->GetN();
  auto x = gr->GetX();
  auto y = gr->GetY();
  for(int i=0;i<npt;i++){
    auto e_theory = f_tof_energy->GetX(y);
    gr_ediff->SetPoint(i, e_theory, e_theory-x);
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

  gr->Fit(f_tof_energy,"", "", 0.3,4);
  gr->Draw("AP");
  f_tof_energy->Draw("same");
  c.Print(Form("%s", pdffilename.Data()));

  c.Print(Form("%s]", pdffilename.Data()));


  delete fin;
}
