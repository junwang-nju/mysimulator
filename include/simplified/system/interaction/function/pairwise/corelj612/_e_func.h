
#ifndef _System_Interaction_Function_Pairwise_CoreLJ612_E_Func_H_
#define _System_Interaction_Function_Pairwise_CoreLJ612_E_Func_H_

#include "system/interaction/function/pairwise/corelj612/post-name.h"
#include "system/interaction/function/pairwise/lj612/_e_func.h"

namespace mysimulator {

  void _efunc_pair_corelj612(
      Array<Double> const& _post,const InteractionParameter& P,double *Func) {
    assert((bool)_post);
    assert((bool)P);
    if(_post[PairCoreLJ612PostName::DistanceSQ] >
       P[PairCoreLJ612ParameterName::EqRadiusSQ]) *Func=0;
    else {
      _efunc_pair_lj612(_post,P,Func);
      *Func+=P[PairCoreLJ612ParameterName::EqEnergyDepth];
    }
  }

}

#endif

