
#ifndef _Monomer_Propagator_Operation_H_
#define _Monomer_Propagator_Operation_H_

#include "monomer-name.h"
#include "propagator-move-name.h"
#include "monomer-propagator-particle-conste-vverlet.h"

namespace std {

  void SetUp(class MonomerPropagator& MP,
             const unsigned int UnitType, const unsigned int MoveType) {
    MP.UnitMode=UnitType;
    if(MP.UnitMode==ParticleType) {
      if(MoveType==ConstE_VelocityVerlet) SetAsParticleEV(MP);
      else myError("Not Implemented Type");
    } else myError("Not Implemented Type");
  }

}

#endif

