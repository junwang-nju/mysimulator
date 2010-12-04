
#ifndef _Interaction_Name_H_
#define _Interaction_Name_H_

#include "data/name/harmonic.h"
#include "data/name/lj612.h"
#include "data/name/lj612cut.h"
#include "data/name/lj1012.h"
#include "data/name/lj1012cut.h"
#include "data/name/core12.h"
#include "data/name/corelj612.h"
#include "data/name/coulomb.h"

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
