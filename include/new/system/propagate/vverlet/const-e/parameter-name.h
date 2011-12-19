
#ifndef _System_Propagate_VelocityVerlet_ConstE_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_ConstE_Parameter_Name_H_

namespace mysimulator {

  enum ParameterConstEVelVerletame {
    ModCEVVerletMass=0,
    PtrCEVVerletTimeStep,
    PtrCEVVerletMass,
    PtrCEVVerletNegHTIM,
    PtrCEVVerletVelocitySQ,
    DatCEVVerletMass,
    DatCEVVerletNegHTIM,
    DatCEVVerletVelocitySQ,
    ValCEVVerletKineticEnergy,
    FunCEVVerletUpdateHTIM,
    FunCEVVerletUpdateVSQ,
    FunCEVVerletUpdateVSQInit,
    FunCEVVerletUpdateKE,
    FunCEVVerletBfMove,
    FunCEVVerletAfMove,
    NumberParameterConstEVelVerlet
  };

}

#endif

