
#ifndef _Monomer_Propagator_Parameter_Name_Particle_Berendsen_VelocityVerlet_H_
#define _Monomer_Propagator_Parameter_Name_Particle_Berendsen_VelocityVerlet_H_

#include "propagator-parameter-name-berendsen-vverlet.h"

namespace std {

  enum MonomerPropagatorMovenameParticleBV {
    PBV_BeforeG=BV_BeforeG,
    PBV_AfterG=BV_AfterG,
    PBV_PostProcess=BV_PostProcess,
    NumberMoveParticleBV=NumberMoveBV
  };

  enum MonomerPropagatorSetNameParticleBV {
    NumberSetParticleBV=0
  };

  enum MonomerPropagatorParameterNameParticleBV {
    PBV_HalfDeltaTIvM=0,
    NumberParameterParticleBV
  };

}

#endif

