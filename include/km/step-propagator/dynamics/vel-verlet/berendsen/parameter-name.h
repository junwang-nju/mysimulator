
#ifndef _Step_Propagator_Dynamics_VelVerlet_Berendsen_Parameter_Name_H_
#define _Step_Propagator_Dynamics_VelVerlet_Berendsen_Parameter_Name_H_

#include "step-propagator/dynamics/vel-verlet/const-e/parameter-name.h"

namespace mysimulator {

  enum VelVerletBerendsenParameterName {
    VelVerletBerendsen_ValKineticEnergy = VelVerletConstE_ValKineticEnergy,
    VelVerletBerendsen_PtrMass          = VelVerletConstE_PtrMass,
    VelVerletBerendsen_PtrNegHTIM       = VelVerletConstE_PtrNegHTIM,
    VelVerletBerendsen_PtrVelocitySQ    = VelVerletConstE_PtrVelocitySQ,
    VelVerletBerendsen_SrcTimeStep      = VelVerletConstE_SrcTimeStep,
    VelVerletBerendsen_SrcMass          = VelVerletConstE_SrcMass,
    VelVerletBerendsen_SrcNegHTIM       = VelVerletConstE_SrcNegHTIM,
    VelVerletBerendsen_SrcVelocitySQ    = VelVerletConstE_SrcVelocitySQ,
    VelVerletBerendsen_SrcRelaxTime     = VelVerletConstE_NumberParameter,
    VelVerletBerendsen_SrcTemperature,
    VelVerletBerendsen_ValFacBf1,
    VelVerletBerendsen_ValFacBf2,
    VelVerletBerendsen_ValFacAf1,
    VelVerletBerendsen_ValFacAf2,
    VelVerletBerendsen_ValDOF,
    VelVerletBerendsen_ValDualKineticEnergy,
    VelVerletBerendsen_NumberParameter
  };

}
#endif

