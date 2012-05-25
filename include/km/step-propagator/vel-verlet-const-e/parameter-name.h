
#ifndef _Step_Propagator_VelVerlet_ConsetE_Parameter_Name_H_
#define _Step_Propagator_VelVerlet_ConsetE_Parameter_Name_H_

namespace mysimulator {

  enum VelVerletConstEParameterName {
    VelVerletConstE_PtrMass=0,
    VelVerletConstE_PtrNegHTIM,
    VelVerletConstE_PtrVelocitySQ,
    VelVerletConstE_SrcTimeStep,
    VelVerletConstE_SrcMass,
    VelVerletConstE_SrcNegHTIM,
    VelVerletConstE_SrcVelocitySQ,
    VelVerletConstE_ValKineticEnergy,
    VelVerletConstE_NumberParameter
  };

}

#endif

