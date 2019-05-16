void testSegmentation(const char *filename)
{
  // sensor_edge[i][j], index i represents Sensor from Si1, Si2, Ge1 to Ge2
  // index j represents the edge from -z, +z, -y, +y
  // Based on the build_geom.C on 09.05.2019
  Double_t sensor_edge_minusz[4]={-2.64,2.61,9.175,16.035};
  Double_t sensor_edge_minusy[4]={-5.675,0.675,-5.675,0.675};

  Double_t sensor_edge[4][4]={
    {sensor_edge_minusz[0],sensor_edge_minusz[0]+7.68,sensor_edge_minusy[0],sensor_edge_minusy[0]+5}
    {sensor_edge_minusz[1],sensor_edge_minusz[1]+7.68,sensor_edge_minusy[1],sensor_edge_minusy[1]+5}
    {sensor_edge_minusz[2],sensor_edge_minusz[2]+8.04,sensor_edge_minusy[2],sensor_edge_minusy[2]+5}
    {sensor_edge_minusz[3],sensor_edge_minusz[3]+8.04,sensor_edge_minusy[3],sensor_edge_minusy[3]+5}
  }; // [cm]
  Double_t sensor_thickness[4]={0.1,0.1,0.5,1.1}; // [cm]
  Double_t sensor_distance=101.096; // [cm]

  // strip merging
  Double_t strip_width=0.12; // [cm]
  //////////
  TFile* f = new TFile(filename);
  TTree* tree = (TTree*)f->Get("cbmsim");
  TClonesArray* RecPoints = new TClonesArray("KoaRecPoint");
  tree->SetBranchAddress("KoaRecPoint",&RecPoints);

  Int_t entries = tree->GetEntries();
  // for(int id=0;id<entries;id++){
  for(int id=0;id<1;id++){
    tree->GetEntry(id);
    Int_t recHits = RecPoints->GetEntriesFast();
    if(recHits>0){
      for(int i=0;i<recHits;i++){
        KoaRecPoint* recpoint = (KoaRecPoint*)RecPoints->At(i);
        recpoint->Print();
      }
    }
  }
}
