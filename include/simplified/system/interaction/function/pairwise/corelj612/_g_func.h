
#ifndef _System_Interaction_Function_Pairwise_CoreLJ612_G_Func_H_
#define _System_Interaction_Function_Pairwise_CoreLJ612_G_Func_H_

#include "system/interaction/function/pairwise/corelj612/post-name.h"
#include "system/interaction/function/pairwise/lj612/_g_func.h"

namespace mysimulator {

  void _gfunc_pair_corelj612(
      Array<Double> const& _post,const InteractionParameter& P,double *Diff) {
    assert((bool)_post);
    assert((bool)P);
    if(_post[PairCoreLJ612PostName::DistanceSQ] >
       P[PairCoreLJ612ParameterName::EqRadiusSQ]) *Diff=0;
    else _gfunc_pair_lj612(_post,P,Diff);
  }

}

#endif

