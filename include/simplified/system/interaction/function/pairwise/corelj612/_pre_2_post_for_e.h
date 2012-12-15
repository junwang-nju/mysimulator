
#ifndef _System_Interaction_Function_Pairwise_CoreLJ612_P2P_forE_H_
#define _System_Interaction_Function_Pairwise_CoreLJ612_P2P_forE_H_

#include "system/interaction/function/pairwise/corelj612/pre-name.h"
#include "system/interaction/function/pairwise/corelj612/post-name.h"
#include "system/interaction/function/pairwise/lj612/_pre_2_post_for_e.h"

namespace mysimulator {

  void _pre_2_post_for_e_pair_corelj612(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status, const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    double tmd=_pre[PairCoreLJ612PreName::DistanceSQ];
    _post[PairCoreLJ612PostName::DistanceSQ]=tmd;
    if(tmd<P[PairCoreLJ612ParameterName::EqRadiusSQ])
      _pre_2_post_for_e_pair_lj612(_pre,_post,_status,P);
    else _status.SetReady4EnergyGradient();
  }

}

#endif

