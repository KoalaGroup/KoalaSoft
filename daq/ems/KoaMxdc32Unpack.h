#ifndef KOA_MXDC32_UNPACK_H
#define KOA_MXDC32_UNPACK_H

#include "KoaUnpack.h"
#include "KoaMxdc32Data.h"
#include "KoaEmsConfig.h"
#include <map>

class KoaMxdc32Unpack : public KoaUnpack
{
 public:
  KoaMxdc32Unpack(ems_u32 is_id) : KoaUnpack(is_id, "Mxdc32Unpacker", "Unpacker for Mxdc32 module data")
  {}
  ~KoaMxdc32Unpack() {}

  Bool_t Init();
  Int_t  DoUnpack(const ems_u32* buf, Int_t size);
  void   Reset() {}

private:
  std::map<ModuleId, KoaMxdc32Buffer*> fModuleBuffer;
  ModuleTable fModuleTable;

  ClassDef(KoaMxdc32Unpack, 1)
};
#endif
