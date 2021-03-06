
#ifndef _System_Interaction_Function_Pairwise_Core12_E_Func_H_
#define _System_Interaction_Function_Pairwise_Core12_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/core12/post-name.h"

namespace mysimulator {

  void _efunc_pair_core12(
      Array<Double> const& _post, const InteractionParameter& P, double* Func) {
    assert((bool)_post);
    assert((bool)P);
    *Func=P[PairCore12ParameterName::EqStrength]*
          _post[PairCore12PostName::IvDistance12];
  }

}

#endif

