#include "CB2Shape.cxx"

using namespace RooFit;

void fill_expo_cb2_workspace(RooWorkspace& ws,
                             int stripNr = 1,
                             double param_cb_mean = 0.15,
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
  double range_low = param_cb_mean - 20*param_cb_sigma;
  double range_high = param_cb_mean + 15*param_cb_sigma;
  if(range_high > range_limit) range_high = range_limit;

  double draw_low = range_low - 2*param_cb_sigma;
  double draw_high = range_high + 2*param_cb_sigma;
  auto strip_sigma = param_cb_sigma/TMath::Sqrt((double)stripNr);

  RooRealVar energy("energy", "Energy (MeV)", draw_low, draw_high);
  energy.setRange("fitRange", range_low, range_high);
  energy.setRange("drawRange", draw_low, draw_high);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  RooRealVar expo_lambda("expo_lambda", "expo_lambda",param_expo, param_expo*1.1, param_expo*0.9 );
  RooExponential bkg_model("bkg_model", "Exponential Background", energy, expo_lambda);
  ws.import(bkg_model);

  /*********************************************************************************************************/
  // Elastic model: multiple CB2Shape (double-sided Crystal Ball Function)
  /*********************************************************************************************************/
  RooRealVar cb_sigma("cb_sigma", "CrystallBall sigma", strip_sigma, strip_sigma-0.01, strip_sigma+0.01);
  RooRealVar cb_alpha1("cb_alpha1", "CrystallBall leading turning point", param_cb_alpha1, param_cb_alpha1-0.5, param_cb_alpha1+1);
  RooRealVar cb_n1("cb_n1", "CrystallBall trailing exponent", param_cb_n1, param_cb_n1-1, param_cb_n1+3);
  RooRealVar cb_alpha2("cb_alpha2", "CrystallBall trailing turning point", param_cb_alpha2, param_cb_alpha2-0.5, param_cb_alpha2+1.);
  RooRealVar cb_n2("cb_n2", "CrystallBall tailing exponent", param_cb_n2, param_cb_n2-1, param_cb_n2+2);

  if(stripNr == 1) {
    RooRealVar cb_m0("cb_m0_1", "Peak of CrystalBall 1", param_cb_mean-param_cb_sigma, param_cb_mean+param_cb_sigma);
    CB2Shape elastic_model("elastic_model", "Elastic Model", energy, cb_m0, cb_sigma, cb_alpha1, cb_n1, cb_alpha2, cb_n2);
    ws.import(elastic_model);

    ws.factory(Form( "SUM::model(nelastic[%.1f,%f,%f]*elastic_model,nbkg[%f,0,%f]*bkg_model)",ntotal,0.2*ntotal,2*ntotal, 0.01*ntotal, 0.1*ntotal));
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
      elastic_model_str.Append(Form("frac_cb%d[%.2f,%.2f,%.2f]*cb%d,",i+1, frac_avg, frac_avg*0.6, frac_avg*1.4, i+1));
    }
    elastic_model_str.Append(Form("cb%d)",stripNr));
    ws.factory(elastic_model_str.Data());

    // compose the final model
    ws.factory(Form( "SUM::model(nelastic[%.1f,%f,%f]*elastic_model,nbkg[%f,0,%f]*bkg_model)",ntotal,0.2*ntotal,2*ntotal, 0.01*ntotal, 0.1*ntotal));
  }
}
