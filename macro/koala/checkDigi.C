void checkDigi(const char* filename, bool isSimulation,  const char* treename,
               bool useList = true, const char* listName = "fwdhit_elist")
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
  Int_t nbin=7000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  Int_t RecIdRange[2];
  encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  // histograms definition
  histo2d h2map_EnergyVsPosition;
  for(auto id: ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto& id: ChIDs){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy_cut;
  std::vector<Int_t> TdcChIds = encoder->GetRecTdcChIDs();
  for(auto& id: TdcChIds){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_cut_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_cut_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy_cut.emplace(std::piecewise_construct, tindex, thist);
  }

  // input
  TFile* f = new TFile(filename,"update");
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress("KoaRecDigi",&RecDigis);
  TClonesArray* FwdDigis = new TClonesArray("KoaFwdDigi");
  tree->SetBranchAddress("KoaFwdDigi",&FwdDigis);

  Bool_t isCoin = false;
  TBranch *br_coin;
  if (!useList){
    br_coin = tree->Branch("isCoin", &isCoin, "isCoin/O");
  }

  // output/input entry list 
  TDirectory *edir;
  if(!(edir=f->GetDirectory("elists")))
    edir = f->mkdir("elists");

  TEntryList *cutlist;
  TEntryList *elist;
  if (useList) {
    edir->GetObject(listName, cutlist);
    if(!cutlist){
      std::cout << "Error: no list found in file: " << filename << std::endl;
      return;
    }

    tree->SetEntryList(cutlist);
  }
  else {
    elist = new TEntryList("fwdhit_elist","Events hitting coincidence area");
    elist->SetTree(tree);
    elist->SetDirectory(edir);
  }

  // event loop
  Int_t entries;
  if(useList){
    entries = cutlist->GetN();
  }
  else{
    entries = tree->GetEntries();
  }

  Int_t det_id, ch_id, id;
  Double_t charge;
  Double_t timestamp;

  std::map<Int_t, Double_t> fwd_time;
  std::map<Int_t, Double_t> fwd_amp;
  Int_t fwd_low, fwd_high;
  encoder->GetFwdDetIDRange(fwd_low, fwd_high);
  Int_t index0 = encoder->EncodeChannelID(fwd_low, 0);
  Int_t index1 = encoder->EncodeChannelID(fwd_low+1, 0);
  for(int entry=0;entry<entries;entry++){
    if(useList) {
      Int_t entrynum = tree->GetEntryNumber(entry);
      tree->GetEntry(entrynum);
      // if( !cutlist->Contains(entrynum) ){
      //   std::cout << "Not contained in entrylist" << std::endl;
      // }
      // else{
      //   std::cout << "Contained" << std::endl;
      // }
    }
    else{
      tree->GetEntry(entry);
      isCoin = false;
    }

    // fwd digis
    Int_t fwddigis = FwdDigis->GetEntriesFast();
    for (int i=0;i<fwddigis;i++){
      KoaFwdDigi* digi = (KoaFwdDigi*)FwdDigis->At(i);
      id = digi->GetDetID();
      fwd_time[id] = digi->GetTimeStamp();
      fwd_amp[id]  = digi->GetCharge();
    }

    //
    Int_t digis=RecDigis->GetEntriesFast();
    for(int i=0;i<digis;i++){
      // rec digis
      KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
      id = digi->GetDetID();
      ch_id = encoder->DecodeChannelID(id, det_id);

      if (isSimulation) {
        charge = 1000*digi->GetCharge();
      }
      else {
        charge = digi->GetCharge()/1000.;
      }

      h2map_EnergyVsPosition[det_id].Fill(ch_id+1, charge);
      h1map_Energy[id].Fill(charge);

      //
      if ( digi->GetTimeStamp() > 0) {
        if ( fwd_amp[index0] > 1000 && fwd_amp[index1] > 1000
             && (fwd_time[index0]-fwd_time[index1]) < 10
             && (fwd_time[index0]-fwd_time[index1]) > -10) {

          h1map_Energy_cut[id].Fill(charge);

          if (!useList){
            elist->Enter(entry);
            isCoin = true;
          }
        }
      }
    }

    if(!useList) {
      br_coin->Fill();
    }

    fwd_time.clear();
    fwd_amp.clear();
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
  for (auto & hist : h1map_Energy_cut ) {
    hist.second.Write(0, TObject::kOverwrite);
  }

  //
  if(!useList){
    edir->cd();
    elist->Write(0, TObject::kOverwrite);
  }

  //
  if(!useList){
    f->cd();
    tree->Write();
  }
  delete f;
  delete fout;

  // timer stat
  timer.Stop();
  timer.Print();
}

// DataFrame + Threaded Histogram + IMT
void checkDigi_rdf_threaded(const char* infile, bool isSimulation, const char* treename)
{
  // switches
  ROOT::EnableImplicitMT(6);
  // ROOT::GeImplicitMTPoolSize();
  TH1::AddDirectory(false);

  // timer start
  TStopwatch timer;
  // timer.Start();

  //
  using integers = ROOT::VecOps::RVec<Int_t>;
  using doubles  = ROOT::VecOps::RVec<Double_t>;
  using histo1d = std::map<Int_t, ROOT::TThreadedObject<TH1D>>;
  using histo2d = std::map<Int_t, ROOT::TThreadedObject<TH2D>>;

  // book histograms
  Int_t nbin=14000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  Int_t RecIdRange[2]; encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  histo2d h2map_EnergyVsPosition;
  for(auto id: ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto& id: ChIDs){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
    it.first->second->GetName();//lazy init, make sure histogram is constructed
  }

  // define lambda
  auto fillhist = [&] (integers ids, doubles charges){
    charges*=1000;

    const auto size = ids.size();
    // for(const auto& id: ids){
    // for(size_t i=0;i<size;i++){
    for(auto i: ROOT::TSeqI(size)){
      Int_t det_id, ch_id;
      Double_t charge;
      Double_t timestamp;
      
      ch_id = encoder->DecodeChannelID(ids[i], det_id);
      if ( isSimulation ) {
        charge = charges[i]*1000;
      }
      else {
        charge = charges[i]/1000.;
      }

      h2map_EnergyVsPosition[det_id]->Fill(ch_id+1, charge);
      h1map_Energy[ids[i]]->Fill(charge);
    }
  };

  // rdf process
  ROOT::RDataFrame rdf(treename, infile);
  rdf.Foreach(fillhist,{"KoaRecDigi.fDetID","KoaRecDigi.fCharge"});

  // write histograms
  auto fout=TFile::Open(infile,"update");
  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  for(auto& hist: h2map_EnergyVsPosition){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }
  for(auto& hist: h1map_Energy){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }

  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
  
}

// TTreeProcessorMT + Threaded Histogram
void checkDigi_processtree_threaded(const char* infile, bool isSimulation, const char* treename)
{
  // switches
  ROOT::EnableImplicitMT(6);
  // ROOT::GeImplicitMTPoolSize();
  TH1::AddDirectory(false);

  // timer start
  TStopwatch timer;
  // timer.Start();

  //
  using integers = ROOT::VecOps::RVec<Int_t>;
  using doubles  = ROOT::VecOps::RVec<Double_t>;
  using histo1d = std::map<Int_t, ROOT::TThreadedObject<TH1D>>;
  using histo2d = std::map<Int_t, ROOT::TThreadedObject<TH2D>>;

  // book histograms
  Int_t nbin=14000;
  Float_t xlow=0,xhigh=70;

  KoaMapEncoder* encoder = KoaMapEncoder::Instance();
  std::vector<Int_t> ChIDs = encoder->GetRecChIDs();
  Int_t RecIdRange[2]; encoder->GetRecDetIDRange(RecIdRange[0], RecIdRange[1]);

  histo2d h2map_EnergyVsPosition;
  for(auto id: ROOT::TSeqI(RecIdRange[0],RecIdRange[1]+1)){
    Int_t ChNr = encoder->GetChNr(id);
    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)),Form("h2_EnergyVsPosition_%s",encoder->DetectorIDToVolName(id)), ChNr, 0.5, 0.5+ChNr, nbin, xlow,xhigh);
    h2map_EnergyVsPosition.emplace(std::piecewise_construct, tindex, thist);
  }

  histo1d h1map_Energy;
  for(auto& id: ChIDs){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy.emplace(std::piecewise_construct, tindex, thist);
    it.first->second->GetName();//lazy init, make sure histogram is constructed
  }

  histo1d h1map_Energy_cut;
  std::vector<Int_t> TdcChIds = encoder->GetRecTdcChIDs();
  for(auto& id: TdcChIds){
    TString volName; Int_t ch_id = encoder->DecodeChannelID(id, volName);

    auto tindex = std::make_tuple(id);
    auto thist  = std::make_tuple(Form("h1_energy_cut_%s_%d",volName.Data(), ch_id+1), Form("h1_energy_cut_%s_%d",volName.Data(), ch_id+1), nbin, xlow, xhigh);
    auto it = h1map_Energy_cut.emplace(std::piecewise_construct, tindex, thist);
    it.first->second->GetName();//lazy init, make sure histogram is constructed
  }

  // define lambda
  auto fillhist = [&] (TTreeReader &myreader){
    TTreeReaderArray<KoaRecDigi> digis(myreader, "KoaRecDigi");
    TTreeReaderArray<KoaFwdDigi> fwddigis(myreader, "KoaFwdDigi");

    Int_t det_id, ch_id, id;
    Double_t charge;
    Double_t fwd_time[2], fwd_amp[2];
    while(myreader.Next()){
      // fwd digis
      for(int index=0;index<2;index++){
        fwd_time[index] = fwddigis[index].GetTimeStamp();
        fwd_amp[index]  = fwddigis[index].GetCharge();
      }

      // rec digis
      for(auto&& digi: digis){
        id=digi.GetDetID();
        ch_id = encoder->DecodeChannelID(id, det_id);
        if ( isSimulation ) {
          charge = 1000*digi.GetCharge();
        }
        else {
          charge = digi.GetCharge() / 1000.;
        }

        h2map_EnergyVsPosition[det_id]->Fill(ch_id+1, charge);
        h1map_Energy[id]->Fill(charge);

        //
        if ( digi.GetTimeStamp() > 0 ) {
          if ( fwd_amp[0] > 1000 && fwd_amp[1] > 1000
               && (fwd_time[0]-fwd_time[1]) < 10
               && (fwd_time[0]-fwd_time[1]) > -10) {

            h1map_Energy_cut[id]->Fill(charge);
          }
        }
      }
    }
  };

  // rdf process
  ROOT::TTreeProcessorMT tp(infile, treename);
  tp.Process(fillhist);

  // write histograms
  auto fout=TFile::Open(infile,"update");
  TDirectory* hdir;
  if(!(hdir=fout->GetDirectory("histograms")))
    hdir = fout->mkdir("histograms");

  for(auto& hist: h2map_EnergyVsPosition){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }
  for(auto& hist: h1map_Energy){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }
  for(auto& hist: h1map_Energy_cut){
    auto sumed = hist.second.Merge();
    sumed->Print();
    hdir->WriteTObject(sumed.get(),"","WriteDelete");
  }

  delete fout;

  // timer stop
  timer.Stop();
  timer.Print();
  
}
