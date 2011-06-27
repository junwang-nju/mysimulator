
#ifndef _Propagator_Parameter_Update_VelocityVerlet_H_
#define _Propagator_Parameter_Update_VelocityVerlet_H_

#include "propagator/parameter/vverlet/name.h"
#include "propagator/parameter/common/update.h"

namespace mysimulator {

  template <typename T>
  void UpdatePropagatorVelocityVerlet(Propagator<T>& P) {
    UpdatePropagatorCommon(P);
  }

}

#endif

