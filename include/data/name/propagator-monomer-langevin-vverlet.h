
#ifndef _Parameter_Propagator_Monomer_Langevin_VelocityVerlet_H_
#define _Parameter_Propagator_Monomer_Langevin_VelocityVerlet_H_

#include "data/name/propagator-monomer-base.h"

namespace std {

  enum PropagatorMonomerLangevinVVerletParameterName {
    LV_MoveBeforeG=PropagatorMonomerBaseNumberParameter,
    LV_MoveAfterG,
    PropagatorMonomerLVNumberParameter
  };

}

#endif

