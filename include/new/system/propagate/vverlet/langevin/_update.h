
#ifndef _System_Propagate_VelocityVerlet_Langevin_Update_Func_H_
#define _System_Propagate_VelocityVerlet_Langevin_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/interface.h"
#include "intrinsic-type/inverse.h"
#include "intrinsic-type/square-root.h"

#define _VALUE(name) (*reinterpret_cast<T*>(name.ptr[0]))
#define _ARRAY(name) (*reinterpret_cast<Array1D<VT<T> >*>(name.ptr[0]))
#define _CARRAY(name) (*reinterpret_cast<const Array1D<VT<T> >*>(name.ptr[0]))

namespace mysimulator {

  template <typename T>
  void _UpdateFuncLgVVerletRSizeGMassGFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize) {
    _VALUE(RSize)=sqroot(dt*Temp*_VALUE(Fric)/_VALUE(Mass));
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletRSizeAMassGFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize) {
    for(unsigned int n=0;n<_ARRAY(Mass).size;++n) {
      copy(_ARRAY(RSize)[n],_CARRAY(Mass)[n]);
      inverse(_ARRAY(RSize)[n]);
      scale(_ARRAY(RSize)[n],dt*Temp*_VALUE(Fric));
      sqroot(_ARRAY(RSize)[n]);
    }
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletRSizeGMassAFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize) {
    for(unsigned int n=0;n<_ARRAY(Fric).size;++n) {
      copy(_ARRAY(RSize)[n],_CARRAY(Fric)[n]);
      scale(_ARRAY(RSize)[n],dt*Temp*_VALUE(Mass));
      sqroot(_ARRAY(RSize)[n]);
    }
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletRSizeAMassAFric(
      const T& dt, const T& Temp, const Unique64Bit& Mass,
      const Unique64Bit& Fric, Unique64Bit& RSize) {
    for(unsigned int n=0;n<_ARRAY(Mass).size;++n) {
      copy(_ARRAY(RSize)[n],_CARRAY(Mass)[n]);
      inverse(_ARRAY(RSize)[n]);
      scale(_ARRAY(RSize)[n],dt*Temp);
      scale(_ARRAY(RSize)[n],_CARRAY(Fric)[n]);
      sqroot(_ARRAY(RSize)[n]);
    }
  }

  template <typename T>
  void _UpdateFuncLgVVerletFacGMassGFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2) {
    T d=0.5*dt*_VALUE(Fric)/_VALUE(Mass);
    _VALUE(Fac1)=ValueOne<T>()-d;
    _VALUE(Fac2)=ValueOne<T>()+d;
    inverse(_VALUE(Fac2));
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletFacAMassGFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2) {
    for(unsigned int n=0;n<_ARRAY(Mass).size;++n) {
      copy(_ARRAY(Fac1)[n],_CARRAY(Mass)[n]);
      inverse(_ARRAY(Fac1)[n]);
      scale(_ARRAY(Fac1)[n],-0.5*dt*_VALUE(Fric));
      copy(_ARRAY(Fac2)[n],_CARRAY(Fac1)[n]);
      shift(_ARRAY(Fac1)[n],cOne);
      scale(_ARRAY(Fac2)[n],-cOne);
      shift(_ARRAY(Fac2)[n],cOne);
      inverse(_ARRAY(Fac2)[n]);
    }
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletFacGMassAFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2) {
    for(unsigned int n=0;n<_ARRAY(Fric).size;++n) {
      copy(_ARRAY(Fac1)[n],_CARRAY(Fric)[n]);
      scale(_ARRAY(Fac1)[n],-0.5*dt/_VALUE(Mass));
      copy(_ARRAY(Fac2)[n],_CARRAY(Fac1)[n]);
      shift(_ARRAY(Fac1)[n],cOne);
      scale(_ARRAY(Fac2)[n],-cOne);
      shift(_ARRAY(Fac2)[n],cOne);
      inverse(_ARRAY(Fac2)[n]);
    }
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletFacAMassAFric(
      const T& dt, const Unique64Bit& Mass, const Unique64Bit& Fric,
      Unique64Bit& Fac1, Unique64Bit& Fac2) {
    for(unsigned int n=0;n<_ARRAY(Mass).size;++n) {
      copy(_ARRAY(Fac1)[n],_ARRAY(Mass)[n]);
      inverse(_ARRAY(Fac1)[n]);
      scale(_ARRAY(Fac1)[n],-0.5*dt);
      scale(_ARRAY(Fac1)[n],_CARRAY(Fric)[n]);
      copy(_ARRAY(Fac2)[n],_CARRAY(Fac1)[n]);
      shift(_ARRAY(Fac1)[n],cOne);
      scale(_ARRAY(Fac2)[n],-cOne);
      shift(_ARRAY(Fac2)[n],cOne);
      inverse(_ARRAY(Fac2)[n]);
    }
  }

}

#undef _CARRAY
#undef _ARRAY
#undef _VALUE

#include "system/propagate/vverlet/const-e/_update.h"

namespace mysimulator {

  template <typename T>
  void _UpdateFuncLgVVerletHTIMGMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM) {
    _UpdateFuncCEVVerletHTIMGMass<T>(dt,Mass,negHTIM);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletHTIMAMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM) {
    _UpdateFuncCEVVerletHTIMAMass<T,VT>(dt,Mass,negHTIM);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletVSQGMass(
      Unique64Bit& VSQ, const Array1DContent<SysContentWithEGV<T,VT> >& gC) {
    _UpdateFuncCEVVerletVSQGMass<T,VT>(VSQ,gC);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletVSQAMass(
      Unique64Bit& VSQ, const Array1DContent<SysContentWithEGV<T,VT> >& gC) {
    _UpdateFuncCEVVerletVSQAMass<T,VT>(VSQ,gC);
  }

  template <typename T>
  void _UpdateFuncLgVVerletKEnergyGMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    _UpdateFuncCEVVerletKEnergyGMass<T>(KE,Mass,VelSQ);
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncLgVVerletKEnergyAMass(
      T& KE, const Unique64Bit& Mass, const Unique64Bit& VelSQ) {
    _UpdateFuncCEVVerletKEnergyAMass<T,VT>(KE,Mass,VelSQ);
  }

}

#endif

