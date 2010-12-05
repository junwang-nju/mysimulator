
#ifndef _Parameter_Propagator_Monomer_Berendsen_VelocityVerlet_H_
#define _Parameter_Propagator_Monomer_Berendsen_VelocityVerlet_H_

#include "data/name/propagator-monomer-base.h"

namespace std {

  enum PropagatorMonomerBerendsenVVerlet {
    BV_MovePreProcess=PropagatorMonomerBaseNumberParameter,
    BV_MoveBeforeG,
    BV_MoveAfterG,
    BV_MovePostProcess,
    PropagatorMonomerBVNumberParameter
  };

}

#endif

