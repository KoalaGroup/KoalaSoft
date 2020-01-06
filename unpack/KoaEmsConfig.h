#ifndef KOA_EMS_CONFIG_H
#define KOA_EMS_CONFIG_H

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

  void SetConfigFile();
  std::map<Int_t, Int_t> GetChannelMap();
  
private:
  std::map<Int_t, Int_t> fChannelMap; // mapping from DAQ channel to Detector Channel
  std::vector<ems_u32>   fModuleId;
  std::vector<std::string> fModuleName;
  std::vector<Int_t>     fModuleType;

  static KoaEmsConfig* fgInstance;

  ClassDef(KoaEmsConfig, 1)
};
#endif
