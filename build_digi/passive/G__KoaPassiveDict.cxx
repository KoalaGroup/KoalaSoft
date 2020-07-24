// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIyongdIsrcdIKoalaSoftdIbuild_digidIpassivedIG__KoaPassiveDict

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
#include "KoaCave.h"
#include "KoaPipe.h"
#include "KoaGeoCave.h"
#include "KoaPassiveContFact.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KoaCave(void *p = 0);
   static void *newArray_KoaCave(Long_t size, void *p);
   static void delete_KoaCave(void *p);
   static void deleteArray_KoaCave(void *p);
   static void destruct_KoaCave(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaCave*)
   {
      ::KoaCave *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaCave >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaCave", ::KoaCave::Class_Version(), "", 27,
                  typeid(::KoaCave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaCave::Dictionary, isa_proxy, 4,
                  sizeof(::KoaCave) );
      instance.SetNew(&new_KoaCave);
      instance.SetNewArray(&newArray_KoaCave);
      instance.SetDelete(&delete_KoaCave);
      instance.SetDeleteArray(&deleteArray_KoaCave);
      instance.SetDestructor(&destruct_KoaCave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaCave*)
   {
      return GenerateInitInstanceLocal((::KoaCave*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaCave*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPipe(void *p = 0);
   static void *newArray_KoaPipe(Long_t size, void *p);
   static void delete_KoaPipe(void *p);
   static void deleteArray_KoaPipe(void *p);
   static void destruct_KoaPipe(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPipe*)
   {
      ::KoaPipe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPipe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPipe", ::KoaPipe::Class_Version(), "", 65,
                  typeid(::KoaPipe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPipe::Dictionary, isa_proxy, 4,
                  sizeof(::KoaPipe) );
      instance.SetNew(&new_KoaPipe);
      instance.SetNewArray(&newArray_KoaPipe);
      instance.SetDelete(&delete_KoaPipe);
      instance.SetDeleteArray(&deleteArray_KoaPipe);
      instance.SetDestructor(&destruct_KoaPipe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPipe*)
   {
      return GenerateInitInstanceLocal((::KoaPipe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPipe*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaGeoCave(void *p = 0);
   static void *newArray_KoaGeoCave(Long_t size, void *p);
   static void delete_KoaGeoCave(void *p);
   static void deleteArray_KoaGeoCave(void *p);
   static void destruct_KoaGeoCave(void *p);
   static void streamer_KoaGeoCave(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaGeoCave*)
   {
      ::KoaGeoCave *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaGeoCave >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaGeoCave", ::KoaGeoCave::Class_Version(), "", 113,
                  typeid(::KoaGeoCave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaGeoCave::Dictionary, isa_proxy, 16,
                  sizeof(::KoaGeoCave) );
      instance.SetNew(&new_KoaGeoCave);
      instance.SetNewArray(&newArray_KoaGeoCave);
      instance.SetDelete(&delete_KoaGeoCave);
      instance.SetDeleteArray(&deleteArray_KoaGeoCave);
      instance.SetDestructor(&destruct_KoaGeoCave);
      instance.SetStreamerFunc(&streamer_KoaGeoCave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaGeoCave*)
   {
      return GenerateInitInstanceLocal((::KoaGeoCave*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaGeoCave*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KoaPassiveContFact(void *p = 0);
   static void *newArray_KoaPassiveContFact(Long_t size, void *p);
   static void delete_KoaPassiveContFact(void *p);
   static void deleteArray_KoaPassiveContFact(void *p);
   static void destruct_KoaPassiveContFact(void *p);
   static void streamer_KoaPassiveContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KoaPassiveContFact*)
   {
      ::KoaPassiveContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KoaPassiveContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KoaPassiveContFact", ::KoaPassiveContFact::Class_Version(), "", 152,
                  typeid(::KoaPassiveContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KoaPassiveContFact::Dictionary, isa_proxy, 16,
                  sizeof(::KoaPassiveContFact) );
      instance.SetNew(&new_KoaPassiveContFact);
      instance.SetNewArray(&newArray_KoaPassiveContFact);
      instance.SetDelete(&delete_KoaPassiveContFact);
      instance.SetDeleteArray(&deleteArray_KoaPassiveContFact);
      instance.SetDestructor(&destruct_KoaPassiveContFact);
      instance.SetStreamerFunc(&streamer_KoaPassiveContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KoaPassiveContFact*)
   {
      return GenerateInitInstanceLocal((::KoaPassiveContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KoaPassiveContFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KoaCave::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaCave::Class_Name()
{
   return "KoaCave";
}

//______________________________________________________________________________
const char *KoaCave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaCave*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaCave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaCave*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaCave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaCave*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaCave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaCave*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPipe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPipe::Class_Name()
{
   return "KoaPipe";
}

//______________________________________________________________________________
const char *KoaPipe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPipe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPipe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPipe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPipe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPipe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPipe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPipe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaGeoCave::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaGeoCave::Class_Name()
{
   return "KoaGeoCave";
}

//______________________________________________________________________________
const char *KoaGeoCave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoCave*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaGeoCave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoCave*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaGeoCave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoCave*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaGeoCave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaGeoCave*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KoaPassiveContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KoaPassiveContFact::Class_Name()
{
   return "KoaPassiveContFact";
}

//______________________________________________________________________________
const char *KoaPassiveContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPassiveContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KoaPassiveContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KoaPassiveContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KoaPassiveContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPassiveContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KoaPassiveContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KoaPassiveContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KoaCave::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaCave.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaCave::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaCave::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaCave(void *p) {
      return  p ? new(p) ::KoaCave : new ::KoaCave;
   }
   static void *newArray_KoaCave(Long_t nElements, void *p) {
      return p ? new(p) ::KoaCave[nElements] : new ::KoaCave[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaCave(void *p) {
      delete ((::KoaCave*)p);
   }
   static void deleteArray_KoaCave(void *p) {
      delete [] ((::KoaCave*)p);
   }
   static void destruct_KoaCave(void *p) {
      typedef ::KoaCave current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaCave

//______________________________________________________________________________
void KoaPipe::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPipe.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KoaPipe::Class(),this);
   } else {
      R__b.WriteClassBuffer(KoaPipe::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPipe(void *p) {
      return  p ? new(p) ::KoaPipe : new ::KoaPipe;
   }
   static void *newArray_KoaPipe(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPipe[nElements] : new ::KoaPipe[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPipe(void *p) {
      delete ((::KoaPipe*)p);
   }
   static void deleteArray_KoaPipe(void *p) {
      delete [] ((::KoaPipe*)p);
   }
   static void destruct_KoaPipe(void *p) {
      typedef ::KoaPipe current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KoaPipe

//______________________________________________________________________________
void KoaGeoCave::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaGeoCave.

   FairGeoSet::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaGeoCave(void *p) {
      return  p ? new(p) ::KoaGeoCave : new ::KoaGeoCave;
   }
   static void *newArray_KoaGeoCave(Long_t nElements, void *p) {
      return p ? new(p) ::KoaGeoCave[nElements] : new ::KoaGeoCave[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaGeoCave(void *p) {
      delete ((::KoaGeoCave*)p);
   }
   static void deleteArray_KoaGeoCave(void *p) {
      delete [] ((::KoaGeoCave*)p);
   }
   static void destruct_KoaGeoCave(void *p) {
      typedef ::KoaGeoCave current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaGeoCave(TBuffer &buf, void *obj) {
      ((::KoaGeoCave*)obj)->::KoaGeoCave::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaGeoCave

//______________________________________________________________________________
void KoaPassiveContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class KoaPassiveContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KoaPassiveContFact(void *p) {
      return  p ? new(p) ::KoaPassiveContFact : new ::KoaPassiveContFact;
   }
   static void *newArray_KoaPassiveContFact(Long_t nElements, void *p) {
      return p ? new(p) ::KoaPassiveContFact[nElements] : new ::KoaPassiveContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_KoaPassiveContFact(void *p) {
      delete ((::KoaPassiveContFact*)p);
   }
   static void deleteArray_KoaPassiveContFact(void *p) {
      delete [] ((::KoaPassiveContFact*)p);
   }
   static void destruct_KoaPassiveContFact(void *p) {
      typedef ::KoaPassiveContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_KoaPassiveContFact(TBuffer &buf, void *obj) {
      ((::KoaPassiveContFact*)obj)->::KoaPassiveContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::KoaPassiveContFact

namespace {
  void TriggerDictionaryInitialization_G__KoaPassiveDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/home/yong/fairroot/v18_jun19/include",
"/home/yong/src/KoalaSoft/passive",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/fairsoft/jun19/include",
"/home/yong/fairsoft/jun19/include/root6",
"/home/yong/src/KoalaSoft/build_digi/passive/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__KoaPassiveDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(PNDCaveSD)ATTRDUMP"))) KoaCave;
class __attribute__((annotate(R"ATTRDUMP(KoaPIPE)ATTRDUMP"))) KoaPipe;
class __attribute__((annotate(R"ATTRDUMP(Class for the geometry of CAVE)ATTRDUMP"))) KoaGeoCave;
class __attribute__((annotate(R"ATTRDUMP(Factory for all Passive parameter containers)ATTRDUMP"))) KoaPassiveContFact;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__KoaPassiveDict dictionary payload"

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
// -----                    KoaCave  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef Cave_H
#define Cave_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for KoaCave::Class, ClassDef, etc

class KoaCave : public FairModule
{
  public:
    KoaCave(const char* name, const char* Title="Exp Cave");
    KoaCave();
    virtual ~KoaCave();
    virtual void ConstructGeometry();

    virtual FairModule* CloneModule() const;

  private:
    Double_t world[3];

    KoaCave(const KoaCave&);

    ClassDef(KoaCave,1) //PNDCaveSD
};

#endif //Cave_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaPipe file                                -----
// -----                Created by M. Al-Turany  June 2014             -----
// -------------------------------------------------------------------------

#ifndef PIPE_H
#define PIPE_H

#include "FairModule.h"

class KoaPipe : public FairModule {
  public:
    KoaPipe(const char * name, const char *Title="Koa Pipe");
    KoaPipe();

    virtual ~KoaPipe();
    virtual void ConstructGeometry();

    virtual FairModule* CloneModule() const;
   
 private:
    KoaPipe(const KoaPipe& rhs);
    KoaPipe& operator=(const KoaPipe& rhs);

    ClassDef(KoaPipe,1) //KoaPIPE

};

#endif //PIPE_H


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaGeoCave  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef MYGEOCAVE_H
#define MYGEOCAVE_H

#include "FairGeoSet.h"                 // for FairGeoSet
#include <iosfwd>                       // for fstream
#include "Rtypes.h"                     // for KoaGeoCave::Class, Bool_t, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoMedia;

class  KoaGeoCave : public FairGeoSet
{
  protected:
    TString name;
  public:
    KoaGeoCave();
    ~KoaGeoCave() {}
    const char* getModuleName(Int_t) {return name.Data();}
    Bool_t read(std::fstream&,FairGeoMedia*);
    void addRefNodes();
    void write(std::fstream&);
    void print();
    ClassDef(KoaGeoCave,0) // Class for the geometry of CAVE
};

#endif  /* !PNDGEOCAVE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    KoaPassiveContFact  file                    -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef PNDPASSIVECONTFACT_H
#define PNDPASSIVECONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc
#include "Rtypes.h"                     // for KoaPassiveContFact::Class, etc

class FairParSet;

class KoaPassiveContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    KoaPassiveContFact();
    ~KoaPassiveContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( KoaPassiveContFact,0) // Factory for all Passive parameter containers
};

#endif  /* !PNDPASSIVECONTFACT_H */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KoaCave", payloadCode, "@",
"KoaGeoCave", payloadCode, "@",
"KoaPassiveContFact", payloadCode, "@",
"KoaPipe", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__KoaPassiveDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__KoaPassiveDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__KoaPassiveDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__KoaPassiveDict() {
  TriggerDictionaryInitialization_G__KoaPassiveDict_Impl();
}
