
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Both_H_

#include "interaction/func/impl/pairwise/lj1012/func.h"
#include "interaction/func/impl/pairwise/lj1012/diff.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012(const T* buf,const Unique64Bit* P,T* func,T* diff) {
    FuncLJ1012(buf,P,func);
    DiffLJ1012(buf,P,diff);
  }

}

#endif

