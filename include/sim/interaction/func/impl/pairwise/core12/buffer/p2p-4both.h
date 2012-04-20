
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/core12/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void Core12Pre2Post4Both(const T* pre,const Unique64Bit* P,T* post,
                           bool& flag) {
    Core12Pre2Post4Diff(pre,P,post,flag);
  }

}

#endif

