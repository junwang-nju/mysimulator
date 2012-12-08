
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_EG_Func_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_EG_Func_H_

#include "system/interaction/function/pairwise/lj612cut/post-name.h"
#include "system/interaction/function/pairwise/lj612/_eg_func.h"

namespace mysimulator {

  void _egfunc_pair_lj612cut(
      Array<Double> const& _post, const InteractionParameter& P,
      double* Func, double* Diff) {
    assert((bool)_post);
    assert((bool)P);
    if(_post[PairLJ612CutPostName::DistanceSQ] >
       P[PairLJ612CutParameterName::CutRSQ]) { *Func=0; *Diff=0; }
    else {
      _egfunc_pair_lj612(_post,P,Func,Diff);
      *Func-=P[PairLJ612CutParameterName::Vc];
      *Func-=P[PairLJ612CutParameterName::Kc]*
             (_post[PairLJ612CutPostName::Distance]-
              P[PairLJ612CutParameterName::CutR]);
      *Diff-=P[PairLJ612CutParameterName::Kc]*
             _post[PairLJ612CutPostName::IvDistance];
    }
  }

}

#endif

