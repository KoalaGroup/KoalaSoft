#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;
using namespace std;

void checkEta(const char* point_file,
              const char* geoFile = "geo_standard.root"
              )
{
  // geometry model
  auto geoHandler = getGeometryHandler(geoFile);

  // input
  auto fin = TFile::Open(point_file);
  TTree* tin; fin->GetObject("koalasim", tin);

  auto recPts = new TClonesArray("KoaRecPoint", 200);
  tin->SetBranchAddress("KoaRecPoint", &recPts);

  // book histograms
  string hname = "eta_percentage";
  string htitle = "MCPoint: Fraction of FirstHit Channel VS Impact Position";
  string hdir = "mcpoint_eta_percentage";

  auto h2map_all = bookH2dByChannelId(hname.data(),
                                      htitle.data(),
                                      100, -0.1, 4.9,
                                      102, -0.01, 1.01,
                                      true);
  auto h2map_single = bookH2dByChannelId((hname+"_single").data(),
                                         (htitle+" (SingleHit)").data(),
                                         100, -0.1, 4.9,
                                         102, -0.01, 1.01,
                                         true);
  auto h2map_double = bookH2dByChannelId((hname+"_double").data(),
                                         (htitle+" (DoubleHit)").data(),
                                         100, -0.1, 4.9,
                                         102, -0.01, 1.01,
                                         true);
  auto h2map_multi = bookH2dByChannelId((hname+"_multi").data(),
                                        (htitle+" (MultiHit)").data(),
                                        100, -0.1, 4.9,
                                        102, -0.01, 1.01,
                                        true);

  // TString hname_percentage_relative_position = "eta_percentage_relative_position";
  // TString htitle_percentage_relative_position = "MCPoint: FirstHit Energy Fraction VS Relative Hit Position in FirstHit Channel";
  // TString hdir_percentage_relative_position = "mcpoint_eta_percentage_relative_position";

  // auto h2map_relative_position = bookH2dByChannelId(hname_percentage_relative_position.Data(),
  //                                                              htitle_percentage_relative_position.Data(),
  //                                                              102, -0.01, 1.01,
  //                                                              102, -0.01, 1.01,
  //                                                              true);

  // out parameters
  ParameterList<double> outParamters;
  auto& totalHits = addValueContainer(outParamters, "TotalHit");
  auto& singleHits = addValueContainer(outParamters, "SingleHit");
  auto& doubleHits = addValueContainer(outParamters, "DoubleHit");
  auto& multiHits = addValueContainer(outParamters, "MultiHit");
  auto& singleFractions = addValueContainer(outParamters, "SingleHit(%)");
  auto& doubleFractions = addValueContainer(outParamters, "DoubleHit(%)");
  auto& multiFractions = addValueContainer(outParamters, "MultiHit(%)");

  auto encoder = KoaMapEncoder::Instance();
  auto ChIDs = encoder->GetRecChIDs();
  for(auto id: ChIDs){
    totalHits[id] = 0;
    singleHits[id] = 0;
    doubleHits[id] = 0;
    multiHits[id] = 0;
  }

  // looping
  auto entries = tin->GetEntries();
  for(auto entry=0; entry < entries; entry++) {
    tin->GetEntry(entry);

    auto points = recPts->GetEntries();
    for(int pt=0; pt < points; pt++) {
      KoaRecPoint* curPoint = (KoaRecPoint*)recPts->At(pt);

      Int_t detID = curPoint->GetDetectorID();

      Double_t global_in[3], global_out[3];
      Double_t local_in[3], local_out[3];
      global_in[0]=curPoint->GetX();
      global_in[1]=curPoint->GetY();
      global_in[2]=curPoint->GetZ();

      global_out[0]=curPoint->GetXEnd();
      global_out[1]=curPoint->GetYEnd();
      global_out[2]=curPoint->GetZEnd();

      Int_t chID_in, chID_out;
      geoHandler->GlobalToLocal(global_in, local_in, detID);
      chID_in = geoHandler->RecLocalPositionToDetCh(local_in, detID);

      geoHandler->GlobalToLocal(global_out, local_out, detID);
      chID_out = geoHandler->RecLocalPositionToDetCh(local_out, detID);

      // Double_t eLoss = 1e6*curPoint->GetEnergyLoss();// in keV

      if( chID_in > chID_out ) {
        // std::cout << "warning: input position larger than output position\n";
        continue;
      }

      totalHits[chID_in] += 1;

      Double_t point_start = local_in[2];
      Double_t point_stop  = local_out[2];
      Int_t step = chID_out - chID_in + 1;

      Double_t point_low,point_high;
      geoHandler->RecDetChToPosition(chID_in, point_low, point_high);
      Double_t track_len = point_stop - point_start;

      if(chID_out == chID_in){
        h2map_all[chID_in].Fill((point_start - point_low)*10, 1);
        // h2map_relative_position[chID_in].Fill((point_start - point_low)/(point_high - point_low), 1);

        h2map_single[chID_in].Fill((point_start - point_low)*10, 1);

        singleHits[chID_in] += 1;
      }
      else if(step == 2){
        h2map_all[chID_in].Fill((point_start - point_low)*10, (point_high - point_start)/track_len);
        // h2map_relative_position[chID_in].Fill((point_start - point_low)/(point_high - point_low), 1);

        h2map_double[chID_in].Fill((point_start - point_low)*10, (point_high - point_start)/track_len);

        doubleHits[chID_in] += 1;
      }
      else{
        h2map_all[chID_in].Fill((point_start - point_low)*10, (point_high - point_start)/track_len);
        // h2map_relative_position[chID_in].Fill((point_start - point_low)/(point_high - point_low), (point_high - point_start)/track_len);

        h2map_multi[chID_in].Fill((point_start - point_low)*10, (point_high - point_start)/track_len);

        multiHits[chID_in] += 1;
      }
    }
  }
  std::cout<< "Entries: " << entries << std::endl;

  // output
  TString outfilename(point_file);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hDirectory = nullptr;
  hDirectory = getDirectory(fout, hdir.data());
  writeHistos(hDirectory, h2map_all);
  writeHistos(hDirectory, h2map_single);
  writeHistos(hDirectory, h2map_double);
  writeHistos(hDirectory, h2map_multi);

  // hdir = getDirectory(fout, hdir_percentage_relative_position.Data());
  // writeHistos(hdir, h2map_relative_position);

  TString pdfFileName(point_file);
  pdfFileName.ReplaceAll(".root", "_eta.pdf");
  printHistos<TH2D>(h2map_all, pdfFileName.Data());

  // pdfFileName.ReplaceAll(".pdf", "_relative_position.pdf");
  // printHistos<TH2D>(h2map_relative_position, pdfFileName.Data());

  // parameters
  TString textFileName(point_file);
  textFileName.ReplaceAll(".root", "_singleHits_multiHits_counts.txt");

  calcValueContainer<double, std::divides>(singleHits, totalHits, singleFractions);
  calcValueContainer<double, std::divides>(doubleHits, totalHits, doubleFractions);
  calcValueContainer<double, std::divides>(multiHits, totalHits, multiFractions);
  printValueList(outParamters, textFileName.Data());

  //
  delete geoHandler;
  delete fin;
  delete fout;
}
