
#ifndef _System_Propagate_VelocityVerlet_Langevin_Move_Func_H_
#define _System_Propagate_VelocityVerlet_Langevin_Move_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletGMassGFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim,  const Unique64Bit& fac,
      const Unique64Bit& rv, const Unique64Bit& rsize) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      scale(gC[i].Velocity(),_VALUE(fac));
      shift(gC[i].Velocity(),_VALUE(nhtim),gC[i].EGData.Gradient());
      shift(gC[i].Velocity(),_VALUE(rsize),_CARRAY(rv)[i]);
      shift(gC[i].X(),dt,gC[i].Velocity());
    }
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletAMassGFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim,  const Unique64Bit& fac,
      const Unique64Bit& rv, const Unique64Bit& rsize) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      scale(gC[i].Velocity(),_CARRAY(fac)[i]);
      shift(gC[i].Velocity(),_CARRAY(nhtim)[i],gC[i].EGData.Gradient());
      shift(gC[i].Velocity(),_CARRAY(rsize)[i],_CARRAY(rv)[i]);
      shift(gC[i].X(),dt,gC[i].Velocity());
    }
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletGMassAFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim,  const Unique64Bit& fac,
      const Unique64Bit& rv, const Unique64Bit& rsize) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      scale(gC[i].Velocity(),_CARRAY(fac)[i]);
      shift(gC[i].Velocity(),_VALUE(nhtim),gC[i].EGData.Gradient());
      shift(gC[i].Velocity(),_CARRAY(rsize)[i],_CARRAY(rv)[i]);
      shift(gC[i].X(),dt,gC[i].Velocity());
    }
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncLgVVerletAMassAFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim,  const Unique64Bit& fac,
      const Unique64Bit& rv, const Unique64Bit& rsize) {
    _BfMoveFuncLgVVerletAMassGFric(gC,dt,nhtim,fac,rv,rsize);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletGMassGFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const Unique64Bit& rv, const Unique64Bit& rsize) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      shift(gC[i].Velocity(),_VALUE(rsize),_CARRAY(rv)[i]);
      shift(gC[i].Velocity(),_VALUE(nhtim),gC[i].EGData.Gradient());
      scale(gC[i].Velocity(),_VALUE(fac));
    }
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletAMassGFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const Unique64Bit& rv, const Unique64Bit& rsize) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      shift(gC[i].Velocity(),_CARRAY(rsize)[i],_CARRAY(rv)[i]);
      shift(gC[i].Velocity(),_CARRAY(nhtim)[i],gC[i].EGData.Gradient());
      scale(gC[i].Velocity(),_CARRAY(fac)[i]);
    }
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletGMassAFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const Unique64Bit& rv, const Unique64Bit& rsize) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      shift(gC[i].Velocity(),_CARRAY(rsize)[i],_CARRAY(rv)[i]);
      shift(gC[i].Velocity(),_VALUE(nhtim),gC[i].EGData.Gradient());
      scale(gC[i].Velocity(),_CARRAY(fac)[i]);
    }
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncLgVVerletAMassAFric(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim,
      const Unique64Bit& fac, const Unique64Bit& rv, const Unique64Bit& rsize) {
    _AfMoveFuncLgVVerletAMassGFric(gC,nhtim,fac,rv,rsize);
  }

}

#undef _CARRAY
#undef _VALUE

#endif

