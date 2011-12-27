
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Parameter_Name_H_

namespace mysimulator {

  enum ParameterBerendsenVelVerletName {
    BsVVerletTimeStep=0,
    BsVVerletTemperature,
    BsVVerletMassMode,
    BsVVerletMass,
    BsVVerletMassData,
    BsVVerletNegHTIM,
    BsVVerletNegHTIMData,
    BsVVerletVelocitySQ,
    BsVVerletVelocitySQData,
    BsVVerletKineticEnergy,
    BsVVerletUpdateNegHTIMFunc,
    BsVVerletUpdateVSQFunc,
    BsVVerletUpdateVSQInitFunc,
    BsVVerletUpdateKEFunc,
    BsVVerletBfMoveFunc,
    BsVVerletAfMoveFunc,
    NumberParameterBerendsenVelVerlet
  };

}

#endif

