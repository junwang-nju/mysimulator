
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Parameter_Name_H_

#include "interaction/func/impl/pairwise/common/parameter/name.h"

namespace mysimulator {

  enum HarmonicParameterName {
    HarmonicEqLength=PairwiseCommonNumberParameters,
    HarmonicEqStrength,
    HarmonicDualEqStrength,
    HarmonicNumberParameters
  };

}

#include "interaction/func/impl/pairwise/harmonic/parameter/build.h"

#endif

