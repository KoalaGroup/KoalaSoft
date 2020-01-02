#ifndef KOA_UNPACK_H
#define KOA_UNPACK_H

#include "TObject.h"
#include "ems_interface.h"

class KoaUnpack : public TObject
{
 public:
  KoaUnpack(ems_u32 is_id);
  virtual ~KoaUnpack();

  virtual Bool_t Init() = 0;
  virtual Bool_t ReInit() { return kTRUE; }
  virtual Bool_t DoUnpack(Int_t* data, Int_t size) = 0;
  virtual void   Reset() = 0;
  virtual void   SetParContainers() {  };

  inline Short_t GetISId()    const { return fType;     }

 private:
  ems_u32 fISId; // Instrument ID in EMS configuration file

 protected:
  virtual void Register() = 0;

  ClasDef(KoaUnpack, 1)
};
#endif
