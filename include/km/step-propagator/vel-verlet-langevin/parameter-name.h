
#ifndef _Step_Propagator_VelVerlet_Langevin_Parameter_Name_H_
#define _Step_Propagator_VelVerlet_Langevin_Parameter_Name_H_

namespace mysimulator {

  enum VelVerletLangevinParameterName {
    VelVerletLangevin_PtrMass,
    VelVerletLangevin_PtrFriction,
    VelVerletLangevin_PtrRandVector,
    VelVerletLangevin_PtrRandSize,
    VelVerletLangevin_PtrNegHTIM,
    VelVerletLangevin_PtrFacBf,
    VelVerletLangevin_PtrFacAf,
    VelVerletLangevin_PtrVelocitySQ,
    VelVerletLangevin_SrcTimeStep,
    VelVerletLangevin_SrcTemperature,
    VelVerletLangevin_SrcGaussRNG,
    VelVerletLangevin_SrcMass,
    VelVerletLangevin_SrcFriction,
    VelVerletLangevin_SrcRandVector,
    VelVerletLangevin_SrcRandSize,
    VelVerletLangevin_SrcNegHTIM,
    VelVerletLangevin_SrcFacBf,
    VelVerletLangevin_SrcFacAf,
    VelVerletLangevin_SrcVelocitySQ,
    VelVerletLangevin_ValKineticEnergy,
    VelVerletLangevin_NumberParameter
  };

}

#endif

