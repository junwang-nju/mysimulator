
#ifndef _Step_Propagator_Dynamics_VelVerlet_Parameter_Name_H_
#define _Step_Propagator_Dynamics_VelVerlet_Parameter_Name_H_

#include "step-propagator/dynamics/parameter-name.h"

namespace mysimulator {

  enum VelVerletParameterName {
    VelVerlet_ValKineticEnergy=Dynamics_ValKineticEnergy,
    VelVerlet_PtrMass=Dynamics_NumberParameter,
    VelVerlet_PtrNegHTIM,
    VelVerlet_PtrVelocitySQ,
    VelVerlet_SrcTimeStep,
    VelVerlet_SrcMass,
    VelVerlet_SrcNegHTIM,
    VelVerlet_SrcVelocitySQ,
    VelVerlet_NumberParameter
  };

}

#endif

