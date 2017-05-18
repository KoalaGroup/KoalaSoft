// -------------------------------------------------------------------------
// -----                KoaPpelasticGenerator source file                  -----
// -------------------------------------------------------------------------


#include <iostream>
#include "TClonesArray.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TVector3.h"
#include "TParticle.h"
#include "KoaPpelasticGenerator.h"
#include "FairPrimaryGenerator.h"




using namespace std;

// -----   Default constructor   ------------------------------------------
KoaPpelasticGenerator::KoaPpelasticGenerator() {
  iEvent     = 0;
  fInputFile = NULL;
  fInputTree = NULL;
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
KoaPpelasticGenerator::KoaPpelasticGenerator(const Char_t* fileName) {
  iEvent     = 0;
  fFileName  = fileName;
  fInputFile = new TFile(fFileName);
  fInputTree = (TTree*) fInputFile->Get("data");
  fParticles = new TClonesArray("TParticle",100);
  fInputTree->SetBranchAddress("Particles", &fParticles);
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
KoaPpelasticGenerator::~KoaPpelasticGenerator() {
  CloseInput();
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t KoaPpelasticGenerator::ReadEvent(FairPrimaryGenerator* primGen) {

  // Check for input file
  if ( ! fInputFile ) {
    cout << "-E KoaPpelasticGenerator: Input file nor open!" << endl;
    return kFALSE;
  }

  // Check for number of events in input file
  if ( iEvent > fInputTree->GetEntries() ) {
    cout << "-E KoaPpelasticGenerator: No more events in input file!" << endl;
    CloseInput();
    return kFALSE;
  }
  TFile  *g=gFile;
  fInputFile->cd();
  fInputTree->GetEntry(iEvent++);
  g->cd();

   // Get number of particle in TClonesrray
  Int_t nParts = fParticles->GetEntriesFast();

  // Loop over particles in TClonesArray
  for (Int_t iPart=0; iPart < nParts; iPart++) {
    TParticle* part = (TParticle*) fParticles->At(iPart);
    Int_t pdgType = part->GetPdgCode();

    // Check if particle type is known to database
    if ( ! pdgType ) {
      cout << "-W KoaPpelasticGenerator: Unknown type " << part->GetPdgCode()
	   << ", skipping particle." << endl;
      continue;
    }

    Double_t px = part->Px();
    Double_t py = part->Py();
    Double_t pz = part->Pz();

    Double_t vx = part->Vx();
    Double_t vy = part->Vy();
    Double_t vz = part->Vz();

    // Give track to PrimaryGenerator
    primGen->AddTrack(pdgType, px, py, pz, vx, vy, vz);

  }        //  Loop over particle in event

  return kTRUE;

}
// ------------------------------------------------------------------------




// -----   Private method CloseInput   ------------------------------------
void KoaPpelasticGenerator::CloseInput() {
  if ( fInputFile ) {
    cout << "-I KoaPpelasticGenerator: Closing input file " << fFileName
	 << endl;
    fInputFile->Close();
    delete fInputFile;
  }
  fInputFile = NULL;
}
// ------------------------------------------------------------------------



ClassImp(KoaPpelasticGenerator)
