
#ifndef _Monomer_Propagator_Parameter_Name_Particle_ConstantE_VelocityVerlet_H_
#define _Monomer_Propagator_Parameter_Name_Particle_ConstantE_VelocityVerlet_H_

#include "propagator-parameter-name-conste-vverlet.h"

namespace std {

  enum MonomerPropagatorMoveNameParticleEV {
    PEV_BeforeG=EV_BeforeG,
    PEV_AfterG=EV_AfterG,
    NumberMoveParticleEV=NumberMoveEV
  };

  enum MonomerPropagatorSetNameParticleEV {
    NumberSetParticleEV=0
  };

  enum MonomerPropagatorParameterNameparticleEV {
    PEV_HalfDeltaTIvM=0,
    NumberParameterParticleEV
  };

}

#endif

