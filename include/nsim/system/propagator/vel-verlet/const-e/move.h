
#ifndef _System_Propagator_VelVerlet_ConstE_Move_H_
#define _System_Propagator_VelVerlet_ConstE_Move_H_

#include "system/propagator/interface.h"
#include "system/propagator/vel-verlet/const-e/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class CT>
  void _MoveVelVerletConstEBeforeG(SystemPropagator<T,CT>&) {
    fprintf(stderr,"Improper Content Type!\n");
  }
  template <typename T, template<typename> class CT>
  void _MoveVelVerletConstEAfterG(SystemPropagator<T,CT>&) {
    fprintf(stderr,"Improper Content Type!\n");
  }

}

#include "system/content/with-egv/interface.h"

#if !(defined(FUNC)||defined(PTR))
#define PTR(U)  VelVerletConstE##Ptr##U
#define FUNC(U) VelVerletConstE##Func##U
#else
#error "Duplicate Definition for Macro PTR,FUNC"
#endif

#if !(defined(VALUE)||defined(PARAM))
#define PARAM(U)  P.Param[PTR(U)]
#define VALUE(U)  (*reinterpret_cast<T*>(PARAM(U).ptr))
#else
#error "Duplicate Definition for Macro PARAM,VALUE"
#endif

namespace mysimulator {

  template <typename T>
  void _MoveVelVerletConstEBeforeG(SystemPropagator<T,SystemContentWithEGV>& P){
    typedef
      void (*MvFunc)(Array1D<SystemContentWithEGV<T> >&,const T&,
                     const Unique64Bit&);
    MvFunc mvf=reinterpret_cast<MvFunc>(P.Param[FUNC(MoveBefore)].ptr);
    mvf(P.GrpContent,VALUE(TimeStep),PARAM(NegHTIM));
  }

  template <typename T>
  void _MoveVelVerletConstEAfterG(SystemPropagator<T,SystemContentWithEGV>& P){
    typedef
      void (*MvFunc)(Array1D<SystemContentWithEGV<T> >&,const Unique64Bit&);
    MvFunc mvf=reinterpret_cast<MvFunc>(P.Param[FUNC(MoveAfter)].ptr);
    mvf(P.GrpContent,PARAM(NegHTIM));
  }

}

#if defined(VALUE)||defined(PARAM)
#undef VALUE
#undef PARAM
#endif

#if defined(FUNC)||defined(PTR)
#undef FUNC
#undef PTR
#endif

namespace mysimulator {

  template <typename T, template<typename> class CT>
  void MoveVelVerletConstEBeforeG(SystemPropagator<T,CT>& P) {
    _MoveVelVerletConstEBeforeG(P);
  }
  template <typename T, template<typename> class CT>
  void MoveVelVerletConstEAfterG(SystemPropagator<T,CT>& P) {
    _MoveVelVerletConstEAfterG(P);
  }

}

#endif

