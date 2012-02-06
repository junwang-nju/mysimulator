
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Update_Name_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Update_Name_H_

namespace mysimulator {

  enum UpdateBerendsenVelVerletName {
    BsVVerletNegHTIMCalc=0,
    BsVVerletFacCalc,
    BsVVerletVSQCalc,
    BsVVerletDualKECalc,
    BsVVerletKECalc,
    NumberUpdateBerendsenVelVerlet
  };

}

#endif

