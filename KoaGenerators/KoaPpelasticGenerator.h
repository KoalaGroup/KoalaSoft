// -------------------------------------------------------------------------
// -----                 KoaPpelasticGenerator header file                  -----
// -----               Created 05/02/07  by S.Spataro                 -----
// -------------------------------------------------------------------------

/** KoaPpelasticGenerator.h
 *@author S.Spataro <stefano.spataro@exp2.physik.uni-giessen.de>
 *
 The KoaPpelasticGenerator reads the DPM output file (ROOT format)
 and inserts the tracks into the PndStack via the FairPrimaryGenerator.
 Derived from FairGenerator.
**/


#ifndef KOA_PPELASTICGENERATOR_H
#define KOA_PPELASTICGENERATOR_H


#include "FairGenerator.h"

class TClonesArray;
class TFile;
class TTree;
class FairPrimaryGenerator;



class KoaPpelasticGenerator : public FairGenerator
{

 public: 

  /** Default constructor (should not be used) **/
  KoaPpelasticGenerator();


  /** Standard constructor
   ** @param fileName The input (PLUTO) file name
   **/
  KoaPpelasticGenerator(const Char_t* fileName);


  /** Destructor **/
  virtual ~KoaPpelasticGenerator();


  /** Reads on event from the input file and pushes the tracks onto
   ** the stack. Abstract method in base class.
   ** @param primGen  pointer to the FairPrimaryGenerator
   **/
  virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  void SetStartEvent(Int_t start) { iEvent = start; };
	
 private:

  Int_t iEvent;      //! Event number
  const Char_t* fFileName;   //! Input file name
  TFile* fInputFile;        //! Pointer to input file
  TTree* fInputTree;        //! Pointer to input tree
  TClonesArray* fParticles;  //! Particle array from PLUTO

  /** Private method CloseInput. Just for convenience. Closes the 
   ** input file properly. Called from destructor and from ReadEvent. **/
  void CloseInput();


  ClassDef(KoaPpelasticGenerator,1);

};

#endif
