#ifndef KOA_PYTHIA8_GENERATOR_H
#define KOA_PYTHIA8_GENERATOR_H 1

#include "FairGenerator.h"
#include "Pythia8/Basics.h"  // for RndmEngine
#include "Pythia8/Pythia.h"  // for Pythia
#include "TRandom1.h"
#include "TRandom3.h"
#include <vector>
#include <string>

class FairPrimaryGenerator;

using namespace Pythia8;

class PyTr1Rng : public RndmEngine
{
 public:
  PyTr1Rng() {
    rng = new TRandom1(gRandom->GetSeed());
  };
  virtual ~PyTr1Rng() {};

  Double_t flat() {
    return rng->Rndm();
  };

 private:
  TRandom1 *rng; //!
};

class PyTr3Rng : public RndmEngine
{
 public:
  PyTr3Rng() {
    rng = new TRandom3(gRandom->GetSeed());
  };
  virtual ~PyTr3Rng() {};

  Double_t flat() {
    return rng->Rndm();
  };

 private:
  TRandom3 *rng; //!
};




class KoaPythia8Generator : public FairGenerator
{
 public:

  /** default constructor **/
  KoaPythia8Generator();

  /** destructor **/
  virtual ~KoaPythia8Generator();

  /** public method ReadEvent **/
  Bool_t ReadEvent(FairPrimaryGenerator*);
  void SetParameters(std::string);
  void Print(); //!

  virtual Bool_t Init(); //!

  void SetId(Int_t id) {
    fId  = id;
  };
  void SetMom(Double_t mom) {
    fMom = mom;
  };
  void UseRandom1() {
    fUseRandom1 = kTRUE;
    fUseRandom3 = kFALSE;
  };
  void UseRandom3() {
    fUseRandom1 = kFALSE;
    fUseRandom3 = kTRUE;
  };

 public:
  Pythia fPythia;             //!

 private:
  RndmEngine* fRandomEngine;  //!
  std::vector<std::string> fParams;         //!

 protected:
  Int_t    fId;        // beam particle type
  Double_t fMom;       // pbar momentum
  Bool_t fUseRandom1;  // flag to use TRandom1
  Bool_t fUseRandom3;  // flag to use TRandom3 (default)

  ClassDef(KoaPythia8Generator,1);
};

#endif /* !KOA_PYTHIA8_GENERATOR_H */
