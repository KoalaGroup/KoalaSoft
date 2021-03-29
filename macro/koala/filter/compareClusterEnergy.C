#include "KoaHistUtility.h"

using namespace KoaUtility;

void compareClusterEnergy(const char* filename,
                          const char* dir1,
                          const char* suffix1,
                          const char* dir2,
                          const char* suffix2,
                          const char* outname
                          )
{
  auto infile = TFile::Open(filename);

  auto hdir1 = getDirectory(infile, dir1);
  auto hist1 = getHistosByChannelId<TH1D>(hdir1, suffix1);

  auto hdir2 = getDirectory(infile, dir2);
  auto hist2 = getHistosByChannelId<TH1D>(hdir2, suffix2);

  //
  auto c = new TCanvas();
  c->SetLogy(); c->SetLogx();

  c->Print(Form("%s[",outname));
  for(auto h1: hist1 ){
    auto id = h1.first;
    auto hist = h1.second;

    hist->SetLineColor(kBlack);
    hist->Draw();

    hist2[id]->SetLineColor(kBlue);
    hist2[id]->Draw("same");

    auto hclone = (TH1*)hist->Clone();
    hclone->Add(hist2[id],-1);
    hclone->SetLineColor(kRed);
    hclone->Draw("same");

    // c->BuildLegend();
    // c->Update();

    c->Print(Form("%s",outname));
    delete hclone;
  }
  c->Print(Form("%s]",outname));

  delete c;

  //
  delete infile;
}
