
#ifndef _Interaction_Name_H_
#define _Interaction_Name_H_

#include "data/name/parameter-harmonic.h"
#include "data/name/parameter-lj612.h"
#include "data/name/parameter-lj612cut.h"
#include "data/name/parameter-lj1012.h"
#include "data/name/parameter-lj1012cut.h"
#include "data/name/parameter-core12.h"
#include "data/name/parameter-corelj612.h"
#include "data/name/parameter-coulomb.h"

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
