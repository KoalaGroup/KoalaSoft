#include "KoaHistUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void compareDigiWithCalculation(const char* filename, const char* branchName, const char* prefix,
                                double beam_energy, const char* geoFile)
{
  // timer
  TStopwatch timer;

  // global z position of strip
  auto geoHandler = getGeometryHandler(geoFile);
  Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));

  // elastic calculator
  KoaElasticCalculator calculator(beam_energy);
  calculator.SetRecDistance(recoil_distance);

  // map encoder
  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  // std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  // Int_t RecIdRange[2];
  // encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  // histograms definition
  atuo h1map_normalized = bookH1dByChId("normalized_energy","Energy normalized to calculated value",
                             1300, -0.1, 1.2);

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(branchName, &RecDigis);

  // other variables
  Int_t det_id, ch_id, id;
  Double_t charge;
  Double_t timestamp;

  Double_t pos_low, pos_high, pos_center;
  Double_t global_pos[3] = {0};
  Double_t local_pos[3] = {0};

  // event loop
  auto entries = tree->GetEntries();
  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    //
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      // rec digis
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      charge = digi->GetCharge()/1000.; // MeV

      ch_id = encoder->DecodeChannelID(id, det_id);

    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  // outfilename.ReplaceAll("_digi.root","");
  outfilename.Append("_result.root");
  // outfilename.Append(Form("_%s_result.root",prefix));
  TFile *fout = new TFile(outfilename.Data(),"recreate");

  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  hdir->cd();
  for (auto & hist : h2map_EnergyVsPosition ) {
    hist.second.Write(0, TObject::kOverwrite);
  }
  for (auto & hist : h1map ) {
    hist.second.Write(0, TObject::kOverwrite);
  }

  delete f;
  delete fout;
  delete geoHandler;

  // timer stat
  timer.Stop();
  timer.Print();
}
