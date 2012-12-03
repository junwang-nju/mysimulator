
#ifndef _System_Interaction_Function_Pairwise_Harmonic_EG_Func_H_
#define _System_Interaction_Function_Pairwise_Harmonic_EG_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"

namespace mysimulator {

  void _egfunc_pair_harmonic(
      Array<Double> const& _post, const InteractionParameter& P,
      double* Func, double* Diff) {
    assert((bool)_post);
    assert((bool)P);
    double Dd=_post[PairHarmonicPostName::PairHarmonicLength] -
              P[PairHarmonicParameterName::EqLength];
    double tmd=P[PairHarmonicParameterName::EqStrength]*Dd;
    *Func=tmd*Dd;
    *Diff=(tmd+tmd)*_post[PairHarmonicPostName::PairHarmonicIvLength];
  }

}

#endif

