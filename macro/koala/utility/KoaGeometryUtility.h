#ifndef KOAGEOMETRYUTILITY_H
#define KOAGEOMETRYUTILITY_H

namespace KoaUtility
{
  KoaGeoHandler* getGeometryHandler(const char* geoFile)
  {
    auto fgeo = TFile::Open(geoFile);
    fgeo->Get("FAIRGeom");
    auto geoHandler = new KoaGeoHandler(kFALSE);

    return geoHandler;
  }

  std::map<int, double> getStripGlobalPosition(const char* geoFile)
  {
    auto geoHandler = getGeometryHandler(geoFile);

    KoaMapEncoder* encoder = KoaMapEncoder::Instance();
    std::vector<int> ChIDs = encoder->GetRecChIDs();

    Double_t pos_low, pos_high, pos_center;
    Double_t global_pos[3] = {0};
    Double_t local_pos[3] = {0};

    std::map<int, double> positions;
    for(auto id : ChIDs) {
      pos_center = geoHandler->RecDetChToPosition(id, pos_low, pos_high);
      local_pos[2] = pos_center;
      geoHandler->LocalToGlobal(local_pos, global_pos, id);
      positions.emplace(global_pos[2]);
    }

    delete geoHandler;

    return positions;
  }

  double getRecoilSensorPosition(const char* geoFile)
  {
    auto geoHandler = getGeometryHandler(geoFile);
    
    Double_t rec_distance = TMath::Abs(geoHandler->GetDetPositionByName("SensorSi1"));

    delete geoHandler;
    return rec_distance;
  }
}

#endif
