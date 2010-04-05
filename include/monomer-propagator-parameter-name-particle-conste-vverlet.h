
#ifndef _Monomer_Propagator_Parameter_Name_Particle_ConstE_VelocityVerlet_H_
#define _Monomer_Propagator_Parameter_Name_Particle_ConstE_VelocityVerlet_H_

#include "propagator-parameter-name-conste-vverlet.h"

namespace std {

  enum MonomerPropagatorMoveNameEV {
    PEV_BeforeG=EV_BeforeG,
    PEV_AfterG=EV_AfterG,
    NumberMoveParticleEV=NumberMoveEV
  };

  enum MonomerPropagatorParamNameParticleEV{
    PEV_HalfDeltaTIvM=0,
    NumberParamParticleEV
  };

  enum MonomerPropagatorSetNameParticleEV {
    NumberSetParticleEV=0
  };

}

#endif

