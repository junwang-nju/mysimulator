
#ifndef _Parameter_Monomer_Propagator_Langevin_VelocityVerlet_H_
#define _Parameter_Monomer_Propagator_Langevin_VelocityVerlet_H_

#include "data/name/monomer-propagator-base.h"

namespace std {

  enum PropagatorMonomerLangevinVVerletParameterName {
    LV_MoveBeforeG=monomerPropagatorBaseNumberParameter,
    LV_MoveAfterG,
    monomerPropagatorLVNumberParameter
  };

}

#endif

