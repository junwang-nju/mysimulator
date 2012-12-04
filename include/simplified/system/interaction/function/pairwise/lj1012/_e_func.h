
#ifndef _System_Interaction_Function_Pairwise_LJ1012_E_Func_H_
#define _System_Interaction_Function_Pairwise_LJ1012_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/lj1012/post-name.h"

namespace mysimulator {

  void _efunc_pair_lj1012(
      Array<Double> const& _post, const InteractionParameter& P, double* Func) {
    assert((bool)_post);
    assert((bool)P);
    *Func=_post[PairLJ1012PostName::IvDistance10] *
          ( P[PairLJ1012ParameterName::FactorA] * 
            _post[PairLJ1012PostName::IvDistanceSQ] -
            P[PairLJ1012ParameterName::FactorB] );
  }

}

#endif

