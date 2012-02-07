
#ifndef _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_
#define _System_Propagate_VelocityVerlet_ConstE_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"
#include "system/content/with-egv/interface.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _ARRAY(name) (*reinterpret_cast<Array1D<VT<T> >*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T>
  void _UpdateFuncCEVVerletHTIMGMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM) {
    _VALUE(negHTIM)=-0.5*dt/_VALUE(Mass);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletHTIMAMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM) {
    T hdt=-0.5*dt;
    for(unsigned int i=0;i<_ARRAY(Mass).size;++i) {
      copy(_ARRAY(negHTIM)[i],_CARRAY(Mass)[i]);
      inverse(_ARRAY(negHTIM)[i]);
      scale(_ARRAY(negHTIM)[i],hdt);
    }
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQGMass(
      Unique64Bit& VSQ, const Array1DContent<SysContentWithEGV<T,VT> > & gC) {
    _VALUE(VSQ)=0;
    for(unsigned int i=0;i<gC.size;++i) _VALUE(VSQ)+=normSQ(gC[i].Velocity());
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletVSQAMass(
      Unique64Bit& VSQ, const Array1DContent<SysContentWithEGV<T,VT> > & gC) {
    for(unsigned int i=0;i<gC.size;++i) {
      copy(_ARRAY(VSQ)[i],gC[i].Velocity());
      scale(_ARRAY(VSQ)[i],gC[i].Velocity());
    }
  }

  template <typename T>
  void _UpdateFuncCEVVerletKEnergySimpleGMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    KE=0.5*_VALUE(Mass)*_VALUE(VelSQ);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletKEnergySimpleAMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    KE=0;
    for(unsigned int i=0;i<_ARRAY(VelSQ).size;++i)
      KE+=dot(_ARRAY(Mass)[i],_ARRAY(VelSQ)[i]);
    KE*=0.5;
  }

}

#undef _CARRAY
#undef _ARRAY
#undef _VALUE

#endif

