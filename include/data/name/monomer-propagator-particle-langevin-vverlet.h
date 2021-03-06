
#ifndef _Parameter_Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_
#define _Parameter_Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_

#include "data/name/monomer-propagator-langevin-vverlet.h"

namespace std {

  enum monomerPropagatorParticleLangevinVVerletParameterName {
    PLV_HalfTimeStepIvM=monomerPropagatorLVNumberParameter,
    PLV_FrictionCoef,
    PLV_HydrodynamicRadius,
    PLV_RandomVelocitySize,
    PLV_FactorBeforeG,
    PLV_FactorAfterG,
    PLV_RandomVelocity,
    monomerPropagatorPLVNumberParameter
  };

}

#endif

