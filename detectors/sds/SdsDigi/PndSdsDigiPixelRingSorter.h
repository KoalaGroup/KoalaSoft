/*
 * PndSdsDigiPixelRingSorter.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef PNDSDSDIGIPIXELRINGSORTER_H_
#define PNDSDSDIGIPIXELRINGSORTER_H_

#include <FairRingSorter.h>

class PndSdsDigiPixelRingSorter: public FairRingSorter {
public:
	PndSdsDigiPixelRingSorter(int size = 100, double width = 10):FairRingSorter(size, width){};
	virtual ~PndSdsDigiPixelRingSorter();

	virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

	ClassDef (PndSdsDigiPixelRingSorter,1);
};

#endif /* PNDSDSDIGIPIXELRINGSORTER_H_ */
