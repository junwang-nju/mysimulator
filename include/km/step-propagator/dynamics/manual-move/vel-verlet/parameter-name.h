
#ifndef _Step_Propagator_Dynamics_ManualMove_VelVerlet_Parameter_Name_H_
#define _Step_Propagator_Dynamics_ManualMove_VelVerlet_Parameter_Name_H_

#include "step-propagator/dynamics/parameter-name.h"

namespace mysimulator {

  enum ManualVelVerletParameterName {
    ManualVelVerlet_ValKineticEnergy = Dynamics_ValKineticEnergy,
    ManualVelVerlet_SrcTimeStep = Dynamics_NumberParameter,
    ManualVelVerlet_NumberParameter
  };

}

#endif

