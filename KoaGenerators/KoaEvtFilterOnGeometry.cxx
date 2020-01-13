// -------------------------------------------------------------------------
// -----                KoaEvtFilterOnGeometry source file                  -----
// -------------------------------------------------------------------------

#include "KoaEvtFilterOnGeometry.h"
#include "TParticle.h"
#include "TMath.h"

// As long as one primary particle hit the defined region, this event is accepted
Bool_t KoaEvtFilterOnGeometry::EventMatches(Int_t evtNr)
{
  Bool_t kMatches = kFALSE;
  //
  Double_t Y,Z;
  Double_t Vx, Vy, Vz;
  Double_t Px, Py, Pz;
  for(Int_t iPart=0; iPart < fParticleList->GetEntriesFast(); iPart++){
    TParticle* particle = (TParticle*)fParticleList->At(iPart);
    if(0 == particle) {continue;}
    if(( particle->Px()*fXDistance ) > 0){
      Vx = particle->Vx(); Px = particle->Px();
      Vy = particle->Vy(); Py = particle->Py();
      Vz = particle->Vz(); Pz = particle->Pz();

      Y = (fXDistance-Vx)*(Py/Px);
      Z = (fXDistance-Vx)*(Pz/Px);

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
