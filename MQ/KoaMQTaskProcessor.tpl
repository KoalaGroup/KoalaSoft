/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

template <typename T>
KoaMQTaskProcessor<T>::KoaMQTaskProcessor()
    : fInputChannelName("data-in")
    , fOutputChannelName("data-out")
    , fParamChannelName("param")
    , fEventHeader(nullptr)
    , fMCEventHeader(nullptr)
    , fInput(nullptr)
    , fOutput(nullptr)
    , fStaticParameters(false)
    , fNewRunId(1)
    , fCurrentRunId(-1)
    , fDataToKeep("")
    , fReceivedMsgs(0)
    , fSentMsgs(0)
    , fFairTask(nullptr)
    , fParCList(nullptr)
    , fGeoPar(nullptr)
{
}

template <typename T>
KoaMQTaskProcessor<T>::~KoaMQTaskProcessor()
{
    delete fGeoPar;
    fGeoPar = nullptr;
    delete fInput;
    fInput = nullptr;
    delete fOutput;
    fOutput = nullptr;
    delete fFairTask;
}


template <typename T>
void KoaMQTaskProcessor<T>::Init()
{
    fDataToKeep        = fConfig->GetValue<std::string>("keep-data");
    fInputChannelName  = fConfig->GetValue<std::string>("in-channel");
    fOutputChannelName = fConfig->GetValue<std::string>("out-channel");
    fParamChannelName  = fConfig->GetValue<std::string>("par-channel");
    fStaticParameters  = fConfig->GetValue<bool>       ("static-pars");

    fFairTask = new T();
    fFairTask->SetStreamProcessing(kTRUE);
    fGeoPar = new FairGeoParSet("FairGeoParSet");
    fParCList = new TList();
    fParCList->Add(fGeoPar);
    fFairTask->GetParList(fParCList);

    fOutput = new TList();
    fInput = new TList();

    OnData(fInputChannelName, &FairMQPixelTaskProcessor<T>::ProcessData);
}

template <typename T>
bool KoaMQTaskProcessor<T>::ProcessData(FairMQParts& parts, int /*index*/)
{
    TObject* objectToKeep = nullptr;

    // LOG(debug)<<"message received with " << parts.Size() << " parts.";
    fReceivedMsgs++;

    std::vector<TObject*> tempObjects;
    for (int ipart = 0; ipart < parts.Size(); ipart++)
    {
        TObject* obj = nullptr;
        Deserialize<RootSerializer>(*parts.At(ipart),obj);
        tempObjects.push_back(obj);
        // LOG(trace) << "got TObject with name \"" << tempObjects[ipart]->GetName() << "\".";
        if (strcmp(tempObjects.back()->GetName(),"EventHeader.") == 0)
        {
            fEventHeader = (FairEventHeader*)(tempObjects.back());
        }
        if (strcmp(tempObjects.back()->GetName(),"MCEventHeader.") == 0)
        {
            fMCEventHeader = (FairMCEventHeader*)(tempObjects.back());
        }
        else
        {
            fInput->Add(tempObjects.back());
        }
    }

    if ( fStaticParameters == false || fCurrentRunId == -1 ) {
        // TODO: create fEventHeader form fMCEventHeader, if not there
        if ( fEventHeader )
            fNewRunId = fEventHeader->GetRunId();
        else if ( fMCEventHeader )
            fNewRunId = fMCEventHeader->GetRunID();

    // LOG(debug)<<"got event header with run = " << fNewRunId;

        if (fNewRunId != fCurrentRunId)
        {
            fCurrentRunId = fNewRunId;
            UpdateParameters();
            fFairTask->InitMQ(fParCList);

            LOG(info) << "Parameters updated, back to ProcessData(" << parts.Size() << " parts!)";
        }
    }

    // Execute hit finder task
    fOutput->Clear();
    // LOG(info) << " The blocking line... analyzing event " << fEventHeader->GetMCEntryNumber();
    fFairTask->ExecMQ(fInput, fOutput);

    if (!fDataToKeep.empty())
    {
        objectToKeep = (fInput->FindObject(fDataToKeep.c_str()))->Clone();
        if (objectToKeep) fOutput->Add(objectToKeep);
    }

    FairMQParts partsOut;

    if ( fEventHeader ) {
        FairMQMessagePtr mess(NewMessage());
        Serialize<RootSerializer>(*mess,fEventHeader);
        partsOut.AddPart(std::move(mess));
    }
    else if ( fMCEventHeader ) {
        FairMQMessagePtr mess(NewMessage());
        Serialize<RootSerializer>(*mess,fMCEventHeader);
        partsOut.AddPart(std::move(mess));
    }

    for (int iobj = 0; iobj < fOutput->GetEntries(); iobj++) {
        FairMQMessagePtr mess(NewMessage());
        Serialize<RootSerializer>(*mess,fOutput->At(iobj));
        partsOut.AddPart(std::move(mess));
    }

    Send(partsOut, fOutputChannelName);
    fSentMsgs++;

    fInput->Clear();

    for (unsigned int ipart = 0; ipart < tempObjects.size(); ipart++)
        {
            if (tempObjects[ipart])
                {
                    delete tempObjects[ipart];
                }
        }

    tempObjects.clear();

    return true;
}

template <typename T>
void KoaMQTaskProcessor<T>::PostRun()
{
    LOG(info) << "KoaMQTaskProcessor<T>::PostRun() Received " << fReceivedMsgs << " and sent " << fSentMsgs << " messages!";
}

template <typename T>
void KoaMQTaskProcessor<T>::UpdateParameters()
{
  for (int iparC = 0; iparC < fParCList->GetEntries(); iparC++) {
    FairParGenericSet* tempObj = (FairParGenericSet*)(fParCList->At(iparC));
    fParCList->Remove(tempObj);
    fParCList->AddAt(UpdateParameter(tempObj), iparC);
  }
}

template <typename T>
FairParGenericSet* KoaMQTaskProcessor<T>::UpdateParameter(FairParGenericSet* thisPar)
{
    std::string paramName = thisPar->GetName();
    //  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));
    LOG(debug) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << " (" << thisPar << ")";

    FairMQMessagePtr req(NewMessage(const_cast<char*>(reqStr->c_str()),
                                    reqStr->length(),
                                    [](void* /* data */, void* hint){ delete static_cast<std::string*>(hint); },
                                    reqStr));
    FairMQMessagePtr rep(NewMessage());

    if (Send(req, fParamChannelName) > 0)
    {
        if (Receive(rep, fParamChannelName) > 0)
        {
            thisPar = nullptr;
            Deserialize<RootSerializer>(*rep,thisPar);
            LOG(info) << "Received parameter"<< paramName <<" from the server (" << thisPar << ")";
            return thisPar;
        }
    }

    return nullptr;
}
