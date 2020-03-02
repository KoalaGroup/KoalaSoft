#ifndef KOA_EVENT_ANALYZER_H
#define KOA_EVENT_ANALYZER_H

#include "KoaRawEventAnalyzer.h"
#include "KoaEventData.h"
#include "KoaMxdc32Data.h"
#include "KoaRawEvent.h"
#include "KoaEmsConfig.h"
#include <map>

class KoaEventAnalyzer : public KoaRawEventAnalyzer
{
public:
  KoaEventAnalyzer() {}
  ~KoaEventAnalyzer();

private:
  void InitInputBuffer();
  void InitChannelMap();
  void InitOutputBuffer();
  void InitOutputTree();

  bool NextEvent();
  void Decode();
  void FillTree();
  void Recycle() { fCurrentEvent->Recycle(); }

private:
  // koala event buffer
  KoaEventBuffer* fBuffer; //!
  KoaEventDataItem* fCurrentEvent; //!

  // ems configuration and channel mapping
  ModuleTable fModuleTable; //!
  ChannelMap fAmplitudeChannelMap; //!
  ChannelMap fTimeChannelMap; //!

  // output trees, each module has it's own tree
  std::map<ems_u32, TTree*> fTreeMap; //!

  // Koala Event Data, where the decoded module data are stored
  std::map<ems_u32, Int_t> fIndexMap; //! mapping from module id to array index
  UChar_t *fModuleId; //!
  Char_t  *fResolution; //!
  Short_t   *fNrWords; //!
  Long64_t *fTimestamp; //!
  Int_t (*fData)[34]; //!
  std::map<Int_t, Int_t*> fAmplitudeValueMapInput; //!
  std::map<Int_t, Int_t*> fTimeValueMapInput; //!
  std::map<Int_t, Char_t*> fTimeResolutionMap; //!

  // Output class data, where the channel mapping is resolved
  KoaRawEvent* fRawEvent; //!
  std::map<Int_t, Int_t*> fAmplitudeValueMapOutput; //!
  std::map<Int_t, Float_t*> fTimeValueMapOutput; //!

  /* constexpr static Float_t fTimeUnit[] = {-1,1./256,2./256,4./256,8./256,16./256,32./256,64./256,128./256}; //! unit: ns */
  static const Float_t fTimeUnit[9];

  ClassDef(KoaEventAnalyzer, 1)
};
#endif
