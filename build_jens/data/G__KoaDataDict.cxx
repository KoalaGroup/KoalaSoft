// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_jensdIdatadIG__KoaDataDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "MCData/KoaStack.h"
#include "MCData/KoaMCTrack.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaStack(void *p = 0);
   static void *newArray_KoaStack(Long_t size, void *p);
   static void delete_KoaStack(void *p);
   static void deleteArray_KoaStack(void *p);
   static void destruct_KoaStack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaStack*)
   {
      ::KoaStack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaStack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaStack", ::KoaStack::Class_Version(), "", 56,
                  typeid(::KoaStack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaStack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaStack) );
      instance.SetNew(&new_KoaStack);
      instance.SetNewArray(&newArray_KoaStack);
      instance.SetDelete(&delete_KoaStack);
      instance.SetDeleteArray(&deleteArray_KoaStack);
      instance.SetDestructor(&destruct_KoaStack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaStack*)
   {
      return GenerateInitInstanceLocal((::KoaStack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaStack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaMCTrack(void *p = 0);
   static void *newArray_KoaMCTrack(Long_t size, void *p);
   static void delete_KoaMCTrack(void *p);
   static void deleteArray_KoaMCTrack(void *p);
   static void destruct_KoaMCTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaMCTrack*)
   {
      ::KoaMCTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaMCTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaMCTrack", ::KoaMCTrack::Class_Version(), "", 264,
                  typeid(::KoaMCTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaMCTrack::Dictionary, isa_proxy, 4,
                  sizeof(::KoaMCTrack) );
      instance.SetNew(&new_KoaMCTrack);
      instance.SetNewArray(&newArray_KoaMCTrack);
      instance.SetDelete(&delete_KoaMCTrack);
      instance.SetDeleteArray(&deleteArray_KoaMCTrack);
      instance.SetDestructor(&destruct_KoaMCTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaMCTrack*)
   {
      return GenerateInitInstanceLocal((::KoaMCTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaMCTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaStack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaStack::Class_Name()
{
   return "KoaStack";
}

//______________________________________________________________________________
const char *KoaStack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaStack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaStack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaStack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaStack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaStack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaStack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaStack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaMCTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaMCTrack::Class_Name()
{
   return "KoaMCTrack";
}

//______________________________________________________________________________
const char *KoaMCTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMCTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaMCTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaMCTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaMCTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMCTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaMCTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaMCTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaStack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaStack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaStack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaStack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaStack(void *p) {
      return  p ? new(p) ::KoaStack : new ::KoaStack;
   }
   static void *newArray_KoaStack(Long_t nElements, void *p) {
      return p ? new(p) ::KoaStack[nElements] : new ::KoaStack[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaStack(void *p) {
      delete ((::KoaStack*)p);
   }
   static void deleteArray_KoaStack(void *p) {
      delete [] ((::KoaStack*)p);
   }
   static void destruct_KoaStack(void *p) {
      typedef ::KoaStack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaStack

//______________________________________________________________________________
void KoaMCTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaMCTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaMCTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaMCTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaMCTrack(void *p) {
      return  p ? new(p) ::KoaMCTrack : new ::KoaMCTrack;
   }
   static void *newArray_KoaMCTrack(Long_t nElements, void *p) {
      return p ? new(p) ::KoaMCTrack[nElements] : new ::KoaMCTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaMCTrack(void *p) {
      delete ((::KoaMCTrack*)p);
   }
   static void deleteArray_KoaMCTrack(void *p) {
      delete [] ((::KoaMCTrack*)p);
   }
   static void destruct_KoaMCTrack(void *p) {
      typedef ::KoaMCTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaMCTrack

namespace {
  void TriggerDictionaryInitialization_G__KoaDataDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/data/SdsData",
"/home/yong/src/KoalaSoft/data/TrackData",
"/home/yong/src/KoalaSoft/data/MCData",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_jens/data/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaDataDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Multi-Thread Enabled)ATTRDUMP"))) KoaStack;
class KoaMCTrack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaDataDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                       KoaStack header file                 -----
// -----                  M. Al-Turany   June 2014                     -----
// -------------------------------------------------------------------------

/** KoaStack.h
 **
 ** This class handles the particle stack for the transport simulation.
 ** For the stack FILO functionality, it uses the STL stack. To store
 ** the tracks during transport, a TParticle array is used.
 ** At the end of the event, tracks satisfying the filter criteria
 ** are copied to a KoaMCTrack array, which is stored in the output.
 **
 ** The filtering criteria for the output tracks are:
 ** - primary tracks are stored in any case.
 ** - secondary tracks are stored if they have a minimal number of
 **   points (sum of all detectors) and a minimal energy, or are the
 **
 ** The storage of secondaries can be switched off.
 ** The storage of all mothers can be switched off.
 ** By default, the minimal number of points is 1 and the energy cut is 0.
 **/

#ifndef KoaStack_H
#define KoaStack_H

#include "FairGenericStack.h" // for FairGenericStack

#include "KoaDetectorList.h" // for DetectorId

#include "Rtypes.h"     // for Int_t, Double_t, Bool_t, etc
#include "TMCProcess.h" // for TMCProcess

#include <map> // for map, map<>::iterator
#include <unordered_map>
#include <stack>   // for stack
#include <utility> // for pair

class TClonesArray;
class TParticle;
class TRefArray;

class KoaStack : public FairGenericStack
{

public:
  /** Default constructor
     *param size  Estimated track number
     **/
  KoaStack(Int_t size = 100);

  /** Destructor  **/
  virtual ~KoaStack();

  /** Add a TParticle to the stack.
     ** Declared in TVirtualMCStack
     *@param toBeDone  Flag for tracking
     *@param parentID  Index of mother particle
     *@param pdgCode   Particle type (PDG encoding)
     *@param px,py,pz  Momentum components at start vertex [GeV]
     *@param e         Total energy at start vertex [GeV]
     *@param vx,vy,vz  Coordinates of start vertex [cm]
     *@param time      Start time of track [s]
     *@param polx,poly,polz Polarisation vector
     *@param proc      Production mechanism (VMC encoding)
     *@param ntr       Track number (filled by the stack)
     *@param weight    Particle weight
     *@param is        Generation status code (whatever that means)
     **/
  virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                         Double_t px, Double_t py, Double_t pz,
                         Double_t e, Double_t vx, Double_t vy,
                         Double_t vz, Double_t time, Double_t polx,
                         Double_t poly, Double_t polz, TMCProcess proc,
                         Int_t &ntr, Double_t weight, Int_t is);

  virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                         Double_t px, Double_t py, Double_t pz,
                         Double_t e, Double_t vx, Double_t vy,
                         Double_t vz, Double_t time, Double_t polx,
                         Double_t poly, Double_t polz, TMCProcess proc,
                         Int_t &ntr, Double_t weight, Int_t is, Int_t secondParentId);

  /** Get next particle for tracking from the stack.
     ** Declared in TVirtualMCStack
     *@param  iTrack  index of popped track (return)
     *@return Pointer to the TParticle of the track
     **/
  virtual TParticle *PopNextTrack(Int_t &iTrack);

  /** Get primary particle by index for tracking from stack
     ** Declared in TVirtualMCStack
     *@param  iPrim   index of primary particle
     *@return Pointer to the TParticle of the track
     **/
  virtual TParticle *PopPrimaryForTracking(Int_t iPrim);

  /** Set the current track number
     ** Declared in TVirtualMCStack
     *@param iTrack  track number
     **/
  virtual void SetCurrentTrack(Int_t iTrack) { fCurrentTrack = iTrack; }

  /** Get total number of tracks
     ** Declared in TVirtualMCStack
     **/
  virtual Int_t GetNtrack() const { return fNParticles; }

  /** Get number of primary tracks
     ** Declared in TVirtualMCStack
     **/
  virtual Int_t GetNprimary() const { return fNPrimaries; }

  /** Get the current track's particle
     ** Declared in TVirtualMCStack
     **/
  virtual TParticle *GetCurrentTrack() const;

  /** Get the number of the current track
     ** Declared in TVirtualMCStack
     **/
  virtual Int_t GetCurrentTrackNumber() const { return fCurrentTrack; }

  /** Get the track number of the parent of the current track
     ** Declared in TVirtualMCStack
     **/
  virtual Int_t GetCurrentParentTrackNumber() const;

  /** Add a TParticle to the fParticles array **/
  virtual void AddParticle(TParticle *part);

  /** Fill the MCTrack output array, applying filter criteria **/
  virtual void FillTrackArray();

  /** Update the track index in the MCTracks and MCPoints **/
  virtual void UpdateTrackIndex(TRefArray *detArray = 0);

  /** Resets arrays and stack and deletes particles and tracks **/
  virtual void Reset();

  /** Register the MCTrack array to the Root Manager  **/
  virtual void Register();

  /** Output to screen
     **@param iVerbose: 0=events summary, 1=track info
     **/
  virtual void Print(Int_t iVerbose = 0) const;

  /** Modifiers  **/
  void StoreSecondaries(Bool_t choice = kTRUE) { fStoreSecondaries = choice; }
  void SetMinPoints(Int_t min) { fMinPoints = min; }
  void SetEnergyCut(Double_t eMin) { fEnergyCut = eMin; }
  void StoreMothers(Bool_t choice = kTRUE) { fStoreMothers = choice; }

  /** Increment number of points for the current track in a given detector
     *@param iDet  Detector unique identifier
     **/
  void AddPoint(DetectorId iDet);

  /** Increment number of points for an arbitrary track in a given detector
     *@param iDet    Detector unique identifier
     *@param iTrack  Track number
     **/
  void AddPoint(DetectorId iDet, Int_t iTrack);

  /** Accessors **/
  TParticle *GetParticle(Int_t trackId) const;
  TClonesArray *GetListOfParticles() { return fParticles; }

  /** Clone this object (used in MT mode only) */
  virtual FairGenericStack *CloneStack() const { return new KoaStack(*this); }

private:
  /** STL stack (FILO) used to handle the TParticles for tracking **/
  std::stack<TParticle *> fStack; //!

  /** Array of TParticles (contains all TParticles put into or created
     ** by the transport
     **/
  TClonesArray *fParticles; //!

  /** Array of KoaMCTracks containg the tracks written to the output **/
  TClonesArray *fTracks;

  /** STL map from particle index to storage flag  **/
  std::map<Int_t, Bool_t> fStoreMap;            //!
  std::map<Int_t, Bool_t>::iterator fStoreIter; //!

  /** STL map from particle index to track index  **/
  std::map<Int_t, Int_t> fIndexMap;            //!
  std::map<Int_t, Int_t>::iterator fIndexIter; //!

  /** mapping of track index to map of detector ID and number of MCPoints **/
  std::unordered_map<Int_t, std::unordered_map<Int_t, Int_t>> fPointsMap; //!

  /** Some indizes and counters **/
  Int_t fCurrentTrack; //! Index of current track
  Int_t fNPrimaries;   //! Number of primary particles
  Int_t fNParticles;   //! Number of entries in fParticles
  Int_t fNTracks;      //! Number of entries in fTracks
  Int_t fIndex;        //! Used for merging

  /** Variables defining the criteria for output selection **/
  Bool_t fStoreSecondaries;
  Int_t fMinPoints;
  Double32_t fEnergyCut;
  Bool_t fStoreMothers;

  /** Mark tracks for output using selection criteria  **/
  void SelectTracks();

  KoaStack(const KoaStack &);
  KoaStack &operator=(const KoaStack &);

  ClassDef(KoaStack, 2) // Multi-Thread Enabled
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                  KoaMCTrack header file                  -----
// -----                  M. Al-Turany   June 2014                     -----
// -------------------------------------------------------------------------

/** KoaMCTrack.h
 ** Data class for storing Monte Carlo tracks processed by the KoaStack.
 ** A KoaMCTrack can be a primary track put into the simulation or a
 ** secondary one produced by the transport through decay or interaction.
 **/

#ifndef KoaMCTrack_H
#define KoaMCTrack_H 1

#include "TObject.h"         // for TObject
#include "KoaDetectorList.h" // for DetectorId
#include "Rtypes.h"          // for Double_t, Int_t, Double32_t, etc
#include "TLorentzVector.h"  // for TLorentzVector
#include "TMath.h"           // for Sqrt
#include "TVector3.h"        // for TVector3

class TParticle;

class KoaMCTrack : public TObject
{

public:
  /**  Default constructor  **/
  KoaMCTrack();

  // /**  Standard constructor  **/
  // KoaMCTrack(Int_t pdgCode, Int_t motherID, Double_t px, Double_t py,
  //             Double_t pz, Double_t x, Double_t y, Double_t z,
  //             Double_t t, Int_t nPoints);

  /**  Copy constructor  **/
  KoaMCTrack(const KoaMCTrack &track);

  /**  Constructor from TParticle  **/
  KoaMCTrack(TParticle *particle);

  /**  Destructor  **/
  virtual ~KoaMCTrack() = default;

  /**  Output to screen  **/
  void Print(Int_t iTrack = 0) const;

  /**  Accessors  **/
  Int_t GetPdgCode() const { return fPdgCode; }
  Int_t GetMotherId() const { return fMotherId; }
  Double_t GetPx() const { return fPx; }
  Double_t GetPy() const { return fPy; }
  Double_t GetPz() const { return fPz; }
  Double_t GetStartX() const { return fStartX; }
  Double_t GetStartY() const { return fStartY; }
  Double_t GetStartZ() const { return fStartZ; }
  Double_t GetStartT() const { return fStartT; }
  Double_t GetMass() const;
  // Double_t GetEnergy() const {return fE;};
  Double_t GetE() const { return fE; };
  Double_t GetPt() const { return TMath::Sqrt(fPx * fPx + fPy * fPy); }
  Double_t GetP() const { return TMath::Sqrt(fPx * fPx + fPy * fPy + fPz * fPz); }
  Double_t GetRapidity() const;
  TVector3 GetMomentum() const { return TVector3(fPx, fPy, fPz); }
  TLorentzVector Get4Momentum() const;
  TVector3 GetStartVertex() const;

  /** Accessors to the number of MCPoints in the detectors **/
  // Int_t GetNPoints(DetectorId detId) const;

  /**  Modifiers  **/
  void SetMotherId(Int_t id) { fMotherId = id; }
  // void SetNPoints(Int_t iDet, Int_t np);

private:
  /**  PDG particle code  **/
  Int_t fPdgCode;

  /**  Index of mother track. -1 for primary particles.  **/
  Int_t fMotherId;

  /** Momentum components at start vertex [GeV]  **/
  Double32_t fPx, fPy, fPz, fE;

  /** Coordinates of start vertex [cm, ns]  **/
  Double32_t fStartX, fStartY, fStartZ, fStartT;

  ClassDef(KoaMCTrack, 2);
};

// ==========   Inline functions   ========================================

inline TLorentzVector KoaMCTrack::Get4Momentum() const
{
  return TLorentzVector(fPx, fPy, fPz, fE);
}

inline TVector3 KoaMCTrack::GetStartVertex() const
{
  return TVector3(fStartX, fStartY, fStartZ);
}

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaMCTrack", payloadCode, "@",
"KoaStack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaDataDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaDataDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaDataDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaDataDict() {
  TriggerDictionaryInitialization_G__KoaDataDict_Impl();
}
