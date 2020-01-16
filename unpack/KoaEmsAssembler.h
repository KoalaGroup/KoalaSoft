#ifndef KOA_EMS_ASSEMBLER_H
#define KOA_EMS_ASSEMBLER_H

/* This class will assemble tha data from each module into a synchronized event based timestamp
 *
 */

#include "TObject.h"

class KoaEmsAssembler : public TObject
{
public:
  KoaEmsAssembler();
  ~KoaEmsAssembler();

  void Init() = 0;
  

private:

  ClassDef(KoaEmsAssembler, 1)
};
#endif
