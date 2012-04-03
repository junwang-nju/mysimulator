
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/core12/buffer/update4diff.h"

namespace mysimulator {

  template <typename T>
  void Core12Update4Both(const T& dsq,const Unique64Bit* P,T* buffer) {
    Core12Update4Diff(dsq,P,buff);
  }

}

#endif

