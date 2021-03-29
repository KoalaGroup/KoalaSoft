
/** PndLmdHybridHitProducer.h
 **
 **/
        
#ifndef KOALAHYBRIDHITPRODUCER_H
#define KOALAHYBRIDHITPRODUCER_H 1

#include "PndSdsHybridHitProducer.h"
#include "PndSdsTotDigiPar.h"
#include "TString.h"

class LumiHybridHitProducer : public PndSdsHybridHitProducer
{
 public:

  /** Default constructor **/
 LumiHybridHitProducer();

  /** Destructor **/
  virtual ~LumiHybridHitProducer();

  /** Specific Parameter set loading **/
  virtual void SetParContainers();
  
  virtual InitStatus Init();

  /** Specify the branch & folder names for the I/O **/
  void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  
  /** Take default naming **/
  virtual void SetBranchNames();
    
  ClassDef(LumiHybridHitProducer,9);

};

#endif
