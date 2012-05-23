
#ifndef _Interaction_Parameter_DistCoulomb_Name_H_
#define _Interaction_Parameter_DistCoulomb_Name_H_

#include "interaction-parameter/coulomb/name.h"

namespace mysimulator {

  enum DistDielCoulombParameterName {
    DistDielCoulombChargeA = CoulombChargeA,
    DistDielCoulombChargeB = CoulombChargeB,
    DistDielCoulombDielectricFactor = CoulombDielectric,
    DistDielCoulombStrength = CoulombStrength,
    DistDielCoulombDualStrength = CoulombNumberParameter,
    DistDielCoulombNumberParameter
  };

}

#endif

