
#ifndef _Propagator_Base__Parameter_Update_VelocityVerlet_H_
#define _Propagator_Base_Parameter_Update_VelocityVerlet_H_

#include "propagator/base/parameter/vverlet/name.h"
#include "propagator/base/parameter/common/update.h"

namespace mysimulator {

  template <typename T>
  void UpdatePropagatorBaseVelocityVerlet(PropagatorBase<T>& P) {
    UpdatePropagatorBaseCommon(P);
  }

}

#endif

