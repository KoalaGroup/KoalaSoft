using namespace std;

void calc_rate(const char* infile,
               const char* outfile,
               int half_window = 2)
{
  // 1. read the scalor data into buffer
  auto fin = new TFile(infile);
  
  auto tin = (TTree*)fin->Get("Ems");
  KoaEmsRawEvent *ems = nullptr;
  tin->SetBranchAddress("KoaEmsRawEvent", &ems);

  vector<array<UInt_t, 32>> scalor;
  vector<Long64_t> sec;
  vector<Long64_t> usec;
  vector<double> time;

  auto entries = tin->GetEntries();
  for(auto entry = 0 ; entry<entries; entry++){
    tin->GetEntry(entry);

    scalor.emplace_back();
    for(int i = 0; i<32; i++){
      scalor[entry][i] = ems->Scalor[i];
    }
    time.emplace_back(ems->Second+1.e-6*ems->Usecond);
    sec.emplace_back(ems->Second);
    usec.emplace_back(ems->Usecond);
  }
  cout << "Entries: " << entries << endl;

  // 2. Retrieve the scalor channel mapping
  map<string,int>* ScalorChMap = nullptr;
  fin->GetObject("ScalorChMap", ScalorChMap);

  // 3. configure the output branch
  auto fout = new TFile(outfile, "recreate");
  auto tout = new TTree("Rates", "Rates from EMS scalor");

  double rate[32];
  Long64_t second;
  Long64_t usecond;
  tout->Branch("Second", &second, "Second/L");
  tout->Branch("Usecond", &second, "Usecond/L");
  for(auto it = ScalorChMap->begin(); it != ScalorChMap->end(); it++) {
    tout->Branch(Form("%s_Rate",it->first.data()), rate+it->second, Form("%s_Rate/d",it->first.data()));
  }

  double fwd_InOut_ratio, fwd_UpDown_ratio, daq_efficiency;
  tout->Branch("Fwd_InOut_Ratio", &fwd_InOut_ratio, "Fwd_InOut_Ratio/d");
  tout->Branch("Fwd_UpDown_Ratio", &fwd_UpDown_ratio, "Fwd_UpDown_Ratio/d");
  tout->Branch("DAQ_Efficiency", &daq_efficiency, "DAQ_Efficiency/d");

  // 4. calculate the rate in the event window [-half_window-current, half_window+current]
  auto get_edge_entry = [&](long current, long total, int half = 2, bool decrease_order = false) -> long
                        {
                          long edge;
                          if(decrease_order) {
                            edge = current - half;
                            while(edge<0) edge++;

                            for(edge;edge<current;edge++){
                              if((time[current]-time[edge]) < 2)// edge not in cycle interval
                                break;
                            }
                          }
                          else{
                            edge = current + half;
                            while(edge>=total) edge--;

                            for(edge;edge>current;edge--){
                              if((time[edge]-time[current]) < 2)// edge not in cycle interval
                                break;
                            }
                          }
                          return edge;
                        };

  for(auto entry = 0 ; entry<entries; entry++){
    auto low = get_edge_entry(entry, entries, half_window, true);
    auto high = get_edge_entry(entry, entries, half_window, false);
    auto dt = time[high] - time[low];

    for(auto it = ScalorChMap->begin(); it != ScalorChMap->end(); it++) {
      rate[it->second] = (scalor[high][it->second] - scalor[low][it->second])/dt;
    }

    second = sec[entry];
    usecond = usec[entry];

    fwd_InOut_ratio = rate[(*ScalorChMap)["Fwd_Inside"]]/rate[( *ScalorChMap )["Fwd_Outside"]];
    fwd_UpDown_ratio = rate[( *ScalorChMap )["Fwd_Up"]]/rate[( *ScalorChMap )["Fwd_Down"]];
    daq_efficiency = rate[( *ScalorChMap )["Trigger"]]/rate[( *ScalorChMap )["CommonOR"]];

    //
    tout->Fill();
  }

  // 5. write the output
  fout->WriteTObject(tout,"","Delete");

  delete fout;
  delete fin;
}
