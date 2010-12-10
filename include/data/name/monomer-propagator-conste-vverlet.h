
#ifndef _Parameter_Propagator_Monomer_ConstantE_VelocityVerlet_H_
#define _Parameter_Propagator_Monomer_ConstantE_VelocityVerlet_H_

#include "data/name/propagator-monomer-base.h"

namespace std {

  enum PropagatorMonomerConstEVVerlet {
    EV_MoveBeforeG=PropagatorMonomerBaseNumberParameter,
    EV_MoveAfterG,
    PropagatorMonomerEVNumberParameter
  };

}

#endif

