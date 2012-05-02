
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Func_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012/func.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012Cut(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func) {
    if(post[LJ1012CutDistanceSQ]>Value<T>(P[LJ1012CutCutRSQ])) *func=0;
    else {
      FuncLJ1012(post,P,func);
      (*func)-=Value<T>(P[LJ1012CutVc]);
      (*func)-=Value<T>(P[LJ1012CutKc])
              *(post[LJ1012CutDistance]-Value<T>(P[LJ1012CutCutR]));
    }
  }

}

#endif

