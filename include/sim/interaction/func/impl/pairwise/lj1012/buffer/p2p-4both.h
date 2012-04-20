
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4func.h"

namespace mysimulator {

  template <typename T>
  void LJ1012Pre2Post4Both(const T* pre,const Unique64Bit* P, T* post,
                           bool& flag) {
    LJ1012Pre2Post4Func(pre,P,post,flag);
  }

}

#endif
