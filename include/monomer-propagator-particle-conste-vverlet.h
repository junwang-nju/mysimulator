
#ifndef _Monomer_Propagator_Particle_ConstantE_VelocityVerlet_H_
#define _Monomer_Propagator_Particle_ConstantE_VelocityVerlet_H_

#include "monomer-propagator.h"
#include "propagator-name-particle-conste-vverlet.h"

namespace std {

  class MonomerPropagatorParticleConstEVVerlet : public MonomerPropagatorBase {

    public:

      typedef MonomerPropagatorParticleConstEVVerlet    Type;
      typedef MonomerPropagatorBase   ParentType;

      MonomerPropagatorParticleConstEVVerlet() : ParentType() {
        this->Move.allocate();
      }

  };

}

#endif

