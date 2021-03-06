
#ifndef _System_Interaction_Function_Pairwise_Harmonic_E_Func_H_
#define _System_Interaction_Function_Pairwise_Harmonic_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"

namespace mysimulator {

  void _efunc_pair_harmonic(
      Array<Double> const& _post, const InteractionParameter& P, double* Func) {
    assert((bool)_post);
    assert((bool)P);
    double Dd=_post[PairHarmonicPostName::Length] -
             P[PairHarmonicParameterName::EqLength];
    *Func = P[PairHarmonicParameterName::EqStrength]*Dd*Dd;
  }

}

#endif

