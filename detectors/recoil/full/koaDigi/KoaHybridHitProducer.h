
/** KoaHybridHitProducer.h
 **
 **/
        
#ifndef KOAHYBRIDHITPRODUCER_H
#define KOAHYBRIDHITPRODUCER_H 1

#include "PndSdsHybridHitProducer.h"
#include "PndSdsTotDigiPar.h"
#include "TString.h"

class KoaHybridHitProducer : public PndSdsHybridHitProducer
{
 public:

  /** Default constructor **/
 KoaHybridHitProducer();

  /** Destructor **/
  virtual ~KoaHybridHitProducer();

  /** Specific Parameter set loading **/
  virtual void SetParContainers();
  
  virtual InitStatus Init();

  /** Specify the branch & folder names for the I/O **/
  void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  
  /** Take default naming **/
  virtual void SetBranchNames();
    
  ClassDef(KoaHybridHitProducer,9);

};

#endif
