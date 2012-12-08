
#ifndef _System_Interaction_Function_Pairwise_StepContinuous_EG_Func_H_
#define _System_Interaction_Function_Pairwise_StepContinuous_EG_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/step-continuous/post-name.h"
#include "basic/util/tanh.h"

namespace mysimulator {

  void _egfunc_pair_step_continuous(
      Array<Double> const& _post, const InteractionParameter& P,
      double *Func,double *Diff) {
    assert((bool)_post);
    assert((bool)P);
    double dDSQ=_post[PairStepContinuousPostName::DistanceSQ]-
                P[PairStepContinuousParameterName::RadiusSQ];
    double sDSQ=P[PairStepContinuousParameterName::Sharpness]*dDSQ;
    double TH=__tanh(sDSQ);
    *Func=P[PairStepContinuousParameterName::HalfDepth]*(1+TH);
    *Diff=P[PairStepContinuousParameterName::DSProduct]*(1-TH*TH);
  }

}

#endif

