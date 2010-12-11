
#ifndef _Parameter_Subsystem_Propagator_Langevin_VelocityVerlet_H_
#define _Parameter_Subsystem_Propagator_Langevin_VelocityVerlet_H_

#include "data/name/subsys-propagator-vverlet.h"

namespace std {

  enum subsysPropagatorLVParameterName {
    LV_Temperature=subsysPropagatorVelVerletNumberParameter,
    LV_Viscosity,
    LV_TemperatureTimeStep,
    LV_GaussianRNG,
    subsysPropagatorLVNumberParameter
  };

}

#endif

