#ifndef KOA_UNPACK_H
#define KOA_UNPACK_H

#include "TNamed.h"
#include "ems_interface.h"

class KoaUnpack : public TNamed
{
 public:
  KoaUnpack(ems_u32 is_id, const char* name, const char* title) : TNamed(name, title), fISId(is_id) {}
  virtual ~KoaUnpack() {}

  virtual Bool_t Init() = 0;
  virtual Bool_t ReInit() { return kTRUE; }
  virtual Int_t DoUnpack(const ems_u32* buf, Int_t size) = 0;
  virtual void   Reset() = 0;
  virtual void   SetParContainers() {};

  inline ems_u32 GetISId()    const { return fISId; }

 private:
  ems_u32 fISId; // Instrument ID in EMS configuration file

  ClassDef(KoaUnpack, 1)
};
#endif
