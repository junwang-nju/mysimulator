
#ifndef _System_Propagate_ConstE_VelocityVerlet_Particle_Init_H_
#define _System_Propagate_ConstE_VelocityVerlet_Particle_Init_H_

#include "system/propagate/interface.h"
#include "system/propagate/constE-vverlet-particle/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void InitCEVVerletParticle(SysPropagate<T,VT,SCT>&) {}

}

#endif

