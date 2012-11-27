
#ifndef _System_Interaction_Function_Pairwise_Harmonic_E_Func_H_
#define _System_Interaction_Function_Pairwise_Harmonic_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/parameter/pairwise/harmonic/name.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"

namespace mysimulator {

  void _efunc_pair_harmonic(
      Array<Float> const& _post, const InteractionParameter& P, float* Func) {
    assert((bool)_post);
    assert((bool)P);
    float Dd=_post[PairHarmonicPostName::PairHarmonicLength] -
             P[PairHarmonicParameterName::EqLength];
    *Func = P[PairHarmonicParameterName::EqStrength]*Dd*Dd;
  }

}

#endif

