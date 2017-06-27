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
  Double_t kZ, kY, kX;
  kY=15.; kZ=30.; kX=100;

  Double_t Y,Z;
  for(Int_t iPart=0; iPart < fParticleList->GetEntriesFast(); iPart++){
    TParticle* particle = (TParticle*)fParticleList->At(iPart);
    if(0 == particle) {continue;}
    if(particle->Px() > 0){
      Y = kX*(particle->Py()/particle->Px());
      Z = kX*(particle->Pz()/particle->Px());
      if( (TMath::Abs(Y) <= kY) && TMath::Abs(Z) <= kZ){
        kMatches = kTRUE;
        break;
      }
    }
  }
  return kMatches;
}
