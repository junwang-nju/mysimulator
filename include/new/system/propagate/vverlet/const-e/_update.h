
#ifndef _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _ARRAY(name) (*reinterpret_cast<Array1D<VT<T> >*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T>
  void _UpdateFuncCEVVerletHTIMGMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int&) {
    _VALUE(negHTIM)=-0.5*dt/_VALUE(Mass);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletHTIMAMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM,
      const unsigned int& n) {
    copy(_ARRAY(negHTIM)[n],_CARRAY(Mass)[n]);
    inverse(_ARRAY(negHTIM)[n]);
    scale(_ARRAY(negHTIM)[n],-dt*0.5);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQGMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int&) {
    _VALUE(VSQ)+=dot(Vel,Vel);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQAMass(
      Unique64Bit& VSQ, const VT<T>& Vel, const unsigned int& n) {
    copy(_ARRAY(VSQ)[n],Vel);
    scale(_ARRAY(VSQ)[n],Vel);
  }

  template <typename T>
  void _UpdateFuncCEVVerletVSQInitGMass(Unique64Bit& VSQ) {
    _VALUE(VSQ)=0;
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQInitAMass(Unique64Bit& VSQ) {
    for(unsigned int i=0;i<_ARRAY(VSQ).size;++i)  fill(_ARRAY(VSQ)[i],0);
  }

  template <typename T>
  void _UpdateFuncCEVVerletKEnergyGMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    KE=0.5*_VALUE(Mass)*_VALUE(VelSQ);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletKEnergyAMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    KE=0;
    for(unsigned int i=0;i<_ARRAY(VelSQ).size;++i)
      KE+=0.5*dot(_ARRAY(Mass)[i],_ARRAY(VelSQ)[i]);
  }

}

#undef _CARRAY
#undef _ARRAY
#undef _VALUE

#endif

