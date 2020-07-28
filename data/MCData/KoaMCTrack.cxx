/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                   KoaMCTrack source file                   -----
// -----                  M. Al-Turany   June 2014                     -----
// ----- This is a light weight particle class that is saved to disk
// ----- instead of saveing the TParticle class
// ----- IT is also used for filtring the stack
// -------------------------------------------------------------------------

#include "KoaMCTrack.h"

#include "FairLogger.h"   // for FairLogger, etc
#include "TDatabasePDG.h" // for TDatabasePDG
#include "TParticle.h"    // for TParticle
#include "TParticlePDG.h" // for TParticlePDG

KoaMCTrack::KoaMCTrack()
    : TObject(),
      fPdgCode(0),
      fMotherId(-1),
      fPx(0.),
      fPy(0.),
      fPz(0.),
      fE(0.),
      fStartX(0.),
      fStartY(0.),
      fStartZ(0.),
      fStartT(0.)
{
}

KoaMCTrack::KoaMCTrack(const KoaMCTrack &track)
    : TObject(track),
      fPdgCode(track.fPdgCode),
      fMotherId(track.fMotherId),
      fPx(track.fPx),
      fPy(track.fPy),
      fPz(track.fPz),
      fE(track.fE),
      fStartX(track.fStartX),
      fStartY(track.fStartY),
      fStartZ(track.fStartZ),
      fStartT(track.fStartT)
{
}

KoaMCTrack::KoaMCTrack(TParticle *part)
    : TObject(),
      fPdgCode(part->GetPdgCode()),
      fMotherId(part->GetMother(0)),
      fPx(part->Px()),
      fPy(part->Py()),
      fPz(part->Pz()),
      fE(part->Energy()),
      fStartX(part->Vx()),
      fStartY(part->Vy()),
      fStartZ(part->Vz()),
      fStartT(part->T() * 1e09)
{
}

void KoaMCTrack::Print(Int_t trackId) const
{
  LOG(debug) << "Track " << trackId << ", mother : " << fMotherId << ", Type "
             << fPdgCode << ", momentum (" << fPx << ", " << fPy << ", "
             << fPz << ") GeV";
  // LOG(debug2) << "       Ref " << GetNPoints(kREF)
  //             << ", TutDet " << GetNPoints(kTutDet)
  //             << ", Rutherford " << GetNPoints(kFairRutherford);
}

Double_t KoaMCTrack::GetMass() const
{
  if (TDatabasePDG::Instance())
  {
    TParticlePDG *particle = TDatabasePDG::Instance()->GetParticle(fPdgCode);
    if (particle)
    {
      return particle->Mass();
    }
    else
    {
      return std::sqrt(fE * fE - fPx * fPx - fPy * fPy - fPz * fPz);
    }
  }
  return 0.;
}

Double_t KoaMCTrack::GetRapidity() const
{
  Double_t y = 0.5 * TMath::Log((fE + fPz) / (fE - fPz));
  return y;
}

ClassImp(KoaMCTrack)
