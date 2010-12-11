
#ifndef _Parameter_Subsystem_Propagator_Berendsen_VelocityVerlet_H_
#define _Parameter_Subsystem_Propagator_Berendsen_VelocityVerlet_H_

#include "data/name/subsys-propagator-vverlet.h"

namespace std {

  enum subsysPropagatorBVParameterName {
    BV_Temperature=subsysPropagatorVelVerletNumberParameter,
    BV_RelaxTime,
    BV_DegreeFreedom,
    BV_HalfTimeStepIvRelaxT,
    BV_BScaleFactor,
    BV_AScaleFactor,
    BV_TemperatureDOF,
    BV_DualKineticEnergy,
    BV_TemperatureDOFIvDKineticEnergy,
    BV_IvHalfTimeStepIvRelaxTPlusOne,
    subsysPropagatorBVNumberParameter
  };

}

#endif

