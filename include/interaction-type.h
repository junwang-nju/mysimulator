
#ifndef _Interaction_Type_H_
#define _Interaction_Type_H_

namespace std {

  enum InteractionType {
    UnknownInteraction = 0,
    ParticleParticle_Harmonic,
    InteractionTableTerminus,
    NumberInteractions = InteractionTableTerminus-1
  };

}

#endif

