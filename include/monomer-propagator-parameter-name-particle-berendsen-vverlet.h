
#ifndef _Monomoer_Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_
#define _Monomoer_Propagator_Parameter_Name_Berendsen_VelocityVerlet_H_

#include "propagator-parameter-name-berendsen-vverlet.h"

namespace std {

  enum MonomerPropagatorMoveNameParticleBV {
    PBV_BeforeG=BV_BeforeG,
    PBV_AfterG=BV_AfterG,
    PBV_PostProcess=BV_PostProcess,
    NumberMoveParticleBV=NumberMoveBV
  };

  enum MonomerPropagatorParamNameParticleBV {
    PBV_HalfDeltaTIvM=0,
    NumberParamParticleBV
  };

  enum MonomerPropagatorSetNameParticleBV {
    NumberSetParticleBV=0
  };

}

#endif

