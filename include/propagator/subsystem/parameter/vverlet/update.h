
#ifndef _Propagator_Subsystem_Parameter_Update_VelocityVerlet_H_
#define _Propagator_Subsystem_Parameter_Update_VelocityVerlet_H_

#include "propagator/subsystem/parameter/common/update.h"
#include "propagator/subsystem/parameter/vverlet/name.h"

namespace mysimulator {

  template <typename T>
  void UpdateSubsysPropagatorVelVerlet(SubsysPropagator<T>& SP) {
    UpdateSubsysPropagatorCommon<T>(SP);
  }

}

#endif

