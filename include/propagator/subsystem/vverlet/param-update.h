
#ifndef _Propagator_Subsystem_Parameter_Update_VelocityVerlet_H_
#define _Propagator_Subsystem_Parameter_Update_VelocityVerlet_H_

#include "propagator/subsystem/common/param-update.h"
#include "propagator/subsystem/vverlet/param-name.h"

namespace mysimulator {

  template <typename T>
  void UpdateSubsysPropagatorVelVerlet(SubsysPropagator<T>& SP) {
    UpdateSubsysPropagatorCommon<T>(SP);
  }

}

#endif

