
#ifndef _System_Interaction_Function_Pairwise_Harmonic_P2P_forEG_H_
#define _System_Interaction_Function_Pairwise_Harmonic_P2P_forEG_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/harmonic/pre-name.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"
#include "array/interface.h"

namespace mysimulator {

  void _pre_2_post_for_eg_pair_harmonic(
      Array<Float> const& _pre, Array<Float>& _post,
      InteractionFuncDataState& _status,const InteractionParameter& P) {
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)P);
    float tmd=__square_root(_pre[PairHarmonicPreName::PairDistanceSQ]);
    _post[PairHarmonicPostName::PairHarmonicLength] = tmd;
    _post[PairHarmonicPostName::PairHarmonicIvLength] = 1./tmd;
    _status.SetReady4EnergyGradient();
  }

}

#endif

