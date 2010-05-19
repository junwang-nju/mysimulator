
#ifndef _Monomer_Propagator_Operate_H_
#define _Monomer_Propagator_Operate_H_

#include "monomer-name.h"
#include "propagator-move-name.h"
#include "monomer-propagator-particle-conste-vverlet.h"
#include "monomer-propagator-particle-berendsen-vverlet.h"
#include "monomer-propagator-particle-langevin-vverlet.h"

namespace std {

  void Set(MonomerPropagator& MP,
           const unsigned int UType, const unsigned int MType) {
    assert(IsAvailable(MP));
    *(MP.UnitKind)=UType;
    *(MP.MoveMode)=MType;
    if(UType==ParticleType) {
      if(MType==ConstantE_VelocityVerlet) SetAsParticleEV(MP);
      else if(MType==Berendsen_VelocityVerlet) SetAsParticleBV(MP);
      else if(MType==Langevin_VelocityVerlet) SetAsParticleLV(MP);
      else myError("Not Implemented Move Type");
    } else myError("Not Implemented Monomer Type");
  }

}

#endif

