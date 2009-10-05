
#ifndef _Particle_H_
#define _Particle_H_

#include "property.h"

namespace std {

  enum ParticlePropertyFlag {

    Particle_VelocityEnable=1U,
    
    Particle_GradientEnable=2U,
    
    Particle_MassEnable=4U

  };

  Property& allocate_as_Particle(Property& Prop, uint Dimen, uint Flag=0U) {
    Prop.MonomerType=Particle;
    Prop.Info.allocate(1);
    Prop.Info[0]=Dimen;
    Prop.Coordinate.allocate(Dimen);
    Prop.Mask.allocate(Dimen);
    if(Flag&Particle_VelocityEnable)   Prop.Velocity.allocate(Dimen);
    if(Flag&Particle_GradientEnable)   Prop.Gradient.allocate(Dimen);
    if(Flag&Particle_MassEnable) {
      Prop.Mass.allocate(1);
      Prop.ivMass.allocate(1);
    }
    return Prop;
  }

}

#endif

