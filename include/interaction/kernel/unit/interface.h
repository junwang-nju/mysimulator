
#ifndef _Interaction_Kernel_Unit_Interface_H_
#define _Interaction_Kernel_Unit_Interface_H_

#include "interaction/func/name.h"
#include "list/interface.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer, typename GeomType, typename T>
  struct InteractionKernelUnit {

    typedef InteractionKernelUnit<DBuffer,GeomType,T>   Type;

    typedef void (*EFuncType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,Vector<T>*);
    typedef void (*GFuncType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,Vector<T>*,Vector<T>*);
    typedef void (*BFuncType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,Vector<T>*,Vector<T>*);

    InteractionFunctionName tag;
    List<T> tmvec;
    EFuncType EFunc;
    GFuncType GFunc;
    BFuncType BFunc;

    InteractionKernelUnit()
      : tag(UnknownInteractionFunc), tmvec(),
        EFunc(NULL),GFunc(NULL),BFunc(NULL) {}
    InteractionKernelUnit(const Type&) {
      Error("Copier of InteractionKernelUnit Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for InteractionKernelUnit Disabled!");
      return *this;
    }
    ~InteractionKernelUnit() { clearData(); }

    void clearData() {
      tag=UnknownInteractionFunc; release(tmvec);
      EFunc=NULL; GFunc=NULL; BFunc=NULL;
    }

  };

  template <template<typename> class DBuffer, typename GeomType, typename T>
  bool IsValid(const InteractionKernelUnit<DBuffer,GeomType,T>& KU) {
    return (KU.tag!=UnknownInteractionFunc)&&(KU.EFunc!=NULL)&&
           (KU.GFunc!=NULL)&&(KU.BFunc!=NULL);
  }

  template <template<typename> class DBuffer, typename GeomType, typename T>
  void release(InteractionKernelUnit<DBuffer,GeomType,T>& KU){ KU.clearData(); }

}

#endif

