
#ifndef _System_Interaction_Parameter_Pairwise_Harmonic_Allocate_H_
#define _System_Interaction_Parameter_Pairwise_Harmonic_Allocate_H_

#include "array/interface.h"
#include "system/interaction/parameter/pairwise/harmonic/name.h"

namespace mysimulator {

  void _allocate_pair_harmonic(Array<Double>& _FParam, Array<Int>>& _IParam) {
    _FParam.allocate(PairHarmonicParameterName::NumberParameter);
  }

}

#endif

