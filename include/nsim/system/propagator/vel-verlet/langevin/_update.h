
#ifndef _System_Propagator_VelVerlet_Langevin_Update_Func_H_
#define _System_Propagator_VelVerlet_Langevin_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/2d/copy.h"
#include "array/2d/inverse.h"
#include "array/2d/scale.h"
#include "array/2d/shift.h"
#include "array/2d/square-root.h"

#if !(defined(_VALUE)||defined(_ARRAY))
#define _VALUE(U) (*Pointer<T>(U))
#define _ARRAY(U) (*Pointer<Array1D<Array2D<T> > >(U))
#else
#error "Duplicate Definition for Macro _VALUE,_ARRAY"
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
      BlasCopy(_ARRAY(RSize)[i],_ARRAY(Mass)[i]);
      Inverse(_ARRAY(RSize)[i]);
      BlasScale(_ARRAY(RSize)[i],dt*Tempe*_VALUE(Fric));
      Sqroot(_ARRAY(RSize)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletLangevinRandSize_UMassAFric(
      const T& dt,const T& Tempe,const Unique64Bit& Mass,
      const Unique64Bit& Fric,Unique64Bit& RSize) {
    for(unsigned int i=0;i<_ARRAY(Fric).Size();++i) {
      BlasCopy(_ARRAY(RSize)[i],_ARRAY(Fric)[i]);
      BlasScale(_ARRAY(RSize)[i],dt*Tempe/_VALUE(Mass));
      Sqroot(_ARRAY(RSize)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletLangevinRandSize_AMassAFric(
      const T& dt,const T& Tempe,const Unique64Bit& Mass,
      const Unique64Bit& Fric,Unique64Bit& RSize) {
    assert(_ARRAY(Mass).Size()==_ARRAY(Fric).Size());
    for(unsigned int i=0;i<_ARRAY(Mass).Size();++i) {
      BlasCopy(_ARRAY(RSize)[i],_ARRAY(Mass)[i]);
      Inverse(_ARRAY(RSize)[i]);
      BlasScale(_ARRAY(RSize)[i],dt*Tempe);
      BlasScale(_ARRAY(RSize)[i],_ARRAY(Fric)[i]);
      Sqroot(_ARRAY(RSize)[i]);
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
    for(unsigned int i=0;i<_ARRAY(Mass).Size();++i) {
      BlasCopy(_ARRAY(FacBf)[i],_ARRAY(Mass)[i]);
      Inverse(_ARRAY(FacBf)[i]);
      BlasScale(_ARRAY(FacBf)[i],-0.5*dt*_VALUE(Fric));
      BlasCopy(_ARRAY(FacAf)[i],_ARRAY(FacBf)[i]);
      BlasShift(_ARRAY(FacBf)[i],1.);
      BlasScale(_ARRAY(FacAf)[i],-1.);
      BlasShift(_ARRAY(FacAf)[i],1.);
      Inverse(_ARRAY(FacAf)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletFac_UMassAFric(
      const T& dt,const Unique64Bit& Mass,const Unique64Bit& Fric,
      Unique64Bit& FacBf, Unique64Bit& FacAf) {
    for(unsigned int i=0;i<_ARRAY(Fric).Size();++i) {
      BlasCopy(_ARRAY(FacBf)[i],_ARRAY(Fric)[i]);
      BlasScale(_ARRAY(FacBf)[i],-0.5*dt/_VALUE(Mass));
      BlasCopy(_ARRAY(FacAf)[i],_ARRAY(FacBf)[i]);
      BlasShift(_ARRAY(FacBf)[i],1.);
      BlasScale(_ARRAY(FacAf)[i],-1.);
      BlasShift(_ARRAY(FacAf)[i],1.);
      Inverse(_ARRAY(FacAf)[i]);
    }
  }

  template <typename T>
  void _UpdateVelVerletFac_AMassAFric(
      const T& dt,const Unique64Bit& Mass,const Unique64Bit& Fric,
      Unique64Bit& FacBf, Unique64Bit& FacAf) {
    assert(_ARRAY(Mass).Size()==_ARRAY(Fric).Size());
    for(unsigned int i=0;i<_ARRAY(Mass).Size();++i) {
      BlasCopy(_ARRAY(FacBf)[i],_ARRAY(Mass)[i]);
      Inverse(_ARRAY(FacBf)[i]);
      BlasScale(_ARRAY(FacBf)[i],-0.5*dt);
      BlasScale(_ARRAY(FacBf)[i],_ARRAY(Fric)[i]);
      BlasCopy(_ARRAY(FacAf)[i],_ARRAY(FacBf)[i]);
      BlasShift(_ARRAY(FacBf)[i],1.);
      BlasScale(_ARRAY(FacAf)[i],-1.);
      BlasShift(_ARRAY(FacAf)[i],1.);
      Inverse(_ARRAY(FacAf)[i]);
    }
  }

}

#if defined(_VALUE)||defined(_ARRAY)
#undef _ARRAY
#undef _VALUE
#endif

#include "system/propagator/vel-verlet/const-e/_update.h"

namespace mysimulator {

  template <typename T>
  void _UpdateVelVerletLangevinHTIM_UMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& NegHTIM) {
    _UpdateVelVerletConstEHTIM_UMass(dt,Mass,NegHTIM);
  }

  template <typename T>
  void _UpdatevelVerletLangevinHTIM_AMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& NegHTIM) {
    _UpdateVelVerletConstEHTIM_AMass(dt,Mass,NegHTIM);
  }

  template <typename T, template<typename> class CT>
  void _UpdateVelVerletLangevinVSQ_UMass(
      Unique64Bit& VSQ, const Array1D<CT<T> >& gC) {
    _UpdateVelVerletConstEVSQ_UMass(VSQ,gC);
  }

  template <typename T, template<typename> class CT>
  void _UpdateVelVerletLangevinVSQ_AMass(
      Unique64Bit& VSQ, const Array1D<CT<T> >& gC) {
    _UpdateVelVerletConstEVSQ_AMass(VSQ,gC);
  }

  template <typename T>
  void _UpdateVelVerletLangevinKEnergySimple_UMass(
      T& KE,const Unique64Bit& Mass,const Unique64Bit& VelSQ) {
    _UpdateVelVerletConstEKEnergySimple_UMass(KE,Mass,VelSQ);
  }

  template <typename T>
  void _UpdateVelVerletLangevinKEnergySimple_AMass(
      T& KE,const Unique64Bit& Mass,const Unique64Bit& VelSQ) {
    _UpdateVelVerletConstEKEnergySimple_AMass(KE,Mass,VelSQ);
  }

}

#endif

