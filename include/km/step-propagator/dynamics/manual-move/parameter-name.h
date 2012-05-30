
#ifndef _Step_Propagator_Dynamics_ManualMove_Parameter_Name_H_
#define _Step_Propagator_Dynamics_ManualMove_Parameter_Name_H_

#include "step-propagator/dynamics/parameter-name.h"

namespace mysimulator {

  enum ManualMoveParameterName {
    ManualMove_ValKineticEnergy = Dynamics_ValKineticEnergy,
    ManualMove_SrcTimeStep = Dynamics_NumberParameter,
    ManualMove_NumberParameter
  };

}

#endif

