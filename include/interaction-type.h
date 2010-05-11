
#ifndef _Interaction_Type_H_
#define _Interaction_Type_H_

#include "interaction-pairwise-harmonic.h"
#include "interaction-pairwise-lj612.h"
#include "interaction-pairwise-core12.h"
#include "interaction-pairwise-lj1012.h"
#include "interaction-pairwise-lj612cut.h"
#include "interaction-pairwise-lj1012cut.h"
#include "interaction-pairwise-corelj612.h"
#include "interaction-pairwise-coulomb.h"
#include "interaction-pairwise-quadharm.h"

namespace std {
  enum InteractionTypeName {
    PairwiseHarmonic=0,
    PairwiseLJ612,
    PairwiseLJ1012,
    PairwiseCore12,
    PairwiseLJ612Cut,
    PairwiseLJ1012Cut,
    PairwiseCoreLJ612,
    PairwiseCoulomb,
    PairwiseQuadHarm,
    InteractionTypeTableTerminus,
    NumberInteractions = InteractionTypeTableTerminus-1
  };
}

#endif

