#include "KoaColors.h"

using namespace KoaUtility;

void compareDigi(const char* base_path, const char* sensor, int strip,
                 bool use_cut = true, bool use_rebin = false,
                 double range_low=0, double range_high=70)
{
  // setup color scheme
  init_KoaColors();
  set_KoaPalette_Sunset(100);

  TH1::AddDirectory(false);

  //
  std::map<std::string, std::string> files;
  auto insertFile = [&] (const char* prefix) -> bool
                    {
                      TString filename(base_path);
                      filename.Append(Form("_%s_result.root", prefix));

                      auto file = TFile::Open(filename);
                      TDirectory *hdir = nullptr;
                      if(!(hdir=file->GetDirectory("histograms"))){
                        std::cerr << "Error: no histograms dir" << std::endl;
                        return false;
                      }

                      files.emplace(filename, prefix);
                      std::cout << filename << ", " << prefix << std::endl;
                      delete file;
                      return true;
                    };

  //
  if(!insertFile("digi")) return;
  // if(!insertFile("division")) return;
  // if(!insertFile("fano")) return;
  // if(!insertFile("noise")) return;
  // if(!insertFile("collection")) return;

  //
  auto getHist = [&] (std::string filename, std::string prefix) -> TH1D*
                 {
                   auto file = TFile::Open(filename.data());
                   TDirectory *hdir = file->GetDirectory("histograms");
                   TH1D *hist = nullptr;
                   TString hname(Form("h1_%s_Sensor%s_%d", prefix.data(), sensor, strip));
                   hdir->GetObject(hname, hist);
                   if ( !hist ) {
                     std::cerr << "Error: no histogram " << hname << std::endl;
                   }

                   delete file;
                   return hist;
                 };

  std::vector<TH1*> histograms;
  int index = 0;
  for(auto& file: files) {
    TH1D* hist = getHist(file.first, file.second);
    if(!hist) return;
    hist->SetLineColor(kTBriBlue+index);
    hist->SetLineWidth(2);
    histograms.emplace_back(hist);

    index++;
  }

  // beam test spectrum
  TH1D* hist;
  if (use_cut){
    hist = getHist("P_2.6_result.root", "energy_cut");
  }
  else{
    hist = getHist("P_2.6_result.root", "energy");
  }
  if(!hist) return;

  // if (use_rebin){
  //   hist->Rebin(4);
  // }
  // hist->GetXaxis()->SetRange(range_low,range_high);
  auto ref_max = hist->GetBinContent(hist->GetMaximumBin());

  for(auto& h1: histograms) {
    // if (use_rebin){
    //   h1->Rebin(4);
    // }
    // h1->GetXaxis()->SetRange(range_low,range_high);
    auto max = h1->GetBinContent(h1->GetMaximumBin());
    h1->Scale(ref_max/max, "nosw2");
  }

  hist->SetLineColor(kBlack);
  hist->SetLineWidth(2);
  histograms.emplace_back(hist);

  // draw
  auto can = new TCanvas();
  for(auto& h1: histograms) {
    h1->Draw("same");
  }
}
