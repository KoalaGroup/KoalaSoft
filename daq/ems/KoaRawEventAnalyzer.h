#ifndef KOA_RAWEVENT_ANALYZER_H
#define KOA_RAWEVENT_ANALYZER_H

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

  /* whether save data into array based tree */
  // CAVEAT: should be invoked after setting FairRootFileSink in macro
  void SetPersistence(bool flag) {
    fPersistence = flag;
    fRootFile = nullptr;

    if (fPersistence) {
      fRootFile = InitOutputFile();
    }
  }

  /* initialize */
  void Init() {
    LOG(info) << "KoaRawEventAnalyzer::Init";

    // 1. get channel mapping parameter
    InitChannelMap();

    // 2. get input event buffer
    InitInputBuffer();

    // 3. initialize output buffer
    InitOutputBuffer();

    // 4. initialize output tree
    InitOutputTree();

    // 5. initialize histograms
    InitHist();
  }

  /* analyze */
  virtual bool Analyze() {
    // 1. get the latest event from input buffer
    if (!NextEvent())  return false;

    // 2. decode
    Decode();

    // 3. update
    Update();

    // 4. fill tree
    FillTree();

    // 5. fill histograms
    FillHist();

    // 6. recycle input event buffer
    Recycle();

    return true;
  }

  /* finish */
 virtual void Finish() {
    if ( fPersistence && fRootFile ) {
      fRootFile->Write();
    }
  }


private:
  virtual TFile* InitOutputFile() = 0;

  virtual void InitInputBuffer() = 0;
  virtual void InitChannelMap() = 0;
  virtual void InitOutputBuffer() = 0;
  virtual void InitOutputTree() = 0;

  virtual bool NextEvent() = 0;
  virtual void Decode() = 0;
  virtual void FillTree() = 0;
  virtual void Recycle() = 0;

protected:
  virtual void InitHist() {}
  virtual void FillHist() {}
  virtual void DeleteHist() {}

  virtual void Update() {}

  bool fPersistence;
  TFile* fRootFile;

  ClassDef(KoaRawEventAnalyzer, 1)
};
#endif
