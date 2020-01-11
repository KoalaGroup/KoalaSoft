#ifndef KOA_EMS_CONFIG_H
#define KOA_EMS_CONFIG_H

#include "TObject.h"
#include <cstdint>
#include <ifstream>
#include <string>
#include <sstream>
#include <map>

/* Module type enumeration. The value comes from KoalaEms definition, which is not important in KoalaSoft. */
enum class MesytecType : std::uint64_t
{
  MTDC32 = 0x23f10032UL,
  MADC32 = 0x21f10032UL,
  MQDC32 = 0x22f10032UL
};

/* Module configuration table. Module id as key, Module info as value */
struct ModuleInfo
{
  MesytecType type;
  std::string name;
};

using ModuleId = std::uint32_t;
using ModuleTable = std::map<ModuleId, ModuleInfo>;

/* Types used in Module Channel mapping */
using ChannelInfo = std::pair<Int_t, Int_t>; // for DAQ, it's <ModuleId, ModuleCh>; for detector, it's <DetectorId, DetectorCh>
using ChannelMap = std::map<Int_t, ChannelInfo>; // from encoded detector channel id to DAQ channel info
using ChannelMapReverse = std::map<ChannelInfo, Int_t>; // from DAQ channel info to encoded detector channel id
using ChannelInfoMap = std::map<ChannelInfo, ChannelInfo>; // from channel info pair to channel info map

using ScalorMap = std::map<std::string, int>;

/* This class stores the EMS DAQ configuration information and the mapping table from
   DAQ channel to Detector channel.

   DAQ configuration information is:
   1. Number of Modules used
   2. Type ID of the module
   3. ID of the module
   4. Name of the module

   The mapping table is:
   1. 1-1 mapping from module channel to Koala detector readout channel
   2. Each type of the module has a separate mapping table

   These information is provide by the user as a text configuration file.
   It's a singleton class and should be instantiated once by the user directly.
 */
class KoaEmsConfig : public TObject
{
public:
  KoaEmsConfig();
  ~KoaEmsConfig();

  static KoaEmsConfig* Instance() {
    return fgInstance;
  }

  // Module configuration table

  bool SetEmsConfigFile(const char* filename);
  bool SetAmplitudeChannelMap(const char* filename);
  bool SetTimeChannelMap(const char* filename);
  bool SetScalorChannelMap(const char* filename);

  //
  void PrintModuleTable(const char* filename = nullptr);
  void PrintAmplitudeChannelMap(const char* filename = nullptr);
  void PrintTimeChannelMap(const char* filename = nullptr);
  void PrintScalorChannelMap(const char* filename = nullptr);

  //
  ModuleTable GetModuleTable() { return fModuleTable; }

  ChannelInfoMap GetAmplitudeChMapInfo() { return fChInfoMap_Amplitude; }
  ChannelInfoMap GetTimeChMapInfo() { return fChInfoMap_Time; }

  ChannelInfoMap GetAmplitudeChMapInfoReverse() { return fChInfoMapReverse_Amplitude; }
  ChannelInfoMap GetTimeChMapInfoReverse() { return fChInfoMapReverse_Time; }

  ChannelMap GetAmplitudeChMap() { return fChMap_Amplitude; }
  ChannelMap GetTimeChMap() { return fChMap_Time; }

  ChannelMapReverse GetAmplitudeChMapReverse() { return fChMapReverse_Amplitude; }
  ChannelMapReverse GetTimeChMapReverse() { return fChMapReverse_Time; }

  ScalorMap GetScalorChMap() { return fScalorChMap; }

private:
  bool ReadEmsConfig(std::ifstream& infile);
  bool ReadAmplitudeChannelMapConfig(std::ifstream& infile);
  bool ReadTimeChannelMapConfig(std::ifstream& infile);
  bool ReadScalorChannelMapConfig(std::ifstream& infile);

private:
  std::string fFileEmsConfig;
  std::string fFileAmplitudeMapConfig;
  std::string fFileTimeMapConfig;
  std::string fFileScalorMapConfig;

  ModuleTable fModuleTable; // EMS configuration

  ChannelInfoMap fChInfoMap_Amplitude; // from detector channel info pair to DAQ channel info pair
  ChannelInfoMap fChInfoMap_Time;
  ChannelInfoMap fChInfoMapReverse_Amplitude; // from DAQ channel info pair to detector channel info pair
  ChannelInfoMap fChInfoMapReverse_Time;

  ChannelMap     fChMap_Amplitude; // from encoded detector channel id to DAQ channel info pair
  ChannelMap     fChMap_Time;
  ChannelMapReverse fChMapReverse_Amplitude; // from DAQ channel info pair to encoded channel id
  ChannelMapReverse fChMapReverse_Time;

  ScalorMap fScalorChMap;

  // static instance
  static KoaEmsConfig* fgInstance;

  ClassDef(KoaEmsConfig, 1)
};
#endif
