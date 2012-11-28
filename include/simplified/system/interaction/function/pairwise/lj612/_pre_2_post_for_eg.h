
#ifndef _System_Interaction_Function_Pairwise_LJ612_P2P_For_EG_H_
#define _System_Interaction_Function_Pairwise_LJ612_P2P_For_EG_H_

#include "system/interaction/function/pairwise/lj612/_pre_2_post_for_g.h"

namespace mysimulator {

  void _pre_2_post_for_eg_pair_lj612(
      Array<Float> const& _pre, Array<Float>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    _pre_2_post_for_g_pair_lj612(_pre,_post,_status,P);
  }

}

#endif

