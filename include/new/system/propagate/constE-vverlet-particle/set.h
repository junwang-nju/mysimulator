
#ifndef _System_Propagate_ConstE_VelocityVerlet_Particle_Set_H_
#define _System_Propagate_ConstE_VelocityVerlet_Particle_Set_H_

#include "system/propagate/constE-vverlet-particle/update.h"
#include "system/propagate/constE-vverlet-particle/move.h"
#include "system/property/mass-method-name.h"

namespace mysimulator {

  template <typename T,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SetMassFunc(SysPropagate<T,VT,SCT>& SE,const MassMethodName& MN) {
    typedef void (*UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    typedef void (*BMvFunc)(VT<T>&,VT<T>&,VT<T>&,const T&,const Unique64Bit&);
    typedef void (*AMvFunc)(VT<T>&,VT<T>&,const T&,const Unique64Bit&);
    switch(MN) {
      case GlobalMass:
        SE.Param[CEVVerletParticleUpdateHTIMFunc].ptr[0]=
        reinterpret_cast<void*>(
        static_cast<UpFunc>(_UpdateFuncCEVVerletParticleHTIMGlobaleMass<T>));
        SE.Param[CEVVerletParticleBfMoveFunc].ptr[0]=
        reinterpret_cast<void*>(
        static_cast<BMvFunc>(_BfMoveFuncCEVVerletPartcleGlobalMass<T,VT>));
        SE.Param[CEVVerletParticleAfMoveFunc].ptr[0]=
        reinterpret_cast<void*>(
        static_cast<AMvFunc>(_AfMoveFuncCEVVerletPartcleGlobalMass<T,VT>));
        break;
      case ArrayMass:
        SE.Param[CEVVerletParticleUpdateHTIMFunc].ptr[0]=
        reinterpret_cast<void*>(
        static_cast<UpFunc>(_UpdateFuncCEVVerletParticleHTIMArrayMass<T,VT>));
        SE.Param[CEVVerletParticleBfMoveFunc].ptr[0]=
        reinterpret_cast<void*>(
        static_cast<BMvFunc>(_BfMoveFuncCEVVerletPartcleArrayMass<T,VT>));
        SE.Param[CEVVerletParticleAfMoveFunc].ptr[0]=
        reinterpret_cast<void*>(
        static_cast<AMvFunc>(_AfMoveFuncCEVVerletPartcleArrayMass<T,VT>));
        break;
      default:
        Error("Unknown Mode for Function related to Mass!");
    }
  }

}

#endif

