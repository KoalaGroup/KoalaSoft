#include "KoaHistUtility.h"

using namespace KoaUtility;

void align_target_profile(const char* filename,
                          const char* dirname,
                          int last_id = 30
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
  auto dir_norm = getDirectory(fout, "align_normalized");
  auto dir = getDirectory(fout, "align");

  TMultiGraph *mg_align = new TMultiGraph();
  mg_align->SetName("mg_align");
  mg_align->SetTitle("Align Target Profiles to Z = 0 mm");
  TMultiGraph *mg_norm = new TMultiGraph();
  mg_norm->SetName("mg_align_normalized");
  mg_norm->SetTitle("Align Target Profiles to Z = 0 mm and Normalized to same Peak Density");

  // auto z_ref = z0[last_id-1];
  auto A_ref = A[0];
  for(int ch = 0; ch<last_id;ch++){
    auto fin = TFile::Open(Form("%s/ref_%.0fkeV.root", dirname, e_ref[ch]));
    auto dir_in = (TDirectory*)fin->Get(Form("profile_si1_%.2f_si2_%.2f", zoffset_si1[ch], zoffset_si2[ch]));
    auto gr = (TGraph*)dir_in->Get("gr_strip_si1");

    auto deltaA = A_ref - A[ch];
    auto deltaZ = - z0[ch];

    auto npts = gr->GetN();
    auto x = gr->GetX();
    auto y = gr->GetY();
    
    auto gr_align = new TGraph();
    gr_align->SetName(Form("gr_align_ref_%.0fkeV", e_ref[ch]));
    gr_align->SetMarkerStyle(20);
    gr_align->SetMarkerSize(0.4);
    mg_align->Add(gr_align, "PL");

    auto gr_norm = new TGraph();
    gr_norm->SetName(Form("gr_align_normalized_ref_%.0fkeV", e_ref[ch]));
    gr_norm->SetMarkerStyle(20);
    gr_norm->SetMarkerSize(0.4);
    mg_norm->Add(gr_norm, "PL");

    for(int i=0;i<npts;i++){
      gr_align->SetPoint(i, x[i]+deltaZ, y[i]);
      gr_norm->SetPoint(i, x[i]+deltaZ, y[i]+deltaA);
    }

    //
    dir->WriteTObject(gr_align, "", "WriteDelete");
    dir_norm->WriteTObject(gr_norm, "", "WriteDelete");

    delete gr;
    delete fin;
  }
  
  //
  dir->WriteTObject(mg_align, "", "WriteDelete");
  dir_norm->WriteTObject(mg_norm, "", "WriteDelete");

  //
  delete fout;
}