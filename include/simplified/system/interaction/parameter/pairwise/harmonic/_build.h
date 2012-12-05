
#ifndef _System_Interaction_Parameter_Pairwise_Harmonic_Build_H_
#define _System_Interaction_Parameter_Pairwise_Harmonic_Build_H_

#include "system/interaction/parameter/pairwise/harmonic/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_pair_harmonic(
      Array<Double>& _FParam,Array<Int>&,Array<InteractionParameter>&) {
    assert((bool)_FParam);
    assert(_FParam.size()>=PairHarmonicParameterName::NumberParameter);
    _FParam[PairHarmonicParameterName::DualEqStrength] =
      2* _FParam[PairHarmonicParameterName::EqStrength];
  }

}

#endif

