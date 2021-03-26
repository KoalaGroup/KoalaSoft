#ifndef KOA_EVENT_LIGHTASSEMBLER_H
#define KOA_EVENT_LIGHTASSEMBLER_H

#include "KoaEventAssembler.h"
#include <vector>

/* Assemble algorithms:
 * 1. find the smallest timestamp
 * 2. If all the modules have the same timestamp, pop out all top items and assemble
 * 3. Otherwise, pop out the top item of modules which have the same timestamp as the smallest timestamp
 * 4. Go back to step1 and repeat
 */
class KoaEventLgtAsm : public KoaEventAssembler
{
public:
  KoaEventLgtAsm() {}
  virtual ~KoaEventLgtAsm() {}

private:
  bool NextEvent();

private:
  std::vector<ModuleId> fMinTSs;

  ClassDef(KoaEventLgtAsm, 1)
};
#endif
