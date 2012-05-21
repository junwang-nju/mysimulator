
#ifndef _System_Propagator_VelVerlet_Langevin_Clear_H_
#define _System_Propagator_VelVerlet_Langevin_Clear_H_

#include "system/propagator/interface.h"
#include "system/propagator/vel-verlet/langevin/parameter-name.h"
#include "system/property/mass-method-name.h"
#include "system/property/friction-method-name.h"

#if !(defined(MOD)||defined(PTR)||defined(FUNC)||defined(SRC))
#define MOD(U)  VelVerletLangevin##Mod##U
#define PTR(U)  VelVerletLangevin##Ptr##U
#define FUNC(U) VelVerletLangevin##Func##U
#define SRC(U)  VelVerletLangevin##Src##U
#else
#error "Duplicate Definition for Macro MOD,PTR,FUNC,SRC!"
#endif

#ifndef PRM
#define PRM(U)  P.Param[U]
#else
#error "Duplicate Definition for Macro PRM!"
#endif

#if !(defined(_ClearElement)||defined(_ClearArray)||defined(_ClearFunc)||defined(_ClearSrc))
#define _ClearElement(U)  PRM(PTR(U)).ptr=NULL;
#define _ClearArray(U) \
  if(Prm(PTR(U)).ptr!=NULL) { \
    Clear(*Pointer<Array1D<Array2D<T> > >(Prm(PTR(U)))); \
    delete Pointer<Array1D<Array2D<T> > >(Prm(PTR(U))); \
    _DelElement(U) \
  }
#define _ClearFunc(U)   Prm(FUNC(U)).ptr=NULL;
#define _ClearSrc(U)    Prm(SRC(U)).ptr=NULL;
#else
#error "Duplicate Definition for Macro _ClearElement,_ClearArray,_ClearFunc,_ClearSrc!"
#endif

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void ClearVelVerletLg(SystemPropagator<T,CT>& P) {
    _ClearSrc(TimeStep)
    _ClearSrc(Temperature)
    _ClearSrc(GaussRNG)
    _ClearArray(RandVector)
    _ClearSrc(RandVector)
    MassMethodName MMN=static_cast<MassMethodName>(Prm(MOD(Mass)).u);
    FrictionMethodName
      FMN=static_cast<FrictionMethodName>(Prm(MOD(Friction)).u);
    if(MMN==UniqueMass) {
      _ClearElement(Mass)
      _ClearElement(NegHTIM)
      _ClearElement(VelocitySQ)
    } else {
      _ClearArray(Mass)
      _ClearArray(NegHTIM)
      _ClearArray(VelocitySQ)
    }
    _ClearSrc(Mass)
    _ClearSrc(VelocitySQ)
    if(FMN=-UniqueFriction) { _ClearElement(Friction) }
    else { _ClearArray(Friction) }
    _ClearSrc(Friction)
    if((MMN==UniqueMass)&&(FMN==UniqueFriction)) {
      _ClearElement(RandSize)
      _ClearElement(FacBf)
      _ClearElement(FacAf)
    } else {
      _ClearArray(RandSize)
      _ClearArray(FacBf)
      _ClearArray(FacAf)
    }
    _ClearSrc(RandSize)
    _ClearSrc(FacBf)
    _ClearSrc(FacAf)
    _ClearFunc(UpdateHTIM)
    _ClearFunc(UpdateFac)
    _ClearFunc(UpdateRandSize)
    _ClearFunc(UpdateVSQ)
    _ClearFunc(UpdateKESimple)
    _ClearFunc(MoveBefore)
    _ClearFunc(MoveAfter)
  }

}

#if defined(_ClearElement)||defined(_ClearArray)||defined(_ClearFunc)||defined(_ClearSrc)
#undef _ClearSrc
#undef _ClearFunc
#undef _ClearArray
#undef _ClearElement
#endif

#ifdef PRM
#undef PRM
#endif

#if defined(MOD)||defined(PTR)||defined(FUNC)||defined(SRC)
#undef SRC
#undef FUNC
#undef PTR
#undef MOD
#endif

#endif

