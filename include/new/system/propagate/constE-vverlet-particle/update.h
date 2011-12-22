
#ifndef _System_Propagate_ConstE_VelocityVerlet_Particle_Update_H_
#define _System_Propagate_ConstE_VelocityVerlet_Particle_Update_H_

#include "system/propagate/interface.h"
#include "system/propagate/constE-vverlet-particle/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _UpdateCEVVerletParticleHTIM(SysPropagate<T,VT,SCT>& SE) {
    Error("Improper Content Type!");
  }

  template <typename T>
  void _UpdateFuncCEVVerletParticleHTIMGlobaleMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM) {
    negHTIM.value<T>()=-0.5*dt*Mass.value<T>();
  }

  template <typename T, template<typename> class VT>
  void _UpdateFuncCEVVerletParticleHTIMArrayMass(
      const T& dt, const Unique64Bit& Mass, Unique64Bit& negHTIM) {
    copy(*reinterpret_cast<VT<T>*>(negHTIM.ptr[0]),
         *reinterpret_cast<VT<T>*>(Mass.ptr[0]));
    inverse(*reinterpret_cast<VT<T>*>(negHTIM.ptr[0]));
    scale(*reinterpret_cast<VT<T>*>(negHTIM.ptr[0]),-dt*0.5);
  }

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _UpdateCEVVerletParticleHTIM(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_RunUpdateFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _RunUpdateFunc updfunc=
      reinterpret_cast<_RunUpdateFunc>(
          P[CEVVerletParticleUpdateHTIMFunc].ptr[0]);
    updfunc(P[CEVVerletParticleTimeStep].value<T>(),
            P[CEVVerletParticleMass],
            P[CEVVerletParticleNegHTimeIMass]);
  }

}

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void UpdateCEVVerletParticleHTIM(SysPropagate<T,VT,SCT>& SE) {
    _UpdateCEVVerletParticleHTIM(SE);
  }

}

#endif

