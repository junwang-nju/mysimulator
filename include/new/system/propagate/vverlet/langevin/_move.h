
#ifndef _System_Propagate_VelocityVerlet_Langevin_Move_Func_H_
#define _System_Propagate_VelocityVerlet_Langevin_Move_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletGMassGFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int&) {
    assert(IsValid(X)&&IsValid(G)&&IsValid(V));
    scale(V,fac.value<T>());
    shift(V,nhtim.value<T>(),G);
    shift(V,rsize.value<T>(),rv);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletAMassGFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(X)&&IsValid(G)&&IsValid(V));
    scale(V,(*reinterpret_cast<const AVT*>(fac.ptr[0]))[n]);
    shift(V,(*reinterpret_cast<const AVT*>(nhtim.ptr[0]))[n],G);
    shift(V,(*reinterpret_cast<const AVT*>(rsize.ptr[0]))[n],rv);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletGMassAFric(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const VT<T>& rv, const Unique64Bit& rsize,
      const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(X)&&IsValid(G)&&IsValid(V));
    scale(V,(*reinterpret_cast<const AVT*>(fac.ptr[0]))[n]);
    shift(V,nhtim.value<T>(),G);
    shift(V,(*reinterpret_cast<const AVT*>(rsize.ptr[0]))[n],rv);
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
    shift(V,rsize.value<T>(),rv);
    shift(V,nhtim.value<T>(),G);
    scale(V,fac.value<T>());
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletAMassGFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(V)&&IsValid(G));
    shift(V,(*reinterpret_cast<const AVT*>(rsize.ptr[0]))[n],rv);
    shift(V,(*reinterpret_cast<const AVT*>(nhtim.ptr[0]))[n],G);
    scale(V,(*reinterpret_cast<const AVT*>(fac.ptr[0]))[n]);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletGMassAFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int& n) {
    typedef Array1D<VT<T> >   AVT;
    assert(IsValid(V)&&IsValid(G));
    shift(V,(*reinterpret_cast<const AVT*>(rsize.ptr[0]))[n],rv);
    shift(V,nhtim.value<T>(),G);
    scale(V,(*reinterpret_cast<const AVT*>(fac.ptr[0]))[n]);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletAMassAFric(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const Unique64Bit& fac,
      const VT<T>& rv, const Unique64Bit& rsize, const unsigned int& n) {
    _AfMoveFuncLgVVerletAMassGFric(V,G,nhtim,fac,rv,rsize,n);
  }

}

#endif

