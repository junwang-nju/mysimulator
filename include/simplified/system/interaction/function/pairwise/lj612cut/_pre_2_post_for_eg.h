
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_P2P_forEG_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_P2P_forEG_H_

#include "system/interaction/function/pairwise/lj612cut/pre-name.h"
#include "system/interaction/function/pairwise/lj612cut/post-name.h"
#include "system/interaction/function/pairwise/lj612/_pre_2_post_for_eg.h"

namespace mysimulator {

  void _pre_2_post_for_eg_pair_lj612cut(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    double tmd=_pre[PairLJ612CutPreName::DistanceSQ];
    _post[PairLJ612CutPostName::DistanceSQ]=tmd;
    if(tmd<P[PairLJ612CutParameterName::CutRSQ]) {
      _pre_2_post_for_eg_pair_lj612(_pre,_post,_status,P);
      _post[PairLJ612CutPostName::Distance]=__square_root(tmd);
      _post[PairLJ612CutPostName::IvDistance] =
        _post[PairLJ612CutPostName::Distance] *
        _post[PairLJ612CutPostName::IvDistanceSQ];
    } else _status.SetReady4EnergyGradient();
  }

}

#endif

