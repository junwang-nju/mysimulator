
#ifndef _Step_Propagator_Dynamics_ManualMove_Interface_H_
#define _Step_Propagator_Dynamics_ManualMove_Interface_H_

#include "step-propagator/dynamics/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorManualMove : public StepPropagatorDynamics<T> {
  };

}

#endif

