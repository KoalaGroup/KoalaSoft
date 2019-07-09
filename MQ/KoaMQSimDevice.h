/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * KoaMQSimDevice.h
 *
 * @since 2019-07-08
 * @author Y.Zhou
 * @modified from FairMQSimDevice
 */

#ifndef KOAMQSIMDEVICE_H_
#define KOAMQSIMDEVICE_H_

#include <string>
#include "TString.h"

#include "FairMQDevice.h"

class FairEventHeader;
class FairRunSim;
class FairField;
class FairParIo;
class FairPrimaryGenerator;
class TObject;
class TObjArray;
class FairSink;

class KoaMQSimDevice : public FairMQDevice
{
 public:
    KoaMQSimDevice();
    virtual ~KoaMQSimDevice();

    virtual void        SendBranches();

    // ------ FairRunSim setters ------
    void SetNofEvents       (int64_t nofev)                 { fNofEvents = nofev;};
    void SetTransportName   (std::string str)               { fTransportName = str;};
    void SetMaterials       (std::string str)               { fMaterialsFile = str;};
    void SetMagneticField   (FairField* field)              { fMagneticField = field;};
    void SetDetectorArray   (TObjArray* array)              { fDetectorArray = array;};
    void SetGenerator       (FairPrimaryGenerator* primGen) { fPrimaryGenerator = primGen;};
    void SetStoreTraj       (bool flag=true)                { fStoreTrajFlag = flag;};
    void SetTaskArray       (TObjArray* array)              { fTaskArray = array;};
    void SetFirstParameter  (FairParIo* par)                { fFirstParameter  = par;};
    void SetSecondParameter (FairParIo* par)                { fSecondParameter = par;};
    void SetUserConfig      (const TString& Config)         { fUserConfig = Config;}
    void SetUserCuts        (const TString& Cuts)           { fUserCuts = Cuts;}
    void SetSink            (FairSink* sink)                { fSink = sink;}
    // ------ ---------- -------- ------

    void SetParamUpdateChannelName(TString tString) { fUpdateChannelName = tString; }

 protected:
    virtual void InitTask();
    virtual void PreRun();
    virtual void PostRun();
    virtual bool ConditionalRun();

 private:
    UInt_t fSimDeviceId;
    std::string fUpdateChannelName;

    FairRunSim*     fRunSim;
    // ------ FairRunSim settings ------
    int64_t               fNofEvents;
    std::string           fTransportName;
    std::string           fMaterialsFile;
    FairField*            fMagneticField;
    TObjArray*            fDetectorArray;
    FairPrimaryGenerator* fPrimaryGenerator;
    bool                  fStoreTrajFlag;
    TObjArray*            fTaskArray;
    FairParIo*            fFirstParameter;    // first (prefered) input for parameters
    FairParIo*            fSecondParameter;   // second input (used if not found in first input)
    TString               fUserConfig;        //!                  /** Macro for geant configuration*/
    TString               fUserCuts;          //!                  /** Macro for geant cuts*/
    FairSink*             fSink;
    // ------ ---------- -------- ------

    void UpdateParameterServer();
    void SendObject(TObject* obj, std::string chan);

    KoaMQSimDevice(const KoaMQSimDevice&);
    KoaMQSimDevice& operator=(const KoaMQSimDevice&);
};

#endif /* KOAMQSIMDEVICE_H_ */