
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/func.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612Cut(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func) {
    if(post[LJ612CutDistanceSQ]>Value<T>(P[LJ612CutCutRSQ]))  *func=0;
    else {
      FuncLJ612(post,P,func);
      (*func)-=Value<T>(P[LJ612CutVc]);
      (*func)-=Value<T>(P[LJ612CutKc])
              *(post[LJ612CutDistance]-Value<T>(P[LJ612CutCutR]));
    }
  }

}

#endif

