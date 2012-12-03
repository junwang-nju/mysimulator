
#ifndef _System_Interaction_Function_Pairwise_Core12_P2P_forEG_H_
#define _System_Interaction_Function_Pairwise_Core12_P2P_forEG_H_

#include "system/interaction/function/pairwise/core12/_pre_2_post_for_g.h"

namespace mysimulator {

  void _pre_2_post_for_eg_pair_core12(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    _pre_2_post_for_g_pair_core12(_pre,_post,_status,P);
  }

}

#endif

