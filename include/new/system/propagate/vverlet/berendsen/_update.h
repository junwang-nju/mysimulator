
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Update_Func_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Update_Func_H_

#include "system/propagate/vverlet/const-e/_update.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncBsVVerletNegHTIMGMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& nhtim) {
    _UpdateFuncCEVVerletHTIMGMass<T>(dt,Mass,nhtim);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletNegHTIMAMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& nhtim) {
    _UpdateFuncCEVVerletHTIMAMass<T,VT>(dt,Mass,nhtim);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletVSQGMass(
      Unique64Bit& VSQ, const Array1DContent<SysContentWithEGV<T,VT> >& gC) {
    _UpdateFuncCEVVerletVSQGMass<T,VT>(VSQ,gC);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletVSQAMass(
      Unique64Bit& VSQ, const Array1DContent<SysContentWithEGV<T,VT> >& gC) {
    _UpdateFuncCEVVerletVSQAMass<T,VT>(VSQ,gC);
  }

}

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T>
  void _UpdateFuncBsVVerletDualKEGMass(
      const Unique64Bit& VSQ, const Unique64Bit& Mass, T& dKE) {
    dKE=_VALUE(VSQ)*_VALUE(Mass);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletDualKEAMass(
      const Unique64Bit& VSQ, const Unique64Bit& Mass, T& dKE) {
    dKE=0;
    for(unsigned int i=0;i<_CARRAY(VSQ).size;++i)
      dKE+=dot(_CARRAY(Mass)[i],_CARRAY(VSQ)[i]);
  }

}

#undef _CARRAY
#undef _VALUE

#endif

