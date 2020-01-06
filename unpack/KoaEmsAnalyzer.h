#ifndef KOA_EMS_ANALYZER_H
#define KOA_EMS_ANALYZER_H

#include "TObject.h"
#include "KoaRawEvent.h"

/* This class will decode the module data into koala specific event data.
 * May also generate some histograms.
 */
class KoaEmsAnalyzer : TObject
{

  ClassDef(KoaEmsAnalyzer, 1)
};
#endif
