
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Parameter_Name_H_

namespace mysimulator {

  enum ParameterBerendsenVelVerletName {
    ModBsVVerletMass=0,
    PtrBsVVerletTimeStep,
    PtrBsVVerletRelaxTime,
    PtrBsVVerletTemperature,
    PtrBsVVerletMass,
    PtrBsVVerletNegHTIM,
    PtrBsVVerletVelocitySQ,
    DatBsVVerletMass,
    DatBsVVerletNegHTIM,
    DatBsVVerletVelocitySQ,
    ValBsVVerletDOF,
    ValBsVVerletVFacA1,
    ValBsVVerletVFacA2,
    ValBsVVerletVFacB1,
    ValBsVVerletVFacB2,
    ValBsVVerletKineticEnergy,
    ValBsVVerletDualKineticEnergy,
    FunBsVVerletUpdateHTIM,
    FunBsVVerletUpdateVSQ,
    FunBsVVerletUpdateDKE,
    FunBsVVerletBfMove,
    FunBsVVerletAfMove,
    NumberParameterBerendsenVelVerlet
  };

}

#endif

