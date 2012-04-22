
#ifndef _System_Propagator_VelVerlet_ConstE_Clear_H_
#define _System_Propagator_VelVerlet_ConstE_Clear_H_

#include "system/propagator/interface.h"
#include "system/propagator/vel-verlet/const-e/parameter-name.h"
#include "system/property/mass-method-name.h"

#if !(defined(MOD)||defined(PTR)||defined(FUNC))
#define MOD(U)  VelVerletConstE##Mod##U
#define PTR(U)  VelVerletConstE##Ptr##U
#define FUNC(U) VelVerletConstE##Func##U
#else
#error "Duplicate Definitions for Macro MOD, PTR, FUNC"
#endif

#if !(defined(_ClearElement)||defined(_ClearArray)||defined(_ClearFunc))
#define _ClearElement(U) P.Param[PTR(U)].ptr=NULL;
#define _ClearArray(U)  \
  if(P.Param[PTR(U)].ptr!=NULL) { \
    Array1D<Array2D<T> > *p; \
    p=reinterpret_cast<Array1D<Array2D<T> >*>(P.Param[PTR(U)].ptr); \
    p->Clear(); \
    delete p; \
    P.Param[PTR(U)].ptr=NULL; \
  }
#define _ClearFunc(U) P.Param[FUNC(U)].ptr=NULL;
#else
#error "Duplicate Definitions for Macro _ClearElement,_ClearArray,_ClearFunc"
#endif

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void ClearVelVerletCE(SystemPropagator<T,CT>& P) {
    _ClearElement(TimeStep)
    MassMethodName MMN=static_cast<MassMethodName>(P.Param[MOD(Mass)].u);
    switch(MMN) {
      case UniqueMass:
        _ClearElement(Mass)
        _ClearElement(NegHTIM)
        _ClearElement(VelocitySQ)
        break;
      case ArrayMass:
        _ClearArray(Mass)
        _ClearArray(NegHTIM)
        _ClearArray(VelocitySQ)
        break;
      default:
        fprintf(stderr,"Unknown Mass Method!\n");
    }
    _ClearFunc(UpdateHTIM)
    _ClearFunc(UpdateVSQ)
    _ClearFunc(UpdateKESimple)
    _ClearFunc(MoveBefore)
    _ClearFunc(MoveAfter)
  }

}

#if defined(_ClearElement)||defined(_ClearArray)||defined(_ClearFunc)
#undef _ClearFunc
#undef _ClearArray
#undef _ClearElement
#endif

#if defined(MOD)||defined(PTR)||defined(FUNC)
#undef FUNC
#undef PTR
#undef MOD
#endif

#endif

