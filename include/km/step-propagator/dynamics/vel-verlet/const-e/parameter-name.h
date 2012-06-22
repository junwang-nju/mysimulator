
#ifndef _Step_Propagator_Dynamics_VelVerlet_ConstE_Parameter_Name_H_
#define _Step_Propagator_Dynamics_VelVerlet_ConstE_Parameter_Name_H_

#include "step-propagator/dynamics/vel-verlet/parameter-name.h"

namespace mysimulator {

  enum VelVerletConstEParameterName {
    VelVerletConstE_ValKineticEnergy  = VelVerlet_ValKineticEnergy,
    VelVerletConstE_PtrMass           = VelVerlet_PtrMass,
    VelVerletConstE_PtrNegHTIM        = VelVerlet_PtrNegHTIM,
    VelVerletConstE_PtrVelocitySQ     = VelVerlet_PtrVelocitySQ,
    VelVerletConstE_SrcTimeStep       = VelVerlet_SrcTimeStep,
    VelVerletConstE_SrcMass           = VelVerlet_SrcMass,
    VelVerletConstE_SrcNegHTIM        = VelVerlet_SrcNegHTIM,
    VelVerletConstE_SrcVelocitySQ     = VelVerlet_SrcVelocitySQ,
    VelVerletConstE_NumberParameter   = VelVerlet_NumberParameter
  };

}

#endif

