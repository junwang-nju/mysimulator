
#ifndef _System_Interaction_Function_Pairwise_LJ1012_P2P_forE_H_
#define _System_Interaction_Function_Pairwise_LJ1012_P2P_forE_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/lj1012/pre-name.h"
#include "system/interaction/function/pairwise/lj1012/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_e_pair_lj1012(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    double tmd=1./_pre[PairLJ1012PreName::PairDistanceSQ];
    _post[PairLJ1012PostName::PairLJ1012IvDistanceSQ]=tmd;
    double tmd1=tmd*tmd;
    tmd1*=tmd1;
    _post[PairLJ1012PostName::PairLJ1012IvDistance10]=tmd1*tmd;
    _status.SetReady4Energy();
  }

}

#endif

