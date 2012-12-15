
#ifndef _System_Interaction_Parameter_Pairwise_Core12_Allocate_H_
#define _System_Interaction_Parameter_Pairwise_Core12_Allocate_H_

#include "array/interface.h"
#include "system/interaction/parameter/pairwise/core12/name.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_pair_core12(
      Array<Double>& _FParam, Array<Int>&, Array<InteractionParameter>&) {
    _FParam.allocate(PairCore12ParameterName::NumberParameter);
  }

}

#endif

