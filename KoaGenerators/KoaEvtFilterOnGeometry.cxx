// -------------------------------------------------------------------------
// -----                KoaEvtFilterOnGeometry source file                  -----
// -------------------------------------------------------------------------

#include "KoaEvtFilterOnGeometry.h"
#include "TParticle.h"
#include "TMath.h"

Bool_t KoaEvtFilterOnGeometry::EventMatches(Int_t evtNr)
{
  Bool_t kMatches = kFALSE;
  //
  Double_t Y,Z;
  for(Int_t iPart=0; iPart < fParticleList->GetEntriesFast(); iPart++){
    TParticle* particle = (TParticle*)fParticleList->At(iPart);
    if(0 == particle) {continue;}
    if(particle->Px() > 0){
      Y = fXDistance*(particle->Py()/particle->Px());
      Z = fXDistance*(particle->Pz()/particle->Px());
      if(!fUnlimitY && !fUnlimitZ){
        if((fYMin <= Y) &&
           (fYMax >= Y) &&
           (fZMin <= Z) &&
           (fZMax >= Z)){
          kMatches = kTRUE;
          break;
        }
      }
      else if(fUnlimitZ && !fUnlimitY){
        if((fYMin <= Y) && (fYMax >= Y)){
          kMatches = kTRUE;
          break;
        }
      }
      else if(fUnlimitY && !fUnlimitZ){
        if((fZMin <= Z) && (fZMax >= Z)){
          kMatches = kTRUE;
          break;
        }
      }
      else{
        kMatches = kTRUE;
        break;
      }
    }
  }
  return kMatches;
}
