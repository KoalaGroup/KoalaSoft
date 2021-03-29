void cluster(const char* filename, const char* treename)
{
  // timer
  TStopwatch timer;

  // input
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get(treename);
  TClonesArray* RecDigis = new TClonesArray("KoaRecDigi");
  tree->SetBranchAddress("KoaRecDigi",&RecDigis);


  TString foutname(filename);
  foutname.ReplaceAll("_calib.root","_cluster.root");
  TFile* fout=new TFile(foutname.Data(),"recreate");
  TTree* tout=new TTree("KoalaClusterEvent","Koala Cluster Event");
  TClonesArray* RecClusters = new TClonesArray("KoaRecCluster",10);
  tout->Branch("KoaRecCluster", &RecClusters);

  // Loop
  Int_t det_id, ch_id, id;
  Long64_t entries = tree->GetEntries();
  KoaMapEncoder *encoder = KoaMapEncoder::Instance();
  for(int entry=0;entry<entries;entry++){
    //
    tree->GetEntry(entry);

    //
    RecClusters->Clear();
    
    //
    Int_t index = 0;
    TClonesArray& RecClusterCol = *RecClusters;

    Int_t digis=RecDigis->GetEntriesFast();
    KoaRecCluster * rec_cluster = nullptr;
    if ( digis > 0 ) {
      KoaRecDigi* thedigi=(KoaRecDigi*)RecDigis->At(0);
      ch_id = encoder->DecodeChannelID(thedigi->GetDetID(), det_id);
      rec_cluster = new (RecClusterCol[index++]) KoaRecCluster(det_id);
      rec_cluster->AddDigi(thedigi);

      for(int i=1;i<digis;i++){
        KoaRecDigi* digi=(KoaRecDigi*)RecDigis->At(i);
        if( !rec_cluster->isInCluster( digi ) ) {
          ch_id = encoder->DecodeChannelID(digi->GetDetID(), det_id);
          rec_cluster = new (RecClusterCol[index++]) KoaRecCluster(det_id);
        }
        rec_cluster->AddDigi(digi);
      }
    }

    //
    tout->Fill();
  }

  fout->cd();
  tout->Write(0, TObject::kOverwrite);

  //
  delete f;
  delete fout;

  //
  timer.Stop();
  timer.Print();
}
