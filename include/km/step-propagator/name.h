
#ifndef _Step_Propagator_Name_H_
#define _Step_Propagator_Name_H_

namespace mysimulator {

  enum StepPropagatorName {
    FixPosition=0,
    MinimizerShiftLine,
    VelVerletConstE,
    VelVerletLangevin,
    VelVerletBerendsen,
    VelVerletConstVelocity,
    NumberStepPropagator,
    UnassignedStepPropagator
  };

}

#endif

