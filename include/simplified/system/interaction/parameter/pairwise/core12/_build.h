
#ifndef _System_Interaction_Parameter_Pairwise_Core12_Build_H_
#define _System_Interaction_Parameter_Pairwise_Core12_Build_H_

#include "array/interface.h"
#include "system/interaction/parameter/pairwise/core12/name.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_pair_core12(
      Array<Double>& _FParam,Array<Int>&, Array<InteractionParameter>&) {
    assert((bool)_FParam);
    assert(_FParam.size()>=PairCore12ParameterName::NumberParameter);
    _FParam[PairCore12ParameterName::TwlfEqStrength] =
      12 * _FParam[PairCore12ParameterName::EqStrength];
  }

}

#endif

