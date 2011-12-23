
#ifndef _System_Propagate_VelocityVerlet_ConstE_Parameter_Name_H_
#define _System_Propagate_VelocityVerlet_ConstE_Parameter_Name_H_

namespace mysimulator {

  enum ParameterConstEVelVerletame {
    CEVVerletTimeStep=0,
    CEVVerletMassMode,
    CEVVerletMass,
    CEVVerletMassData,
    CEVVerletNegHTimeIMass,
    CEVVerletNegHTimeIMassData,
    CEVVerletUpdateHTIMFunc,
    CEVVerletBfMoveFunc,
    CEVVerletAfMoveFunc,
    NumberParameterConstEVelVerlet
  };

}

#endif

