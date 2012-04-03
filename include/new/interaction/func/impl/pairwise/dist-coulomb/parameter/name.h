
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Name_H_

#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  enum DistCoulombParameterName {
    dCoulombChargeA=InteractionCommonNumberParameters,
    dCoulombChargeB,
    dCoulombDielectricFac,
    dCoulombStrength,
    dCoulombDualStrength,
    DistCoulombNumberParameters
  };

}

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/build.h"

#endif

