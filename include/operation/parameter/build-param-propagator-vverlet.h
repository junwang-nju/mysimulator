
#ifndef _Build_Parameter_Propagator_VelocityVerlet_H_
#define _Build_Parameter_Propagator_VelocityVerlet_H_

#include "operation/parameter/build-param-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorVVerlet(Propagator<T>& P) {
    BuildParameterPropagatorBase<T>(P);
  }

}

#endif

