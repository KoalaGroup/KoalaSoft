#ifndef KOA_HISTUTILTIY_H
#define KOA_HISTUTILTIY_H

#include "KoaUtility.h"

namespace KoaUtility
{

using IndexContainer = std::vector<Int_t>;
using Histo1D = std::map<Int_t, TH1D>;
using Histo2D = std::map<Int_t, TH2D>;
using HistoPtr1D = std::map<Int_t, TH1D*>;
using HistoPtr2D = std::map<Int_t, TH2D*>;

Histo1D bookH1dByChannelId(const char *hName, const char *hTitle, Int_t nBin = 7000,
                           Double_t xLow = 0, Double_t xHigh = 70, Bool_t IsRec = true,
                           Int_t colorLine = kBlack) {
  Histo1D h1book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  IndexContainer ChIDs;
  if (IsRec) {
    ChIDs = encoder->GetRecChIDs();
  } else {
    ChIDs = encoder->GetFwdChIDs();
  }

  for (auto &ChID : ChIDs) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor", "");

    h1book.emplace(std::piecewise_construct, std::forward_as_tuple(ChID),
                   std::forward_as_tuple(
                       Form("h1_%s_%s_%d", volName.Data(), hName, ch + 1),
                       Form("%s_%d: %s", volName.Data(), ch + 1, hTitle), nBin,
                       xLow, xHigh));

    h1book[ChID].SetLineColor(colorLine);
    h1book[ChID].SetDirectory(0);
  }

  return h1book;
}

// map key: recoil channel ids which have TDC readout
Histo1D bookH1dByRecTdcChannelId(const char *hName, const char *hTitle, Int_t nBin = 7000,
                                 Double_t xLow = 0, Double_t xHigh = 70,
                                 Int_t colorLine = kBlack) {
  Histo1D h1book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  IndexContainer ChIDs = encoder->GetRecTdcChIDs();

  for (auto &ChID : ChIDs) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor", "");

    h1book.emplace(std::piecewise_construct, std::forward_as_tuple(ChID),
                   std::forward_as_tuple(
                       Form("h1_%s_%s_%d", volName.Data(), hName, ch + 1),
                       Form("%s_%d: %s", volName.Data(), ch + 1, hTitle), nBin,
                       xLow, xHigh));

    h1book[ChID].SetLineColor(colorLine);
    h1book[ChID].SetDirectory(0);
  }

  return h1book;
}

Histo1D bookH1dByDetectorId(const char *hName, const char *hTitle, Int_t nBin,
                            Double_t xLow, Double_t xHigh, Bool_t IsRec = true,
                            Int_t colorLine = kBlack) {
  Histo1D h1book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();

  Int_t DetectorIdRange[2];
  if (IsRec) {
    encoder->GetRecDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);
  } else {
    encoder->GetFwdDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);
  }

  // loop
  for (auto detector :
       ROOT::TSeqI(DetectorIdRange[0], DetectorIdRange[1] + 1)) {
    TString volName = encoder->DetectorIDToVolName(detector);
    volName.ReplaceAll("Sensor", "");

    h1book.emplace(
        std::piecewise_construct, std::forward_as_tuple(detector),
        std::forward_as_tuple(Form("h1_%s_%s", volName.Data(), hName),
                              Form("%s : %s", volName.Data(), hTitle), nBin,
                              xLow, xHigh));
  }

  return h1book;
}

Histo1D bookH1dByRecDetectorId(const char *hName, const char *hTitle,
                               Int_t colorLine = kBlack) {
  Histo1D h1book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();

  Int_t DetectorIdRange[2];
  encoder->GetRecDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);

  // loop
  for (auto detector :
       ROOT::TSeqI(DetectorIdRange[0], DetectorIdRange[1] + 1)) {
    TString volName = encoder->DetectorIDToVolName(detector);
    volName.ReplaceAll("Sensor", "");
    Int_t chNumber = encoder->GetChNr(detector);

    h1book.emplace(
        std::piecewise_construct, std::forward_as_tuple(detector),
        std::forward_as_tuple(Form("h1_%s_%s", volName.Data(), hName),
                              Form("%s : %s", volName.Data(), hTitle), chNumber,
                              0.5, chNumber + 0.5));
  }

  return h1book;
}

//////////// 2-d histograms ////////////////////////////////////////////
Histo2D bookH2dByChannelId(const char *hName, const char *hTitle, Int_t nXbin,
                           Double_t xLow, Double_t xHigh, Int_t nYbin,
                           Double_t yLow, Double_t yHigh, Bool_t IsRec = true) {
  Histo2D h2book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  IndexContainer ChIDs;
  if (IsRec) {
    ChIDs = encoder->GetRecChIDs();
  } else {
    ChIDs = encoder->GetFwdChIDs();
  }

  for (auto &ChID : ChIDs) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor", "");

    h2book.emplace(std::piecewise_construct, std::forward_as_tuple(ChID),
                   std::forward_as_tuple(
                       Form("h2_%s_%s_%d", volName.Data(), hName, ch + 1),
                       Form("%s_%d: %s", volName.Data(), ch + 1, hTitle), nXbin,
                       xLow, xHigh, nYbin, yLow, yHigh));

    h2book[ChID].SetDirectory(0);
  }

  return h2book;
}

Histo2D bookH2dByRecTdcChannelId(const char *hName, const char *hTitle, Int_t nXbin,
                                 Double_t xLow, Double_t xHigh, Int_t nYbin,
                                 Double_t yLow, Double_t yHigh, Bool_t IsRec = true) {
  Histo2D h2book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  IndexContainer ChIDs = encoder->GetRecTdcChIDs();

  for (auto &ChID : ChIDs) {
    TString volName;
    Int_t ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor", "");

    h2book.emplace(std::piecewise_construct, std::forward_as_tuple(ChID),
                   std::forward_as_tuple(
                       Form("h2_%s_%s_%d", volName.Data(), hName, ch + 1),
                       Form("%s_%d: %s", volName.Data(), ch + 1, hTitle), nXbin,
                       xLow, xHigh, nYbin, yLow, yHigh));

    h2book[ChID].SetDirectory(0);
  }

  return h2book;
}

Histo2D bookH2dByDetectorId(const char *hName, const char *hTitle, Int_t nXbin,
                            Double_t xLow, Double_t xHigh, Int_t nYbin,
                            Double_t yLow, Double_t yHigh,
                            Bool_t IsRec = true) {
  Histo2D h2book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();

  Int_t DetectorIdRange[2];
  if (IsRec) {
    encoder->GetRecDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);
  } else {
    encoder->GetFwdDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);
  }

  // loop
  for (auto detector :
       ROOT::TSeqI(DetectorIdRange[0], DetectorIdRange[1] + 1)) {
    TString volName = encoder->DetectorIDToVolName(detector);
    volName.ReplaceAll("Sensor", "");

    h2book.emplace(
        std::piecewise_construct, std::forward_as_tuple(detector),
        std::forward_as_tuple(Form("h2_%s_%s", volName.Data(), hName),
                              Form("%s : %s", volName.Data(), hTitle), nXbin,
                              xLow, xHigh, nYbin, yLow, yHigh));
  }

  return h2book;
}

// specific TH2D with Recoil Sensor ID as index , and the X-axis binning is the
// channel number of each sensor
Histo2D bookH2dByRecDetectorId(const char *hName, const char *hTitle,
                               Int_t nYbin, Double_t yLow, Double_t yHigh) {
  Histo2D h2book;
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();

  Int_t DetectorIdRange[2];
  encoder->GetRecDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);

  // loop
  for (auto detector :
       ROOT::TSeqI(DetectorIdRange[0], DetectorIdRange[1] + 1)) {
    TString volName = encoder->DetectorIDToVolName(detector);
    volName.ReplaceAll("Sensor", "");
    Int_t chNumber = encoder->GetChNr(detector);

    h2book.emplace(
        std::piecewise_construct, std::forward_as_tuple(detector),
        std::forward_as_tuple(Form("h2_%s_%s", volName.Data(), hName),
                              Form("%s : %s", volName.Data(), hTitle), chNumber,
                              0.5, chNumber + 0.5, nYbin, yLow, yHigh));
  }

  return h2book;
}

/////////////////////// IO of histograms ///////////////////////

// Options can be:
// 1. "" : keep orginal, write new one with new cycle number
// 2. "Overwrite" : delete object with same name and then write to the file, cycle number is 1
// 3. "WriteDelete" : write to the file first and then delete the original, cycle number is increased by 1
template <typename T>
void writeHistos(TDirectory *hDir, T &histos, const char* option = "Overwrite") {
  for (const auto &hist : histos) {
    hDir->WriteTObject(&hist.second, "", option);
  }

  return;
}

template <typename T>
std::map<Int_t, T*> getHistosByChannelId(TDirectory *hDir, const char* hName, bool IsRec = true)
{
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  IndexContainer ChIDs;
  if (IsRec) {
    ChIDs = encoder->GetRecChIDs();
  } else {
    ChIDs = encoder->GetFwdChIDs();
  }

  //
  T* hist = nullptr;
  std::map<Int_t, T*> histoMap;

  // checking TH1 or TH2
  std::string hPrefix;
  if ( std::is_base_of<TH1,T>::value) {
    hPrefix = "h1";
  }
  else if( std::is_base_of<TH2,T>::value) {
    hPrefix = "h2";
  }
  else {
    std::cerr << "getHistosByChannelId: only TH1 and TH2 are supported\n";
    return histoMap;
  }

  for (auto &ChID : ChIDs) {
    TString volName;
    auto ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor", "");
    TString name(Form("%s_%s_%s_%d", hPrefix.data(), volName.Data(), hName, ch + 1));

    hDir->GetObject(name, hist);
    if ( !hist ) {
      std::cerr << "Error: no histogram found " << name << std::endl;
    }
    histoMap.emplace(ChID, hist);
  }

  return histoMap;
}

template <typename T>
std::map<Int_t, T*> getHistosByRecTdcChannelId(TDirectory *hDir, const char* hName)
{
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  IndexContainer ChIDs = encoder->GetRecTdcChIDs();

  T* hist = nullptr;
  std::map<Int_t, T*> histoMap;

  for (auto &ChID : ChIDs) {
    TString volName;
    auto ch = encoder->DecodeChannelID(ChID, volName);
    volName.ReplaceAll("Sensor", "");
    TString name(Form("h1_%s_%s_%d", volName.Data(), hName, ch + 1));

    hDir->GetObject(name, hist);
    if ( !hist ) {
      std::cerr << "Error: no histogram found " << name << std::endl;
    }
    histoMap.emplace(ChID, hist);
  }

  return histoMap;
}
// template<typename T>
// T* getHisto(TDirectory)

/////////////////////// Compare two sets of histograms ///////////////////////
bool compareTwoHisto(TH1* h1, TH1* h2)
{
  auto NrBinx1 = h1->GetNbinsX();
  if ( NrBinx1 != h2->GetNbinsX() ) {
    std::cout << "compareTwoHisto: unequal bin numbers in the two histograms\n";
    return false;
  }

  for(auto bin=0; bin < NrBinx1 ; bin++) {
    auto value1 = h1->GetBinContent(bin);
    auto value2 = h2->GetBinContent(bin);

    if ( value1 != value2 ) {
      std::cout << "compareTwoHisto: uneual bin content found\n";
      return false;
    }
  }

  return true;
}

bool compareHistos(HistoPtr1D& hMap1, HistoPtr1D& hMap2)
{
  if( hMap1.size() != hMap2.size() ) {
    std::cerr << "compareHistos: uneuqual size of histogram maps\n";
    return false;
  }

  for(auto& h1 : hMap1) {
    auto id = h1.first;
    auto search = hMap2.find(id);
    if ( search == hMap2.end()) {
      std::cerr << "compareTwoHisto: unmatched id found\n";
      return false;
    }

    if ( !compareTwoHisto(h1.second,search->second) ) {
      return false;
    }
  }

  return true;
}

};  // namespace KoaUtility
#endif
