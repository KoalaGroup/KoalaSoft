#ifndef KOA_EVENT_ANALYZER_H
#define KOA_EVENT_ANALYZER_H

#include "KoaRawEventAnalyzer.h"
#include "KoaEventData.h"
#include "KoaRawEvent.h"
#include "KoaEmsConfig.h"
#include <map>

class KoaEventAnalyzer : public KoaRawEventAnalyzer
{
public:
  KoaEventAnalyzer() {}
  ~KoaEventAnalyzer();

  virtual void Init();
  virtual bool Analyze();
  virtual void Finish();

  virtual void Recycle() { fCurrentEvent->Recycle(); }
  virtual void Fill();

private:
  void Decode();

  virtual void InitHist() {}
  virtual void FillHist() {}
  virtual void DeleteHist() {}

private:
  // koala event buffer
  KoaEventBuffer* fBuffer;
  KoaEventDataItem* fCurrentEvent;

  // ems configuration and channel mapping
  ModuleTable fModuleTable;
  ChannelMap fAmplitudeChannelMap;
  ChannelMap fTimeChannelMap;

  // output trees, each module has it's own tree
  std::map<ems_u32, TTree*> fTreeMap;

  // Koala Event Data, where the decoded module data are stored
  std::map<ems_u32, Int_t> fIndexMap; // mapping from module id to array index
  UChar_t *fModuleId;
  Char_t  *fResolution;
  Short_t   *fNrWords;
  Long64_t *fTimestamp;
  Int_t (*fData)[34];
  std::map<Int_t, Int_t*> fAmplitudeValueMapInput;
  std::map<Int_t, Float_t*> fTimeValueMapInput;

  // Output class data, where the channel mapping is resolved
  KoaRawEvent* fRawEvent;
  std::map<Int_t, Int_t*> fAmplitudeValueMapOutput;
  std::map<Int_t, Float_t*> fTimeValueMapOutput;

  ClassDef(KoaEventAnalyzer, 1)
};
#endif
