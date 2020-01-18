#ifndef KOA_EMS_FILE_SOURCE_H
#define KOA_EMS_FILE_SOURCE_H

#include "KoaEmsSource.h"
#include <string>

class KoaEmsFileSource : public KoaEmsSource
{
public:
  KoaEmsFileSource() {}
  KoaEmsFileSource(const char* filename)
  {
    SetInput(filename);
  }
  ~KoaEmsFileSource() {}

  virtual Bool_t SetupInput(const char* filename);

private:
  std::string fFileName;

  ClassDef(KoaEmsFileSource, 1)
};

#endif
