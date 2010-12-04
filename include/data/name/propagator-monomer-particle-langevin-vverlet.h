
#ifndef _Parameter_Propagator_Monomer_Particle_Langevin_VelocityVerlet_H_
#define _Parameter_Propagator_Monomer_Particle_Langevin_VelocityVerlet_H_

#include "data/name/propagator-monomer-langevin-vverlet.h"

namespace std {

  enum PropagatorMonomerParticleLangevinVVerletParameterName {
    PLV_HalfDeltaTIvM=PropagatorMonomerLVNumberParameter,
    PLV_FrictionCoef,
    PLV_HydrodynamicRadius,
    PLV_RandomVelocitySize,
    PLV_FactorBeforeG,
    PLV_FactorAfterG,
    PLV_RandomVelocity,
    PropagatorMonomerPLVNumberParameter
  };

}

#endif

