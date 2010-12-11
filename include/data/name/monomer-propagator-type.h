
#ifndef _Monomer_Propagator_Type_H_
#define _Monomer_Propagator_Type_H_

namespace std {

  enum MonomerPropagatorTypeName {
    ParticleConstEVVerlet=0,
    ParticleBerendsenVVerlet,
    ParticleLangevinVVerlet,
    monomerPropagatorNumberType
  };

}

#include "data/name/monomer-propagator-particle-conste-vverlet.h"
#include "data/name/monomer-propagator-particle-berendsen-vverlet.h"
#include "data/name/monomer-propagator-particle-langevin-vverlet.h"

namespace std {

  static
  const unsigned int
  monomerPropagatorParameterSize[monomerPropagatorNumberType]={
    monomerPropagatorPEVNumberParameter,
    monomerPropagatorPBVNumberParameter,
    monomerPropagatorPLVNumberParameter
  };

}

#endif
