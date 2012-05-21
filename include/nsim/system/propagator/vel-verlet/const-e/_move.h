
#ifndef _System_Propagator_VelVerlet_ConstE_Move_Func_H_
#define _System_Propagator_VelVerlet_ConstE_Move_Func_H_

#include "unique/64bit/interface.h"
#include "system/content/with-egv/interface.h"
#include "array/2d/shift.h"

#if !(defined(_VALUE)||defined(_CARRAY))
#define _VALUE(U)   (*reinterpret_cast<T*>(U.ptr))
#define _CARRAY(U)  (*reinterpret_cast<Array1D<Array2D<T> >*>(U.ptr))
#else
#error "Duplicate Definition for Macro _VALUE,_CARRAY"
#endif

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void __MoveVelVerletConstEBeforeG_UMass(Array1D<CT<T> >&,const T&,
                                          const Unique64Bit&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void __MoveVelVerletConstEBeforeG_UMass(
      Array1D<SystemContentWithEGV<T> >& GC,const T& dt,
      const Unique64Bit& nHTIM) {
    for(unsigned int i=0;i<GC.Size();++i) {
      BlasShift(GC[i].Velocity,_VALUE(nHTIM),GC[i].EGData.Gradient);
      BlasShift(GC[i].X,dt,GC[i].Velocity);
    }
  }

  template <typename T,template<typename> class CT>
  void _MoveVelVerletConstEBeforeG_UMass(
      Array1D<CT<T> >& GC,const T& dt,const Unique64Bit& nHTIM) {
    __MoveVelVerletConstEBeforeG_UMass(GC,dt,nHTIM);
  }

  template <typename T,template<typename> class CT>
  void __MoveVelVerletConstEBeforeG_AMass(Array1D<CT<T> >&,const T&,
                                          const Unique64Bit&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void __MoveVelVerletConstEBeforeG_AMass(
      Array1D<SystemContentWithEGV<T> >& GC,const T& dt,
      const Unique64Bit& nHTIM) {
    for(unsigned int i=0;i<GC.Size();++i) {
      BlasShift(GC[i].Velocity,_CARRAY(nHTIM)[i],GC[i].EGData.Gradient);
      BlasShift(GC[i].X,dt,GC[i].Velocity);
    }
  }

  template <typename T,template<typename> class CT>
  void _MoveVelVerletConstEBeforeG_AMass(
      Array1D<CT<T> >& GC,const T& dt,const Unique64Bit& nHTIM) {
    __MoveVelVerletConstEBeforeG_AMass(GC,dt,nHTIM);
  }

  template <typename T,template<typename> class CT>
  void __MoveVelVerletConstEAfterG_UMass(Array1D<CT<T> >&,const Unique64Bit&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void __MoveVelVerletConstEAfterG_UMass(
      Array1D<SystemContentWithEGV<T> >& GC,const Unique64Bit& nHTIM) {
    for(unsigned int i=0;i<GC.Size();++i)
      BlasShift(GC[i].Velocity,_VALUE(nHTIM),GC[i].EGData.Gradient);
  }

  template <typename T,template<typename> class CT>
  void _MoveVelVerletConstEAfterG_UMass(
      Array1D<CT<T> >& GC,const Unique64Bit& nHTIM) {
    __MoveVelVerletConstEAfterG_UMass(GC,nHTIM);
  }

  template <typename T,template<typename> class CT>
  void __MoveVelVerletConstEAfterG_AMass(Array1D<CT<T> >&,const Unique64Bit&) {
    fprintf(stderr,"Not Available!\n");
  }

  template <typename T>
  void __MoveVelVerletConstEAfterG_AMass(
      Array1D<SystemContentWithEGV<T> >& GC,const Unique64Bit& nHTIM) {
    for(unsigned int i=0;i<GC.Size();++i)
      BlasShift(GC[i].Velocity,_CARRAY(nHTIM)[i],GC[i].EGData.Gradient);
  }

  template <typename T,template<typename> class CT>
  void _MoveVelVerletConstEAfterG_AMass(
      Array1D<CT<T> >& GC,const Unique64Bit& nHTIM) {
    __MoveVelVerletConstEAfterG_AMass(GC,nHTIM);
  }

}

#if defined(_VALUE)||defined(_CARRAY)
#undef _VALUE
#undef _CARRAY
#endif

#endif

