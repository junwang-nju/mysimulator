
#ifndef _Parameter_Subsystem_Propagator_VelocityVerlet_H_
#define _Parameter_Subsystem_Propagator_VelocityVerlet_H_

#include "subsys-propagator-base.h"

namespace std {

  enum subsysPropagatorVelVerletParameterName {
    VVerletMove_BeforeG=subsysPropagatorBaseNumberParameter,
    VVerletMove_AfterG,
    subsysPropagatorVelVerletNumberParameter
  };

}

#endif
