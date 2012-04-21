
#ifndef _System_Propagator_VelocityVerlet_ConstE_Parameter_Name_H_
#define _System_Propagator_VelocityVerlet_ConstE_Parameter_Name_H_

namespace mysimulator {

  enum VelVerletConstEParameterName {
    ModVVerletCEMass=0,
    PtrVVerletCETimeStep,
    PtrVVerletCEMass,
    PtrVverletCENegHTIM,
    PtrVVerletCEVelocitySQ,
    ValVverletCEKineticEnergy,
    FuncVVerletCEUpdateHTIM,
    FuncVVerletCEUpdateVSQ,
    FuncVVerletCEUpdateKESimple,
    FuncVVerletCEBeforeMove,
    FuncVVerletCEAfterMove,
    VelVerletConstENumberParameters
  };

}

#endif

