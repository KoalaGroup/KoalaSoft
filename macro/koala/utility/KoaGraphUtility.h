#ifndef KOAGRAPHUTILITY_H
#define KOAGRAPHUTILITY_H

namespace KoaUtility
{
  using Graphs = std::map<int, TGraphErrors>;
  using GraphPtrs = std::map<int, TGraph*>;

  // book graphs by channel id
  Graphs bookGraphByChannelId(const char *gName, const char *gTitle,
                              int markerColor=kBlack, int markerStyle=105,
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
    }

    return graphs;
  }

  // book graphs by rec channels with tdc connection
  Graphs bookGraphByRecTdcChannelId(const char *gName, const char *gTitle,
                                    int markerColor=kBlack, int markerStyle=105
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
};

#endif
