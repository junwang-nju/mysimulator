
#ifndef _Interaction_Function_Base_Interface_H_
#define _Interaction_Function_Base_Interface_H_

#include "unique-parameter/64bit/interface.h"
#include "vector/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer, typename GeomType,
            typename T=double>
  struct InteractionFuncBase {

    typedef void (*EFunctionalType)(const T&,const UniqueParameter64Bit*,T&);
    typedef void (*DFunctionalType)(const T&,const UniqueParameter64Bit*,T&);
    typedef void (*BFunctionalType)(const T&,const UniqueParameter64Bit*,T&,T&);
    typedef void (*EFuncType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,EFunctionalType);
    typedef void (*GFuncType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,Vector<T>*,DFunctionalType);
    typedef void (*BFuncType)(
        const Vector<T>*,const unsigned int*,const UniqueParameter64Bit*,
        DBuffer<T>&,const GeomType&,T&,Vector<T>*,BFunctionalType);

    static const EFunctionalType efunctional;
    static const DFunctionalType dfunctional;
    static const BFunctionalType bfunctional;
    static const EFuncType efunc;
    static const GFuncType gfunc;
    static const BFuncType bfunc;

    void Energy(
        const Vector<T>* X,const unsigned int* id,const UniqueParameter64Bit* P,
        DBuffer<T>& B,const GeomType& G,T& E) {
      assert(IsValid(efunc));
      efunc(X,id,P,B,G,E,efunctional);
    }
    void Gradient(
        const Vector<T>* X,const unsigned int* id,const UniqueParameter64Bit* P,
        DBuffer<T>& B,const GeomType& G,Vector<T>* D) {
      assert(IsValid(gfunc));
      gfunc(X,id,P,B,G,D,dfunctional);
    }
    void Both(
        const Vector<T>* X,const unsigned int* id,const UniqueParameter64Bit* P,
        DBuffer<T>& B,const GeomType& G,T& E,Vector<T>* D) {
      assert(IsValid(bfunc));
      bfunc(X,id,P,B,G,E,D,bfunctional);
    }

  };

  template <template<typename> class DBuffer, typename GeomType, typename T>
  const typename InteractionFuncBase<DBuffer,GeomType,T>::EFunctionalType
  InteractionFuncBase<DBuffer,GeomType,T>::efunctional=NULL;

  template <template<typename> class DBuffer, typename GeomType, typename T>
  const typename InteractionFuncBase<DBuffer,GeomType,T>::DFunctionalType
  InteractionFuncBase<DBuffer,GeomType,T>::dfunctional=NULL;

  template <template<typename> class DBuffer, typename GeomType, typename T>
  const typename InteractionFuncBase<DBuffer,GeomType,T>::BFunctionalType
  InteractionFuncBase<DBuffer,GeomType,T>::bfunctional=NULL;

}

#endif


