#ifndef KOA_TEST_H
#define KOA_TEST_H
#include "TObject.h"

class KoaTest : public TObject
{
  
 public:
  KoaTest() {
    
  }
  ~KoaTest() {}

  void Print();

  ClassDef(KoaTest, 1)
};
#endif
