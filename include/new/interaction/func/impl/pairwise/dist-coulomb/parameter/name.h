
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Name_H_

#include "interaction/func/impl/pairwise/common/parameter/name.h"

namespace mysimulator {

  enum DistCoulombParameterName {
    DistCoulombChargeA=PairwiseCommonNumberParameters,
    DistCoulombChargeB,
    DistCoulombDielectricFac,
    DistCoulombStrength,
    DistCoulombDualStrength,
    DistCoulombNumberParameters
  };

}

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/build.h"

#endif

