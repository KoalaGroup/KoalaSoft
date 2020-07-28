#ifndef PNDSDSCLUSTER_H
#define PNDSDSCLUSTER_H

//#include "FairMultiLinkedData.h" 
#include "KoaDetectorList.h" // contains SensorSide enumeration
#include "FairMultiLinkedData_Interface.h"
#include "TObject.h"
#include <vector>
#include <iostream>


//! PndSdsCluster.h
//! @author T.Stockmanns <t.stockmanns@fz-juelich.de>
//!
//! \brief Class to store the Digis which belong to one cluster
//! This class holds the information which Digi belongs to the actual cluster.
//! The information is stored in a vector<Int_t> which contains the
//! position of the digi in the TClonesArray where it is stored.
class PndSdsCluster : public FairMultiLinkedData_Interface
{

friend std::ostream& operator<< (std::ostream& out, PndSdsCluster& cl){
      std::vector<Int_t> list = cl.GetClusterList();
      out << "Hits in Cluster: (" ;
      for (UInt_t i = 0; i<list.size();i++)
        out << list[i] << " ";
      out << ")" << std::endl;

      return out;
    }

public :
    PndSdsCluster():fClusterList(){};
    ~PndSdsCluster(){};
    PndSdsCluster(std::vector<Int_t> list);

    virtual void SetClusterList(Int_t DigiType, std::vector<Int_t> list, Int_t fileId, Int_t eventId) = 0;
    std::vector<Int_t> GetClusterList() const {return fClusterList;}
    Int_t GetClusterSize() const {return fClusterList.size();}
    Int_t GetDigiIndex(Int_t i) const {return fClusterList[i];}

    bool DigiBelongsToCluster(Int_t digiIndex);

    virtual void Print();

protected :
    std::vector<Int_t> fClusterList;


ClassDef(PndSdsCluster,2);

};

#endif
