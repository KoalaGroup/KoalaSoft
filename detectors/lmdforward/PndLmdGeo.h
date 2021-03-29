/*
 * PndLmdGeo.h
 * *  Created on: Jun 30, 2010
 *      Author: huagen
 */
/*
 * PndLmdGeo class will define the detector name by user. It was inherited from
 * Sds base class PndSdsGeo.
 */

#ifndef PNDLMDGEO_H_
#define PNDLMDGEO_H_

#include "PndSdsGeo.h"

class PndLmdGeo : public PndSdsGeo {
 public:
  PndLmdGeo();
  ~PndLmdGeo();

  const char* getModuleName(Int_t m);
  const char* getEleName(Int_t m);

  ClassDef(PndLmdGeo, 1);
};

#endif /* PNDLMDGEO_H_ */
