#ifndef KOA_RAWEVENT_ANALYZER_H
#define KOA_RAWEVENT_ANALYZER_H

#include "FairRootManager.h"
#include "FairLogger.h"
#include "TObject.h"
#include "TFile.h"
#include "TString.h"

class KoaRawEventAnalyzer : public TObject
{
public:
  KoaRawEventAnalyzer() : fPersistence(false), fRootFile(nullptr) {}
  virtual ~KoaRawEventAnalyzer() {
    DeleteHist();

    if (fRootFile) {
      delete fRootFile;
    }
  }

  virtual void Init() {}
  virtual bool Analyze() { return true; }
  virtual void Finish() {
    if ( fPersistence && fRootFile ) {
      fRootFile->Write();
    }
  }

  virtual void Recycle() {}
  virtual void Fill() {}

  virtual void SetPersistence(bool flag) {
    fPersistence = flag;

    if (fPersistence) {
      FairRootManager* ioMan = FairRootManager::Instance();
      auto sink = ioMan->GetSink();
      if(!sink) {
        LOG(fatal) << "KoaRawEventAnalyzer::SetPersistence : no sink available, setup sink first";
      }

      TString fileName = sink->GetFileName();
      fileName.ReplaceAll(".root","_RawModuleBased.root");
      fRootFile = new TFile(fileName, "recreate");
    }
  }

private:
  virtual void Decode() {}

  virtual void InitHist() {}
  virtual void FillHist() {}
  virtual void DeleteHist() {}

protected:
  bool fPersistence;
  TFile* fRootFile;

  ClassDef(KoaRawEventAnalyzer, 1)
};
#endif
