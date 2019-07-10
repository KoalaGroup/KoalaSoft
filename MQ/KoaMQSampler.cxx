/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * KoaMQSampler.cxx
 *
 * @since 2019-07-08
 * @author Y.Zhou
 * @modified from FairMQPixelSampler
 */

#include "KoaMQSampler.h"

#include "RootSerializer.h"
#include "TClonesArray.h"

#include "FairMQLogger.h"
#include "FairMQMessage.h"

#include "FairSource.h"
#include "FairFileSource.h"

using namespace std;

KoaMQSampler::KoaMQSampler()
  : FairMQDevice()
  , fOutputChannelName("data-out")
  , fAckChannelName("")
  , fRunAna(NULL)
  , fSource(NULL)
  , fInputObjects()
  , fNObjects(0)
  , fMaxIndex(-1)
  , fEventCounter(0)
  , fBranchNames()
  , fFileNames()
  , fAckListener()
{
}

void KoaMQSampler::InitTask() 
{
  fFileNames         = fConfig->GetValue<std::vector<std::string>>("file-name");
  fMaxIndex          = fConfig->GetValue<int64_t>                 ("max-index");
  fBranchNames       = fConfig->GetValue<std::vector<std::string>>("branch-name");
  fOutputChannelName = fConfig->GetValue<std::string>             ("out-channel");
  fAckChannelName    = fConfig->GetValue<std::string>             ("ack-channel");

  // Needed or not ???
  fRunAna = new FairRunAna();

  // the default source is from ROOT file
  if ( fSource == NULL ){
    fSource = new FairFileSource(fFileNames.at(0).c_str());
    for ( unsigned int ifile = 1 ; ifile < fFileNames.size() ; ifile++ ) 
      ((FairFileSource*)fSource)->AddFile(fFileNames.at(ifile));
  }

  // Init source
  fSource->Init();
  LOG(info) << "Going to request " << fBranchNames.size() << "  branches:";
  for ( unsigned int ibrn = 0 ; ibrn < fBranchNames.size() ; ibrn++ ) {
    LOG(info) << " requesting branch \"" << fBranchNames[ibrn] << "\"";
    int branchStat = fSource->ActivateObject((TObject**)&fInputObjects[fNObjects],fBranchNames[ibrn].c_str()); // should check the status...
    if ( fInputObjects[fNObjects] ) {
      LOG(info) << "Activated object \"" << fInputObjects[fNObjects] << "\" with name \"" << fBranchNames[ibrn] << "\" (" << branchStat << "), it got name: \"" << fInputObjects[fNObjects]->GetName() << "\"";
      if ( strcmp(fInputObjects[fNObjects]->GetName(),fBranchNames[ibrn].c_str()) )
        if ( strcmp(fInputObjects[fNObjects]->ClassName(),"TClonesArray") == 0 ) 
          ((TClonesArray*)fInputObjects[fNObjects])->SetName(fBranchNames[ibrn].c_str());
      fNObjects++;
    }
  }

  if ( fMaxIndex < 0 )
    fMaxIndex = fSource->CheckMaxEventNo();
  LOG(info) << "Input source has " << fMaxIndex << " events.";
}

void KoaMQSampler::PreRun()
{
  if (fAckChannelName != "") {
    fAckListener = thread(&KoaMQSampler::ListenForAcks, this);
  }

  LOG(info) << "KoaMQSampler::PreRun() finished!";
}

bool KoaMQSampler::ConditionalRun()
{
  if ( fEventCounter == fMaxIndex ) return false;
  
  Int_t readEventReturn = fSource->ReadEvent(fEventCounter);

  if ( readEventReturn != 0 ) return false;
  
  FairMQParts parts;
  for ( int iobj = 0 ; iobj < fNObjects ; iobj++ ) {
    FairMQMessagePtr mess(NewMessage());
    Serialize<RootSerializer>(*mess,fInputObjects[iobj]);
    parts.AddPart(std::move(mess));
  }
  
  Send(parts, fOutputChannelName);
  
  fEventCounter++;

  return true;
}

void KoaMQSampler::PostRun()
{
  if (fAckChannelName != "") {
    fAckListener.join();
  }

  LOG(info) << "PostRun() finished!";
}

void KoaMQSampler::ListenForAcks()
{
  if(fAckChannelName != "") {
    Long64_t numAcks = 0;
    do {
      unique_ptr<FairMQMessage> ack(NewMessage());
      if (Receive(ack, fAckChannelName) >= 0) {
        numAcks++;
      }
    } while (numAcks < fMaxIndex);
          
    LOG(info) << "Acknowledged " << numAcks << " messages.";
  }
}

KoaMQSampler::~KoaMQSampler()
{
}
