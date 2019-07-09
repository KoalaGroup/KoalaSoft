/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * KoaMQSimSink.cxx
 *
 * @since 2019-07-09
 * @author Y.Zhou
 * @modified from FairOnlineSink
 */

#include "KoaMQSimSink.h"
  
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "FairMQProgOptions.h"

#include "KoaMQSimDevice.h"
#include "FairRootManager.h"

#include "FairEventHeader.h"
#include "FairModule.h"
#include "FairPrimaryGenerator.h"
#include "FairParRootFileIo.h"
#include "FairParSet.h"

#include "FairMCEventHeader.h"

#include "TROOT.h"
#include "TRint.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"
#include "TList.h"
#include "TObjString.h"
#include "TObjArray.h"

using namespace std;

KoaMQSimSink::KoaMQSimSink()
  : FairSink()
  , fMQSimDevice(NULL)
{
}

KoaMQSimSink::~KoaMQSimSink()
{
}

//_____________________________________________________________________________
void KoaMQSimSink::RegisterImpl(const char* , const char* , void* )
{
  return;
}

//_____________________________________________________________________________
void KoaMQSimSink::RegisterAny(const char* /* brname */, const std::type_info &/* oi */, const std::type_info &/* pi */, void* /* obj */)
{
  return;
}

void  KoaMQSimSink::Fill()
{
  /// Fill the Root tree.
  LOG(DEBUG) << "called KoaMQSimSink::Fill()!!!!";
  
  if ( fMQSimDevice )
      fMQSimDevice->SendBranches();
}
 
Bool_t KoaMQSimSink::InitSink()
{
    return kTRUE;
}

void  KoaMQSimSink::Reset()
{
}

void  KoaMQSimSink::Close()
{
}
