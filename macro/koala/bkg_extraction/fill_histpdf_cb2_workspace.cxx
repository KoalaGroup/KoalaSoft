#include "CB2Shape.cxx"
#include "TMath.h"

using namespace RooFit;

void fill_histpdf_cb2_workspace(RooWorkspace& ws,
                                TH1D*  hbkg,
                                double range_low = 0.75,
                                double range_high = 16,
                                double param_cb_m0 = 0.8,
                                double param_cb_sigma = 0.15,
                                double param_cb_alpha1 = 1.58,
                                double param_cb_alpha2 = -2.58,
                                double param_cb_n1 = 4,
                                double param_cb_n2 = 9,
                                double ntotal = 100
                                )
{
  /*********************************************************************************************************/
  // Define the x-axis: recoil energy in MeV [0, max_energy]
  /*********************************************************************************************************/
  RooRealVar energy("energy", "Energy (MeV)", 0.1, 8);
  energy.setRange("fitRange", range_low, range_high);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  RooDataHist dh_bkg("dh_bkg", "Background Histogram", energy, Import(*hbkg));
  RooHistPdf bkg_model("bkg_model", "Bkg Model based on histogram background template", energy, energy, dh_bkg);
  ws.import(bkg_model);

  /*********************************************************************************************************/
  // Elastic model: multiple CB2Shape (double-sided Crystal Ball Function)
  /*********************************************************************************************************/
  RooRealVar cb_sigma("cb_sigma", "CrystallBall sigma", param_cb_sigma, param_cb_sigma-0.01, param_cb_sigma+0.01);
  RooRealVar cb_alpha1("cb_alpha1", "CrystallBall leading turning point", param_cb_alpha1, param_cb_alpha1-0.5, 4);
  RooRealVar cb_n1("cb_n1", "CrystallBall trailing exponent", param_cb_n1, 1, 6);
  RooRealVar cb_alpha2("cb_alpha2", "CrystallBall trailing turning point", param_cb_alpha2, param_cb_alpha2-0.5, 5);
  RooRealVar cb_n2("cb_n2", "CrystallBall tailing exponent", param_cb_n2, 2, 8);
  RooRealVar cb_m0("cb_m0", "Peak of CrystalBall", param_cb_m0 , 0.85*param_cb_m0, 1.15*param_cb_m0);

  CB2Shape elastic_model("elastic_model", "Elastic Model", energy, cb_m0, cb_sigma, cb_alpha1, cb_n1, cb_alpha2, cb_n2);
  ws.import(elastic_model);

  //
  ws.factory(Form( "SUM::model(nbkg[%.1f,0,%f]*bkg_model,nelastic[%.1f,0,%f]*elastic_model)",ntotal,100*ntotal,0.5*ntotal,ntotal));
}
