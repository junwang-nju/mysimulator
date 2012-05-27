
#ifndef _Step_Propagator_VelVerlet_Parameter_Name_Interface_H_
#define _Step_Propagator_VelVerlet_Parameter_Name_Interface_H_

#include "step-propagator/parameter-name.h"

namespace mysimulator {

  enum VelVerletParameterName {
    VelVerlet_ValKineticEnergy=StepPropagator_ValKineticEnergy,
    VelVerlet_PtrMass=StepPropagator_NumberParameter,
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

