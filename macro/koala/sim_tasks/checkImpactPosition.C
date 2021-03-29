#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void checkImpactPosition(const char* point_file,
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
  TString hname_pos = "hit_position";
  TString htitle_pos = "MCPoint Impact Position;Z (mm);Y (mm)";
  TString hdir_pos = "mcpoint_hit_position";

  auto h2map_pos_all = bookH2dByChannelId(hname_pos.Data(),
                                          htitle_pos.Data(),
                                          100, -0.1, 4.9,
                                          102, 25.5, 25.5,
                                          true);

  auto h2map_pos_single = bookH2dByChannelId(Form("%s_single", hname_pos.Data()),
                                             htitle_pos.Prepend("(SingleHit)").Data(),
                                             100, -0.1, 4.9,
                                             102, 25.5, 25.5,
                                             true);

  auto h2map_pos_double = bookH2dByChannelId(Form("%s_double", hname_pos.Data()),
                                             htitle_pos.Prepend("(DoubleHit)").Data(),
                                             100, -0.1, 4.9,
                                             102, 25.5, 25.5,
                                             true);

  auto h2map_pos_multi = bookH2dByChannelId(Form("%s_multi", hname_pos.Data()),
                                            htitle_pos.Prepend("(MultiHit)").Data(),
                                            100, -0.1, 4.9,
                                            102, 25.5, 25.5,
                                            true);

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

      Double_t point_start = local_in[2];
      Double_t point_stop  = local_out[2];
      Int_t step = chID_out - chID_in + 1;

      Double_t point_low,point_high;
      geoHandler->RecDetChToPosition(chID_in, point_low, point_high);
      Double_t track_len = point_stop - point_start;

      h2map_pos_all[chID_in].Fill((point_start - point_low)*10, local_in[1]*10);
      if(chID_out == chID_in){
        h2map_pos_single[chID_in].Fill((point_start - point_low)*10, local_in[1]*10);
      }
      else if(step == 2){
        h2map_pos_double[chID_in].Fill((point_start - point_low)*10, local_in[1]*10);
      }
      else{
        h2map_pos_multi[chID_in].Fill((point_start - point_low)*10, local_in[1]*10);
      }
    }
  }
  std::cout<< "Entries: " << entries << std::endl;

  // output
  TString outfilename(point_file);
  outfilename.ReplaceAll(".root","_result.root");
  TFile *fout = new TFile(outfilename.Data(), "update");

  TDirectory* hDirectory = nullptr;
  hDirectory = getDirectory(fout, hdir_pos.Data());
  writeHistos(hDirectory, h2map_pos_all);
  writeHistos(hDirectory, h2map_pos_single);
  writeHistos(hDirectory, h2map_pos_double);
  writeHistos(hDirectory, h2map_pos_multi);

  TString pdfFileName(point_file);
  pdfFileName.ReplaceAll(".root", "_singlehit_position.pdf");
  printHistos<TH2D>(h2map_pos_single, pdfFileName.Data());

  //
  delete geoHandler;
  delete fin;
  delete fout;
}
