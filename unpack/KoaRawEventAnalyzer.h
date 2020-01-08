#ifndef KOA_RAWEVENT_ANALYZER_H
#define KOA_RAWEVENT_ANALYZER_H

#include "TObject.h"
#include "FairRootManager.h"

class KoaRawEventAnalyzer : public TObject
{
public:
  KoaRawEventAnalyzer() : fPersistence(false), fRootFile(nullptr) {}
  ~KoaRawEventAnalyzer() {}

  virtual void Init() = 0;
  virtual bool Analyze() = 0;
  virtual void Finish() = 0;

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
  bool fPersistence;
  TFile* fRootFile;

  ClassDef(KoaRawEventAnalyzer, 1)
};
#endif
