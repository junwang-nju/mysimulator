
#ifndef _Build_Parameter_Subsystem_Propagator_Base_H_
#define _Build_Parameter_Subsystem_Propagator_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/subsys-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterSubsysPropagatorBase(subsysPropagator<T>& SP) {
    copy(SP[HalfTimeStep],
         0.5*static_cast<UniqueParameter&>(SP[TimeStep]).value<T>());
    SP[PropagateTrigger].u=SP[PropagateTriggerStep].u;
  }

}

#endif

