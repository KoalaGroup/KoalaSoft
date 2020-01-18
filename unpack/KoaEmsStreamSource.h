#ifndef KOA_EMS_STREAM_SOURCE_H
#define KOA_EMS_STREAM_SOURCE_H

#include "KoaEmsSource.h"

class KoaEmsStreamSource : public KoaEmsSource
{
public:
  KoaEmsStreamSource() {}
  KoaEmsStreamSource(const char* server)
  {
    SetupInput(server);
  }
  ~KoaEmsStreamSource() {}

  virtual Bool_t SetupInput(const char* server);
  virtual Bool_t SetupInput(std::string char* ip, std::string port);
  virtual void Close();

  ClassDef(KoaEmsStreamSource, 1)
};
#endif
