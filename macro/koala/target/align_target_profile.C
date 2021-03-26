#include "KoaHistUtility.h"

using namespace KoaUtility;

void align_target_profile(const char* filename,
                          const char* dirname,
                          const char* sensor = "si1", // or 'si2'
                          double e_start = 180, // in keV
                          double e_step = 60, // in keV
                          int e_nr = 30
                          )
{
  gStyle->SetPalette(kDeepSea);

  ////////////////////////////////////////
  // Read in the fitting params
  ////////////////////////////////////////

  ValueContainer<double> e_ref;
  ValueContainer<double> zoffset_si1, zoffset_si2;
  ValueContainer<double> A;
  ValueContainer<double> z0;

  auto read_params = [&]() {
                       auto fit_params = readParameterList<double>(filename);

                       auto it = findValueContainer(fit_params, "E_ref(keV)");
                       e_ref = it->second;

                       it = findValueContainer(fit_params, "si1(mm)");
                       zoffset_si1 = it->second;
                       it = findValueContainer(fit_params, "si2(mm)");
                       zoffset_si2 = it->second;

                       it = findValueContainer(fit_params, "A");
                       A = it->second;
                       it = findValueContainer(fit_params, "Z0(mm)");
                       z0 = it->second;
                     };
  read_params();
  
  //
  auto fout = TFile::Open(Form("%s/aggregate_profiles.root",dirname), "update");
  auto dir_norm = getDirectory(fout, Form("align_normalized_%s", sensor));
  auto dir_scale = getDirectory(fout, Form("align_scaled_%s", sensor));
  auto dir = getDirectory(fout, Form("align_%s",sensor));
  auto dir_noalign = getDirectory(fout, Form("noalign_%s",sensor));

  TMultiGraph *mg_noalign = new TMultiGraph();
  mg_noalign->SetName("mg_noalign");
  mg_noalign->SetTitle("Original Target Profiles");

  TMultiGraph *mg_align = new TMultiGraph();
  mg_align->SetName("mg_align");
  mg_align->SetTitle("Align Target Profiles to Z = 0 mm");

  TMultiGraph *mg_norm = new TMultiGraph();
  mg_norm->SetName("mg_align_normalized");
  mg_norm->SetTitle("Align Target Profiles to Z = 0 mm and Normalized to same Peak Density");

  TMultiGraph *mg_scale = new TMultiGraph();
  mg_scale->SetName("mg_align_scaled");
  mg_scale->SetTitle("Align Target Profiles to Z = 0 mm and Scaled to same Peak Density");

  // auto z_ref = z0[last_id-1];
  auto A_ref = A[0];
  int index = 0;
  for(auto item: A){
    auto ch = item.first;

    bool found = false;
    for(int i = 0; i<e_nr; i++) {
      if(10 > TMath::Abs(e_ref[ch] - (e_start+e_step*i))) {
        found = true;
        break;
      }
    }

    if (!found) continue;

    auto fin = TFile::Open(Form("%s/ref_%.0fkeV.root", dirname, e_ref[ch]));
    auto dir_in = (TDirectory*)fin->Get(Form("profile_si1_%.2f_si2_%.2f", zoffset_si1[ch], zoffset_si2[ch]));
    auto gr = (TGraph*)dir_in->Get(Form("gr_strip_%s", sensor));

    auto deltaA = A_ref - A[ch];
    auto deltaZ = - z0[ch];
    auto scaleA = A_ref/A[ch];

    auto npts = gr->GetN();
    auto x = gr->GetX();
    auto y = gr->GetY();
    
    auto gr_noalign = new TGraph();
    gr_noalign->SetName(Form("gr_noalign_ref_%.0fkeV", e_ref[ch]));
    gr_noalign->SetMarkerStyle(20);
    gr_noalign->SetMarkerSize(0.6);
    mg_noalign->Add(gr_noalign, "PL");

    auto gr_align = new TGraph();
    gr_align->SetName(Form("gr_align_ref_%.0fkeV", e_ref[ch]));
    gr_align->SetMarkerStyle(20);
    gr_align->SetMarkerSize(0.6);
    mg_align->Add(gr_align, "PL");

    auto gr_norm = new TGraph();
    gr_norm->SetName(Form("gr_align_normalized_ref_%.0fkeV", e_ref[ch]));
    gr_norm->SetMarkerStyle(20);
    gr_norm->SetMarkerSize(0.6);
    mg_norm->Add(gr_norm, "PL");

    auto gr_scale = new TGraph();
    gr_scale->SetName(Form("gr_align_scaled_ref_%.0fkeV", e_ref[ch]));
    gr_scale->SetMarkerStyle(20);
    gr_scale->SetMarkerSize(0.6);
    mg_scale->Add(gr_scale, "PL");

    for(int i=0;i<npts;i++){
      gr_noalign->SetPoint(i, x[i], y[i]);
      gr_align->SetPoint(i, x[i]+deltaZ, y[i]);
      gr_norm->SetPoint(i, x[i]+deltaZ, y[i]+deltaA);
      gr_scale->SetPoint(i, x[i]+deltaZ, y[i]*scaleA);
    }

    //
    dir_noalign->WriteTObject(gr_noalign, "", "WriteDelete");
    dir->WriteTObject(gr_align, "", "WriteDelete");
    dir_norm->WriteTObject(gr_norm, "", "WriteDelete");
    dir_scale->WriteTObject(gr_scale, "", "WriteDelete");

    delete gr;
    delete fin;
  }
  
  //
  dir_noalign->WriteTObject(mg_noalign, "", "WriteDelete");
  dir->WriteTObject(mg_align, "", "WriteDelete");
  dir_norm->WriteTObject(mg_norm, "", "WriteDelete");
  dir_scale->WriteTObject(mg_scale, "", "WriteDelete");

  //
  delete fout;
}
