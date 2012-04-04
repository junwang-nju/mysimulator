
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Parameter_Name_H_

#include "interaction/func/impl/pairwise/common/parameter/name.h"

namespace mysimulator {

  enum CoulombParameterName {
    CoulombChargeA=PairwiseCommonNumberParameters,
    CoulombChargeB,
    CoulombDielectric,
    CoulombStrength,
    CoulombNumberParameters
  };

}

#include "interaction/func/impl/pairwise/coulomb/parameter/build.h"

#endif

