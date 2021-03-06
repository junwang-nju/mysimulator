
#ifndef _System_Interaction_Function_Pairwise_LJ612_E_Func_H_
#define _System_Interaction_Function_Pairwise_LJ612_E_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  void _efunc_pair_lj612(
      Array<Double> const& _post, const InteractionParameter& P, double* Func) {
    assert((bool)_post);
    assert((bool)P);
    double tmd=_post[PairLJ612PostName::IvDistance6];
    *Func = tmd*(P[PairLJ612ParameterName::FactorA] * tmd -
                 P[PairLJ612ParameterName::FactorB]);
  }

}

#endif

