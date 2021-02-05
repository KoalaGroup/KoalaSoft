#include "CB2Shape.cxx"
#include "TMath.h"

using namespace RooFit;

void fill_histpdf_bkg_workspace(RooWorkspace& ws,
                                TH1D*  hbkg,
                                double range_low = 0.75,
                                double range_high = 16,
                                double range_start = 6,
                                double param_cb_m0 = 0.8,
                                double param_cb_sigma = 0.15
                                )
{
  double fit_low = param_cb_m0 + 10*param_cb_sigma;
  double fit_high = range_high;

  if(fit_low < range_low) {
    fit_low = range_low;
  }
  if(fit_low > range_start) {
    fit_low = range_start;
  }

  if(fit_high > range_high) {
    fit_high = range_high;
  }

  if(param_cb_m0 > 3.7) {
    fit_low = 1.2;
    fit_high = param_cb_m0-10*param_cb_sigma;
  }

  TH1D* hclone = (TH1D*)hbkg->Clone("hclone");

  // rebin the background
  if(param_cb_m0 < 1.6)
    hclone->Rebin(2);
  else
    hclone->Rebin(8);

  auto bin_low = hclone->GetXaxis()->FindBin(0.12);
  auto bin_high = hclone->GetXaxis()->FindBin(6);
  double nbkg = hclone->Integral(bin_low, bin_high);

  /*********************************************************************************************************/
  // Define the x-axis: recoil energy in MeV [0, max_energy]
  /*********************************************************************************************************/
  RooRealVar energy("energy", "Energy (MeV)", 0.0, 6.0);
  energy.setRange("fitRange", fit_low, fit_high);
  energy.setRange("tofeRange", 0.12, 6.0);
  energy.setRange("drawRange", 0.0, 6.0);

  /*********************************************************************************************************/
  // Background model: frac_mip * bkg_mip + frac_expo1 * bkg_expo1 + (1-frac_mip-frac_expo1) * bkg_expo2
  /*********************************************************************************************************/
  RooDataHist dh_bkg("dh_bkg", "Background Histogram", energy, Import(*hclone));
  RooHistPdf bkg_model("bkg_model", "Bkg Model based on histogram background template", energy, energy, dh_bkg);
  ws.import(bkg_model);
  delete hclone;

  //
  ws.factory(Form( "SUM::model(nbkg[%.1f,%f,%f]*bkg_model)",nbkg,0.2*nbkg, 2*nbkg));
}
