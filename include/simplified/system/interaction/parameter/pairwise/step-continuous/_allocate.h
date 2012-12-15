
#ifndef _System_Interaction_Parameter_Pairwise_StepContinuous_Allocate_H_
#define _System_Interaction_Parameter_Pairwise_StepContinuous_Allocate_H_

#include "system/interaction/parameter/pairwise/step-continuous/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_pair_step_continuous(
      Array<Double>& _FParam, Array<Int>&, Array<InteractionParameter>&) {
    _FParam.allocate(PairStepContinuousParameterName::NumberParameter);
  }

}

#endif

