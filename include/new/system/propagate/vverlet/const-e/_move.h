
#ifndef _System_Propagate_VelocityVerlet_ConstE_Move_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Move_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletGlobalMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int&) {
    assert(IsValid(X)&&IsValid(V)&&IsValid(G));
    shift(V,nhtim.value<T>(),G);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletArrayMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(X)&&IsValid(V)&&IsValid(G));
    shift(V,(*reinterpret_cast<const AVT*>(nhtim.ptr[0]))[n],G);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletGlobalMass(
      VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int&) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,nhtim.value<T>(),G);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletArrayMass(
      VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(V)&&IsValid(G));
    shift(V,(*reinterpret_cast<const AVT*>(nhtim.ptr[0]))[n],G);
  }

}

#endif

