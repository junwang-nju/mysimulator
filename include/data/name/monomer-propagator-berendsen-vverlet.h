
#ifndef _Parameter_Monomer_Propagator_Berendsen_VelocityVerlet_H_
#define _Parameter_Monomer_Propagator_Berendsen_VelocityVerlet_H_

#include "data/name/monomer-propagator-base.h"

namespace std {

  enum monomerPropagatorBerendsenVVerlet {
    BV_MovePreProcess=monomerPropagatorBaseNumberParameter,
    BV_MoveBeforeG,
    BV_MoveAfterG,
    BV_MovePostProcess,
    monomerPropagatorBVNumberParameter
  };

}

#endif

