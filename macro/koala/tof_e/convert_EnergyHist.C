#include "KoaHistUtility.h"
using namespace KoaUtility;

void convert_EnergyHist(const char* filename1,
                        const char* filename2
                        )
{
  auto fin = TFile::Open(filename1);
  auto dir_in = getDirectory(fin, "rec_cluster_energy_FirstHit_fwdhit_TimeValid");
  auto hist_in = getHistosByRecTdcChannelId<TH1D>(dir_in, "cluster_energy_firstHit_fwdhit_TimeValid");

  auto fout = TFile::Open(filename2,"update");
  auto dir_out = getDirectory(fout, "Energy_Coincidence");
  auto hist_out = bookH1dByRecTdcChannelId("Energy_Coincidence", "Recoil and Fwd Coincidence",
                                           700,0,7);

  for(auto& item: hist_out){
    auto id = item.first;
    auto& hout = item.second;
    hist_in[id]->Rebin(10);

    auto nbins=hout.GetNbinsX();
    for(int i=1;i<=nbins;i++){
      auto x = hout.GetXaxis()->GetBinCenter(i);
      auto bin = hist_in[id]->GetXaxis()->FindBin(x);
      auto y = hist_in[id]->GetBinContent(bin);
      hout.SetBinContent(i, y);
    }
  }

  writeHistos<TH1D>(dir_out, hist_out);

  delete fin;
  delete fout;
}
