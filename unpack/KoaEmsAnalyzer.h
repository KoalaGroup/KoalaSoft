#ifndef KOA_EMS_ANALYZER_H
#define KOA_EMS_ANALYZER_H

#include "TObject.h"
#include "KoaRawEvent.h"
#include "KoaEventData.h"
#include "KoaEmsEventData.h"

/* This class will decode the module data into koala specific event data.
 * May also generate some histograms.
 */
class KoaEmsAnalyzer : TObject
{
public:
  KoaEmsAnalyzer();
  ~KoaEmsAnalyzer();

  virtual void Init() {}

  /* return true if there is still koala event available, otherwise false */
  virtual bool Analyze() {
    // 1. check whether there is koala event available

    // 2. get the next koala event
    // 2.1 analyze this event
    // 2.2 fill into tree
    // 2.3 recycle this event

    // 3. if ems event buffer is not empty
    // 3.1 analyze this event
    // 3.2 fill into tree
    // 3.3 recycle this event
  }

  virtual void Finish() {}

  /*********************************************************************/
  void SetKoalaEventPersistence(bool flag);
  void SetEmsEventPersistence(bool flag);

private:
  // fill events into tree
  virtual void FillEmsEvent() = 0;
  virtual void FillKoalaEvent() = 0;

  // recycle the buffers
  virtual void RecycleEmsBuffer() = 0;
  virtual void RecycleKoalaBuffer() = 0;

private:
  bool fKoalaEventPersistence;
  bool fEmsEventPersistence;

  KoaRawEventAnalyzer* fKoalaEventAnalyzer;
  KoaRawEventAnalyzer* fEmsEventAnalyzer;

  ClassDef(KoaEmsAnalyzer, 1)
};
#endif
