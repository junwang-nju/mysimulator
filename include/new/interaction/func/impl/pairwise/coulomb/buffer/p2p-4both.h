
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/coulomb/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void CoulombPre2Post4Both(const T* pre, const Unique64Bit* P,T* post,
                            bool& flag) {
    CoulombPre2Post4Diff(pre,P,post,flag);
  }

}

#endif

