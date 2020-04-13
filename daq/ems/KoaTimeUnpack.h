#ifndef KOA_TIME_UNPACK_H
#define KOA_TIME_UNPACK_H

#include "KoaUnpack.h"
#include "KoaEmsEventData.h"

class KoaTimeUnpack : public KoaUnpack
{
 public:
 KoaTimeUnpack(ems_u32 is_id) : KoaUnpack(is_id, "TimeUnpacker", "Unpacker for Ems Time information")
    {}
  ~KoaTimeUnpack() {}

  Bool_t Init();
  Int_t  DoUnpack(const ems_u32* buf, Int_t size);
  void   Reset() {}

 private:
  KoaEmsEventBuffer *fEmsBuffer;

  ClassDef(KoaTimeUnpack, 1)
};
#endif
