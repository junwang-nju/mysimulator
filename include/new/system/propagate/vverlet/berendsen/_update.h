
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Update_Func_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Update_Func_H_

#include "system/propagate/vverlet/const-e/_update.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncBsVVerletNegHTIMGlobalMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& nhtim,
      const unsigned int&) {
    _UpdateFuncCEVVerletHTIMGlobaleMass<T>(dt,Mass,nhtim,0);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletNegHTIMArrayMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& nhtim,
      const unsigned int& n) {
    _UpdateFuncCEVVerletHTIMArrayMass<T,VT>(dt,Mass,nhtim,n);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletVSQGlobalMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int&) {
    _UpdateFuncCEVVerletVSQGlobalMass<T,VT>(VSQ,Vel,0);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletVSQArrayMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int& n) {
    _UpdateFuncCEVVerletVSQArrayMass<T,VT>(VSQ,Vel,n);
  }

  template <typename T>
  void _UpdateFuncBsVVerletVSQInitGlobalMass(Unique64Bit& VSQ) {
    _UpdateFuncCEVVerletVSQInitGlobalMass<T>(VSQ);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletVSQInitArrayMass(Unique64Bit& VSQ) {
    _UpdateFuncCEVVerletVSQInitArrayMass<T,VT>(VSQ);
  }

  template <typename T>
  void _UpdateFuncBsVVerletDualKEGlobalMass(
      const Unique64Bit& VSQ, const Unique64Bit& Mass, T& dKE) {
    dKE=(*reinterpret_cast<T*>(VSQ.ptr[0]))*
        (*reinterpret_cast<T*>(Mass.ptr[0]));
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncBsVVerletDualKEArrayMass(
      const Unique64Bit& VSQ, const Unique64Bit& Mass, T& dKE) {
    typedef Array1D<VT<T> >   AVT;
    dKE=0;
    for(unsigned int i=0;i<reinterpret_cast<AVT*>(VSQ.ptr[0])->size;++i)
      dKE+=dot((*reinterpret_cast<AVT*>(Mass.ptr[0]))[i],
               (*reinterpret_cast<AVT*>(VSQ.ptr[0]))[i]);
  }

}

#endif

