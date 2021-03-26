#include "KoaGraphUtility.h"
#include "KoaUtility.h"

using namespace KoaUtility;

void fitGraph(const char* inFileName)
{
  // timer start
  TStopwatch timer;
  
  // get graphs
  TFile *fin = new TFile(inFileName, "update");

  TDirectory* gdir = nullptr;
  gdir = getDirectory(fin, "time_walk");

  auto gmap_timewalk = getGraphsByRecTdcChannelId(gdir, "timewalk");

  // define fit parameter container
  ParameterList<double> fitParameters;

  // fit func form: p0/x + p1
  auto& p0 = addValueContainer(fitParameters, "p0");
  auto& p1 = addValueContainer(fitParameters, "p1");
  auto& p0_err = addValueContainer(fitParameters, "err(p0)");
  auto& p1_err = addValueContainer(fitParameters, "err(p1)");
  auto& chi2_ndf = addValueContainer(fitParameters, "chi2/ndf");

  // fit and fetch result
  auto fitGraph = [] (TGraph* gr) -> TF1*
                  {
                    TF1* func_timewalk = new TF1("ftimewalk", "[0]/x+[1]", 100, 7000);

                    // fit
                    func_timewalk->SetParameter(0, -1);
                    func_timewalk->SetParameter(1, 1500);

                    gr->Fit(func_timewalk, "RQ");
                    func_timewalk->SetLineColor(kRed);
                    // func_timewalk->ResetBit(1<<9);

                    return func_timewalk;
                  };

  for(auto gr_timewalk : gmap_timewalk) {
    auto id = gr_timewalk.first;
    auto graph = gr_timewalk.second;

    auto f1 = fitGraph(graph);
    p0.emplace(id, f1->GetParameter(0));
    p1.emplace(id, f1->GetParameter(1));
    p0_err.emplace(id, f1->GetParError(0));
    p1_err.emplace(id, f1->GetParError(1));
    chi2_ndf.emplace(id, f1->GetChisquare()/f1->GetNDF());
  }

  // output
  TString outTxt(inFileName);
  outTxt.ReplaceAll(".root", ".txt");
  printValueList<double>(fitParameters, outTxt.Data());

  TString outPdf(inFileName);
  outPdf.ReplaceAll(".root", ".pdf");
  printGraphs(gmap_timewalk,outPdf.Data());

  gdir = getDirectory(fin, "time_walk_fit");
  writeGraphs(gdir, gmap_timewalk, "Overwrite");

  // clean up
  delete fin;

  // timer stat
  timer.Stop();
  timer.Print();

  return;
}
