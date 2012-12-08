
#ifndef _System_Interaction_Function_Pairwise_StepContinuous_E_Func_H_
#define _System_Interaction_Function_Pairwise_StepContinuous_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/step-continuous/post-name.h"
#include "basic/util/tanh.h"

namespace mysimulator {

  void _efunc_pair_step_continuous(
      Array<Double> const& _post, const InteractionParameter& P, double *Func) {
    assert((bool)_post);
    assert((bool)P);
    double dDSQ=_post[PairStepContinuousPostName::DistanceSQ]-
                P[PairStepContinuousParameterName::RadiusSQ];
    double sDSQ=P[PairStepContinuousParameterName::Sharpness]*dDSQ;
    *Func=P[PairStepContinuousParameterName::HalfDepth]*(1+__tanh(sDSQ));
  }

}

#endif

