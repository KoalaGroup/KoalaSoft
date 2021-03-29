/* Min Fwd Width VS Beam Momentum
   x[0] : beam momentum in GeV/c
   p[0] : |t| max in GeV/c
   p[1] : beam size width in mm
   p[2] : recoil distance in cm
   p[3] : fwd distance in cm
   p[4] : recoil sensor spread in Y-axis in cm

   return in cm
 */
double width_vs_mom_imp(double *x, double *p){
  KoaElasticCalculator calculator(x[0], p[2], p[3]);
  double alpha = calculator.GetAlphaByEnergy(p[0]/2./0.938272081*1000); // degree
  double theta = calculator.GetThetaByAlpha(alpha)/180.*3.14151926; // radian

  return p[4]*p[3]*theta/p[2]+p[1]/10.;
}

/* Fwd Length VS Beam Momentum
   x[0] : beam momentum in GeV/c
   p[0] : |t| in GeV/c
   p[1] : fwd distance in cm

   return in cm
*/
double length_vs_mom_imp(double *x, double *p)
{
  KoaElasticCalculator calculator(x[0], 90.4, p[1]);
  double length = calculator.GetFwdXByEnergy(p[0]/2./0.938272081*1000); // cm

  return length;
}

/* Get a graph representing the area between two TF1
 */
TGraph* get_shade_area(TF1* f1, TF1* f2)
{
  auto npx = f1->GetNpx();
  auto xmin = f1->GetXmin();
  auto xmax= f1->GetXmax();
  auto xstep = (xmax-xmin)/npx;

  TGraph* gr =new TGraph();
  gr->SetName(Form("gr_%s_%s",f1->GetName(),f2->GetName()));
  gr->SetFillColor(f2->GetFillColor());
  gr->SetFillStyle(f2->GetFillStyle());
  for(int i=0;i<npx;i++){
    auto x1 = xmin + i*xstep;
    auto y1 = f1->Eval(x1);
    gr->SetPoint(i,x1,y1);

    auto x2 = xmin + (npx-1-i)*xstep;
    auto y2 = f2->Eval(x2);
    gr->SetPoint(npx+i,x2,y2);
  }

  return gr;
}

/* e_low : t min 
   e_high: t max

   Plot fwd width and length requirement VS beam momentum
 */
void plotFwdRequirement(double e_low, double e_high, const char* geoFile)
{
  TFile* fgeo=new TFile(geoFile);
  TGeoManager* geoMan=(TGeoManager*)fgeo->Get("FAIRGeom");
  KoaGeoHandler* geoHandler = new KoaGeoHandler(kFALSE);

  Double_t fwd_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSc1"));
  Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));
  auto pts_si1 = geoHandler->GetDetBoundaryPointsById(0); 
  auto pts_si2 = geoHandler->GetDetBoundaryPointsById(1); 
  double rec_spread = TMath::Abs(pts_si1[2].Y()-pts_si2[1].Y());

  //
  TFile *fout = new TFile(Form("fwd_requirement_%.4f_to_%.3f.root",e_low,e_high),"recreate");

  // Width VS Momentum
  // beam size = 0
  TF1* f_width_vs_mom = new TF1("f_width_vs_mom", width_vs_mom_imp, 1.2, 3.7, 5);
  f_width_vs_mom->SetParName(0, "t (GeV/c2)^2");
  f_width_vs_mom->SetParameter(0, e_high);
  f_width_vs_mom->SetParName(1, "beam profile (mm)");
  f_width_vs_mom->SetParameter(1, 0);
  f_width_vs_mom->SetParName(2, "recoil distance (cm)");
  f_width_vs_mom->SetParameter(2, rec_distance);
  f_width_vs_mom->SetParName(3, "fwd distance (cm)");
  f_width_vs_mom->SetParameter(3, fwd_distance);
  f_width_vs_mom->SetParName(4, "recoil sensor spread (cm)");
  f_width_vs_mom->SetParameter(4, rec_spread);
  f_width_vs_mom->SetNpx(1000);
  f_width_vs_mom->SetLineColor(46);
  fout->WriteTObject(f_width_vs_mom, "", "WriteDelete");

  // beam size = 7 mm
  TF1* f_width_vs_mom_7mm = new TF1("f_width_vs_mom_7mm", width_vs_mom_imp, 1.2, 3.7, 5);
  f_width_vs_mom_7mm->SetParName(0, "t (GeV/c2)^2");
  f_width_vs_mom_7mm->SetParameter(0, e_high);
  f_width_vs_mom_7mm->SetParName(1, "beam profile (mm)");
  f_width_vs_mom_7mm->SetParameter(1, 7);
  f_width_vs_mom_7mm->SetParName(2, "recoil distance (cm)");
  f_width_vs_mom_7mm->SetParameter(2, rec_distance);
  f_width_vs_mom_7mm->SetParName(3, "fwd distance (cm)");
  f_width_vs_mom_7mm->SetParameter(3, fwd_distance);
  f_width_vs_mom_7mm->SetParName(4, "recoil sensor spread (cm)");
  f_width_vs_mom_7mm->SetParameter(4, rec_spread);
  f_width_vs_mom_7mm->SetNpx(1000);
  f_width_vs_mom_7mm->SetLineColor(46);
  f_width_vs_mom_7mm->SetFillColor(46);
  f_width_vs_mom_7mm->SetFillStyle(3001);
  fout->WriteTObject(f_width_vs_mom_7mm, "", "WriteDelete");

  // beam size = 10 mm
  TF1* f_width_vs_mom_10mm = new TF1("f_width_vs_mom_10mm", width_vs_mom_imp, 1.2, 3.7, 5);
  f_width_vs_mom_10mm->SetParName(0, "t (GeV/c2)^2");
  f_width_vs_mom_10mm->SetParameter(0, e_high);
  f_width_vs_mom_10mm->SetParName(1, "beam profile (mm)");
  f_width_vs_mom_10mm->SetParameter(1, 10);
  f_width_vs_mom_10mm->SetParName(2, "recoil distance (cm)");
  f_width_vs_mom_10mm->SetParameter(2, rec_distance);
  f_width_vs_mom_10mm->SetParName(3, "fwd distance (cm)");
  f_width_vs_mom_10mm->SetParameter(3, fwd_distance);
  f_width_vs_mom_10mm->SetParName(4, "recoil sensor spread (cm)");
  f_width_vs_mom_10mm->SetParameter(4, rec_spread);
  f_width_vs_mom_10mm->SetNpx(1000);
  f_width_vs_mom_10mm->SetLineColor(46);
  f_width_vs_mom_10mm->SetFillColor(46);
  f_width_vs_mom_10mm->SetFillStyle(3011);
  fout->WriteTObject(f_width_vs_mom_10mm, "", "WriteDelete");

  fout->WriteTObject(get_shade_area(f_width_vs_mom,f_width_vs_mom_7mm), "", "WriteDelete");
  fout->WriteTObject(get_shade_area(f_width_vs_mom,f_width_vs_mom_10mm), "", "WriteDelete");
  fout->WriteTObject(get_shade_area(f_width_vs_mom_7mm,f_width_vs_mom_10mm), "", "WriteDelete");
  
  // Length VS Momentum
  TF1* f_length_vs_mom_low = new TF1("f_length_vs_mom_low", length_vs_mom_imp, 1.2, 3.7, 2);
  f_length_vs_mom_low->SetParName(0, "t (GeV/c2)^2");
  f_length_vs_mom_low->SetParameter(0, e_low);
  f_length_vs_mom_low->SetParName(1, "fwd distance (cm)");
  f_length_vs_mom_low->SetParameter(1, fwd_distance);
  f_length_vs_mom_low->SetNpx(1000);
  f_length_vs_mom_low->SetLineColor(46);
  fout->WriteTObject(f_length_vs_mom_low, "", "WriteDelete");

  TF1* f_length_vs_mom_high = new TF1("f_length_vs_mom_high", length_vs_mom_imp, 1.2, 3.7, 2);
  f_length_vs_mom_high->SetParName(0, "t (GeV/c2)^2");
  f_length_vs_mom_high->SetParameter(0, e_high);
  f_length_vs_mom_high->SetParName(1, "fwd distance (cm)");
  f_length_vs_mom_high->SetParameter(1, fwd_distance);
  f_length_vs_mom_high->SetNpx(1000);
  f_length_vs_mom_high->SetFillColor(46);
  f_length_vs_mom_high->SetFillStyle(3001);
  fout->WriteTObject(f_length_vs_mom_high, "", "WriteDelete");

  fout->WriteTObject(get_shade_area(f_length_vs_mom_low,f_length_vs_mom_high), "", "WriteDelete");
  //
  std::cout << "fwd distance: " << fwd_distance << " cm\n";
  std::cout << "recoil distance: " << rec_distance << " cm\n";
  std::cout << "recoil spread: " << rec_spread << " cm\n";

  //
  delete fout;
  delete fgeo;
  delete geoHandler;
}
