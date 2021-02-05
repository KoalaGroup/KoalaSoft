#include "CB2Shape.cxx"
#include "TMath.h"

using namespace RooFit;

void fill_coulomb_histpdf_cb2_workspace(RooWorkspace& ws,
                                        TH1D*  hbkg,
                                        double range_low = 0.75,
                                        double range_high = 16,
                                        double param_cb_m0 = 0.8,
                                        double param_cb_sigma = 0.15,
                                        double param_cb_alpha1 = 1.58,
                                        double param_cb_alpha2 = -2.58,
                                        double param_cb_n1 = 4,
                                        double param_cb_n2 = 9,
                                        double nelastic = 10000,
                                        double ncoulomb = 1000
                                        )
{
  double rg_low = param_cb_m0 - param_cb_sigma*11;
  double rg_high = param_cb_m0 + param_cb_sigma*10;
  if(param_cb_m0 < 1.6) {
    // rg_low = rg_low - param_cb_sigma;
    rg_high = range_high;
    rg_low = range_low;
  }

  TH1D* hclone = (TH1D*)hbkg->Clone("hclone");
  if(param_cb_m0 < 1.) hclone->Rebin(5);
  else hclone->Rebin(10);

  auto bin_low = hclone->GetXaxis()->FindBin(rg_low);
  auto bin_high = hclone->GetXaxis()->FindBin(rg_high);
  double nbkg = hclone->Integral(bin_low, bin_high);

  /*********************************************************************************************************/
  // Define the x-axis: recoil energy in MeV [0, max_energy]
  /*********************************************************************************************************/
  RooRealVar energy("energy", "Energy (MeV)", rg_low, rg_high);
  energy.setRange("fitRange", rg_low, rg_high);
  energy.setRange("drawRange", rg_low-param_cb_sigma, rg_high+2*param_cb_sigma);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  RooDataHist dh_bkg("dh_bkg", "Background Histogram", energy, Import(*hclone));
  RooHistPdf bkg_model("bkg_model", "Bkg Model based on histogram background template", energy, energy, dh_bkg);
  ws.import(bkg_model);
  delete hclone;

  /*********************************************************************************************************/
  // Coulomb Background
  /*********************************************************************************************************/
  double truth_seed = 6.2e-6;
  RooRealVar frac_coul("frac_coul", "frac_coul", truth_seed);
  RooGenericPdf* coulomb_model = new RooGenericPdf("coulomb_model", "Coulomb Model", "@1/TMath::Power(0.002*0.938*@0,2)/TMath::Power(1+TMath::Abs(0.002*0.938*@0)/0.71,8)", RooArgList(energy, frac_coul));
  ws.import(*coulomb_model);

  /*********************************************************************************************************/
  // Elastic model: multiple CB2Shape (double-sided Crystal Ball Function)
  /*********************************************************************************************************/
  RooRealVar cb_m0("cb_m0", "Peak of CrystalBall", param_cb_m0 , 0.9*param_cb_m0, 1.1*param_cb_m0);
  RooRealVar cb_sigma("cb_sigma", "CrystallBall sigma", param_cb_sigma, param_cb_sigma-0.01, param_cb_sigma+0.01);
  RooRealVar cb_alpha1("cb_alpha1", "CrystallBall leading turning point", param_cb_alpha1, param_cb_alpha1-0.5, param_cb_alpha1+1);
  RooRealVar cb_n1("cb_n1", "CrystallBall trailing exponent", param_cb_n1, param_cb_n1-1, param_cb_n1+3);
  RooRealVar cb_alpha2("cb_alpha2", "CrystallBall trailing turning point", param_cb_alpha2, param_cb_alpha2-0.5, param_cb_alpha2+1.);
  RooRealVar cb_n2("cb_n2", "CrystallBall tailing exponent", param_cb_n2, param_cb_n2-1, param_cb_n2+2);

  CB2Shape elastic_model("elastic_model", "Elastic Model", energy, cb_m0, cb_sigma, cb_alpha1, cb_n1, cb_alpha2, cb_n2);
  ws.import(elastic_model);

  //
  ws.factory(Form( "SUM::model(ncoul[%f,%f, %f]*coulomb_model,nbkg[%.1f,%f,%f]*bkg_model,nelastic[%.1f,%f,%f]*elastic_model)",
                   ncoulomb, 0.9*ncoulomb, 10*ncoulomb,
                   nbkg,0.1*nbkg, 1.4*nbkg,nelastic ,0.5*nelastic,5*nelastic));
}
