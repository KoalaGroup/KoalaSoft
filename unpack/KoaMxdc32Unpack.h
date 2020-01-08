#ifndef KOA_MXDC32_UNPACK_H
#define KOA_MXDC32_UNPACK_H

#include "KoaUnpack.h"
#include "KoaMxdc32Data.h"
#include <map>

class KoaMxdc32Unpack : public KoaUnpack
{
 public:
  KoaMxdc32Unpack(ems_u32 is_id) : KoaUnpack(is_id, "Mxdc32Unpacker", "Unpacker for Mxdc32 module data")
  {}
  ~KoaMxdc32Unpack() {}

  Bool_t Init();
  Bool_t ReInit();
  Bool_t DoUnpack(ems_u32* buf, Int_t size);
  void   Reset();
  void   SetParContainers();

protected:
  void Register();

private:
  std::map<ems_u32, KoaMxdc32Buffer*> fModuleBuffers;

  ClassDef(KoaMxdc32Unpack, 1)
};
#endif
