
#ifndef _Interaction_Function_Generic_Interface_H_
#define _Interaction_Function_Generic_Interface_H_

#include "interaction/func/name.h"
#include "list/interface.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <template<typename> typename DBuffer,typename GeomType,typename T>
  struct InteractionFuncGeneric {

    typedef InteractionFuncGeneric<DBuffer,GeomType,T>  Type;

    typedef void (*EFuncType)(
        const Vector<T>*,const unsigned int*, const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,Vector<T>*);
    typedef void (*GFuncType)(
        const Vector<T>*,const unsigned int*, const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,Vector<T>*,Vector<T>*);
    typedef void (*BFuncType)(
        const Vector<T>*,const unsigned int*, const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,Vector<T>*,Vector<T>*);

    InteractionFunctionName tag;
    List<T> tmvec;
    EFuncType EFunc;
    GFuncType GFunc;
    BFuncType BFunc;

    InteractionFuncGeneric() : tag(UnknownInteractionFunc),
        EFunc(NULL),GFunc(NULL),BFunc(NULL) {}
    InteractionFuncGeneric(const Type&) {
      Error("Copier of InteractionFuncGeneric Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for InteractionFuncGeneric Disabled!");
      return *this;
    }
    ~InteractionFuncGeneric() { clearData(); }

    void clearData() {
      tag=UnknownInteractionFunc; release(tmvec);
      EFunc=NULL; GFunc=NULL; BFunc=NULL;
    }

  };

  template <template<typename> typename DBuffer,typename GeomType,typename T>
  bool IsValid(const InteractionFuncGeneric<DBuffer,GeomType,T>& G) {
    return (G.tag!=UnknownInteractionFunc)&&(G.EFunc!=NULL)&&
           (G.GFunc!=NULL)&&(G.BFunc!=NULL);
  }

  template <template<typename> typename DBuffer,typename GeomType,typename T>
  void release(InteractionFuncGeneric<DBuffer,GeomType,T>& G) { G.clearData(); }

}

#endif

