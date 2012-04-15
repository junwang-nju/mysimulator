
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_Update4Diff_H_

#include "interaction/func/impl/pairwise/lj1012/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void LJ1012Update4Diff(const T* dsq,const Unique64Bit* P,T* buffer) {
    LJ1012Update4Func(dsq,P,buffer);
  }

}

#endif

