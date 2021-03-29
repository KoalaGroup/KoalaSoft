#include "CB2Shape.cxx"

using namespace RooFit;

void fill_combined_cb2_workspace(RooWorkspace& ws,
                                 int stripNr = 1,
                                 double range_low = 0.75,
                                 double range_high = 16,
                                 double param_cb_mean = 0.15,
                                 double param_cb_sigma = 0.15,
                                 double param_cb_alpha1 = 1.58,
                                 double param_cb_alpha2 = -2.58,
                                 double param_cb_n1 = 4,
                                 double param_cb_n2 = 9,
                                 double param_expo1 = -2.7,
                                 double param_expo2 = -0.2,
                                 double param_mip_mpv = 2.2,
                                 double param_mip_sigma = 0.3,
                                 double frac_expo1 = 0.9,
                                 double frac_mip = 0.2,
                                 double frac_elastic = 0.4,
                                 double ntotal = 100
                                 )
{
  /*********************************************************************************************************/
  // Define the x-axis: recoil energy in MeV [0, max_energy]
  /*********************************************************************************************************/
  auto strip_sigma = param_cb_sigma/TMath::Sqrt((double)stripNr);

  RooRealVar energy("energy", "Energy (MeV)", range_low, range_high);
  energy.setRange("fitRange", range_low, range_high);

  /*********************************************************************************************************/
  // Double Exponential: as continuous background
  /*********************************************************************************************************/
  RooRealVar et1("expo1", "Background Exponential_1 Parameter", param_expo1, param_expo1*1.1, param_expo1*0.9);
  RooExponential bkg_expo1("bkg_expo1", "Background Component: Exponential 1", energy, et1);

  RooRealVar et2("expo2", "Background Exponential_2 Parameter", param_expo2, param_expo2*1.1, param_expo2*0.9);
  RooExponential bkg_expo2("bkg_expo2", "Background Component: Exponential 2", energy, et2);

  /*********************************************************************************************************/
  // MIP Background: Landau * Gaussian convolution
  /*********************************************************************************************************/
  RooRealVar ml("mpv", "Landau MPV Parameter", param_mip_mpv, param_mip_mpv*0.95, param_mip_mpv*1.05);
  RooRealVar sl("mpv_sigma", "Landau Sigma", param_mip_sigma, param_mip_sigma*0.9, param_mip_sigma*1.1);
  RooLandau  landau("landau", "Landau", energy, ml, sl);

  RooRealVar langau_mg("langau_mg", "Langau's gaussian mean", 0);
  RooRealVar langau_sg("langau_sg", "Langau's gaussian sigma", 0.02, 0.0, 0.05);
  RooGaussian langau_gaus("langau_gaus", "Gaussian for Landau convolution", energy, langau_mg, langau_sg);

  // energy.setBins(100000, "cache");
  energy.setBins(10000, "cache");
  RooFFTConvPdf bkg_mip("bkg_mip", "Background Component: MIP (Landau x Gaussian)", energy, landau, langau_gaus);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  RooRealVar f_expo1("frac_expo1", "Fraction of Exponential_1 in background", frac_expo1, 0.2, 1.);
  RooRealVar f_mip("frac_mip", "Fraction of MIP in background", frac_mip, 0., 0.5);
  RooAddPdf  bkg_model("bkg_model", "Background Model: Exponential_1 + Exponential_2 + Langau", RooArgList(bkg_mip, bkg_expo1, bkg_expo2), RooArgList(f_mip, f_expo1));

  ws.import(bkg_model);

  /*********************************************************************************************************/
  // Elastic model: multiple CB2Shape (double-sided Crystal Ball Function)
  /*********************************************************************************************************/
  RooRealVar cb_sigma("cb_sigma", "CrystallBall sigma", param_cb_sigma, param_cb_sigma-0.01, param_cb_sigma+0.01);
  RooRealVar cb_alpha1("cb_alpha1", "CrystallBall leading turning point", param_cb_alpha1, param_cb_alpha1-0.5, param_cb_alpha1+1);
  RooRealVar cb_n1("cb_n1", "CrystallBall trailing exponent", param_cb_n1, param_cb_n1-1, param_cb_n1+3);
  RooRealVar cb_alpha2("cb_alpha2", "CrystallBall trailing turning point", param_cb_alpha2, param_cb_alpha2-0.5, param_cb_alpha2+1.);
  RooRealVar cb_n2("cb_n2", "CrystallBall tailing exponent", param_cb_n2, param_cb_n2-1, param_cb_n2+2);

  if(stripNr == 1) {
    RooRealVar cb_m0("cb_m0_1", "Peak of CrystalBall 1", param_cb_mean-param_cb_sigma, param_cb_mean+param_cb_sigma);
    CB2Shape elastic_model("elastic_model", "Elastic Model", energy, cb_m0, cb_sigma, cb_alpha1, cb_n1, cb_alpha2, cb_n2);
    ws.import(elastic_model);

    ws.factory(Form( "SUM::model(nbkg[%.1f,0,%f]*bkg_model,nelastic[%.1f,0,%f]*elastic_model)",(1-frac_elastic)*ntotal,ntotal,frac_elastic*ntotal,ntotal ));
  }
  else {
    // compose the CB components
    for(int i=0; i<stripNr; i++){
      RooRealVar cb_m0(Form("cb_m0_%d",i+1), Form("Peak of CrystalBall %d", i+1), param_cb_mean-param_cb_sigma, param_cb_mean+param_cb_sigma);
      CB2Shape cb_model(Form("cb%d",i+1), Form("CrystalBall %d",i+1), energy, cb_m0, cb_sigma, cb_alpha1, cb_n1, cb_alpha2, cb_n2);
      ws.import(cb_model);
    }

    TString elastic_model_str("SUM:elastic_model(");
    double frac_avg = 1./stripNr;
    for(int i=0; i<stripNr-1;i++){
      elastic_model_str.Append(Form("frac_cb%d[%.2f,%.2f,%.2f]*cb%d,",i+1, frac_avg, frac_avg*0.8, frac_avg*1.2, i+1));
    }
    elastic_model_str.Append(Form("cb%d)",stripNr));
    ws.factory(elastic_model_str.Data());

    // compose the final model
    ws.factory(Form( "SUM::model(nbkg[%.1f,0,%f]*bkg_model,nelastic[%.1f,0,%f]*elastic_model)",(1-frac_elastic)*ntotal,2*ntotal,frac_elastic*ntotal,ntotal ));
  }
}
