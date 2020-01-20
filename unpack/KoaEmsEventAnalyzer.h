#ifndef KOA_EMSEVENT_ANALYZER_H
#define KOA_EMSEVENT_ANALYZER_H

#include "KoaRawEventAnalyzer.h"
#include "KoaEmsEventData.h"
#include <map>

class KoaEmsRawEvent;
class TTree;

class KoaEmsEventAnalyzer : public KoaRawEventAnalyzer
{
 public:
  KoaEmsEventAnalyzer() : fInitialEvent(true) {}
  ~KoaEmsEventAnalyzer();

  virtual void Init();
  virtual bool Analyze();
  virtual void Recycle() { fCurrentEvent->Recycle(); }
  virtual void Fill();

 private:
  virtual void Decode();

  virtual void InitHist() {}
  virtual void FillHist();
  virtual void DeleteHist() {}

  void UpdateRate();

 private:
  // ems event buffer and current item
  KoaEmsEventBuffer* fBuffer;
  KoaEmsEventDataItem* fCurrentEvent;

  // decoded ems event data
  KoaEmsRawEvent* fCurrentRawEvent;
  KoaEmsRawEvent* fPreviousRawEvent;

  // output tree
  TTree* fTree;
  std::map<std::string, int> fScalorChMap;

  // rate container
  bool fInitialEvent; // flag for the first coming event
  Long_t fCurrentTime; // unit: second

  using RateMap = std::map<std::string, double>; // map from scalor channel name to scalor counter value
  RateMap fRates;
  std::vector<Long_t> fSpareTime; // array of timestamp in a  long period when no event comes

  ClassDef(KoaEmsEventAnalyzer, 1)
};
#endif
