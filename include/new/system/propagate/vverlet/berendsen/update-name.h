
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Update_Name_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Update_Name_H_

namespace mysimulator {

  enum UpdateBerendsenVelVerletName {
    CalcBsVVerletNegHTIM=0,
    CalcBsVVerletDOF,
    CalcBsVVerletFac,
    CalcBsVVerletVSQ,
    CalcBsVVerletDualKE,
    CalcBsVVerletKESimple,
    NumberUpdateBerendsenVelVerlet
  };

}

#endif

