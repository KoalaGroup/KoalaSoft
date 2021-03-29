/*
 * PndSdsDigiPixelWriteoutBuffer.cxx
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#include <PndSdsDigiPixelWriteoutBuffer.h>

ClassImp(PndSdsDigiPixelWriteoutBuffer);

#include "PndSdsDigiPixel.h"


PndSdsDigiPixelWriteoutBuffer::PndSdsDigiPixelWriteoutBuffer():FairWriteoutBuffer()
, fData_map()
{

	// TODO Auto-generated constructor stub

}


PndSdsDigiPixelWriteoutBuffer::PndSdsDigiPixelWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance): FairWriteoutBuffer(branchName, "PndSdsDigiPixel", folderName, persistance),
fData_map()
{
}

PndSdsDigiPixelWriteoutBuffer::~PndSdsDigiPixelWriteoutBuffer() {
	// TODO Auto-generated destructor stub
}

std::vector<std::pair<double, FairTimeStamp*> > PndSdsDigiPixelWriteoutBuffer::Modify(std::pair<double, FairTimeStamp*> oldData, std::pair<double, FairTimeStamp*> newData)
{
  std::vector<std::pair<double, FairTimeStamp*> > result;
  std::pair<double, FairTimeStamp*> singleResult;
  if (newData.first > 0)
    singleResult.first = newData.first;
  singleResult.second = oldData.second;
  ((PndSdsDigiPixel*)singleResult.second)->AddCharge(((PndSdsDigiPixel*)newData.second)->GetCharge());
  if (fVerbose > 0){
    std::cout << "Modify hit" << std::endl;
    std::cout << "OldData: " << oldData.first << " : " << oldData.second << " NewData: " << newData.first << " : " << newData.second << std::endl;
    std::cout << "Resulting Data: " << singleResult.first << " : " << singleResult.second << std::endl;
  }
  
  result.push_back(singleResult);
  return result;
}

void PndSdsDigiPixelWriteoutBuffer::AddNewDataToTClonesArray(FairTimeStamp* data)
{
  FairRootManager* ioman = FairRootManager::Instance();
  TClonesArray* myArray = ioman->GetTClonesArray(fBranchName);
  if (fVerbose > 1) std::cout << "Data Inserted: "  <<  *(PndSdsDigiPixel*)(data) << std::endl;
  new ((*myArray)[myArray->GetEntries()]) PndSdsDigiPixel(*(PndSdsDigiPixel*)(data));
}

double PndSdsDigiPixelWriteoutBuffer::FindTimeForData(FairTimeStamp* data) 
{
  std::map<PndSdsDigiPixel, double>::iterator it;
  PndSdsDigiPixel myData = *(PndSdsDigiPixel*)data;
  it = fData_map.find(myData);
  if (it == fData_map.end())
    return -1;
  else{
  	if (fVerbose > 1)
	  std::cout << "Search: " << myData << " Found: " << (PndSdsDigiPixel)it->first << " Time: " << it->second << std::endl;
    return it->second;
  }
}
void PndSdsDigiPixelWriteoutBuffer::FillDataMap(FairTimeStamp* data, double activeTime) 
{
  PndSdsDigiPixel myData = *(PndSdsDigiPixel*)data;
  fData_map[myData] = activeTime;
}
void PndSdsDigiPixelWriteoutBuffer::EraseDataFromDataMap(FairTimeStamp* data)
{
  PndSdsDigiPixel myData = *(PndSdsDigiPixel*)data;
  if (fData_map.find(myData) != fData_map.end())
    fData_map.erase(fData_map.find(myData));
}
