
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_G_Func_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_G_Func_H_

#include "system/interaction/function/pairwise/lj612cut/post-name.h"
#include "system/interaction/function/pairwise/lj612/_g_func.h"

namespace mysimulator {

  void _gfunc_pair_lj612cut(
      Array<Double> const& _post, const InteractionParameter& P, double* Diff) {
    assert((bool)_post);
    assert((bool)P);
    if(_post[PairLJ612CutPostName::DistanceSQ] >
       P[PairLJ612CutParameterName::CutRSQ]) *Diff=0;
    else {
      _gfunc_pair_lj612(_post,P,Diff);
      *Diff-=P[PairLJ612CutParameterName::Kc]*
             _post[PairLJ612CutPostName::IvDistance];
    }
  }

}

#endif

