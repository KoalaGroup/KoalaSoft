// -------------------------------------------------------------------------
// -----                  PndLmdHitProducerIdeal header file           -----
// -----                    Created 04/02/10 by M. Michel              -----
// -----            Based on CbmStsHitProducerIdel by V. Friese        -----
// -------------------------------------------------------------------------


/** CbmStsHitProducerIdeal.h
 *@author V.Friese <v.friese@gsi.de>
 **
 ** The ideal hit producer produces hits of type CbmStsMapsHit by copying
 ** the MCPoint position. The position error is set to 1 mum, much 
 ** smaller than can be obtained by any detector. Using the hits from 
 ** this HitProducer is thus equivalent to using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDLMDHITPRODUCERIDEAL_H
#define PNDLMDHITPRODUCERIDEAL_H 

#include "PndSdsHitProducerIdeal.h"
 
class TClonesArray;

class PndLmdHitProducerIdeal : public PndSdsHitProducerIdeal
{
 public:

  /** Default constructor **/  
  PndLmdHitProducerIdeal();


  /** Destructor **/
  virtual ~PndLmdHitProducerIdeal();

  virtual void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  virtual void SetBranchNames();


  ClassDef(PndLmdHitProducerIdeal,4);

};

#endif
