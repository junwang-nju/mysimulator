
#ifndef _System_Interaction_Function_Pairwise_StepContinuous_Allocate_H_
#define _System_Interaction_Function_Pairwise_StepContinuous_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/step-continuous/pre-name.h"
#include "system/interaction/function/pairwise/step-continuous/post-name.h"
#include "system/interaction/function/pairwise/step-continuous/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_pair_step_continuous(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairStepContinuousPreName::NumberPre);
    _post.allocate(PairStepContinuousPostName::NumberPost);
    _vec.allocate(PairStepContinuousVecName::NumberVec,DIM);
  }

}

#endif

