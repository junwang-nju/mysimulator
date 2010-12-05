
#ifndef _Parameter_Propagator_Berendsen_VelocityVerlet_H_
#define _Parameter_Propagator_Berendsen_VelocityVerlet_H_

#include "data/name/propagator-base.h"

namespace std {

  enum PropagatorBVParameterNumber {
    BV_Temperature=PropagatorBaseNumberParameter,
    BV_RelaxTime,
    BV_DegreeFreedom,
    BV_HalfDeltaTIvRelaxT,
    BV_BScaleFactor,
    BV_AScaleFactor,
    BV_TemperatureDOF,
    BV_DualKineticEnergy,
    BV_TemperatureDOFIvDKineticEnergy,
    BV_IvHalfDeltaTIvRelaxTPlusOne,
    PropagatorBVNumberParameter
  };

}

#endif

