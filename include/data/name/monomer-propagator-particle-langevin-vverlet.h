
#ifndef _Parameter_Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_
#define _Parameter_Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_

#include "data/name/monomr-propagator-langevin-vverlet.h"

namespace std {

  enum monomerPropagatorParticleLangevinVVerletParameterName {
    PLV_HalfDeltaTIvM=monomerPropagatorLVNumberParameter,
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

