
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Parameter_Name_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"

namespace mysimulator {

  enum LJ1012CutParameterName {
    LJ1012CutEqRadius       = LJ1012EqRadius,
    LJ1012CutEqEnergyDepth  = LJ1012EqEnergyDepth,
    LJ1012CutFactorA        = LJ1012FactorA,
    LJ1012CutFactorB        = LJ1012FactorB,
    LJ1012CutDiffFactorA    = LJ1012DiffFactorA,
    LJ1012CutDiffFactorB    = LJ1012DiffFactorB,
    LJ1012CutCutR           = LJ1012NumberParameters,
    LJ1012CutCutRSQ,
    LJ1012CutVc,
    LJ1012CutKc,
    LJ1012CutNumberParameter
  };

}

#include "interaction/func/impl/pairwise/lj1012cut/parameter/build.h"

#endif

