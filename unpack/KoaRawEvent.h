#ifndef KOA_RAW_EVENT_H
#define KOA_RAW_EVENT_H

class KoaRawEvent
{
 public:
  // Amplitudes
  Int_t     fSi1Amplitude[48];
  Int_t     fSi2Amplitude[64];
  Int_t     fGe1Amplitude[32];
  Int_t     fGe2Amplitude[32];
  Int_t     fRecRearAmplitude[4];
  Int_t     fFwdAmplitude[8];

  // Timestamps
  Float_t   fSi1Time[48];// unit: ns
  Float_t   fSi2Time[64];// unit: ns
  Float_t   fGe1Time[32];// unit: ns
  Float_t   fGe2Time[32];// unit: ns
  Float_t   fRecRearTime[4];// unit: ns
  Float_t   fFwdTime[8];// unit: ns

  // Mxdc32 Timestamp
  Long64_t  fTimestamp; 

  ClassDef(KoaRawEvent,1);
};
#endif
