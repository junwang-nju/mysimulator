
#ifndef _System_Interaction_Function_Pairwise_StepContinuous_P2P_forEG_H_
#define _System_Interaction_Function_Pairwise_StepContinuous_P2P_forEG_H_

#include "system/interaction/function/pairwise/step-continuous/_pre_2_post_for_e.h"

namespace mysimulator {

  void _pre_2_post_for_eg_pair_step_continuous(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    _pre_2_post_for_e_pair_step_continuous(_pre,_post,_status,P);
  }

}

#endif

