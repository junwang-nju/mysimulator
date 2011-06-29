
#ifndef _Propagator_Monomer_Parameter_Particle_ConstE_VelocityVerlet_Update_H_
#define _Propagator_Monomer_Parameter_Particle_ConstE_VelocityVerlet_Update_H_

#include "propagator/monomer/vverlet/constE/param-update.h"
#include "propagator/monomer/vverlet/constE/particle/param-name.h"

namespace mysimulator {

  template <typename T>
  void UpdateMonomerPropagatorParticleConstEVelVerlet(
      Vector<UniqueParameter64Bit>& MP,
      const Vector<UniqueParameter64Bit>& SP) {
    UpdateMonomerPropagatorConstEVelVerlet<T>(MP,SP);
    copy(MP[PEVHalfTimeStepIvM],
         SP[HalfTimeStep].value<T>()*MP[IvMassData].value<T>());
  }

}

#endif

