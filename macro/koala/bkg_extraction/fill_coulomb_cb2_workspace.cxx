#include "CB2Shape.cxx"
#include "TMath.h"

using namespace RooFit;

void fill_coulomb_cb2_workspace(RooWorkspace& ws,
                                double range_low = 0.75,
                                double range_high = 16,
                                double param_cb_sigma = 0.15,
                                double param_cb_alpha1 = 1.58,
                                double param_cb_alpha2 = -2.58,
                                double param_cb_n1 = 4,
                                double param_cb_n2 = 9,
                                double frac_elastic = 0.9,
                                int ntotal = 100
                                )
{
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
  RooRealVar cb_sigma("cb_sigma", "CrystallBall sigma", param_cb_sigma, 0.01, 1.0);
  RooRealVar cb_alpha1("cb_alpha1", "CrystallBall leading turning point", param_cb_alpha1, 0, 2);
  RooRealVar cb_n1("cb_n1", "CrystallBall trailing exponent", param_cb_n1, 1, 6);
  RooRealVar cb_alpha2("cb_alpha2", "CrystallBall trailing turning point", param_cb_alpha2, 1, 3);
  RooRealVar cb_n2("cb_n2", "CrystallBall tailing exponent", param_cb_n2, 3, 10);
  RooRealVar cb_m0("cb_m0", "Peak of CrystalBall", range_low, range_high);

  CB2Shape elastic_model("elastic_model", "Elastic Model", energy, cb_m0, cb_sigma, cb_alpha1, cb_n1, cb_alpha2, cb_n2);
  ws.import(elastic_model);

  //
  ws.factory(Form( "SUM::model(nbkg[%.1f,0,%d]*bkg_model,nelastic[%.1f,0,%d]*elastic_model)",(1-frac_elastic)*ntotal,ntotal,frac_elastic*ntotal,ntotal ));
}
