
#ifndef _System_Interaction_Parameter_Pairwise_CoreLJ612_Allocate_H_
#define _System_Interaction_Parameter_Pairwise_CoreLJ612_Allocate_H_

#include "system/interaction/parameter/pairwise/corelj612/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_pair_corelj612(
      Array<Double>& _FParam,Array<Int>&,Array<InteractionParameter>&) {
    _FParam.allocate(PairCoreLJ612ParameterName::NumberParameter);
  }

}

#endif

