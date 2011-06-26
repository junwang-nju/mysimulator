
#ifndef _Propagator_Monomer_Parameter_Particle_ConstE_VelocityVerlet_Update_H_
#define _Propagator_Monomer_Parameter_Particle_ConstE_VelocityVerlet_Update_H_

#include "propagator/monomer/parameter/vverlet/conste/update.h"
#include "propagator/subsystem/parameter/vverlet/conste/name.h"
#include "propagator/monomer/parameter/vverlet/conste/particle/name.h"

namespace mysimulator {

  template <typename T>
  void UpdateMonomerPropagatorParticleConstEVelVerlet(
      Vector<UniqueParameter64Bit>& MP,const Vector<UniqueParameter64Bit>& SP){
    UpdateMonomerPropagatorConstEVelVerlet<T>(MP,SP);
    copy(MP[PEVHalfTimeStepIvM],
         SP[HalfTimeStep].value<T>()*MP[IvMassData].value<T>());
  }

}

#endif

