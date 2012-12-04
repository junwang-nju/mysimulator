
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
    double tmd=_pre[PairLJ612CutPreName::PairDistanceSQ];
    _post[PairLJ612CutPostName::PairLJ612CutDistanceSQ]=tmd;
    if(tmd<P[PairLJ612CutParameterName::CutRSQ]) {
      _pre_2_post_for_eg_pair_lj612(_pre,_post,_status,P);
      _post[PairLJ612CutPostName::PairLJ612CutDistance]=__square_root(tmd);
      _post[PairLJ612CutPostName::PairLJ612CutIvDistance] =
        _post[PairLJ612CutPostName::PairLJ612CutDistance] *
        _post[PairLJ612CutPostName::PairLJ612CutIvDistanceSQ];
    } else _status.SetReady4EnergyGradient();
  }

}

#endif

