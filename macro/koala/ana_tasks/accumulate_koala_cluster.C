void accumulate_koala_cluster(const char* clusterfile,
                              const char* rawdigifile
                              )
{
  auto fcluster = new TFile(clusterfile);
  auto tcluster = (TTree*)fcluster->Get("koalasim");
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster");
  tcluster->SetBranchAddress("KoaRecCluster_Smear", &RecClusters);


  auto fdigi = new TFile(rawdigifile);
  auto tdigi  = (TTree*)fdigi->Get("koalasim");
  tcluster->AddFriend(tdigi);
  KoaRawEvent* raw_evt = nullptr;
  tdigi->SetBranchAddress("KoaRawEvent", &raw_evt);

  //
  TString outfile(clusterfile);
  outfile.ReplaceAll(".root", "_counts.root");
  auto fout = new TFile(outfile,"update");
  auto tout = new TTree("ClusterSumCount", "Sum of KOALA Cluster Counts based on Timestamp");

  Long64_t sec, usec;
  std::map<Int_t, Long_t> *sum_counts = new std::map<Int_t, Long_t>();
  tout->Branch("Second", &sec, "Second/L");
  tout->Branch("Usecond", &usec, "Usecond/L");
  tout->Branch("ClusterSumCount", &sum_counts);

  //
  bool first = false;
  Long64_t sec_cur, usec_cur;
  std::map<Int_t, Long_t> prev_counts, cur_counts;

  auto encoder = KoaMapEncoder::Instance();
  auto ChIDs = encoder->GetRecChIDs();
  for(auto item: ChIDs){
    cur_counts.emplace(item, 0);
  }

  //
  auto entries = tcluster->GetEntriesFast();
  for(auto entry = 0; entry < entries; entry++){
    tcluster->GetEntry(entry);

    //
    Int_t clusters = RecClusters->GetEntriesFast();
    for (int i=0;i<clusters;i++){
      KoaRecCluster* cluster = (KoaRecCluster*)RecClusters->At(i);
      auto id = cluster->GetFirstChId();
      cur_counts[id]++;
    }

    //
    sec_cur = raw_evt->Second;
    usec_cur = raw_evt->Usecond;

    if(!first) {
      sec = sec_cur;
      usec = usec_cur;
      first = true;
    }

    if( sec_cur != sec || usec_cur != usec ){
      (*sum_counts) = prev_counts;
      tout->Fill();

      sec = sec_cur;
      usec= usec_cur;
    }

    //
    prev_counts = cur_counts;
  }
  std::cout << entries << " events processed" << std::endl;

  //
  fout->WriteTObject(tout, "", "WriteDelete");

  delete fcluster, fdigi, fout;
}
