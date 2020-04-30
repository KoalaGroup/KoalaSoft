#include "FairPrimaryGenerator.h"
#include "FairLogger.h"
#include "KoaPythia8Generator.h"

// -----   Default constructor   -------------------------------------------
KoaPythia8Generator::KoaPythia8Generator()
{
  fId  = 2212;
  fMom = 15.;
  fUseRandom1 = kFALSE;
  fUseRandom3 = kTRUE;
}
// -------------------------------------------------------------------------

// -----   Default constructor   -------------------------------------------
Bool_t KoaPythia8Generator::Init()
{
  if (fUseRandom1) fRandomEngine = new PyTr1Rng();
  if (fUseRandom3) fRandomEngine = new PyTr3Rng();

  fPythia.setRndmEnginePtr(fRandomEngine);

  // Set Parameters
  for(auto setting : fParams) {
    fPythia.readString(setting);
    LOG(INFO) << "fPythia.readString(\"" << setting <<"\")";
  }

  LOG(INFO) << "Beam Type: " << fId;
  LOG(INFO) << "Beam Momentum: " << fMom;

  // Settings according to the obsolete init function
  fPythia.settings.mode("Beams:idA",   fId);
  fPythia.settings.mode("Beams:idB",   2212);
  fPythia.settings.mode("Beams:frameType",  3);
  fPythia.settings.parm("Beams:pxA",    0.);
  fPythia.settings.parm("Beams:pyA",    0.);
  fPythia.settings.parm("Beams:pzA",    fMom);
  fPythia.settings.parm("Beams:pxB",    0.);
  fPythia.settings.parm("Beams:pyB",    0.);
  fPythia.settings.parm("Beams:pzB",    0.);

  fPythia.init();

  return kTRUE;
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
KoaPythia8Generator::~KoaPythia8Generator()
{
}
// -------------------------------------------------------------------------

// -----   Passing the event   ---------------------------------------------
Bool_t KoaPythia8Generator::ReadEvent(FairPrimaryGenerator* cpg)
{
  Int_t npart = 0;
  while(npart == 0)
  {
    fPythia.next();
    for(int i=0; i<fPythia.event.size(); i++)
    {
      if(fPythia.event[i].isFinal())
      {
        npart++;
      };
    };
  };

  for(Int_t ii=0; ii<fPythia.event.size(); ii++)
    if(fPythia.event[ii].isFinal())
    {
      cpg->AddTrack((Int_t)fPythia.event[ii].id(),
                    (Double_t)fPythia.event[ii].px(),(Double_t)fPythia.event[ii].py(),(Double_t)fPythia.event[ii].pz(),
                    0.,0.,0.);
    };

  return kTRUE;
}
// -------------------------------------------------------------------------
void KoaPythia8Generator::SetParameters(std::string par)
{
  fParams.emplace_back(par);
}

// -------------------------------------------------------------------------
void KoaPythia8Generator::Print() {
  fPythia.settings.listAll();
}
// -------------------------------------------------------------------------

ClassImp(KoaPythia8Generator)

