#ifndef KOACUTOBJECT_H
#define KOACUTOBJECT_H

#include "KoaHistUtility.h"

namespace KoaUtility
{

enum class RegionType : int
  {
    FwdTimeMain=0, FwdTimeBand1, FwdTimeBand2, FwdTimeBand3, FwdTimeBand4, FwdTimeOther,
    FwdTimeInvalid1, FwdTimeInvalid2, FwdTimeInvalid, FwdTimeEnd,
    FwdAmpMain, FwdAmpPed, FwdAmpPed1, FwdAmpPed2, FwdAmpLow1, FwdAmpLow2, FwdAmpLow, FwdAmpEnd,
    ALL_END
  };

RegionType& operator ++ (RegionType& e)
{
  if ( e == RegionType::ALL_END ) {
    throw std::out_of_range("for RegionType& operator ++ (RegionType&)");
  }

  e = RegionType(static_cast<std::underlying_type<RegionType>::type>(e) + 1);
  return e;
}

std::string getRegionName(RegionType type)
{
  std::string name;

  switch (type) {
    // Time Cut
    case RegionType::FwdTimeMain: {
      name = "FwdTimeMain";
      break;
    }
    case RegionType::FwdTimeBand1: {
      name = "FwdTimeBand1";
      break;
    }
    case RegionType::FwdTimeBand2: {
      name = "FwdTimeBand2";
      break;
    }
    case RegionType::FwdTimeBand3: {
      name = "FwdTimeBand3";
      break;
    }
    case RegionType::FwdTimeBand4: {
      name = "FwdTimeBand4";
      break;
    }
    case RegionType::FwdTimeOther: {
      name = "FwdTimeOther";
      break;
    }
    case RegionType::FwdTimeInvalid1: {
      name = "FwdTimeInvalid1";
      break;
    }
    case RegionType::FwdTimeInvalid2: {
      name = "FwdTimeInvalid2";
      break;
    }
    case RegionType::FwdTimeInvalid: {
      name = "FwdTimeInvalid";
      break;
    }
      // Amplitude Cut
    case RegionType::FwdAmpMain: {
      name = "FwdAmpMain";
      break;
    }
    case RegionType::FwdAmpPed: {
      name = "FwdAmpPed";
      break;
    }
    case RegionType::FwdAmpPed1: {
      name = "FwdAmpPed1";
      break;
    }
    case RegionType::FwdAmpPed2: {
      name = "FwdAmpPed2";
      break;
    }
    case RegionType::FwdAmpLow: {
      name = "FwdAmpLow";
      break;
    }
    case RegionType::FwdAmpLow1: {
      name = "FwdAmpLow1";
      break;
    }
    case RegionType::FwdAmpLow2: {
      name = "FwdAmpLow2";
      break;
    }
    default:
      break;
  }

  return name;
}

std::string getRegionTitle(RegionType type)
{
  std::string name;

  switch (type) {
    // Time Cut
    case RegionType::FwdTimeMain: {
      name = "Fwd Time Cut (Main)";
      break;
    }
    case RegionType::FwdTimeBand1: {
      name = "Fwd Time Cut (Band1)";
      break;
    }
    case RegionType::FwdTimeBand2: {
      name = "Fwd Time Cut (Band2)";
      break;
    }
    case RegionType::FwdTimeBand3: {
      name = "Fwd Time Cut (Band3)";
      break;
    }
    case RegionType::FwdTimeBand4: {
      name = "Fwd Time Cut (Band4)";
      break;
    }
    case RegionType::FwdTimeOther: {
      name = "Fwd Time Cut (Other)";
      break;
    }
    case RegionType::FwdTimeInvalid1: {
      name = "Fwd Time Cut (Invalid1)";
      break;
    }
    case RegionType::FwdTimeInvalid2: {
      name = "Fwd Time Cut (Invalid2)";
      break;
    }
    case RegionType::FwdTimeInvalid: {
      name = "Fwd Time Cut (Invalid)";
      break;
    }
      // Amplitude Cut
    case RegionType::FwdAmpMain: {
      name = "Fwd Amplitude Cut (Main)";
      break;
    }
    case RegionType::FwdAmpPed: {
      name = "Fwd Amplitude Cut (Ped)";
      break;
    }
    case RegionType::FwdAmpPed1: {
      name = "Fwd Amplitude Cut (Ped1)";
      break;
    }
    case RegionType::FwdAmpPed2: {
      name = "Fwd Amplitude Cut (Ped2)";
      break;
    }
    case RegionType::FwdAmpLow: {
      name = "Fwd Amplitude Cut (Low)";
      break;
    }
    case RegionType::FwdAmpLow1: {
      name = "Fwd Amplitude Cut (Low1)";
      break;
    }
    case RegionType::FwdAmpLow2: {
      name = "Fwd Amplitude Cut (Low2)";
      break;
    }
    default:
      break;
  }

  return name;
}

  ///////////////// book histograms based on cut conditon ///////////////////////////////////////////////////////////

Histo1D bookH1dByRegionType(const char *hName, const char *hTitle, Int_t nBin = 7000,
                            Double_t xLow = 0, Double_t xHigh = 70, Bool_t IsAmpCut = true,
                            Int_t colorLine = kBlack) {

  RegionType begin, end;
  if ( !IsAmpCut ) {
    begin = RegionType::FwdTimeMain;
    end   = RegionType::FwdTimeEnd;
  }
  else {
    begin = RegionType::FwdAmpMain;
    end   = RegionType::FwdAmpEnd;
  }

  //
  Histo1D h1book;
  for(auto e = begin; e != end; ++e) {
    auto insert = h1book.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(static_cast<std::underlying_type<RegionType>::type>(e)),
                                 std::forward_as_tuple(Form("h1_%s_%s", getRegionName(e).data(), hName),
                                                       Form("%s : %s", getRegionTitle(e).data(), hTitle),
                                                       nBin, xLow, xHigh)
                                 );
    insert.first->second.SetLineColor(colorLine);
    insert.first->second.SetDirectory(0);
  }

  return h1book;
}

Histo2D bookH2dByRegionType(const char *hName, const char *hTitle,
                            Int_t nXBin = 7000, Double_t xLow = 0, Double_t xHigh = 70,
                            Int_t nYBin = 7000, Double_t yLow = 0, Double_t yHigh = 70,
                            Bool_t IsAmpCut = true, Int_t colorLine = kBlack) {

  RegionType begin, end;
  if ( !IsAmpCut ) {
    begin = RegionType::FwdTimeMain;
    end   = RegionType::FwdTimeEnd;
  }
  else {
    begin = RegionType::FwdAmpMain;
    end   = RegionType::FwdAmpEnd;
  }

  //
  Histo2D h2book;
  for(auto e = begin; e != end; ++e) {
    auto insert = h2book.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(static_cast<std::underlying_type<RegionType>::type>(e)),
                                 std::forward_as_tuple(Form("h2_%s_%s", getRegionName(e).data(), hName),
                                                       Form("%s : %s", getRegionTitle(e).data(), hTitle),
                                                       nXBin, xLow, xHigh, nYBin, yLow, yHigh)
                                 );
    insert.first->second.SetLineColor(colorLine);
    insert.first->second.SetDirectory(0);
  }

  return h2book;
}

///////////////// book event list based on cut conditon ///////////////////////////////////////////////////////////
std::map<int, TEventList> bookEListByRegionType( bool IsAmpCut =  true)
{
   RegionType begin, end;
   if ( !IsAmpCut ) {
     begin = RegionType::FwdTimeMain;
     end   = RegionType::FwdTimeEnd;
   }
   else {
     begin = RegionType::FwdAmpMain;
     end   = RegionType::FwdAmpEnd;
   }

   //
   std::map<int, TEventList> elists;

   for(auto e = begin; e != end; ++e) {
     auto insert = elists.emplace(std::piecewise_construct,
                                  std::forward_as_tuple(static_cast<std::underlying_type<RegionType>::type>(e)),
                                  std::forward_as_tuple(Form("elist_%s", getRegionName(e).data()),
                                                        Form("Entry List : %s", getRegionTitle(e).data())
                                                        )
                                  );
     insert.first->second.SetDirectory(0);
   }

   return elists;
 }

///////////////// Predefined Cut Objects, used for cut region identification and store the cut conditions //////////////

////////////////////////////////////////////////////////////////////////////////
// Region Type definition:
//
//     Fwd2_Time
//         |
//         |                               /---      /-
//         |            Other           /--       /--
//         |                        /---       /--
//         +-------------------+----| BAND3 /--
//         |     BAND2         |Main|    /--
//         +-------------------+----+-
//         | Other    ---/    -+ B  |
// Invalid1|      ---/BAND4--/ | A  |
//         |  ---/    ---/     | N  |
//         |-/    ---/         | D  |    Other
//         |  ---/      Other  | 1  |
//         |-/                 |    |
// --------+-------------------+----+----------- Fwd1_Time
// Invalid |      Invalid2
//         |

class KoaFwdTimeCut 
{
 public:
  KoaFwdTimeCut(double low1 = 915, double high1 = 930, double low2 = 915, double high2 = 930,
                double window_low = -10, double window_high = 10)
      : fLow1(low1), fHigh1(high1),
        fLow2(low2), fHigh2(high2),
        fWindowLow(window_low), fWindowHigh(window_high)
  {}

  void SetValue(double low1, double high1, double low2, double high2,
                double window_low, double window_high)
  {
    fLow1 = low1;
    fLow2 = low2;

    fHigh1 = high1;
    fHigh2 = high2;

    fWindowLow = window_low;
    fWindowHigh = window_high;
  }

  RegionType GetType(double fwd1_t, double fwd2_t)
  {
    if ( fwd1_t >= fLow1 && fwd1_t <= fHigh1 ) {
      if ( fwd2_t >= fLow2 && fwd2_t <= fHigh2 )
        return RegionType::FwdTimeMain;
      else if ( fwd2_t < fLow2 && fwd2_t > 0 )
        return RegionType::FwdTimeBand1;
    }

    if ( fwd2_t >= fLow2 && fwd2_t <= fHigh2 &&
         fwd1_t < fLow1 && fwd1_t > 0 ) {
      return RegionType::FwdTimeBand2;
    }

    if ( (fwd2_t - fwd1_t) > fWindowLow && (fwd2_t - fwd1_t) < fWindowHigh ) {
      if (fwd1_t < fLow1 && fwd1_t > 0 && fwd2_t > 0)
        return RegionType::FwdTimeBand4;
      else if ( fwd1_t > fHigh1 && fwd1_t > 0 && fwd2_t > 0)
        return RegionType::FwdTimeBand3;
    }

    if ( fwd1_t <=0 ) {
      if ( fwd2_t <=0 ) {
        return RegionType::FwdTimeInvalid;
      }
      else {
        return RegionType::FwdTimeInvalid1;
      }
    }
    else if ( fwd2_t <= 0 )
      return RegionType::FwdTimeInvalid2;

    return RegionType::FwdTimeOther;
  }

  void Print()
  {
    std::cout << "Cut Object:   KoaFwdTimeCut\n";
    std::cout << "Description:  Using Fwd scintillators' time information as cut condition\n";
    std::cout << "Parameters:\n";
    std::cout << "\t fLow1 = " << fLow1 << ",\t fHigh1 = " << fHigh1 << std::endl;
    std::cout << "\t fLow2 = " << fLow2 << ",\t fHigh2 = " << fHigh2 << std::endl;
    std::cout << "\t Window Size = [" << fWindowLow << ", " << fWindowHigh << "]" << std::endl;
  }

 private:
  // fwd1 cut values
  double fLow1;
  double fHigh1;

  // fwd1 cut values
  double fLow2;
  double fHigh2;

  //
  double fWindowLow;
  double fWindowHigh;
};

  ////////////////////////////////////////////////////////////////////////////////
  // Region Type definition:
  //
  // Fwd2_Amplitude
  //
  //        |        |               |
  //        |        |      Low1     |  Main
  //        |        |               |
  // fHigh2 +  Ped1  +---------------+-------
  //        |        |               |
  //        |        |      Low      |  Low2
  //        |        |               |
  // fLow2  +--------+---------------+-------
  //        |        |
  //        |  Ped   |             Ped2
  //        |        |
  //     ---+--------+---------------+------------ Fwd1_Amplitude
  //        |      fLow1           fHigh1

class KoaFwdAmpCut
{
 public:
  KoaFwdAmpCut(double low1 = 790, double high1 = 1050, double low2 = 780, double high2 = 1030)
      : fLow1(low1), fHigh1(high1),
        fLow2(low2), fHigh2(high2)
  {}

  void SetValue(double low1, double high1, double low2, double high2)
  {
    fLow1 = low1;
    fLow2 = low2;

    fHigh1 = high1;
    fHigh2 = high2;
  }

  RegionType GetType(double fwd1_a, double fwd2_a)
  {
    if ( fwd1_a >= fHigh1 && fwd2_a >= fHigh2 ) {
      return RegionType::FwdAmpMain;
    }

    if ( fwd1_a >= fLow1 ) {
      if ( fwd2_a >= fHigh2 ) {
        return RegionType::FwdAmpLow1;
      }
      else if ( fwd2_a > fLow2 ){
        if ( fwd1_a < fHigh1 )
          return RegionType::FwdAmpLow;
        else
          return RegionType::FwdAmpLow2;
      }
      else {
        return RegionType::FwdAmpPed2;
      }
    }
    else {
      if ( fwd2_a < fLow2 ) {
        return RegionType::FwdAmpPed;
      }
      else {
        return RegionType::FwdAmpPed1;
      }
    }
  }

  void Print()
  {
    std::cout << "Cut Object:   KoaFwdAmpCut\n";
    std::cout << "Description:  Using Fwd scintillators' amplitudes as cut condition\n";
    std::cout << "Parameters:\n";
    std::cout << "\t fLow1 = " << fLow1 << ",\t fHigh1 = " << fHigh1 << std::endl;
    std::cout << "\t fLow2 = " << fLow2 << ",\t fHigh2 = " << fHigh2 << std::endl;
  }

 private:
  // fwd1 cut values
  double fLow1;
  double fHigh1;

  // fwd1 cut values
  double fLow2;
  double fHigh2;
};

//////////////////////////////

};

#endif
