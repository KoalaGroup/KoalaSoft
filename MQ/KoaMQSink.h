/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * KoaMQSink.h
 *
 * @since 2019-07-10
 * @author Y.Zhou
 * @modified from FairMQPixelFileSink
 */

#ifndef KOAMQSINK_H_
#define KOAMQSINK_H_

#include "TClonesArray.h"
#include "TFile.h"
#include "TFolder.h"
#include "TTree.h"
#include "FairEventHeader.h"

#include "FairMQDevice.h"

class KoaMQSink : public FairMQDevice
{
  public:
    KoaMQSink();
    virtual ~KoaMQSink();

    void SetOutputFileName(std::string tempString) { fFileName = tempString; }
    void AddOutputBranch  (std::string classString, std::string branchString) 
    { 
      fClassNames .push_back(classString); 
      fBranchNames.push_back(branchString); 
    }
    std::string GetOutputFileName () { return fFileName;}

    void SetInputChannelName (std::string tstr) {fInputChannelName = tstr;}
    void SetAckChannelName(std::string tstr) {fAckChannelName = tstr;}

  protected:
    bool StoreData(FairMQParts&, int);
    virtual void Init();

 private:
    std::string     fInputChannelName;
    std::string     fAckChannelName;

    std::string fFileName;
    std::string fTreeName;

    std::vector<std::string> fBranchNames;
    std::vector<std::string> fClassNames;

    std::string fFileOption;
    bool fFlowMode;
    bool fWrite;

    TFile* fOutFile;
    TTree* fTree;
    unsigned int    fNObjects;
    TObject**       fOutputObjects;
    /* FairEventHeader* fEventHeader; */
    /* TClonesArray*    fOutput; */
    TFolder* fFolder;

    KoaMQSink(const KoaMQSink&);
    KoaMQSink& operator=(const KoaMQSink&);
};

#endif /* KOAMQSINK_H_ */
