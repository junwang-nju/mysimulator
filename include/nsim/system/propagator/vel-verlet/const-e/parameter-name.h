
#ifndef _System_Propagator_VelVerlet_ConstE_Parameter_Name_H_
#define _System_Propagator_VelVerlet_ConstE_Parameter_Name_H_

namespace mysimulator {

  enum VelVerletConstEParameterName {
    VelVerletConstEModMass=0,
    VelVerletConstEPtrMass,
    VelVerletConstEPtrNegHTIM,
    VelVerletConstEPtrVelocitySQ,
    VelVerletConstESrcTimeStep,
    VelVerletConstESrcMass,
    VelVerletConstESrcNegHTIM,
    VelVerletConstESrcVelocitySQ,
    VelVerletConstEValKineticEnergy,
    VelVerletConstEFuncUpdateHTIM,
    VelVerletConstEFuncUpdateVSQ,
    VelVerletConstEFuncUpdateKESimple,
    VelVerletConstEFuncMoveBefore,
    VelVerletConstEFuncMoveAfter,
    VelVerletConstENumberParameters
  };

}

#endif

