
#ifndef _Parameter_Subsystem_Propagator_Type_H_
#define _Parameter_Subsystem_Propagator_Type_H_

namespace std {

  enum subsysPropagatorTypeName {
    ConstantE_VelocityVerlet=0
    Berendsen_VelocityVerlet,
    Langevin_VelocityVerlet,
    subsysPropagatorNumberType
  };

}

#include "data/name/subsys-propagator-conste-vverlet.h"
#include "data/name/subsys-propagator-langevin-vverlet.h"
#include "data/name/subsys-propagator-berendsen-vverlet.h"

namespace std {

  static const subsysPropagatorParameterSize[subsysPropagatorNumberType]={
    subsysPropagatorEVNumberParameter,
    subsysPropagatorBVNumberParameter,
    subsysPropagatorLVNumberParameter
  };

}

#endif

