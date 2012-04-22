
#ifndef _System_Propagator_VelVerlet_ConstE_Init_H_
#define _System_Propagator_VelVerlet_ConstE_Init_H_

#include "system/propagator/interface.h"
#include "system/property/mass-method-name.h"
#include "system/propagator/vel-verlet/const-e/parameter-name.h"
#include "system/propagator/vel-verlet/const-e/_update.h"
#include "system/propagator/vel-verlet/const-e/_move.h"

#if !(defined(MOD)||defined(PTR)||defined(SRC)||defined(FUNC))
#define MOD(U)    VelVerletConstE##Mod##U
#define PTR(U)    VelVerletConstE##Ptr##U
#define SRC(U)    VelVerletConstE##Src##U
#define FUNC(U)   VelVerletConstE##Func##U
#else
#error "Duplicate Definition for Macro MOD,PTR,SRC,FUNC"
#endif

#if !(defined(_CreateElement)||defined(_CreateArray)||defined(_CreateFunc))
#define _CreateElement(U) P.Param[PTR(U)].ptr=P.Param[SRC(U)].ptr;
#define _CreateArray(U) { \
    assert(P.Param[SRC(U)].ptr!=NULL); \
    Array2D<T>* pv=reinterpret_cast<Array2D<T>*>(P.Param[SRC(U)].ptr); \
    Array1D<Array2D<T> >* pgv=new Array1D<Array2D<T> >; \
    pgv->Allocate(P.IDRange.Size()); \
    for(unsigned int i=0;i<pgv->Size();++i) \
      (*pgv)[i].Refer(*pv,P.IDRange[i].uv[0],P.IDRange[i].uv[1]); \
    P.Param[PTR(U)].ptr=reinterpret_cast<void*>(pgv); \
  }
#define _CreateFunc(U,Type,F) \
  P.Param[FUNC(U)].ptr=reinterpret_cast<void*>(static_cast<Type>(F));
#else
#error "Duplicate Definition for Macro _CreateElement,_CreateArray,_CreateFunc"
#endif

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void InitVelVerletConstE(SystemPropagator<T,CT>& P) {
    typedef
      void (*UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    typedef
      void (*UpVFunc)(Unique64Bit&,const Array1D<CT<T> >&);
    typedef
      void (*UpKFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    typedef
      void (*BMvFunc)(Array1D<CT<T> >&,const T&,const Unique64Bit&);
    typedef
      void (*AMvFunc)(Array1D<CT<T> >&,const Unique64Bit&);
    MassMethodName MMN=static_cast<MassMethodName>(P.Param[MOD(Mass)].u);
    switch(MMN) {
      case UniqueMass:
        _CreateElement(Mass)
        _CreateElement(NegHTIM)
        _CreateFunc(UpdateHTIM,UpFunc,_UpdateVelVerletConstEHTIM_UMass<T>)
        _CreateFunc(MoveBefore,BMvFunc,_MoveVelVerletConstEBeforeG_UMass<T>)
        _CreateFunc(MoveAfter,AMvFunc,_MoveVelVerletConstEAfterG_UMass<T>)
        _CreateElement(VelocitySQ)
        _CreateFunc(UpdateVSQ,UpVFunc,_UpdateVelVerletConstEVSQ_UMass<T>)
        _CreateFunc(UpdateKESimple,UpKFunc,
                    _UpdateVelVerletConstEKEnergySimple_UMass<T>)
        break;
      case ArrayMass:
        _CreateArray(Mass)
        _CreateArray(NegHTIM)
        if(P.Param[SRC(VelocitySQ)].ptr!=NULL) {
          _CreateArray(VelocitySQ)
          _CreateFunc(UpdateVSQ,UpVFunc,_UpdateVelVerletConstEVSQ_AMass<T>)
          _CreateFunc(UpdateKESimple,UpKFunc,
                      _UpdateVelVerletConstEKEnergySimple_AMass<T>)
        }
        _CreateFunc(UpdateHTIM,UpFunc,_UpdateVelVerletConstEHTIM_AMass<T>)
        _CreateFunc(MoveBefore,BMvFunc,_MoveVelVerletConstEBeforeG_AMass<T>)
        _CreateFunc(MoveAfter,AMvFunc,_MoveVelVerletConstEAfterG_AMass<T>)
        break;
      default:
        fprintf(stderr,"Unknown Mass Method!\n");
    }
  }

}

#if defined(_CreateElement)||defined(_CreateArray)||defined(_CreateFunc)
#undef _CreateFunc
#undef _CreateArray
#undef _CreateElement
#endif

#if defined(MOD)||defined(PTR)||defined(SRC)||defined(FUNC)
#undef FUNC
#undef SRC
#undef PTR
#undef MOD
#endif

#endif

