
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_P2P4Diff_H_

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/p2p-4func.h"

namespace mysimulator {

  template <typename T>
  void DistCoulombPre2Post4Diff(const T* pre, const Unique64Bit* P, T* post,
                                bool& flag) {
    DistCoulombOre2Post4func(pre,P,post,flag);
  }

}

#endif

