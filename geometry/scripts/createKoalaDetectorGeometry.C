#include <iostream>

#include "detectors/recoil/full/geokoaladetector.h"

#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairGeoBuilder.h"
#include "FairGeoMedia.h"

#include "TFile.h"
#include "TROOT.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"

#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

void createKoalaDetectorGeometry(std::string output_filename = "Koala-Detector.root",
                                 std::string geo_koala_detector_params_config_file_url = "../../parameters/koala-geo-params.json")
{

  ptree geo_koala_detector_tree;
  read_json(geo_koala_detector_params_config_file_url, geo_koala_detector_tree);

  FairGeoLoader *geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
  FairGeoInterface *geoFace = geoLoad->getGeoInterface();
  std::string koalasoft_dir(getenv("VMCWORKDIR"));
  geoFace->setMediaFile((koalasoft_dir + "/geometry/media_pnd.geo").c_str());
  geoFace->readMedia();
  FairGeoMedia *Media = geoFace->getMedia();
  FairGeoBuilder *geobuild = geoLoad->getGeoBuilder();
  TFile file(output_filename.c_str(), "RECREATE");

  TGeoManager *gGeoMan = (TGeoManager *)gROOT->FindObject("FAIRGeom");

  geokoaladetector geo_koala_detector_factory(geo_koala_detector_tree);

  geo_koala_detector_factory.init(geoLoad);

  TGeoVolumeAssembly *lmd_detectorp = geo_koala_detector_factory.generateLmdGeometry();

  gGeoMan->CheckOverlaps(0.0001); // 1mu
  gGeoMan->PrintOverlaps();

  lmd_detectorp->Write();
  file.Close();

  gGeoMan->SetVisLevel(20);

  // lmd_detectorp->Draw("ogl");
}
