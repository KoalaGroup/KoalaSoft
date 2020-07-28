#ifndef PNDSDSGEO_H
#define PNDSDSGEO_H

#include "FairGeoSet.h"

class  PndSdsGeo : public FairGeoSet
{
 public:
  PndSdsGeo();
  ~PndSdsGeo() {}
  const char* getModuleName(Int_t m);
  const char* getEleName(Int_t m);
  const char* getKeepinName(Int_t i,Int_t j);
  inline Int_t getModNumInMod(const TString& name) const;
 protected:
  char fModName[20];  // name of module
  char fEleName[20];  // substring for elements in module
  char fKeepinName[20];

  ClassDef(PndSdsGeo,1); // Class for PndSds
};

// TODO: we don't need this?

inline Int_t PndSdsGeo::getModNumInMod(const TString& name) const {
 /// returns the module index from module name
 return (Int_t)(name[3]-'0')-1;
}

#endif  /* !PNDSDSGEO_H */
