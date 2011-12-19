
#ifndef _System_Propagate_VelocityVerlet_ConstE_Move_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Move_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletGlobalMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int&) {
    assert(IsValid(X)&&IsValid(V)&&IsValid(G));
    shift(V,_VALUE(nhtim),G);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletArrayMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int& n) {
    assert(IsValid(X)&&IsValid(V)&&IsValid(G));
    shift(V,_CARRAY(nhtim)[n],G);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletGlobalMass(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const unsigned int&) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,_VALUE(nhtim),G);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletArrayMass(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(V)&&IsValid(G));
    shift(V,_CARRAY(nhtim)[n],G);
  }

}

#undef _CARRAY
#undef _VALUE

#endif

