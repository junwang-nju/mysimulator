
#ifndef _System_Interaction_Function_Pairwise_LJ1012_P2P_forG_H_
#define _System_Interaction_Function_Pairwise_LJ1012_P2P_forG_H_

#include "system/interaction/function/pairwise/lj1012/_pre_2_post_for_e.h"

namespace mysimulator {

  void _pre_2_post_for_g_pair_lj1012(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    _pre_2_post_for_e_pair_lj1012(_pre,_post,_status,P);
  }

}

#endif

