
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_AFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_AFric_Interface_H_

#include "step-propagator/vel-verlet/langevin/array-mass/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_AMassAFric
      : public StepPropagatorVelVerletLangevin_AMass<T> {

  };

}

#endif

