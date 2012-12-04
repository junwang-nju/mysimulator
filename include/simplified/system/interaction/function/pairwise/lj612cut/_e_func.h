
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_E_Func_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_E_Func_H_

#include "system/interaction/function/pairwise/lj612cut/post-name.h"
#include "system/interaction/function/pairwise/lj612/_e_func.h"

namespace mysimulator {

  void _efunc_pair_lj612cut(
      Array<Double> const& _post, const InteractionParameter& P, double* Func) {
    assert((bool)_post);
    assert((bool)P);
    if(_post[PairLJ612CutPostName::PairLJ612CutDistanceSQ]>
       P[PairLJ612CutParameterName::CutRSQ])  *Func=0;
    else {
      _efunc_pair_lj612(_post,P,Func);
      *Func-=P[PairLJ612CutParameterName::Vc];
      *Func-=P[PairLJ612CutParameterName::Kc]*
             (_post[PairLJ612CutPostName::PairLJ612CutDistance]-
              P[PairLJ612CutParameterName::CutR]);
    }

  }

}

#endif

