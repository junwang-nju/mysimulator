
#ifndef _System_Interaction_Function_Pairwise_Core12_G_Func_H_
#define _System_Interaction_Function_Pairwise_Core12_G_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/pairwise/core12/post-name.h"

namespace mysimulator {

  void _gfunc_pair_core12(
      Array<Float> const& _post,const InteractionParameter& P, float* Diff) {
    assert((bool)_post);
    assert((bool)P);
    *Diff=P[PairCore12ParameterName::TwlfEqStrength] *
          _post[PairCore12PostName::PairCore12IvDistance14];
  }

}

#endif

