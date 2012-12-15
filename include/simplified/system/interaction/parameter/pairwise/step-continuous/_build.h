
#ifndef _System_Interaction_Parameter_Pairwise_StepContinuous_Build_H_
#define _System_Interaction_Parameter_Pairwise_StepContinuous_Build_H_

#include "system/interaction/parameter/pairwise/step-continuous/name.h"
#include "array/interface.h"
#include "basic/util/square.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_pair_step_continuous(
      Array<Double>& _FParam, Array<Int>&, Array<InteractionParameter>&) {
    assert((bool)_FParam);
    assert(_FParam.size()>=PairStepContinuousParameterName::NumberParameter);
    _FParam[PairStepContinuousParameterName::HalfDepth] =
      0.5 * _FParam[PairStepContinuousParameterName::Depth];
    _FParam[PairStepContinuousParameterName::RadiusSQ] =
      __square(_FParam[PairStepContinuousParameterName::Radius]);
    if(_FParam[PairStepContinuousParameterName::Sharpness] *
       _FParam[PairStepContinuousParameterName::Radius] < 2 ) {
      _FParam[PairStepContinuousParameterName::Sharpness] =
        10./_FParam[PairStepContinuousParameterName::Radius];
    }
    _FParam[PairStepContinuousParameterName::DSProduct] =
      _FParam[PairStepContinuousParameterName::Depth] *
      _FParam[PairStepContinuousParameterName::Sharpness];
  }

}

#endif

