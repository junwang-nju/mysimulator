
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Name_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"

namespace mysimulator {

  enum LJ612CutParameterName {
    LJ612CutEqRadius      = LJ612EqRadius,
    LJ612CutEqEnergyDepth = LJ612EqEnergyDepth,
    LJ612CutFactorA       = LJ612FactorA,
    LJ612CutFactorB       = LJ612FactorB,
    LJ612CutDiffFactorA   = LJ612DiffFactorA,
    LJ612CutDiffFactorB   = LJ612DiffFactorB,
    LJ612CutCutR          = LJ612NumberParameters,
    LJ612CutCutRSQ,
    LJ612CutVc,
    LJ612CutKc,
    LJ612CutNumberParameters
  };

}

#include "interaction/func/impl/pairwise/lj612cut/parameter/build.h"

#endif

