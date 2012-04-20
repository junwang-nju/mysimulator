
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Diff_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "interaction/func/impl/pairwise/core12/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void DiffCore12(const T* post,const Unique64Bit* P,T* diff) {
    *diff=P[Core12TwlfEqStrength].value<T>()*post[Core12IvDist12]
                                            *post[Core12IvDistSQ];
  }

}

#endif

