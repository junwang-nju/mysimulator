
#ifndef _System_Propagate_VelocityVerlet_Langevin_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_Langevin_Parameter_Name_H_

namespace mysimulator {

  enum ParameterLangevinVelVerletName {
  	LgVVerletTimeStep=0,
  	LgVVerletTemperature,
    LgVVerletMassMode,
    LgVVerletFrictionMode,
  	LgVVerletMass,
  	LgVVerletMassData,
  	LgVVerletFriction,
  	LgVVerletFrictionData,
  	LgVVerletGaussRNG,
  	LgVVerletRandVector,
  	LgVVerletRandVectorData,
  	LgVVerletRandSize,
    LgVVerletRandSizeData,
    LgVVerletNegHTIM,
    LgVVerletNegHTIMData,
  	LgVVerletFac1,
  	LgVVerletFac1Data,
  	LgVVerletFac2,
  	LgVVerletFac2Data,
    LgVVerletUpdateHTIMFunc,
    LgVVerletUpdateRandSizeFunc,
    LgVVerletUpdateFacFunc,
  	LgVVerletBfMoveFunc,
  	LgVVerletAfMoveFunc,
  	NumberParameterLangevinVelVerlet
  };

}

#endif

