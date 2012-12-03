
#ifndef _System_Interaction_Function_Pairwise_LJ612_G_Func_H_
#define _System_Interaction_Function_Pairwise_LJ612_G_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/lj612/post-name.h"

namespace mysimulator {

  void _gfunc_pair_lj612(
      Array<Double> const& _post, const InteractionParameter& P, double *Diff) {
    assert((bool)_post);
    assert((bool)P);
    double tmd=_post[PairLJ612PostName::PairLJ612IvDistance6];
    *Diff = tmd * _post[PairLJ612PostName::PairLJ612IvDistanceSQ] *
          ( P[PairLJ612ParameterName::DFactorB] -
            P[PairLJ612ParameterName::DFactorA] * tmd);
  }

}

#endif

