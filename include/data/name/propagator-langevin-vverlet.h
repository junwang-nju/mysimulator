
#ifndef _Parameter_Propagator_Langevin_VelocityVerlet_H_
#define _Parameter_Propagator_Langevin_VelocityVerlet_H_

#include "data/name/propagator.h"

namespace std {

  enum PropagatorLVParameterName {
    LV_Temperature=PropagatorBaseNumberParameter,
    LV_Viscosity,
    LV_TemperatureDeltaT,
    LV_GaussianRNG,
    PropagatorLVNumberParameter
  };

}

#endif

