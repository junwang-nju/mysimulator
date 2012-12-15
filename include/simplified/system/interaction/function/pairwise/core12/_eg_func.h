
#ifndef _System_Interaction_Function_Pairwise_Core12_EG_Func_H_
#define _System_Interaction_Function_Pairwise_Core12_EG_Func_H_

#include "system/interaction/function/pairwise/core12/_e_func.h"
#include "system/interaction/function/pairwise/core12/_g_func.h"

namespace mysimulator {

  void _egfunc_pair_core12(
      Array<Double> const& _post, const InteractionParameter& P,
      double* Func, double* Diff) {
    _efunc_pair_core12(_post,P,Func);
    _gfunc_pair_core12(_post,P,Diff);
  }

}

#endif

