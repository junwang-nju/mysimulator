
#ifndef _System_Interaction_Function_Pairwise_Harmonic_G_Func_H_
#define _System_Interaction_Function_Pairwise_Harmonic_G_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"

namespace mysimulator {

  void _gfunc_pair_harmonic(
      Array<Float> const& _post, const InteractionParameter& P, float* Diff) {
    assert((bool)_post);
    assert((bool)P);
    float Dd=1.-P[PairHarmonicParameterName::EqLength]*
                _post[PairHarmonicPostName::PairHarmonicIvLength];
    *Diff=P[PairHarmonicParameterName::DualEqStrength]*Dd;
  }

}

#endif
