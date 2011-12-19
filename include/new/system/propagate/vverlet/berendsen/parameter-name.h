
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Parameter_Name_H_

namespace mysimulator {

  enum ParameterBerendsenVelVerletName {
    BsVVerletTimeStep=0,
    BsVVerletRelaxTime,
    BsVVerletTemperature,
    BsVVerletMassMode,
    BsVVerletMass,
    BsVVerletMassData,
    BsVVerletNegHTIM,
    BsVVerletNegHTIMData,
    BsVVerletVFacA1,
    BsVVerletVFacA2,
    BsVVerletVFacB1,
    BsVVerletVFacB2,
    BsVVerletVelocitySQ,
    BsVVerletVelocitySQData,
    BsVVerletKineticEnergy,
    BsVVerletDualKineticEnergy,
    BsVVerletUpdateNegHTIMFunc,
    BsVVerletUpdateFacFunc,
    BsVVerletUpdateVSQFunc,
    BsVVerletUpdateVSQInitFunc,
    BsVVerletUpdateKEFunc,
    BsVVerletBfMoveFunc,
    BsVVerletAfMoveFunc,
    NumberParameterBerendsenVelVerlet
  };

}

#endif

