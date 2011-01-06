
#ifndef _Interaction_Name_H_
#define _Interaction_Name_H_

#include "data/name/lj612.h"
#include "data/name/lj612cut.h"
#include "data/name/lj1012.h"
#include "data/name/lj1012cut.h"
#include "data/name/core12.h"
#include "data/name/corelj612.h"
#include "data/name/coulomb.h"
#include "data/name/harmonic.h"
#include "data/name/fene.h"
#include "data/name/quad-plus-harmonic.h"

#include "data/name/angle-harmonic.h"
#include "data/name/dihedral-periodic.h"

#include "data/name/core-expanded-lj612.h"
#include "data/name/core-expanded-corelj612.h"

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
    FENE,
    QuadPlusHarmonic,
    AngleHarmonic,
    DihedralPeriodic,
    CoreExpandedLJ612,
    CoreExpandedCoreLJ612,
    InteractionTableTerminus,
    NumberInteractions=InteractionTableTerminus-1
  };

}

#endif
