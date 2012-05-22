
#ifndef _System_Propagator_VelVerlet_Langevin_Update_Func_H_
#define _System_Propagator_VelVerlet_Langevin_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/2d/copy.h"
#include "array/2d/inverse.h"
#include "array/2d/scale.h"
#include "array/2d/square-root.h"

#if !(defined(_VALUE)||defined(_ARRAY)||defined(_CARRAY))
#define _VALUE(U) (*Pointer<T>(U))
#define _ARRAY(U) (*Pointer<Array1D<Array2D<T> > >(U))
#else
#error "Duplicate Definition for Macro _VALUE,_ARRAY,_CARRAY"
#endif

namespace mysimulator {

  template <typename T>
  void _UpdateVelVerletLangevinRandSize_UMassUFric(
      const T& dt,const T& Tempe,const Unique64Bit& Mass,
      const Unique64Bit& Fric,Unique64Bit& RSize) {
    _VALUE(RSize)=Sqroot(dt*Tempe*_VALUE(Fric)/_VALUE(MASS));
  }

  template <typename T>
  void _UpdateVelVerletLangevinRandSize_AMassUFric(
      const T& dt,const T& Tempe,const Unique64Bit& Mass,
      const Unique64Bit& Fric,Unique64Bit& RSize) {
    for(unsigned int i=0;i<_ARRAY(Mass).Size();++i) {
      BlasCopy(_Array(RSize)[i],_Array(Mass)[i]);
      Inverse(_Array(RSize)[i]);
      BlasScale(_Array(RSize)[i],dt*Tempe*_VALUE(Fric));
      Sqroot(_Array(RSize)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletLangevinRandSize_UMassAFric(
      const T& dt,const T& Tempe,const Unique64Bit& Mass,
      const Unique64Bit& Fric,Unique64Bit& RSize) {
    for(unsigned int i=0;i<_Array(Fric).Size();++i) {
      BlasCopy(_Array(RSize)[i],_Array(Fric)[i]);
      BlasScale(_Array(RSize)[i],dt*Tempe/_VALUE(Mass));
      Sqroot(_Array(RSize)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletLangevinRandSize_AMassAFric(
      const T& dt,const T& Tempe,const Unique64Bit& Mass,
      const Unique64Bit& Fric,Unique64Bit& RSize) {
    for(unsigned int i=0;i<_ARRAY(Mass).Size();++i) {
      BlasCopy(_Array(RSize)[i],_Array(Mass)[i]);
      Inverse(_Array(RSize)[i]);
      BlasScale(_Array(RSize)[i],dt*Tempe);
      BlasScale(_Array(RSize)[i],_Array(Fric)[i]);
      Sqroot(_Array(RSize)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletFac_UMassUFric(
      const T& dt,const Unique64Bit& Mass,const Unique64Bit& Fric,
      Unique64Bit& FacBf, Unique64Bit& FacAf) {
    T d=0.5*dt*_VALUE(Fric)/_VALUE(Mass);
    _VALUE(FacBf)=1-d;
    _VALUE(FacAf)=1./(1+d);
  }

  template <typename T>
  void _UpdateVelVerletFac_AMassUFric(
      const T& dt,const Unique64Bit& Mass,const Unique64Bit& Fric,
      Unique64Bit& FacBf, Unique64Bit& FacAf) {
  }

}

#endif

