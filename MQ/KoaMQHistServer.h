/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAMQHISTOSERVER_H
#define KOAMQHISTOSERVER_H

#include "FairMQDevice.h"

#include "THttpServer.h"
#include "TObjArray.h"

#include <thread>
#include <string>
#include <memory>

class KoaMQHistoServer : public FairMQDevice
{
  public:
    KoaMQHistoServer();

    virtual ~KoaMQHistoServer();

    void UpdateHttpServer();

  protected:
    virtual void InitTask();

    bool ReceiveData(FairMQMessagePtr& msg, int index);

    virtual void PreRun();

    virtual void PostRun();

 private:
    InitHttp(); // Initialize THttpServer in constructor
    DefaultHttpItemField(); // Default THttpServer setting
    RegisterHttpCommand(); // Add command button to THttpServer

    TObject* RegisterHttpObject(const std::string& name);

  private:
    std::string fInputChannelName;

    // histograms and graphs need different process
    std::unordered_map<std::string, TObject*> fMapObj;

    int fNMessages;

    THttpServer fServer;

    std::thread fThread;
    bool fStopThread;

    KoaMQHistoServer(const KoaMQHistoServer&);
    KoaMQHistoServer& operator=(const KoaMQHistoServer&);
};

#endif
