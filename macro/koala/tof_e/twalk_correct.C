void twalk_correct(double p1 = 4.36466,
                   const char* histname = "h2_Si2_cluster_vs_tof_4",
                   const char* dirname = "cluster_vs_tof",
                   const char* filename = "P_2.2_calib_cluster_purification_multiple_Purification_smear_result.root"
                   )
{
  auto fin = new TFile(filename);
  auto dir = (TDirectory*)fin->Get(dirname);
  auto h2 = (TH2D*)dir->Get(histname);
  h2->SetDirectory(0);

  /* TF1 *f_twalk = new TF1("f_twalk", "[1]/x", 0.1, 10, 2); */
  /* f_walk->SetParameter(0, p0); */
  /* f_walk->SetParameter(1, p1); */

  auto xaxis = h2->GetXaxis();
  auto yaxis = h2->GetYaxis();
  auto xbins = h2->GetNbinsX();
  auto ybins = h2->GetNbinsY();

  auto hist = (TH2D*)h2->Clone(Form("%s_twalk", histname));
  hist->Reset();
  hist->SetDirectory(0);
  for(int x=1; x<=xbins; x++){
    double e = xaxis->GetBinCenter(x);
    double delta_t = p1/e;
    for(int y=1; y<=ybins; y++){
      auto tof = yaxis->GetBinCenter(y);
      auto value = h2->GetBinContent(x,y);
      hist->Fill(e,tof-delta_t,value);
    }
  }

  TCanvas* c = new TCanvas("c", "c", 900, 450);
  c->Divide(2,1);
  c->cd(1);
  h2->Draw("colz");
  c->cd(2);
  hist->Draw("colz");

  auto fout = new TFile(Form("%s_twalk.root", histname), "recreate");
  fout->WriteTObject(hist, "", "WriteDelete");
  fout->WriteTObject(h2, "", "WriteDelete");

  delete fout;
  delete fin;
}
