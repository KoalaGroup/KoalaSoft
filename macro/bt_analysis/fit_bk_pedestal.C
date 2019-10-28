void fit_bk_pedestal(const char* infile, const char* outfile, bool useMT = false)
{
  if(useMT)
    ROOT::EnableImplicitMT(6);

  // timer
  TStopwatch timer;

  // include lambdas
  #include "fit_bk_pedestal_lambda.C"

  // book histograms
  book_hist1D();

  // mt tree processor
  ROOT::TTreeProcessorMT tp(infile, "KoalaEvent");
  tp.Process(fillhist);

  // finish
  write_hist1D(outfile, "histograms");

  // 
  timer.Stop();
  timer.Print();
}
