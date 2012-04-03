
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Parameter_Name_H_

#include "interaction/func/impl/pairwise/common/parameter/name.h"

namespace mysimulator {

  enum Core12ParameterName {
    Core12EqStrength=PairwiseCommonNumberParameters,
    Core12TwlfEqStrength,
    Core12NumberParameters
  };

}

#include "interaction/func/impl/pairwise/core12/parameter/build.h"

#endif

