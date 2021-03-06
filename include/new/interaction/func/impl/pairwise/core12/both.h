
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Both_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Both_H_

#include "interaction/func/impl/pairwise/core12/func.h"
#include "interaction/func/impl/pairwise/core12/diff.h"

namespace mysimulator {

  template <typename T>
  void BothCore12(const T* post,const Unique64Bit* P,T* func,T* diff) {
    FuncCore12(post,P,func);
    DiffCore12(post,P,diff);
  }

}

#endif

