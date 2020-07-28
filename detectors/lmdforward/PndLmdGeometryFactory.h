/*
 * PndLmdGeometryFactory.h
 *
 *  Created on: Nov 6, 2017
 *      Author: steve
 */

#ifndef LMD_LMDMC_PNDLMDGEOMETRYFACTORY_H_
#define LMD_LMDMC_PNDLMDGEOMETRYFACTORY_H_

#include <vector>

#include <boost/property_tree/ptree.hpp>

class TGeoManager;
class TGeoVolume;
class TGeoVolumeAssembly;
class FairGeoLoader;
class TGeoNode;

typedef std::pair<std::string, bool> StringBoolPair;

class PndLmdGeometryFactory {
  boost::property_tree::ptree geometry_property_tree;
  std::vector<StringBoolPair> navigation_paths;
  TGeoManager* gGeoMan;

  void retrieveMaterial(FairGeoLoader* geoLoad);

  TGeoVolume* generateLmdBox() const;
  TGeoVolume* generateBeamPipe() const;

  TGeoVolume* generateDetectorHalf(bool is_bottom_half) const;
  TGeoVolume* generateDetectorHalfPlane(bool is_bottom_half) const;
  TGeoVolume* generateAluminumCoolingStructure() const;
  TGeoVolume* generatePCB() const;
  TGeoVolume* generatePCBMountScrew() const;
  TGeoVolume* generatePCBCopperPlug() const;
  TGeoVolume* generatePCBBacksideElectronics() const;
  TGeoVolume* generateSensorModule() const;
  TGeoVolume* generateCVDCoolingDisc() const;
  TGeoVolume* generateSensor() const;

  TGeoVolume* generateBoxVacuum(const TGeoVolume* lmd_vol) const;
  void recursiveNodeSubtraction(std::stringstream& ss, TGeoNode* node) const;

  void makeNodesAlignable() const;
  void makeNodesAlignable(TGeoNode* node,
                          unsigned int current_navigation_path_index) const;

 public:
  PndLmdGeometryFactory(
      const boost::property_tree::ptree& geometry_property_tree_);
  virtual ~PndLmdGeometryFactory();

  void init(FairGeoLoader* geoLoad);

  TGeoVolumeAssembly* generateLmdGeometry() const;
};

#endif /* LMD_LMDMC_PNDLMDGEOMETRYFACTORY_H_ */
