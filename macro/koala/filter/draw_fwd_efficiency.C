void draw_fwd_efficiency(const char* filename)
{
  auto fin = TFile::Open(filename, "update");
  TDirectory* hdir = (TDirectory*)fin->Get("fwd_evtnr_elastic");

  TH1D* h1_si1_fwd1_passed = (TH1D*)hdir->Get("h1_Si1_fwd1_passed");
  TH1D* h1_si1_fwd1_total = (TH1D*)hdir->Get("h1_Si1_fwd1_total");
  TH1D* h1_si2_fwd1_passed = (TH1D*)hdir->Get("h1_Si2_fwd1_passed");
  TH1D* h1_si2_fwd1_total = (TH1D*)hdir->Get("h1_Si2_fwd1_total");

  TH1D* h1_si1_fwd2_passed = (TH1D*)hdir->Get("h1_Si1_fwd2_passed");
  TH1D* h1_si1_fwd2_total = (TH1D*)hdir->Get("h1_Si1_fwd2_total");
  TH1D* h1_si2_fwd2_passed = (TH1D*)hdir->Get("h1_Si2_fwd2_passed");
  TH1D* h1_si2_fwd2_total = (TH1D*)hdir->Get("h1_Si2_fwd2_total");


  //
  TEfficiency* eff1_si1 = new TEfficiency(*h1_si1_fwd1_passed, *h1_si1_fwd1_total);
  TEfficiency* eff1_si2 = new TEfficiency(*h1_si2_fwd1_passed, *h1_si2_fwd1_total);
  TEfficiency* eff2_si1 = new TEfficiency(*h1_si1_fwd2_passed, *h1_si1_fwd2_total);
  TEfficiency* eff2_si2 = new TEfficiency(*h1_si2_fwd2_passed, *h1_si2_fwd2_total);

  eff1_si1->SetName("efficiency_Si1_fwd1");
  eff1_si1->SetStatisticOption(TEfficiency::kFAC);
  eff1_si1->SetConfidenceLevel(0.95);
  eff1_si1->SetFillColor(kBlue);
  eff1_si1->SetFillStyle(3005);
  eff1_si1->SetMarkerColor(kBlue);
  eff1_si1->SetMarkerStyle(20);
  eff1_si1->SetMarkerSize(0.3);

  eff1_si2->SetName("efficiency_Si2_fwd1");
  eff1_si2->SetStatisticOption(TEfficiency::kFAC);
  eff1_si2->SetConfidenceLevel(0.95);
  eff1_si2->SetFillColor(kBlue);
  eff1_si2->SetFillStyle(3005);
  eff1_si2->SetMarkerColor(kBlue);
  eff1_si2->SetMarkerSize(0.3);
  eff1_si2->SetMarkerStyle(20);


  eff2_si1->SetName("efficiency_Si1_fwd2");
  eff2_si1->SetStatisticOption(TEfficiency::kFAC);
  eff2_si1->SetConfidenceLevel(0.95);
  eff2_si1->SetFillColor(kRed);
  eff2_si1->SetFillStyle(3002);
  eff2_si1->SetMarkerColor(kRed);
  eff2_si1->SetMarkerStyle(2);
  eff2_si1->SetMarkerSize(0.6);

  eff2_si2->SetName("efficiency_Si2_fwd2");
  eff2_si2->SetStatisticOption(TEfficiency::kFAC);
  eff2_si2->SetConfidenceLevel(0.95);
  eff2_si2->SetFillColor(kRed);
  eff2_si2->SetFillStyle(3002);
  eff2_si2->SetMarkerColor(kRed);
  eff2_si2->SetMarkerStyle(2);
  eff2_si2->SetMarkerSize(0.6);

  TLegend* leg1 = new TLegend(0.3,0.1,0.7,0.5);
  leg1->AddEntry(eff1_si1,"Fwd1","F");
  leg1->AddEntry(eff2_si1,"Fwd2","F");

  TLegend* leg2 = new TLegend(0.3,0.1,0.7,0.5);
  leg2->AddEntry(eff1_si2,"Fwd1","F");
  leg2->AddEntry(eff2_si2,"Fwd2","F");

  TCanvas* c1 = new TCanvas("c_efficiency","Efficiency VS Channel No (Si1 and Si2)", 1000,600);
  c1->Divide(2,1);
  c1->cd(1); eff1_si1->Draw("a4"); eff2_si1->Draw("same4"); leg1->Draw("same");
  c1->cd(2); eff1_si2->Draw("a4"); eff2_si2->Draw("same4"); leg2->Draw("same");

  TString pdf_outfilename(filename);
  pdf_outfilename.ReplaceAll(".root","_efficiency.pdf");
  c1->Print(pdf_outfilename);

  hdir->WriteTObject(c1, "", "WriteDelete");
  hdir->WriteTObject(eff1_si1, "", "WriteDelete");
  hdir->WriteTObject(eff1_si2, "", "WriteDelete");
  hdir->WriteTObject(eff2_si1, "", "WriteDelete");
  hdir->WriteTObject(eff2_si2, "", "WriteDelete");

  //
  delete c1;
  delete fin;
}
