
#ifndef _System_Propagate_VelocityVerlet_Langevin_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_Langevin_Parameter_Name_H_

namespace mysimulator {

  enum ParameterLangevinVelVerletName {
    ModLgVVerletMass=0,
    ModLgVVerletFriction,
  	PtrLgVVerletTimeStep,
  	PtrLgVVerletTemperature,
  	PtrLgVVerletMass,
  	PtrLgVVerletFriction,
  	PtrLgVVerletRandVector,
  	PtrLgVVerletRandSize,
    PtrLgVVerletNegHTIM,
  	PtrLgVVerletFac1,
  	PtrLgVVerletFac2,
    PtrLgVVerletVelocitySQ,
  	DatLgVVerletGaussRNG,
  	DatLgVVerletMass,
  	DatLgVVerletFriction,
  	DatLgVVerletRandVector,
    DatLgVVerletRandSize,
    DatLgVVerletNegHTIM,
  	DatLgVVerletFac1,
  	DatLgVVerletFac2,
    DatLgVVerletVelocitySQ,
    ValLgVVerletKineticEnergy,
    FunLgVVerletUpdateHTIM,
    FunLgVVerletUpdateRandSize,
    FunLgVVerletUpdateFac,
    FunLgVVerletUpdateVSQ,
    FunLgVVerletUpdateVSQInit,
    FunLgVVerletUpdateKE,
  	FunLgVVerletBfMove,
  	FunLgVVerletAfMove,
  	NumberParameterLangevinVelVerlet
  };

}

#endif

