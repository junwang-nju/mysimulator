
#ifndef _System_Interaction_Function_Pairwise_LJ1012_EG_Func_H_
#define _System_Interaction_Function_Pairwise_LJ1012_EG_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/lj1012/post-name.h"

namespace mysimulator {

  void _egfunc_pair_lj1012(
      Array<Double> const& _post,const InteractionParameter& P,
      double *Func, double *Diff) {
    assert((bool)_post);
    assert((bool)P);
    double tmd1=_post[PairLJ1012PostName::PairLJ1012IvDistanceSQ];
    double tmd2=_post[PairLJ1012PostName::PairLJ1012IvDistance10];
    *Func=tmd2 * ( P[PairLJ1012ParameterName::FactorA] * tmd1 -
                   P[PairLJ1012ParameterName::FactorB] );
    *Diff=tmd2*tmd1*( P[PairLJ1012ParameterName::DFactorB] -
                      P[PairLJ1012ParameterName::DFactorA] * tmd1 );
  }

}

#endif

