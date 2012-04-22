
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Name_H_

namespace mysimulator {

  enum DistCoulombParameterName {
    DistCoulombChargeA=0,
    DistCoulombChargeB,
    DistCoulombDielectricFac,
    DistCoulombStrength,
    DistCoulombDualStrength,
    DistCoulombNumberParameters
  };

}

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/build.h"

#endif

