#ifndef KOA_SCALOR_UNPACK_H
#define KOA_SCALOR_UNPACK_H

#include "KoaUnpack.h"
#include "KoaEmsEventData.h"

class KoaScalorUnpack : public KoaUnpack
{
 public:
 KoaScalorUnpack(ems_u32 is_id) : KoaUnpack(is_id, "ScalorUnpacker", "Unpacker for Scalor Data")
    {}
  ~KoaScalorUnpack() {}

  Bool_t Init();
  Int_t  DoUnpack(const ems_u32* buf, Int_t size);
  void   Reset() {}

 private:
  KoaEmsEventBuffer *fEmsBuffer;
  
  ClassDef(KoaScalorUnpack, 1)
};
#endif
