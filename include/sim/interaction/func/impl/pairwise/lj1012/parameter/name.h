
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Name_H_

namespace mysimulator {

  enum LJ1012ParameterName {
    LJ1012EqRadius=0,
    LJ1012EqEnergyDepth,
    LJ1012FactorA,
    LJ1012FactorB,
    LJ1012DiffFactorA,
    LJ1012DiffFactorB,
    LJ1012NumberParameters
  };

}

#include "interaction/func/impl/pairwise/lj1012/parameter/build.h"

#endif

