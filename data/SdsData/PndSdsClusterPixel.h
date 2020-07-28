/*
 * PndSdsClusterPixel.h
 *
 *  Created on: Dec 15, 2009
 *      Author: stockmanns, kliemt, michel
 */

#ifndef PNDSDSCLUSTERPIXEL_H_
#define PNDSDSCLUSTERPIXEL_H_

#include "PndSdsCluster.h"

class PndSdsClusterPixel: public PndSdsCluster {
public:
	PndSdsClusterPixel();
	PndSdsClusterPixel(Int_t DigiType, std::vector<Int_t> list, Int_t fileId = -1, Int_t evtId = -1){
		SetClusterList(DigiType, list, fileId, evtId);
	};
	virtual ~PndSdsClusterPixel();

	void SetClusterList(Int_t DigiType, std::vector<Int_t> list, Int_t fileId, Int_t evtId){
		fClusterList = list;
		SetLinks(FairMultiLinkedData(DigiType, list, fileId, evtId));
	}

	ClassDef(PndSdsClusterPixel, 1);
};

#endif /* PNDSDSCLUSTERPixel_H_ */
