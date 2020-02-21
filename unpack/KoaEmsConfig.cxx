#include "KoaEmsConfig.h"
#include "KoaMapEncoder.h"
#include "FairLogger.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

KoaEmsConfig* KoaEmsConfig::fgInstance = nullptr;

KoaEmsConfig::KoaEmsConfig()
{
  if (fgInstance) {
    Fatal("KoaEmsConfig", "Singleton instance already exists");
    return;
  }
  fgInstance = this;
}

KoaEmsConfig::~KoaEmsConfig()
{
  fgInstance = nullptr;
}

bool KoaEmsConfig::SetEmsConfigFile(const char* filename)
{
  std::ifstream ftxt;
  fFileEmsConfig = gSystem->ExpandPathName(filename);
  ftxt.open(fFileEmsConfig);
  if (!ftxt.is_open()) {
    LOG(error) << "KoaEmsConfig::SetEmsConfigFile : can't open file " << filename;
    return false;
  }

  fFileEmsConfig = filename;
  return ReadEmsConfig(ftxt);
}

bool KoaEmsConfig::SetAmplitudeChannelMap(const char* filename)
{
  std::ifstream ftxt;
  fFileAmplitudeMapConfig = gSystem->ExpandPathName(filename);
  ftxt.open(fFileAmplitudeMapConfig);
  if (!ftxt.is_open()) {
    LOG(error) << "KoaEmsConfig::SetAmplitudeChannelMap : can't open file " << filename;
    return false;
  }

  return ReadAmplitudeChannelMapConfig(ftxt);
}

bool KoaEmsConfig::SetTimeChannelMap(const char* filename)
{
  std::ifstream ftxt;
  fFileTimeMapConfig = gSystem->ExpandPathName(filename);
  ftxt.open(fFileTimeMapConfig);
  if (!ftxt.is_open()) {
    LOG(error) << "KoaEmsConfig::SetTimeChannelMap : can't open file " << filename;
    return false;
  }

  return ReadTimeChannelMapConfig(ftxt);
}

bool KoaEmsConfig::SetScalorChannelMap(const char* filename)
{
  std::ifstream ftxt;
  fFileScalorMapConfig = gSystem->ExpandPathName(filename);
  ftxt.open(fFileScalorMapConfig);
  if (!ftxt.is_open()) {
    LOG(error) << "KoaEmsConfig::SetScalorChannelMap : can't open file " << filename;
    return false;
  }

  return ReadScalorChannelMapConfig(ftxt);
}

bool KoaEmsConfig::ReadEmsConfig(std::ifstream& ftxt)
{
  std::string line;

  // get comment line
  std::getline(ftxt, line);

  // read body txt
  Int_t module_id;
  std::string type;
  std::string module_name;
  MesytecType module_type;

  while (!ftxt.eof()) {
    std::getline(ftxt, line);
    std::stringstream ss(line);

    ss >> module_id >> type >> module_name;

    // checking the type
    if ( type == "madc32" ) {
      module_type = MesytecType::MADC32;
    }
    else if ( type == "mqdc32" ) {
      module_type = MesytecType::MQDC32;
    }
    else if ( type == "mtdc32" ) {
      module_type = MesytecType::MTDC32;
    }
    else {
      LOG(error) << "KoaEmsConfig::ReadEmsConfig : unrecognized module type, please choose from 'madc32', 'mqdc32', 'mtdc32'";
      return false;
    }

    // insert into table
    auto search = fModuleTable.find(module_id);
    if ( search != fModuleTable.end() ) {
      LOG(error) << "KoaEmsConfig::ReadEmsConfig : duplicated module id!";
      return false;
    }

    fModuleTable.emplace(std::piecewise_construct,
                         std::forward_as_tuple(module_id),
                         std::forward_as_tuple(module_type, module_name));
  }

  ftxt.close();

  return true;
}

bool KoaEmsConfig::ReadAmplitudeChannelMapConfig(std::ifstream& ftxt)
{
  std::string line;

  // get comment line
  std::getline(ftxt, line);

  // read body txt
  Int_t module_id, module_ch, detector_id, detector_ch;
  std::string type;
  MesytecType module_type;

  auto encoder = KoaMapEncoder::Instance();
  auto detector_encoded_ids = encoder->GetChIDs();
  while (!ftxt.eof()) {
    std::getline(ftxt, line);
    std::stringstream ss(line);

    ss >> module_id >> type >> module_ch >> detector_id >> detector_ch;

    // checking the type
    if ( type == "madc32" ) {
      module_type = MesytecType::MADC32;
    }
    else if ( type == "mqdc32" ) {
      module_type = MesytecType::MQDC32;
    }
    else if ( type == "mtdc32" ) {
      module_type = MesytecType::MTDC32;
    }
    else {
      LOG(error) << "KoaEmsConfig::ReadAmplitudeChannelMapConfig : unrecognized module type, please choose from 'madc32', 'mqdc32', 'mtdc32'";
      return false;
    }

    auto search = fModuleTable.find(module_id);
    if ( search == fModuleTable.end() ) {
      LOG(error) << "KoaEmsConfig::ReadAmplitudeChannelMapConfig : no module found in DAQ config, with id " << module_id;
      return false;
    }

    if ( module_type != search->second.type ) {
      LOG(error) << "KoaEmsConfig::ReadAmplitudeChannelMapConfig : unmatched module type found";
      return false;
    }

    if ( module_ch < 0 || module_ch > 31) {
      LOG(error) << "KoaEmsConfig::ReadAmplitudeChannelMapConfig : outside of module channel range";
      return false;
    }

    // checking detector id
    auto encoded_id = encoder->EncodeChannelID(detector_id, detector_ch);

    auto it = std::find(detector_encoded_ids.begin(), detector_encoded_ids.end(), encoded_id);
    if ( it == detector_encoded_ids.end() ) {
      LOG(error) << "KoaEmsConfig::ReadAmplitudeChannelMapConfig : no detector channel found, with detector_id=" << detector_id << ", ch_id=" << detector_ch;
      return false;
    }

    // insert into mapping table
    fChInfoMap_Amplitude.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(detector_id, detector_ch),
                                 std::forward_as_tuple(module_id, module_ch));
    fChInfoMapReverse_Amplitude.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(module_id, module_ch),
                                        std::forward_as_tuple(detector_id, detector_ch));
    fChMap_Amplitude.emplace(std::piecewise_construct,
                             std::forward_as_tuple(encoded_id),
                             std::forward_as_tuple(module_id, module_ch));
    fChMapReverse_Amplitude.emplace(std::piecewise_construct,
                                    std::forward_as_tuple(module_id, module_ch),
                                    std::forward_as_tuple(encoded_id));
  }

  ftxt.close();

  return true;
}

bool KoaEmsConfig::ReadTimeChannelMapConfig(std::ifstream& ftxt)
{
  std::string line;

  // get comment line
  std::getline(ftxt, line);

  // read body txt
  Int_t module_id, module_ch, detector_id, detector_ch;
  std::string type;
  MesytecType module_type;

  auto encoder = KoaMapEncoder::Instance();
  auto detector_encoded_ids = encoder->GetChIDs();
  while (!ftxt.eof()) {
    std::getline(ftxt, line);
    std::stringstream ss(line);

    ss >> module_id >> type >> module_ch >> detector_id >> detector_ch;

    // checking the type
    if ( type == "madc32" ) {
      module_type = MesytecType::MADC32;
    }
    else if ( type == "mqdc32" ) {
      module_type = MesytecType::MQDC32;
    }
    else if ( type == "mtdc32" ) {
      module_type = MesytecType::MTDC32;
    }
    else {
      LOG(error) << "KoaEmsConfig::ReadTimeChannelMapConfig : unrecognized module type, please choose from 'madc32', 'mqdc32', 'mtdc32'";
      return false;
    }

    auto search = fModuleTable.find(module_id);
    if ( search == fModuleTable.end() ) {
      LOG(error) << "KoaEmsConfig::ReadTimeChannelMapConfig : no module found in DAQ config, with id " << module_id;
      return false;
    }

    if ( module_type != search->second.type ) {
      LOG(error) << "KoaEmsConfig::ReadTimeChannelMapConfig : unmatched module type found";
      return false;
    }

    if ( module_ch < 0 || module_ch > 31) {
      LOG(error) << "KoaEmsConfig::ReadTimeChannelMapConfig : outside of module channel range";
      return false;
    }

    // checking detector id
    auto encoded_id = encoder->EncodeChannelID(detector_id, detector_ch);

    auto it = std::find(detector_encoded_ids.begin(), detector_encoded_ids.end(), encoded_id);
    if ( it == detector_encoded_ids.end() ) {
      LOG(error) << "KoaEmsConfig::ReadTimeChannelMapConfig : no detector channel found, with detector_id=" << detector_id << ", ch_id=" << detector_ch;
      return false;
    }

    // insert into mapping table
    fChInfoMap_Time.emplace(std::piecewise_construct,
                            std::forward_as_tuple(detector_id, detector_ch),
                            std::forward_as_tuple(module_id, module_ch));
    fChInfoMapReverse_Time.emplace(std::piecewise_construct,
                                   std::forward_as_tuple(module_id, module_ch),
                                   std::forward_as_tuple(detector_id, detector_ch));
    fChMap_Time.emplace(std::piecewise_construct,
                        std::forward_as_tuple(encoded_id),
                        std::forward_as_tuple(module_id, module_ch));
    fChMapReverse_Time.emplace(std::piecewise_construct,
                               std::forward_as_tuple(module_id, module_ch),
                               std::forward_as_tuple(encoded_id));
  }

  ftxt.close();

  return true;
}

bool KoaEmsConfig::ReadScalorChannelMapConfig(std::ifstream& ftxt)
{
  std::string line;

  // get comment line
  std::getline(ftxt, line);

  // read body txt
  std::string scalor_name;
  int scalor_index;

  while (!ftxt.eof()) {
    std::getline(ftxt, line);
    std::stringstream ss(line);

    ss >> scalor_name >> scalor_index;

    if ( scalor_index < 0 || scalor_index > 31 ) {
      LOG(error) << "KoaEmsConfig::ReadScalorChannelMapConfig : outside of scalor channel range";
      return false;
    }

    // insert into mapping table
    fScalorChMap.emplace(scalor_name, scalor_index);
  }

  ftxt.close();

  return true;
}

void KoaEmsConfig::PrintModuleTable(const char* filename)
{
  std::ostringstream output;

  // output comment line
  output << "# module_id module_type module_name\n";

  // output table
  for( auto& module : fModuleTable ) {
    auto module_id = module.first;
    auto module_type = module.second.type;
    auto module_name = module.second.name;

    std::string type;
    switch (module_type) {
    case MesytecType::MADC32 :
      {
        type = "madc32";
        break;
      }
    case MesytecType::MQDC32 :
      {
        type = "mqdc32";
        break;
      }
    case MesytecType::MTDC32 :
      {
        type = "mtdc32";
        break;
      }
    }

    output << module_id << "\t" << type << "\t" << module_name << std::endl;
  }

  // write to file or screen
  if ( !filename ) {
    std::cout << output.str();
  }
  else {
    std::ofstream ftxt(gSystem->ExpandPathName(filename));
    ftxt << output.str();
    ftxt.close();
  }
}

void KoaEmsConfig::PrintAmplitudeChannelMap(const char* filename)
{
  std::ostringstream output;

  // output comment line
  output << "# module_id module_type module_channel detector_id detector_channel\n";

  // output table
  for( auto& mapping : fChInfoMapReverse_Amplitude ) {
    auto module_chinfo = mapping.first;
    auto detector_chinfo = mapping.second;

    auto module_id = module_chinfo.first;
    auto module_channel = module_chinfo.second;
    auto detector_id = detector_chinfo.first;
    auto detector_channel = detector_chinfo.second;
    auto module_type = fModuleTable[module_id].type;

    std::string type;
    switch (module_type) {
    case MesytecType::MADC32 :
      {
        type = "madc32";
        break;
      }
    case MesytecType::MQDC32 :
      {
        type = "mqdc32";
        break;
      }
    case MesytecType::MTDC32 :
      {
        type = "mtdc32";
        break;
      }
    }

    output << module_id << "\t" << type << "\t" << module_channel
           << "\t" << detector_id << "\t" << detector_channel << std::endl;
  }

  // write to file or screen
  if ( !filename ) {
    std::cout << output.str();
  }
  else {
    std::ofstream ftxt(gSystem->ExpandPathName(filename));
    ftxt << output.str();
    ftxt.close();
  }
}

void KoaEmsConfig::PrintTimeChannelMap(const char* filename)
{
  std::ostringstream output;

  // output comment line
  output << "# module_id module_type module_channel detector_id detector_channel\n";

  // output table
  for( auto& mapping : fChInfoMapReverse_Time ) {
    auto module_chinfo = mapping.first;
    auto detector_chinfo = mapping.second;

    auto module_id = module_chinfo.first;
    auto module_channel = module_chinfo.second;
    auto detector_id = detector_chinfo.first;
    auto detector_channel = detector_chinfo.second;
    auto module_type = fModuleTable[module_id].type;

    std::string type;
    switch (module_type) {
    case MesytecType::MADC32 :
      {
        type = "madc32";
        break;
      }
    case MesytecType::MQDC32 :
      {
        type = "mqdc32";
        break;
      }
    case MesytecType::MTDC32 :
      {
        type = "mtdc32";
        break;
      }
    }

    output << module_id << "\t" << type << "\t" << module_channel
           << "\t" << detector_id << "\t" << detector_channel << std::endl;
  }

  // write to file or screen
  if ( !filename ) {
    std::cout << output.str();
  }
  else {
    std::ofstream ftxt(gSystem->ExpandPathName(filename));
    ftxt << output.str();
    ftxt.close();
  }
}

void KoaEmsConfig::PrintScalorChannelMap(const char* filename)
{
  std::ostringstream output;

  // output comment line
  output << "# scalor_name scalor_channel";

  // output table
  for( auto& mapping : fScalorChMap ) {
    output << mapping.first << "\t" << mapping.second << std::endl;
  }

  // write to file or screen
  if ( !filename ) {
    std::cout << output.str();
  }
  else {
    std::ofstream ftxt(gSystem->ExpandPathName(filename));
    ftxt << output.str();
    ftxt.close();
  }
}

ClassImp(KoaEmsConfig)
