
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_P2P4Func_H_

#include "intrinsic-type/square-root.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/post-name.h"
#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void HarmonicPre2Post4Func(const T* pre,const Unique64Bit*,T* post,
                             bool& flag) {
    post[HarmonicLength]=sqroot(pre[PairwiseDistanceSQ]);
    flag=true;
  }

}

#endif

