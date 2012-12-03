
#ifndef _System_Interaction_Function_Pairwise_LJ612_EG_Func_H_
#define _System_Interaction_Function_Pairwise_LJ612_EG_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  void _egfunc_pair_Lj612(
      Array<Double> const& _post, const InteractionParameter& P,
      double* Func, double* Diff) {
    assert((bool)_post);
    assert((bool)P);
    double tmd=_post[PairLJ612PostName::PairLJ612IvDistance6];
    *Func = tmd * ( P[PairLJ612ParameterName::FactorA] * tmd -
                    P[PairLJ612ParameterName::FactorB] );
    *Diff = tmd * _post[PairLJ612PostName::PairLJ612IvDistanceSQ] *
          ( P[PairLJ612ParameterName::DFactorB] -
            P[PairLJ612ParameterName::DFactorA] * tmd);
  }

}

#endif

