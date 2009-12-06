
#ifndef _Particle_H_
#define _Particle_H_

#include "property-frame.h"

namespace std {

  enum ParticlePropertyFlag {
    Particle_VelocityEnable=1U,
    Particle_GradientEnable=2U,
    Particle_MassEnable=4U
  };
  
  enum ParticleFeatureSize {
    particle_info_size=4,
    particle_mass_size=1,
    particle_imass_size=1
  };

}

#endif

