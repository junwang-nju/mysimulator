
#ifndef _Step_Propagator_Dynamics_ManualMove_VelVerlet_ConstV_ParameterName_H_
#define _Step_Propagator_Dynamics_ManualMove_VelVerlet_ConstV_ParameterName_H_

#include "step-propagator/dynamics/manual-move/vel-verlet/parameter-name.h"

namespace mysimulator {

  enum VelVerletConstVParameterName {
    VelVerletConstV_ValKineticEnergy = ManualVelVerlet_ValKineticEnergy,
    VelVerletConstV_SrcTimeStep = ManualVelVerlet_SrcTimeStep,
    VelVerletConstV_NumberParameter = ManualVelVerlet_NumberParameter
  };

}

#endif

