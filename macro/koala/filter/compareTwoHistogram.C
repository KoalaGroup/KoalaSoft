#include "KoaHistUtility.h"

using namespace KoaUtility;

void compareTwoHistogram(const char* filename1,
                         const char* dir1,
                         const char* suffix1,
                         const char* filename2,
                         const char* dir2,
                         const char* suffix2,
                         int det_id,
                         int ch_id
                         )
{
  auto encoder = KoaMapEncoder::Instance();
  auto id = encoder->EncodeChannelID(det_id, ch_id);

  //
  auto infile1 = TFile::Open(filename1);
  auto hdir1 = getDirectory(infile1, dir1);
  auto hist1 = getHistosByChannelId<TH1D>(hdir1, suffix1);
  auto h1 = hist1[id];
  h1->SetLineColor(kBlack);
  h1->SetDirectory(0);

  auto infile2 = TFile::Open(filename2);
  auto hdir2 = getDirectory(infile2, dir2);
  auto hist2 = getHistosByChannelId<TH1D>(hdir2, suffix2);
  auto h2 = hist2[id];
  h2->SetLineColor(kBlue);
  h2->SetDirectory(0);

  auto hsub = (TH1*)h1->Clone();
  hsub->Add(h2, -1);
  hsub->SetLineColor(kRed);
  hsub->SetDirectory(0);

  //
  TCanvas* c = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("cCompare");
  if(c) delete c;
  c = new TCanvas("cCompare");

  c->SetLogy(); c->SetLogx();
  h1->Draw();
  h2->Draw("same");
  hsub->Draw("same");

  //
  delete infile1;
  delete infile2;
}
