
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Diff_H_

#include "interaction/func/impl/pairwise/coulomb/buffer/post-name.h"
#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void CoulombPre2Post4Diff(const T* pre, const Unique64Bit*, T* post,
                            bool& flag) {
    T tmd=1./pre[PairwiseDistanceSQ];
    post[CoulombIvDistanceSQ]=tmd;
    post[CoulombIvDistance]=sqroot(tmd);
    flag=false;
  }

}

#endif

