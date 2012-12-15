
#ifndef _System_Interaction_Function_Pairwise_LJ612_P2P_for_E_H_
#define _System_Interaction_Function_Pairwise_LJ612_P2P_for_E_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/lj612/pre-name.h"
#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_e_pair_lj612(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    double tmd=1./_pre[PairLJ612PreName::DistanceSQ];
    _post[PairLJ612PostName::IvDistance6] = tmd*tmd*tmd;
    _status.SetReady4Energy();
  }

}

#endif

