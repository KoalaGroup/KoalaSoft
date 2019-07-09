/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * KoaMQSampler.h
 *
 * @since 2019-07-08
 * @author Y.Zhou
 * @modified from FairMQPixelSampler
 */

#ifndef KOAMQSAMPLER_H_
#define KOAMQSAMPLER_H_

#include <string>
#include <thread>

#include "TClonesArray.h"

#include "FairFileSource.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class KoaMQSampler : public FairMQDevice
{
  public:
    KoaMQSampler();
    virtual ~KoaMQSampler();

    void AddInputFileName  (std::string tempString) { fFileNames  .push_back(tempString); }
    void AddInputBranchName(std::string tempString) { fBranchNames.push_back(tempString); }
    
    void SetMaxIndex(int64_t tempInt) {fMaxIndex=tempInt;}

    void SetSource(FairSource* tempSource) {fSource = tempSource;}

    void ListenForAcks();

    void SetOutputChannelName(std::string tstr) {fOutputChannelName = tstr;}
    void SetAckChannelName(std::string tstr) {fAckChannelName = tstr;}

 protected:
    virtual bool ConditionalRun();
    virtual void PreRun();
    virtual void PostRun();
    virtual void InitTask();
    
 private: 
    std::string     fOutputChannelName;
    std::string     fAckChannelName;

    FairRunAna*     fRunAna;
    FairSource*     fSource;
    TObject*        fInputObjects[100];
    int             fNObjects;
    int64_t         fMaxIndex;

    int             fEventCounter;

    std::vector<std::string>     fBranchNames;
    std::vector<std::string>     fFileNames;

    KoaMQSampler(const KoaMQSampler&);
    KoaMQSampler& operator=(const KoaMQSampler&);

    std::thread fAckListener;
};

#endif /* KOAMQSAMPLER_H_ */
