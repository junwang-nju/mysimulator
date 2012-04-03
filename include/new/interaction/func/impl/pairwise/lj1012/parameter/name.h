
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Name_H_

#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  enum LJ1012ParameterName {
    LJ1012EqRadius=InteractionCommonNumberParameters,
    LJ1012EqEnergyDepth,
    LJ1012EqRadiusSQ,
    LJ1012SixtyEqEnergyDepth,
    LJ1012NumberParameters
  };

}

#include "interaction/func/impl/pairwise/lj1012/parameter/build.h"

#endif

