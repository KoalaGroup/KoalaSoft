#include "KoaHistUtility.h"
#include "KoaGraphUtility.h"
#include "KoaGeometryUtility.h"

using namespace KoaUtility;

void print_channel_position(const char* geoFile,
                            double zoffset_si1 = 0.18, double zoffset_si2 = 0.13, double zoffset_ge1 = 0.12, double zoffset_ge2 = 0.12
                            )
{
  // Detector position correction applied to imput geometry model
  double yoffset[4] = {0};
  double zoffset[4] = {zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2}; // in cm

  // Retrieve the strips/channels z-pos, alpha, expected-energy
  auto Positions = getChannelGlobalPosition(geoFile, zoffset);
  auto Alphas = getChannelAlphas(geoFile, yoffset, zoffset);
  
  ParameterList<double> ChannelParams;
  auto& output_z = addValueContainer(ChannelParams, "Z(mm)");
  auto& output_alpha = addValueContainer(ChannelParams, "alpha(degree)");
  for(auto item: Positions){
    auto id = item.first;
    auto value = item.second;
    output_z.emplace(id, Positions[id]*10);
    output_alpha.emplace(id, Alphas[id]);
  }

  printValueList<double>(ChannelParams, Form("channel_position_%.2f_%.2f_%.2f_%.2f.txt",zoffset_si1, zoffset_si2, zoffset_ge1, zoffset_ge2));

}
