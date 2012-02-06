
#ifndef _System_Propagate_VelocityVerlet_Langevin_Move_Func_H_
#define _System_Propagate_VelocityVerlet_Langevin_Move_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletGMassGFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int&) {
    assert(IsValid(X)&&IsValid(G)&&IsValid(V));
    scale(V,_VALUE(fac));
    shift(V,_VALUE(nhtim),G);
    shift(V,_VALUE(rsize),rv);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletAMassGFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int& n) {
    assert(IsValid(X)&&IsValid(G)&&IsValid(V));
    scale(V,_CARRAY(fac)[n]);
    shift(V,_CARRAY(nhtim)[n],G);
    shift(V,_CARRAY(rsize)[n],rv);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletGMassAFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int& n) {
    assert(IsValid(X)&&IsValid(G)&&IsValid(V));
    scale(V,_CARRAY(fac)[n]);
    shift(V,_VALUE(nhtim),G);
    shift(V,_CARRAY(rsize)[n],rv);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletAMassAFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int& n) {
    _BfMoveFuncLgVVerletAMassGFric(X,V,G,dt,nhtim,fac,rv,rsize,n);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletGMassGFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int&) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,_VALUE(rsize),rv);
    shift(V,_VALUE(nhtim),G);
    scale(V,_VALUE(fac));
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletAMassGFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int& n) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,_CARRAY(rsize)[n],rv);
    shift(V,_CARRAY(nhtim)[n],G);
    scale(V,_CARRAY(fac)[n]);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletGMassAFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int& n) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,_CARRAY(rsize)[n],rv);
    shift(V,_VALUE(nhtim),G);
    scale(V,_CARRAY(fac)[n]);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletAMassAFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int& n) {
    _AfMoveFuncLgVVerletAMassGFric(V,G,nhtim,fac,rv,rsize,n);
  }

}

#undef _CARRAY
#undef _VALUE

#endif

