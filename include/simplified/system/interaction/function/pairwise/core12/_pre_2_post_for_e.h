
#ifndef _System_Interaction_Function_Pairwise_Core12_P2P_forE_H_
#define _System_Interaction_Function_Pairwise_Core12_P2P_forE_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/core12/pre-name.h"
#include "system/interaction/function/pairwise/core12/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_e_pair_core12(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    double tmd=1./_pre[PairCore12PreName::DistanceSQ];
    tmd*=tmd;
    _post[PairCore12PostName::IvDistance12]=tmd*tmd*tmd;
    _status.SetReady4Energy();
  }

}

#endif

