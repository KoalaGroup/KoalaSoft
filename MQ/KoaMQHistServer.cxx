/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <mutex>

#include "KoaMQHistServer.h"
#include "FairLogger.h"
#include "RootSerializer.h"

#include "TObjArray.h"
#include "TH1.h"
#include "TMessage.h"
#include "THttpServer.h"

std::mutex mtx;

KoaMQHistServer::KoaMQHistServer()
    : FairMQDevice()
    , fInputChannelName("histogram-in")
    , fArrayHisto()
    , fNMessages(0)
    , fServer("http:8080")
    , fStopThread(false)
{
}

KoaMQHistServer::~KoaMQHistServer() {}

void KoaMQHistServer::InitTask()
{
    OnData(fInputChannelName, &KoaMQHistServer::ReceiveData);
}

bool KoaMQHistServer::ReceiveData(FairMQMessagePtr& msg, int index)
{
    TObject* tempObject = nullptr;
    Deserialize<RootSerializer>(*msg, tempObject);

    if (TString(tempObject->ClassName()).EqualTo("TObjArray"))
    {
        std::lock_guard<std::mutex> lk(mtx);
        TObjArray* arrayHisto = static_cast<TObjArray*>(tempObject);
        TH1* histogram_new;
        TH1* histogram_existing;
        for (Int_t i = 0; i < arrayHisto->GetEntriesFast(); i++)
        {
            TObject* obj = arrayHisto->At(i);
            TH1* histogram = static_cast<TH1*>(obj);
            int index1 = FindHistogram(histogram->GetName());
            if (-1 == index1)
            {
                histogram_new = static_cast<TH1*>(histogram->Clone());
                fArrayHisto.Add(histogram_new);
                fServer.Register("Histograms", histogram_new);
            }
            else
            {
                histogram_existing = static_cast<TH1*>(fArrayHisto.At(index1));
                histogram_existing->Add(histogram);
            }
        }

        arrayHisto->Clear();
    }

    fNMessages += 1;

    delete tempObject;

    return true;
}

void KoaMQHistServer::PreRun()
{
    fStopThread = false;
    fThread = std::thread(&KoaMQHistServer::UpdateHttpServer, this);
}

void KoaMQHistServer::UpdateHttpServer()
{
    while (!fStopThread)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lk(mtx);

        fServer.ProcessRequests();
    }
}

void KoaMQHistServer::PostRun()
{
    fStopThread = true;
    fThread.join();
}

int KoaMQHistServer::FindHistogram(const std::string& name)
{
    for (int i = 0; i < fArrayHisto.GetEntriesFast(); i++) {
      TObject* obj = fArrayHisto.At(i);
      if (TString(obj->GetName()).EqualTo(name)) {
        return i;
      }
    }
    return -1;
}
