#ifndef KOA_HISTUTILTIY_H
#define KOA_HISTUTILTIY_H

#include "KoaUtility.h"

namespace KoaUtility
{

using IndexContainer = std::vector<Int_t>;
using Histo1D = std::map<Int_t, TH1D>;
using Histo2D = std::map<Int_t, TH2D>;

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

/////////////////////// Write histograms to file ///////////////////////
template <typename T>
void writeHistos(TDirectory *hDir, T &histos) {
  hDir->cd();

  for (const auto &hist : histos) {
    hist.second.Write(0, TObject::kOverwrite);
  }

  return;
}

};  // namespace KoaUtility
#endif
