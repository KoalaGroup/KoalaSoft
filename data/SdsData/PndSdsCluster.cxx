#include "PndSdsCluster.h"

PndSdsCluster::PndSdsCluster(std::vector<Int_t> list) :
fClusterList(list)
{
}

void PndSdsCluster::Print()
{
	std::cout << *this;
}

bool PndSdsCluster::DigiBelongsToCluster(Int_t digiIndex)
{
	for (unsigned int i = 0; i < fClusterList.size(); i++)
		if (fClusterList[i] == digiIndex) return true;

	return false;
}


ClassImp(PndSdsCluster);

