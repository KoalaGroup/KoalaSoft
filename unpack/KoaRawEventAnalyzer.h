#ifndef KOA_RAWEVENT_ANALYZER_H
#define KOA_RAWEVENT_ANALYZER_H

#include "TObject.h"
#include "FairRootManager.h"

class KoaRawEventAnalyzer : public TObject
{
public:
  KoaRawEventAnalyzer() : fPersistence(false), fRootFile(nullptr) {}
  ~KoaRawEventAnalyzer() {
    DeleteHist();

    if (fRootFile) {
      delete fRootFile;
    }
  }

  virtual void Init() = 0;
  virtual bool Analyze() = 0;
  virtual void Finish() {
    if ( fPersistence && fRootFile ) {
      fRootFile->Write();
    }
  }

  virtual void Recycle() = 0;
  virtual void Fill() = 0;

  virtual void SetPersistence(bool flag) {
    fPersistence = flag;

    if (fPersistence) {
      FairRootManager* ioMan = FairRootManager::Instance();
      TString fileName = ioMan->GetSink()->GetFileName();
      fileName.ReplaceAll(".root","_RawModuleBased.root");
      fRootFile = new TFile(fileName, "recreate");
    }
  }

private:
  virtual void InitHist() = 0;
  virtual void FillHist() = 0;
  virtual void DeleteHist() = 0;

private:
  bool fPersistence;
  TFile* fRootFile;

  ClassDef(KoaRawEventAnalyzer, 1)
};
#endif
