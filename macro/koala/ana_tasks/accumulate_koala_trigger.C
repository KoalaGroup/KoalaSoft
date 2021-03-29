void accumulate_koala_trigger(const char* trigger_file)
{
  auto fin = new TFile(trigger_file);

  auto tin = (TTree*)fin->Get("koalasim");
  std::map<Int_t, Long_t>* trig_counts = nullptr;
  tin->SetBranchAddress("TriggerCount", &trig_counts);
  KoaAnaTrigger::TimeStruct *time = nullptr;
  tin->SetBranchAddress("Timestamp",&time);

  // output
  TString outfile(trigger_file);
  outfile.ReplaceAll("_Trigger.root", "_TriggerSumCount.root");
  auto fout = new TFile(outfile.Data(), "recreate");
  auto tout = new TTree("TriggerSumCount", "Sum of KOALA Trigger Counts based on Timestamp");

  Long64_t sec, usec;
  tout->Branch("Second", &sec, "Second/L");
  tout->Branch("Usecond", &usec, "Usecond/L");
  std::map<Int_t, Long_t> *sum_counts = new std::map<Int_t, Long_t>();
  tout->Branch("TriggerSumCount", &sum_counts);

  //
  bool first = false;
  Long64_t sec_cur, usec_cur;
  std::map<Int_t, Long_t> prev_counts;

  auto entries = tin->GetEntriesFast();
  for(auto entry = 0; entry < entries; entry++){
    tin->GetEntry(entry);

    //
    sec_cur = time->Second;
    usec_cur = time->Usecond;

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
    prev_counts = (*trig_counts);
  }
  std::cout << entries << " events processed" << std::endl;

  //
  fout->WriteTObject(tout, "", "Delete");

  delete sum_counts;
  delete fin, fout;
}
