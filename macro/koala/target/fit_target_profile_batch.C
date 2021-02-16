#include "KoaHistUtility.h"

using namespace KoaUtility;

void fit_target_profile_batch(const char* dirname,
                              double zoffset_si1 = 0,
                              double zoffset_si2 = 0,
                              double e_start = 120,
                              double e_step = 50,
                              double nr_step = 30)
{
  gStyle->SetOptFit(1);

  //
  ParameterList<double> OutputParameters;
  auto& output_e_ref = addValueContainer(OutputParameters, "E_ref(keV)");
  auto& output_zoffset_si1 = addValueContainer(OutputParameters, "si1(mm)");
  auto& output_zoffset_si2 = addValueContainer(OutputParameters, "si2(mm)");
  auto& output_A = addValueContainer(OutputParameters, "A");
  auto& output_frac1 = addValueContainer(OutputParameters, "Frac1");
  auto& output_z0 = addValueContainer(OutputParameters, "Z0(mm)");
  auto& output_sigma1 = addValueContainer(OutputParameters, "Sigma1(mm)");
  auto& output_sigma2 = addValueContainer(OutputParameters, "Sigma2(mm)");
  auto& output_fwhm = addValueContainer(OutputParameters, "FWHM(mm)");
  auto& output_xlow = addValueContainer(OutputParameters, "xlow(mm)");
  auto& output_xhigh = addValueContainer(OutputParameters, "xhigh(mm)");

  //
  TCanvas c("c","c",600,600);
  c.Print(Form("%s/profiles_fit.pdf[",dirname));
  for(int i = 0;i<nr_step;i++){
    auto e_current = e_start + i*e_step;
    auto fin = TFile::Open(Form("%s/ref_%.0fkeV.root", dirname, e_current));
    auto dir = (TDirectory*)fin->Get(Form("profile_si1_%.2f_si2_%.2f", zoffset_si1, zoffset_si2));
    auto gr = (TGraph*)dir->Get("gr_strip_si1");

    auto npts = gr->GetN();
    auto x = gr->GetX();
    auto y = gr->GetY();

    double x_low, x_high;
    double thresh = 500;
    x_low = -100; x_high = 100;
    for(int j = 0; j < npts; j++){
      if(y[j] > thresh && x_low == -100) {
        x_low = x[j];
        break;
      }
    }
    for(int j = npts; j > 0; j--){
      if(y[j-1] > thresh && x_high == 100) {
        x_high = x[j-1];
        break;
      }
    }

    auto ffit = new TF1("fbigaus", "[0]*([1]*TMath::Gaus(x, [2],[3])+(1.-[1])*TMath::Gaus(x,[2], [4]))", x_low-10, x_high+10);
    ffit->SetParName(0, "A");
    ffit->SetParameter(0, 800e3);
    ffit->SetParLimits(0, 2e4, 1e6);
    ffit->SetParName(1, "frac1");
    ffit->SetParameter(1, 0.6);
    ffit->SetParLimits(1, 0.4, 1.);
    ffit->SetParName(2, "z0");
    ffit->SetParameter(2, (x_low+x_high)/2.);
    ffit->SetParLimits(2, -3, 3);
    ffit->SetParName(3, "sigma_1");
    ffit->SetParameter(3, 1.5);
    ffit->SetParLimits(3, 0., 3);
    ffit->SetParName(4, "sigma_2");
    ffit->SetParameter(4, 4);
    ffit->SetParLimits(4, 2, 8);
    gr->Fit(ffit,"","",x_low-2,x_high);

    double max = ffit->GetMaximum();
    double max_x = ffit->GetParameter(2);
    double fwhm= ffit->GetX(max/2, max_x, max_x+10) - ffit->GetX(max/2., max_x-10,max_x);
    ffit->SetParLimits(2, max_x-0.5, max_x+0.5);
    x_low = max_x-3*fwhm;
    x_high = max_x+3*fwhm;
    ffit->SetParLimits(3,0,fwhm);
    ffit->SetParLimits(4,fwhm,15);
    gr->Fit(ffit,"","",x_low,x_high);

    // get fwhm
    max = ffit->GetMaximum();
    max_x = ffit->GetParameter(2);
    fwhm= ffit->GetX(max/2, max_x, max_x+10) - ffit->GetX(max/2., max_x-10,max_x);

    // fill in output
    output_e_ref.emplace(i, e_current);
    output_zoffset_si1.emplace(i, zoffset_si1);
    output_zoffset_si2.emplace(i, zoffset_si2);
    output_A.emplace(i, ffit->GetParameter(0));
    output_frac1.emplace(i, ffit->GetParameter(1));
    output_z0.emplace(i, ffit->GetParameter(2));
    output_sigma1.emplace(i, ffit->GetParameter(3));
    output_sigma2.emplace(i, ffit->GetParameter(4));
    output_fwhm.emplace(i, fwhm);
    output_xlow.emplace(i, x_low);
    output_xhigh.emplace(i, x_high);

    // print to pdf
    gr->Draw("AP");
    gr->GetXaxis()->SetRangeUser(x_low, x_high);
    c.Print(Form("%s/profiles_fit.pdf",dirname));

    //
    delete fin;
    delete ffit;
    delete gr;
  }
  c.Print(Form("%s/profiles_fit.pdf]",dirname));

  // print params to txt
  printValueList<double>(OutputParameters, Form("%s/profiles_fit.txt", dirname));
}
