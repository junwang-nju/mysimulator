
#ifndef _System_Propagator_VelVerlet_Langevin_Parameter_Name_H_
#define _System_Propagator_VelVerlet_Langevin_Parameter_Name_H_

namespace mysimulator {

  enum VelVerletLangevinParameterName {
    VelVerletLangevinModMass=0,
    VelVerletLangevinModFriction,
    VelVerletLangevinPtrMass,
    VelVerletLangevinPtrFriction,
    VelVerletLangevinPtrRandVector,
    VelVerletLangevinPtrRandSize,
    VelVerletLangevinPtrNegHTIM,
    VelVerletLangevinPtrFacBf,
    VelVerletLangevinPtrFacAf,
    VelVerletLangevinPtrVelocitySQ,
    VelVerletLangevinSrcTimeStep,
    VelVerletLangevinSrcTemperature,
    VelVerletLangevinSrcGaussRNG,
    VelVerletLangevinSrcMass,
    VelVerletLangevinSrcFriction,
    VelVerletLangevinSrcRandVector,
    VelVerletLangevinSrcRandSize,
    VelVerletLangevinSrcNegHTIM,
    VelVerletLangevinSrcFacBf,
    VelVerletLangevinSrcFacAf,
    VelVerletLangevinSrcVelocitySQ,
    VelVerletLangevinValKineticEnergy,
    VelVerletLangevinFuncUpdateHTIM,
    VelVerletLangevinFuncUpdateRandSize,
    VelVerletLangevinFuncUpdateVSQ,
    VelVerletLangevinFuncUpdateKESimple,
    VelVerletLangevinFuncMoveBefore,
    VelVerletLangevinFuncMoveAfter,
    VelVerletLangevinNumberParameters
  };

}

#endif

