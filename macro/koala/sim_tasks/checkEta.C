#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

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
  TString hname_percentage = "eta_percentage";
  TString htitle_percentage = "MCPoint: FirstHit Energy Fraction VS Hit Position in FirstHit Channel";
  TString hdir_percentage = "mcpoint_eta_percentage";

  auto h2map_percentage = bookH2dByChannelId(hname_percentage.Data(),
                                             htitle_percentage.Data(),
                                             100, -0.1, 4.9,
                                             102, -0.01, 1.01,
                                             true);
  TString hname_percentage_relative_position = "eta_percentage_relative_position";
  TString htitle_percentage_relative_position = "MCPoint: FirstHit Energy Fraction VS Relative Hit Position in FirstHit Channel";
  TString hdir_percentage_relative_position = "mcpoint_eta_percentage_relative_position";

  auto h2map_percentage_relative_position = bookH2dByChannelId(hname_percentage_relative_position.Data(),
                                                               htitle_percentage_relative_position.Data(),
                                                               102, -0.01, 1.01,
                                                               102, -0.01, 1.01,
                                                               true);
  // out parameters
  ParameterList<double> outParamters;
  auto& totalHits = addValueContainer(outParamters, "TotalHit");
  auto& singleHits = addValueContainer(outParamters, "SingleHit");
  auto& multiHits = addValueContainer(outParamters, "MultiHit");
  auto& singleFractions = addValueContainer(outParamters, "SingleHit(%)");

  auto encoder = KoaMapEncoder::Instance();
  auto ChIDs = encoder->GetRecChIDs();
  for(auto id: ChIDs){
    totalHits[id] = 0;
    singleHits[id] = 0;
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

      Double_t point_low,point_high;
      geoHandler->RecDetChToPosition(chID_in, point_low, point_high);
      Double_t track_len = point_stop - point_start;

      if(chID_out == chID_in){
        h2map_percentage[chID_in].Fill((point_start - point_low)*10, 1);
        h2map_percentage_relative_position[chID_in].Fill((point_start - point_low)/(point_high - point_low), 1);

        singleHits[chID_in] += 1;
      }
      else{
        h2map_percentage[chID_in].Fill((point_start - point_low)*10, (point_high - point_start)/track_len);
        h2map_percentage_relative_position[chID_in].Fill((point_start - point_low)/(point_high - point_low), (point_high - point_start)/track_len);

        multiHits[chID_in] += 1;
      }
    }
  }
  std::cout<< "Entries: " << entries << std::endl;

  // output
  TString outfilename(point_file);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hdir = nullptr;
  hdir = getDirectory(fout, hdir_percentage.Data());
  writeHistos(hdir, h2map_percentage);

  hdir = getDirectory(fout, hdir_percentage_relative_position.Data());
  writeHistos(hdir, h2map_percentage_relative_position);

  TString pdfFileName(point_file);
  pdfFileName.ReplaceAll(".root", "_eta.pdf");
  printHistos<TH2D>(h2map_percentage, pdfFileName.Data());

  pdfFileName.ReplaceAll(".pdf", "_relative_position.pdf");
  printHistos<TH2D>(h2map_percentage_relative_position, pdfFileName.Data());

  // parameters
  TString textFileName(point_file);
  textFileName.ReplaceAll(".root", "_singleHits_multiHits_counts.txt");

  calcValueContainer<double, std::divides>(singleHits, totalHits, singleFractions);
  printValueList(outParamters, textFileName.Data());

  //
  delete geoHandler;
  delete fin;
  delete fout;
}
