
#ifndef _Build_Parameter_Propagator_Base_H_
#define _Build_Parameter_Propagator_Base_H_

#include "data/basic/unique-parameter.h"
#include "data/name/propagator-base.h"
#include <iostream>

namespace std {

  template <typename T>
  void BuildParameterSubsysPropagatorBase(subsysPropagator<T>& GP) {
    copy(GP[HalfTimeStep],0.5*GP[TimeStep].value<T>());
  }

}

#endif

