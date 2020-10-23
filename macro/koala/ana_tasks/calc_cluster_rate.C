using namespace std;

/*
 * Calculate the rates of scalor value from EMS event.
 * The calculation is took place within a event window (based on event entry order),
 * the half size of which is provided by user.
 */

void calc_cluster_rate(const char* infile,
                       const char* outfile,
                       int half_window = 2)
{
  // 1. read the scalor data into buffer
  auto fin = new TFile(infile);
  
  auto tin = (TTree*)fin->Get("ClusterSumCount");
  Long64_t sec, usec;
  std::map<Int_t, Long_t> *sum_counts = nullptr;
  tin->SetBranchAddress("Second", &sec);
  tin->SetBranchAddress("Usecond", &usec);
  tin->SetBranchAddress("ClusterSumCount", &sum_counts);

  vector<map<Int_t, Long_t>> counts;
  vector<Long64_t> secs;
  vector<Long64_t> usecs;
  vector<double> time;

  // 2. retrieve counts into buffer
  auto entries = tin->GetEntries();
  for(auto entry = 0 ; entry<entries; entry++){
    tin->GetEntry(entry);

    //
    time.emplace_back(sec+1.e-6*usec);
    secs.emplace_back(sec);
    usecs.emplace_back(usec);
    counts.emplace_back((*sum_counts));
  }
  cout << "Entries: " << entries << endl;

  // 3. configure the output branch
  auto fout = new TFile(outfile, "update");
  auto tout = new TTree("KOALA_Cluster_Rates", "Rates from KOALA Cluster");

  std::map<Int_t, double> *rates = new std::map<Int_t,double>();
  Long64_t second;
  Long64_t usecond;
  tout->Branch("Second", &second, "Second/L");
  tout->Branch("Usecond", &usecond, "Usecond/L");
  tout->Branch("KOALA_Cluster_Rate", &rates);

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
    rates->clear();

    auto low = get_edge_entry(entry, entries, half_window, true);
    auto high = get_edge_entry(entry, entries, half_window, false);
    auto dt = time[high] - time[low];

    for(auto item: counts[high]) {
      auto rate = (item.second - counts[low][item.first])/dt;
      rates->emplace(item.first, rate);
    }

    second = secs[entry];
    usecond = usecs[entry];

    //
    tout->Fill();
  }

  // 5. write the output
  fout->WriteTObject(tout,"","WriteDelete");

  delete fout;
  delete fin;
}
