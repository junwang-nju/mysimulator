
#ifndef _Step_Propagator_VelVerlet_Langevin_Parameter_Name_H_
#define _Step_Propagator_VelVerlet_Langevin_Parameter_Name_H_

#include "step-propagator/vel-verlet/parameter-name.h"

namespace mysimulator {

  enum VelVerletLangevinParameterName {
    VelVerletLangevin_PtrMass           = VelVerlet_PtrMass,
    VelVerletLangevin_PtrNegHTIM        = VelVerlet_PtrNegHTIM,
    VelVerletLangevin_PtrVelocitySQ     = VelVerlet_PtrVelocitySQ,
    VelVerletLangevin_SrcTimeStep       = VelVerlet_SrcTimeStep,
    VelVerletLangevin_SrcMass           = VelVerlet_SrcMass,
    VelVerletLangevin_SrcNegHTIM        = VelVerlet_SrcNegHTIM,
    VelVerletLangevin_SrcVelocitySQ     = VelVerlet_SrcVelocitySQ,
    VelVerletLangevin_ValKineticEnergy  = VelVerlet_ValKineticEnergy,
    VelVerletLangevin_PtrFriction       = VelVerlet_NumberParameter,
    VelVerletLangevin_PtrRandVector,
    VelVerletLangevin_PtrRandSize,
    VelVerletLangevin_PtrFacBf,
    VelVerletLangevin_PtrFacAf,
    VelVerletLangevin_SrcTemperature,
    VelVerletLangevin_SrcGaussRNG,
    VelVerletLangevin_SrcFriction,
    VelVerletLangevin_SrcRandVector,
    VelVerletLangevin_SrcRandSize,
    VelVerletLangevin_SrcFacBf,
    VelVerletLangevin_SrcFacAf,
    VelVerletLangevin_NumberParameter
  };

}

#endif

