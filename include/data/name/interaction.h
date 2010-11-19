
#ifndef _Interaction_Name_H_
#define _Interaction_Name_H_

namespace std {

  enum InteractionName {
    Harmonic=0,
    LJ612,
    LJ612Cut,
    LJ1012,
    LJ1012Cut,
    Core12,
    CoreLJ612,
    Coulomb,
    InteractionTableTerminus,
    NumberInteractions=InteractionTableTerminus-1
  };

}

#endif
