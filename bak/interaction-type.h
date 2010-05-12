
/**
 * @file interaction-type.h
 * @brief The type identities for various interactions
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Interaction_Type_H_
#define _Interaction_Type_H_

namespace std {

  enum InteractionType {
    UnknownInteraction=0,
    ParticleParticle_Harmonic,
    ParticleParticle_LJ1012,
    ParticleParticle_LJ612,
    ParticleParticle_LJ612Cut,
    ParticleParticle_Coulomb,
    ParticleParticle_CoulombWDE,
    ParticleParticle_QuadHarmonic,
    InteractionTableTerminus,
    NumberInteraction=InteractionTableTerminus-1
  };

}

#endif

