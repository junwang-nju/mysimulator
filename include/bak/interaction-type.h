
#ifndef _Interaction_Type_H_
#define _Interaction_Type_H_

namespace std {

  enum InteractionType {
    UnknownInteraction = 0,
    ParticleParticle_Harmonic,
    ParticleParticle_LJ612,
    ParticleParticle_LJ612Cut,
    ParticleParticle_Coulomb,
    ParticleParticle_QuadPlusHarm,
    ParticleParticle_Core12,
    ParticleParticle_CoreLJ612,
    Angle_Harmonic,
    Dihedral_Periodic,
    InteractionTableTerminus,
    NumberInteractions = InteractionTableTerminus-1
  };

}

#endif
