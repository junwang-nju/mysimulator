
#ifndef _System_Propagate_VelocityVerlet_ConstE_Move_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Move_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"
#include "system/content/with-egv/interface.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletGMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      shift(gC[i].Velocity(),_VALUE(nhtim),gC[i].EGData.Gradient());
      shift(gC[i].X(),dt,gC[i].Velocity());
    }
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletAMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i) {
      shift(gC[i].Velocity(),_CARRAY(nhtim)[i],gC[i].EGData.Gradient());
      shift(gC[i].X(),dt,gC[i].Velocity());
    }
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletGMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i)
      shift(gC[i].Velocity(),_VALUE(nhtim),gC[i].EGData.Gradient());
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletAMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim) {
    assert(IsValid(gC));
    for(unsigned int i=0;i<gC.size;++i)
      shift(gC[i].Velocity(),_CARRAY(nhtim)[i],gC[i].EGData.Gradient());
  }

}

#undef _CARRAY
#undef _VALUE

#endif

