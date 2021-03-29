/*
 * PndSdsDigiPixelRingSorter.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include <PndSdsDigiPixelRingSorter.h>
#include "PndSdsDigiPixel.h"


ClassImp(PndSdsDigiPixelRingSorter);


PndSdsDigiPixelRingSorter::~PndSdsDigiPixelRingSorter() {
	// TODO Auto-generated destructor stub
}

FairTimeStamp* PndSdsDigiPixelRingSorter::CreateElement(FairTimeStamp* data) {
	return new PndSdsDigiPixel(*(PndSdsDigiPixel*)data);
}
