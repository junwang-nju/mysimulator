
#ifndef _Parameter_Monomer_Propagator_ConstantE_VelocityVerlet_H_
#define _Parameter_Monomer_Propagator_ConstantE_VelocityVerlet_H_

#include "data/name/monomer-propagator-base.h"

namespace std {

  enum PropagatorMonomerConstEVVerlet {
    EV_MoveBeforeG=monomerPropagatorBaseNumberParameter,
    EV_MoveAfterG,
    monomerPropagatorEVNumberParameter
  };

}

#endif

