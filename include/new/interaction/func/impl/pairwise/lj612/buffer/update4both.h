
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/lj612/buffer/update4diff.h"

namespace mysimulator {

  template <typename T>
  void LJ612Update4Both(const T& dsq,const Unique64Bit* P,T* buffer) {
    LJ612Update4Diff(dsq,P,buffer);
  }

}

#endif

