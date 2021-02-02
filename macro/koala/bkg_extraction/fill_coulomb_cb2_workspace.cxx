#include "CB2Shape.cxx"
#include "TMath.h"

using namespace RooFit;

void fill_coulomb_cb2_workspace(RooWorkspace& ws,
                                double range_low = 0.75,
                                double range_high = 16,
                                double param_cb_m0 = 0.8,
                                double param_cb_sigma = 0.15,
                                double param_cb_alpha1 = 1.58,
                                double param_cb_alpha2 = -2.58,
                                double param_cb_n1 = 4,
                                double param_cb_n2 = 9,
                                double nelastic = 100,
                                double nbkg = 100
                                )
{
  if(nbkg<0) nbkg = 0.1*nelastic;

  double fit_low = range_low;
  double fit_high = param_cb_m0 + 11*param_cb_sigma;
  if(fit_high < 1.6) fit_high = 1.6;

  /*********************************************************************************************************/
  // Define the x-axis: recoil energy in MeV [0, max_energy]
  /*********************************************************************************************************/
  RooRealVar energy("energy", "Energy (MeV)", range_low, range_high);
  energy.setRange("fitRange", range_low, range_high);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  double truth_seed = 6.2e-6;
  RooRealVar frac_coul("frac_coul", "frac_coul", truth_seed);
  RooGenericPdf* bkg_model = new RooGenericPdf("bkg_model", "Bkg Model", "@1/TMath::Power(0.002*0.938*@0,2)/TMath::Power(1+TMath::Abs(0.002*0.938*@0)/0.71,8)", RooArgList(energy, frac_coul));

  ws.import(*bkg_model);

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
  ws.factory(Form( "SUM::model(nbkg[%.1f,0,%f]*bkg_model,nelastic[%.1f,0,%f]*elastic_model)", 0.3*nbkg, 10*nbkg, nelastic, 2*nelastic));
}
