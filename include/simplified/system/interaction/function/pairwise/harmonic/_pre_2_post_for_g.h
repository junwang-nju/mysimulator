
#ifndef _System_Interaction_Function_Pairwise_Harmonic_P2P_forG_H_
#define _System_Interaction_Function_Pairwise_Harmonic_P2P_forG_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/harmonic/pre-name.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"
#include "array/interface.h"

namespace mysimulator {

  void _pre_2_post_for_g_pair_harmonic(
      Array<Double> const& _pre, Array<Double>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    _post[PairHarmonicPostName::PairHarmonicIvLength] =
      1./__square_root(_pre[PairHarmonicPreName::PairDistanceSQ]);
    _status.SetReady4Gradient();
  }

}

#endif

