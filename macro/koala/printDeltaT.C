#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void printDeltaT(const char* outfile,
                 double mom,
                 const char* geoFile,
                 double zoffset_si1 = 0, double zoffset_si2 = 0, double zoffset_ge1 = 0, double zoffset_ge2 = 0
)
{
  // get delta 4-momentum transfer for each strip
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm
  double yoffset[4] = {0, 0, 0, 0}; // in cm

  auto DeltaTs = getStripDelatT(mom,geoFile,yoffset,zoffset);

  // output parameters
  ParameterList<double> OutParameters;
  auto& output_dt = addValueContainer(OutParameters, "dt");

  for(auto item: DeltaTs){
    output_dt.emplace(item.first, item.second);
  }

  //
  printValueList<double>(OutParameters, outfile);
}
