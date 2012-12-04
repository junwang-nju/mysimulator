
#ifndef _System_Interaction_Function_Pairwise_LJ1012_G_Func_H_
#define _System_Interaction_Function_Pairwise_LJ1012_G_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/lj1012/post-name.h"

namespace mysimulator {

  void _gfunc_pair_lj1012(
      Array<Double> const& _post, const InteractionParameter& P,double* Diff) {
    assert((bool)_post);
    assert((bool)P);
    double tmd=_post[PairLJ1012PostName::IvDistanceSQ];
    *Diff=_post[PairLJ1012PostName::IvDistance10] * tmd *
          ( P[PairLJ1012ParameterName::DFactorB] -
            P[PairLJ1012ParameterName::DFactorA] *tmd );
  }

}

#endif

