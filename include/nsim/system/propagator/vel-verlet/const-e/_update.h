
#ifndef _System_Propagator_VelVerlet_ConstE_Update_Func_H_
#define _System_Propagator_VelVerlet_ConstE_Update_Func_H_

#include "unique/64bit/interface.h"
#include "system/content/with-egv/interface.h"
#include "array/2d/copy.h"
#include "array/2d/inverse.h"
#include "array/2d/scale.h"
#include "array/2d/norm.h"
#include "array/2d/scale-copy.h"
#include "array/2d/dot.h"

#if !(defined(_VALUE)||defined(_ARRAY)||defined(_CARRAY))
#define _VALUE(U) (*reinterpret_cast<T*>(U.ptr))
#define _ARRAY(U) (*reinterpret_cast<Array1D<Array2D<T> >*>(U.ptr))
#define _CARRAY(U)  (*reinterpret_cast<const Array1D<Array2D<T> >*>(U.ptr))
#else
#error "Duplicate Definition for Macro _VALUE,_ARRAY_CARRAY"
#endif

namespace mysimulator {

  template <typename T>
  void _UpdateVelVerletConstEHTIM_UMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& NegHTIM) {
    _VALUE(NegHTIM)=-0.5*dt/_VALUE(Mass);
  }

  template <typename T>
  void _UpdateVelVerletConstEHTIM_AMass(
      const T& dt,const Unique64Bit& Mass,Unique64Bit& NegHTIM) {
    T hdt=-0.5*dt;
    unsigned int n=_ARRAY(Mass).Size();
    for(unsigned int i=0;i<n;++i) {
      Copy(_ARRAY(NegHTIM)[i],_CARRAY(Mass)[i]);
      Inverse(_ARRAY(NegHTIM)[i]);
      Scale(_ARRAY(NegHTIM)[i],hdt);
    }
  }

  template <typename T,template<typename> class CT>
  void __UpdateVelVerletConstEVSQ_UMass(Unique64Bit&,const Array1D<CT<T> >&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void __UpdateVelVerletConstEVSQ_UMass(
      Unique64Bit& VSQ,const Array1D<SystemContentWithEGV<T> >& GC) {
    _VALUE(VSQ)=0;
    for(unsigned int i=0;i<GC.Size();++i) _VALUE(VSQ)+=NormSQ(GC[i].Velocity);
  }

  template <typename T,template<typename> class CT>
  void _UpdateVelVerletConstEVSQ_UMass(
      Unique64Bit& VSQ,const Array1D<CT<T> >& GC) {
    __UpdateVelVerletConstEVSQ_UMass(VSQ,GC);
  }

  template <typename T,template<typename> class CT>
  void __UpdateVelVerletConstEVSQ_AMass(Unique64Bit&,const Array1D<CT<T> >&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void __UpdateVelVerletConstEVSQ_AMass(
      Unique64Bit& VSQ,const Array1D<SystemContentWithEGV<T> >& GC) {
    for(unsigned int i=0;i<GC.Size();++i)
      BlasScaleCopy(_ARRAY(VSQ)[i],GC[i].Velocity,GC[i].Velocity);
  }

  template <typename T,template<typename> class CT>
  void _UpdateVelVerletConstEVSQ_AMass(
      Unique64Bit& VSQ,const Array1D<CT<T> >& GC) {
    __UpdateVelVerletConstEVSQ_AMass(VSQ,GC);
  }

  template <typename T>
  void _UpdateVelVerletConstEKEnergySimple_UMass(
      T& KE,const Unique64Bit& Mass,const Unique64Bit& VelSQ) {
    KE=0.5*_VALUE(Mass)*_VALUE(VelSQ);
  }

  template <typename T>
  void _UpdateVelVerletConstEKEnergySimple_AMass(
      T& KE,const Unique64Bit& Mass,const Unique64Bit& VelSQ) {
    KE=0;
    unsigned int n=_ARRAY(VelSQ).Size();
    for(unsigned int i=0;i<n;++i) KE+=Dot(_CARRAY(Mass)[i],_CARRAY(VelSQ)[i]);
    KE*=0.5;
  }

}

#if defined(_VALUE)||defined(_ARRAY)||defined(_CARRAY)
#undef _CARRAY
#undef _ARRAY
#undef _VALUE
#endif

#endif

