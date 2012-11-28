
#ifndef _System_Interaction_Function_Pairwise_LJ612_P2P_For_G_H_
#define _System_Interaction_Function_Pairwise_LJ612_P2P_For_G_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/lj612/pre-name.h"
#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_g_pair_lj612(
      Array<Float> const& _pre, Array<Float>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    float tmd=1./_pre[PairLJ612PreName::PairDistanceSQ];
    _post[PairLJ612PostName::PairLJ612IvDistanceSQ] = tmd;
    _post[PairLJ612PostName::PairLJ612IvDistance6] = tmd*tmd*tmd;
    _status.SetReady4EnergyGradient();
  }

}

#endif

