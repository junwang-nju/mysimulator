
#ifndef _System_Interaction_Function_Pairwise_Harmonic_P2P_forE_H_
#define _System_Interaction_Function_Pairwise_Harmonic_P2P_forE_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/harmonic/pre-name.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"

namespace mysimulator {

  void _pre_2_post_for_e_pair_harmonic(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    _post[PairHarmonicPostName::Length] =
      __square_root(_pre[PairHarmonicPreName::DistanceSQ]);
    _status.SetReady4Energy();
  }

}

#endif

