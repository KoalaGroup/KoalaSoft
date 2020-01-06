#ifndef KOA_TIME_UNPACK_H
#define KOA_TIME_UNPACK_H

#include "KoaUnpack.h"
#include "KoaBufferTemplate.h"

class KoaTimeUnpack : public KoaUnpack
{
 public:
 KoaTimeUnpack(ems_u32 is_id) : KoaUnpack(is_id, "Mxdc32Unpacker", "Unpacker for Mxdc32 module data")
    {}
  ~KoaTimeUnpack() {}

  Bool_t Init();
  Bool_t ReInit();
  Bool_t DoUnpack(ems_u32* buf, Int_t size);
  void   Reset();
  void   SetParContainers();

 protected:
  void Register();

 private:
  
  ClassDef(KoaTimeUnpack, 1)
};
#endif
