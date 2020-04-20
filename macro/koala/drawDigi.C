void drawDigi(const char* filename,  const char* branchName, const char* prefix)
{
  TH1::AddDirectory(false);

  // timer
  TStopwatch timer;
  
  //
  using integers = ROOT::VecOps::RVec<Int_t>;
  using doubles  = ROOT::VecOps::RVec<Double_t>;
  using histo1d = std::map<Int_t, TH1D>;
  using histo2d = std::map<Int_t, TH2D>;

  // parameters
  Int_t nbin=2000;// in keV
  Float_t xlow=0,xhigh=20000;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  Int_t RecIdRange[2];
  encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  // histograms definition
  histo2d h2map_EnergyVsPosition;
  for(auto id: ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EvsX_%s",encoder->DetectorIDToVolName(id)),Form("h2_EvsX_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto& id: ChIDs){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_%s_%s_%d",prefix, volName.Data(), ch_id+1), Form("h1_energy_%s_%s_%d",prefix, volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
  }

  // input
  TFile* f = new TFile(filename,"update");
  TTree* tree = (TTree*)f->Get("koalasim");
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress(branchName, &RecDigis);

  // event loop
  Long_t entries;
  entries = tree->GetEntries();

  Int_t det_id, ch_id, id;
  Double_t charge;
  Double_t timestamp;

  for(auto entry=0;entry<entries;entry++){
    tree->GetEntry(entry);

    //
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      // rec digis
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      charge = digi->GetCharge(); // keV
      h2map_EnergyVsPosition[det_id].Fill(ch_id+1, charge);
      h1map_Energy[id].Fill(charge);
    }
  }
  cout << "EventNr processed : "<< entries << endl;

  // output
  // output file
  TString outfilename(filename);
  outfilename.ReplaceAll(".root","");
  outfilename.Append("_result.root");
  TFile *fout = new TFile(outfilename.Data(),"update");

  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  hdir->cd();
  for (auto & hist : h2map_EnergyVsPosition ) {
    hist.second.Write(0, TObject::kOverwrite);
  }
  for (auto & hist : h1map_Energy ) {
    hist.second.Write(0, TObject::kOverwrite);
  }

  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}
