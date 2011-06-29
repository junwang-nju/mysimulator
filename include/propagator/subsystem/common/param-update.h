
#ifndef _Propagator_Subsystem_Parameter_Update_Common_H_
#define _Propagator_Subsystem_Parameter_Update_Common_H_

#include "propagator/subsystem/common/param-name.h"
#include "propagator/subsystem/interface.h"

namespace mysimulator {

  template <typename T>
  void UpdateSubsysPropagatorCommon(SubsysPropagator<T>& SP) {
    copy(SP.Data[HalfTimeStep],0.5*SP.Data[TimeStep].value<T>());
    SP.Data[MoveTrig].u=SP.Data[MoveTrigInterval].u;
  }

}

#endif

