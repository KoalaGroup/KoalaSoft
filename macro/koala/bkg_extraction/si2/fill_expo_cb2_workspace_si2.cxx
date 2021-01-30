#include "CB2Shape.cxx"
#include "TMath.h"

using namespace RooFit;

void fill_expo_cb2_workspace(RooWorkspace& ws,
                             double param_cb_m0 = 0.8,
                             double param_cb_sigma = 0.15,
                             double param_cb_alpha1 = 1.58,
                             double param_cb_alpha2 = -2.58,
                             double param_cb_n1 = 4,
                             double param_cb_n2 = 9,
                             double param_expo = -0.01,
                             double range_limit = 40,
                             double ntotal = 100
                             )
{
  /*********************************************************************************************************/
  // Define the x-axis: recoil energy in MeV [0, max_energy]
  /*********************************************************************************************************/
  double range_low = param_cb_m0 - param_cb_sigma*15;
  double range_high = param_cb_m0 + param_cb_sigma*15;
  if(range_high > range_limit) range_high = range_limit;

  double draw_low = range_low - param_cb_sigma*8;
  double draw_high = range_high + param_cb_sigma*4;

  RooRealVar energy("energy", "Energy (MeV)", draw_low, draw_high);
  energy.setRange("fitRange", range_low, range_high);
  energy.setRange("drawRange", draw_low, draw_high);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  RooRealVar expo_lambda("expo_lambda", "expo_lambda",param_expo, param_expo*1.1, param_expo*0.9);
  RooExponential bkg_model("bkg_model", "Exponential Background", energy, expo_lambda);
  ws.import(bkg_model);

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
  ws.factory(Form( "SUM::model(nelastic[%.1f,%f,%f]*elastic_model,nbkg[%f,0,%f]*bkg_model)",ntotal,0.2*ntotal,2*ntotal, 0.01*ntotal, 0.1*ntotal));
}
