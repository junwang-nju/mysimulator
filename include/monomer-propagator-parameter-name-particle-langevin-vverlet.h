
#ifndef _Monomer_Propagator_Parameter_Name_Particle_Langevin_VelocityVerlet_H_
#define _Monomer_Propagator_Parameter_Name_Particle_Langevin_VelocityVerlet_H_

#include "propagator-parameter-name-langevin-vverlet.h"

namespace std {

  enum MonomerPropagatorMoveNameParticleLV {
    PLV_BeforeG=LV_BeforeG,
    PLV_AfterG=LV_AfterG,
    NumberMoveParticleLV=NumberMoveLV
  };

  enum MonomerPropagatorSetNameParticleLV {
    HydrodynamicRadiusPLV=0,
    RandomVelocityPointerPLV,
    NumberSetParticleLV
  };

  enum MonomerPropagatorParameterNameParticleLV {
    PLV_HydrodynamicRadius=0,
    PLV_HalfDeltaTIvM,
    PLV_FrictionCoef,
    PLV_RandomVelocitySize,
    PLV_FactorBeforeG,
    PLV_FactorAfterG,
    PLV_RandomVelocityPointer,
    NumberParameterParticleLV
  };

}

#endif

