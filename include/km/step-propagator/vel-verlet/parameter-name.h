
#ifndef _Step_Propagator_VelVerlet_Parameter_Name_Interface_H_
#define _Step_Propagator_VelVerlet_Parameter_Name_Interface_H_

namespace mysimulator {

  enum VelVerletParameterName {
    VelVerlet_PtrMass=0,
    VelVerlet_PtrNegHTIM,
    VelVerlet_PtrVelocitySQ,
    VelVerlet_SrcTimeStep,
    VelVerlet_SrcMass,
    VelVerlet_SrcNegHTIM,
    VelVerlet_SrcVelocitySQ,
    VelVerlet_ValKineticEnergy,
    VelVerlet_NumberParameter
  };

}

#endif

