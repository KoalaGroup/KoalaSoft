#ifndef KOA_DUMMY_H
#define KOA_DUMMY_H

#include "TObject.h"
#include <iostream>

class KoaDummy : public TObject
{
  
 public:
  KoaDummy() {
    
  }
  ~KoaDummy() {}

  void Print() {
    std::cout << "I'm Dummy" << std::endl;
  }

  ClassDef(KoaDummy, 1)
};
#endif
