// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_digidIanalysisdIG__KoaAnalysisDict

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
#include "KoaAnaSolidAngle.h"
#include "KoaTransformToArray.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaAnaSolidAngle(void *p = 0);
   static void *newArray_KoaAnaSolidAngle(Long_t size, void *p);
   static void delete_KoaAnaSolidAngle(void *p);
   static void deleteArray_KoaAnaSolidAngle(void *p);
   static void destruct_KoaAnaSolidAngle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaAnaSolidAngle*)
   {
      ::KoaAnaSolidAngle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaAnaSolidAngle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaAnaSolidAngle", ::KoaAnaSolidAngle::Class_Version(), "", 23,
                  typeid(::KoaAnaSolidAngle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaAnaSolidAngle::Dictionary, isa_proxy, 4,
                  sizeof(::KoaAnaSolidAngle) );
      instance.SetNew(&new_KoaAnaSolidAngle);
      instance.SetNewArray(&newArray_KoaAnaSolidAngle);
      instance.SetDelete(&delete_KoaAnaSolidAngle);
      instance.SetDeleteArray(&deleteArray_KoaAnaSolidAngle);
      instance.SetDestructor(&destruct_KoaAnaSolidAngle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaAnaSolidAngle*)
   {
      return GenerateInitInstanceLocal((::KoaAnaSolidAngle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaAnaSolidAngle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaTransformToArray(void *p = 0);
   static void *newArray_KoaTransformToArray(Long_t size, void *p);
   static void delete_KoaTransformToArray(void *p);
   static void deleteArray_KoaTransformToArray(void *p);
   static void destruct_KoaTransformToArray(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaTransformToArray*)
   {
      ::KoaTransformToArray *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaTransformToArray >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaTransformToArray", ::KoaTransformToArray::Class_Version(), "", 105,
                  typeid(::KoaTransformToArray), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaTransformToArray::Dictionary, isa_proxy, 4,
                  sizeof(::KoaTransformToArray) );
      instance.SetNew(&new_KoaTransformToArray);
      instance.SetNewArray(&newArray_KoaTransformToArray);
      instance.SetDelete(&delete_KoaTransformToArray);
      instance.SetDeleteArray(&deleteArray_KoaTransformToArray);
      instance.SetDestructor(&destruct_KoaTransformToArray);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaTransformToArray*)
   {
      return GenerateInitInstanceLocal((::KoaTransformToArray*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaTransformToArray*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaAnaSolidAngle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaAnaSolidAngle::Class_Name()
{
   return "KoaAnaSolidAngle";
}

//______________________________________________________________________________
const char *KoaAnaSolidAngle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaAnaSolidAngle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaAnaSolidAngle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaAnaSolidAngle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaAnaSolidAngle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaAnaSolidAngle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaAnaSolidAngle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaAnaSolidAngle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaTransformToArray::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaTransformToArray::Class_Name()
{
   return "KoaTransformToArray";
}

//______________________________________________________________________________
const char *KoaTransformToArray::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTransformToArray*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaTransformToArray::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaTransformToArray*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaTransformToArray::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTransformToArray*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaTransformToArray::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaTransformToArray*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaAnaSolidAngle::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaAnaSolidAngle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaAnaSolidAngle::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaAnaSolidAngle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaAnaSolidAngle(void *p) {
      return  p ? new(p) ::KoaAnaSolidAngle : new ::KoaAnaSolidAngle;
   }
   static void *newArray_KoaAnaSolidAngle(Long_t nElements, void *p) {
      return p ? new(p) ::KoaAnaSolidAngle[nElements] : new ::KoaAnaSolidAngle[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaAnaSolidAngle(void *p) {
      delete ((::KoaAnaSolidAngle*)p);
   }
   static void deleteArray_KoaAnaSolidAngle(void *p) {
      delete [] ((::KoaAnaSolidAngle*)p);
   }
   static void destruct_KoaAnaSolidAngle(void *p) {
      typedef ::KoaAnaSolidAngle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaAnaSolidAngle

//______________________________________________________________________________
void KoaTransformToArray::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaTransformToArray.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaTransformToArray::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaTransformToArray::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaTransformToArray(void *p) {
      return  p ? new(p) ::KoaTransformToArray : new ::KoaTransformToArray;
   }
   static void *newArray_KoaTransformToArray(Long_t nElements, void *p) {
      return p ? new(p) ::KoaTransformToArray[nElements] : new ::KoaTransformToArray[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaTransformToArray(void *p) {
      delete ((::KoaTransformToArray*)p);
   }
   static void deleteArray_KoaTransformToArray(void *p) {
      delete [] ((::KoaTransformToArray*)p);
   }
   static void destruct_KoaTransformToArray(void *p) {
      typedef ::KoaTransformToArray current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaTransformToArray

namespace ROOT {
   static TClass *maplEintcOlonggR_Dictionary();
   static void maplEintcOlonggR_TClassManip(TClass*);
   static void *new_maplEintcOlonggR(void *p = 0);
   static void *newArray_maplEintcOlonggR(Long_t size, void *p);
   static void delete_maplEintcOlonggR(void *p);
   static void deleteArray_maplEintcOlonggR(void *p);
   static void destruct_maplEintcOlonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,long>*)
   {
      map<int,long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,long>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,long>", -2, "map", 99,
                  typeid(map<int,long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOlonggR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,long>) );
      instance.SetNew(&new_maplEintcOlonggR);
      instance.SetNewArray(&newArray_maplEintcOlonggR);
      instance.SetDelete(&delete_maplEintcOlonggR);
      instance.SetDeleteArray(&deleteArray_maplEintcOlonggR);
      instance.SetDestructor(&destruct_maplEintcOlonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,long> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,long>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOlonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,long>*)0x0)->GetClass();
      maplEintcOlonggR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOlonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOlonggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,long> : new map<int,long>;
   }
   static void *newArray_maplEintcOlonggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,long>[nElements] : new map<int,long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOlonggR(void *p) {
      delete ((map<int,long>*)p);
   }
   static void deleteArray_maplEintcOlonggR(void *p) {
      delete [] ((map<int,long>*)p);
   }
   static void destruct_maplEintcOlonggR(void *p) {
      typedef map<int,long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,long>

namespace {
  void TriggerDictionaryInitialization_G__KoaAnalysisDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/analysis",
"/home/yong/src/KoalaSoft/data",
"/home/yong/src/KoalaSoft/detectors/recoil/simple",
"/home/yong/src/KoalaSoft/tools",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_digi/analysis/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaAnalysisDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class KoaAnaSolidAngle;
class KoaTransformToArray;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaAnalysisDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOAANASOLIDANGLE_H
#define KOAANASOLIDANGLE_H

#include "FairTask.h"
#include <fstream>
#include <map>

class TClonesArray;
class KoaGeoHandler;

class KoaAnaSolidAngle : public FairTask
{
  public:

    /** Default constructor **/
    KoaAnaSolidAngle();

    /** Constructor with parameters (Optional) **/
    //  KoaAnaSolidAngle(Int_t verbose);


    /** Destructor **/
    ~KoaAnaSolidAngle();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();


    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    void SetMCEntryNo(Long_t entryNo);

 public:
    void SetOutFileName(const char* filename);

 private:
    KoaAnaSolidAngle(const KoaAnaSolidAngle&);
    KoaAnaSolidAngle operator=(const KoaAnaSolidAngle&);

    void Write();

 private:
    /** Input array from previous already existing data level **/
    TClonesArray* fPoints;
    KoaGeoHandler* fGeoHandler;

    Long_t fSi1NrHit[48];
    Long_t fSi2NrHit[64];
    Long_t fGe1NrHit[32];
    Long_t fGe2NrHit[32];
    std::map<Int_t,Long_t> fNrHit;
    Bool_t fMCEntryFromExternal;
    Long_t fMCEntryNo;
    Long_t fNrPoints;

    TString fFileName;
    std::ofstream fOutputFile;

    ClassDef(KoaAnaSolidAngle,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef KOA_TRANSFORMTOARRAY_H
#define KOA_TRANSFORMTOARRAY_H

#include "FairTask.h"
#include <map>

class TClonesArray;
class KoaRecDigi;
class TFile;
class TTree;

class KoaTransformToArray : public FairTask
{
  public:

    /** Default constructor **/
    KoaTransformToArray();

    /** Destructor **/
    ~KoaTransformToArray();


    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    /** Reset eventwise counters **/
    void Reset();

 public:
  void SetInputName(const char* name) {
    fInputName = name;
  }
  void SetOutputName(const char* name) {
    fOutputName = name;
  }
  void SetOutputFileName(const char* name) {
    fOutputFile = TFile::Open(name,"update");
  }

 private:
    // Input digit branch name
    std::string fInputName;
  // Output digit branch name
    std::string fOutputName;

    /** Input array from previous already existing data level **/
    TClonesArray* fInputDigis;

  TFile*    fOutputFile;
  TTree*    fTree;
  Double_t     fSi1[48];
  Double_t     fSi2[64];
  Double_t     fGe1[32];
  Double_t     fGe2[32];

    KoaTransformToArray(const KoaTransformToArray&);
    KoaTransformToArray operator=(const KoaTransformToArray&);

    ClassDef(KoaTransformToArray,1);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaAnaSolidAngle", payloadCode, "@",
"KoaTransformToArray", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaAnalysisDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaAnalysisDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaAnalysisDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaAnalysisDict() {
  TriggerDictionaryInitialization_G__KoaAnalysisDict_Impl();
}
