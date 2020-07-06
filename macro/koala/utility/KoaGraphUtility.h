#ifndef KOAGRAPHUTILITY_H
#define KOAGRAPHUTILITY_H

namespace KoaUtility
{
  using Graphs = std::map<int, TGraphErrors>;
  using GraphPtrs = std::map<int, TGraph*>;

  // book graphs by channel id
  Graphs bookGraphByChannelId(const char *gName, const char *gTitle,
                              int markerColor=kBlack, int markerStyle=8,
                              bool IsRec = true
                              )
  {
    Graphs graphs;

    KoaMapEncoder *encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs;

    if (IsRec) {
      ChIDs = encoder->GetRecChIDs();
    } else {
      ChIDs = encoder->GetFwdChIDs();
    }

    for (auto &ChID : ChIDs) {
      TString volName;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");

      graphs.emplace(std::piecewise_construct,
                     std::forward_as_tuple(ChID),
                     std::forward_as_tuple());

      graphs[ChID].SetName(Form("gr_%s_%s_%d", volName.Data(), gName, ch + 1));
      graphs[ChID].SetTitle(Form("%s_%d: %s", volName.Data(), ch + 1, gTitle));
      graphs[ChID].SetMarkerColor(markerColor);
      graphs[ChID].SetMarkerStyle(markerStyle);
      graphs[ChID].SetMarkerSize(1.2);
    }

    return graphs;
  }

  // book graphs by rec channels with tdc connection
  Graphs bookGraphByRecTdcChannelId(const char *gName, const char *gTitle,
                                    int markerColor=kBlack, int markerStyle=8
                                    )
  {
    Graphs graphs;

    KoaMapEncoder *encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecTdcChIDs();

    for (auto &ChID : ChIDs) {
      TString volName;
      Int_t ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");

      graphs.emplace(std::piecewise_construct,
                     std::forward_as_tuple(ChID),
                     std::forward_as_tuple());

      graphs[ChID].SetName(Form("gr_%s_%s_%d", volName.Data(), gName, ch + 1));
      graphs[ChID].SetTitle(Form("%s_%d: %s", volName.Data(), ch + 1, gTitle));
      graphs[ChID].SetMarkerColor(markerColor);
      graphs[ChID].SetMarkerStyle(markerStyle);
      graphs[ChID].SetMarkerSize(1.2);
    }

    return graphs;
  }

  // book graphs by sensor id
  GraphPtrs bookGraphByRecDetectorId(const char *gName, const char *gTitle,
                                  int markerStyle=8, double markerSize=1
                                  )
  {
    GraphPtrs graphs;

    KoaMapEncoder *encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecTdcChIDs();

    Int_t DetectorIdRange[2];
    encoder->GetRecDetIDRange(DetectorIdRange[0], DetectorIdRange[1]);

    // loop
    Int_t markerColor[4] = {kBlack, kBlue, kRed, kMagenta};
    for (auto detector :
             ROOT::TSeqI(DetectorIdRange[0], DetectorIdRange[1] + 1)) {
      TString volName = encoder->DetectorIDToVolName(detector);
      volName.ReplaceAll("Sensor", "");

      graphs.emplace(std::piecewise_construct,
                     std::forward_as_tuple(detector),
                     std::forward_as_tuple(new TGraph()));

      graphs[detector]->SetName(Form("gr_%s_%s", volName.Data(), gName));
      graphs[detector]->SetTitle(Form("%s: %s", volName.Data(), gTitle));
      graphs[detector]->SetMarkerColor(markerColor[detector-DetectorIdRange[0]]);
      graphs[detector]->SetMarkerStyle(markerStyle);
      graphs[detector]->SetMarkerSize(markerSize);
    }

    return graphs;
  }

  // get graph map from file
  GraphPtrs getGraphsByChannelId(TDirectory *gDir, const char* gName, bool IsRec = true)
  {
    KoaMapEncoder *encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs;

    if (IsRec) {
      ChIDs = encoder->GetRecChIDs();
    } else {
      ChIDs = encoder->GetFwdChIDs();
    }

    //
    TGraph* graph = nullptr;
    GraphPtrs graphMap;

    for (auto &ChID : ChIDs) {
      TString volName;
      auto ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      TString name(Form("gr_%s_%s_%d", volName.Data(), gName, ch + 1));

      gDir->GetObject(name, graph);
      if ( !graph ) {
        std::cerr << "Error: no graph found " << name << std::endl;
      }
      graphMap.emplace(ChID, graph);
    }

    return graphMap;
  }

  // get graph map from file
  GraphPtrs getGraphsByRecTdcChannelId(TDirectory *gDir, const char* gName)
  {
    KoaMapEncoder *encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecTdcChIDs();

    //
    TGraph* graph = nullptr;
    GraphPtrs graphMap;

    for (auto &ChID : ChIDs) {
      TString volName;
      auto ch = encoder->DecodeChannelID(ChID, volName);
      volName.ReplaceAll("Sensor", "");
      TString name(Form("gr_%s_%s_%d", volName.Data(), gName, ch + 1));

      gDir->GetObject(name, graph);
      if ( !graph ) {
        std::cerr << "Error: no graph found " << name << std::endl;
      }
      graphMap.emplace(ChID, graph);
    }

    return graphMap;
  }

  // write graphs to a directory
  template <typename T>
      void writeGraphsImpl(TDirectory *gDir, std::map<Int_t,T> &graphs, const char* option, std::true_type) {
    for (auto graph : graphs) {
      gDir->WriteTObject(graph.second, "", option);
    }
    return;
  }

  template <typename T>
      void writeGraphsImpl(TDirectory *gDir, std::map<Int_t,T> &graphs, const char* option, std::false_type) {
    for (auto& graph : graphs) {
      gDir->WriteTObject(&graph.second, "", option);
    }
    return;
  }

  template <typename T>
      void writeGraphs(TDirectory *gDir, std::map<Int_t,T> &graphs, const char* option = "Overwrite") {
    return writeGraphsImpl(gDir, graphs, option, std::is_pointer<T>());
  }

// print graphs to pdf file
template <typename T>
void printGraphsImp(std::map<Int_t,T> &graphs, const char* filename, std::true_type) {
  auto c = new TCanvas();
  c->Print(Form("%s[",filename));
  for (auto& graph : graphs) {
    graph.second->Draw("AP");
    c->Print(Form("%s",filename));
  }
  c->Print(Form("%s]",filename));
  delete c;
  return;
}

template <typename T>
void printGraphsImp(std::map<Int_t,T> &graphs, const char* filename, std::false_type) {
  auto c = new TCanvas();
  c->Print(Form("%s[",filename));
  for (auto& graph : graphs) {
    graph.second.Draw("AP");
    c->Print(Form("%s",filename));
  }
  c->Print(Form("%s]",filename));
  delete c;
  return;
}

template <typename T>
void printGraphs(std::map<Int_t,T> &graphs, const char* filename) {
  return printGraphsImp(graphs,filename, std::is_pointer<T>());
}

};

#endif
