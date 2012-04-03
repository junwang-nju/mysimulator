
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Name_H_

#include "interaction/func/impl/pairwise/common/parameter/name.h"

namespace mysimulator {

  enum LJ612ParameterName {
    LJ612EqRadius=PairwiseCommonNumberParameters,
    LJ612EqEnergyDepth,
    LJ612FactorA,
    LJ612FactorB,
    LJ612DiffFactorA,
    LJ612DiffFactorB,
    LJ612NumberParameters
  };

}

#include "interaction/func/impl/pairwise/lj612/parameter/build.h"

#endif

