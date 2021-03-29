/*
 * PndLmdGeo.cxx *
 *  Created on: Jun 30, 2010
 *      Author: huagen
 */

#include "PndLmdGeo.h"
#include "PndSdsGeo.h"

#include <iostream>

ClassImp(PndLmdGeo)

    // constructor
    PndLmdGeo::PndLmdGeo() {
  fName = "lmd";
  maxSectors = 99;
  maxModules = 99;
}

PndLmdGeo::~PndLmdGeo() {}

const char* PndLmdGeo::getModuleName(Int_t m) {
  //  PndSdsGeo::getModuleName(m);
  if (m < 0) {
    std::cout << "-E- CbmGeoSts::getModuleName:: Module number " << m
              << " not known!" << std::endl;
    return "";
  }
  if (m < 9)
    sprintf(fModName, "lmdTrapStrip0%i", m + 1);
  else
    sprintf(fModName, "lmdTrapStrip%i", m + 1);
  return fModName;
}
const char* PndLmdGeo::getEleName(Int_t m) {
  // PndSdsGeo::getEleName(m);
  // Returns the element name of Lmd number m
  if (m < 9)
    sprintf(fEleName, "lmd0%i", m + 1);
  else
    sprintf(fEleName, "lmd%i", m + 1);

  return fEleName;
}
