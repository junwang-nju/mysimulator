
#ifndef _Interaction_Function_Component_Name_H_
#define _Interaction_Function_Component_Name_H_

#include "vector/interface.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType, typename T>
  struct InteractionFuncComponentName {

    typedef void (*EFunctionalType)(const T&,const UniqueParameter64Bit*,T&);
    typedef void (*DFunctionalType)(const T&,const UniqueParameter64Bit*,T&);
    typedef void (*BFunctionalType)(const T&,const UniqueParameter64Bit*,T&,T&);
    typedef void (*EFuncMethodType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,EFunctionalType);
    typedef void (*GFuncMethodType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,Vector<T>*,DFunctionalType);
    typedef void (*BFuncMethodType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,Vector<T>*,BFunctionalType);

  };

}

#endif

