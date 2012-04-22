
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Both_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/both.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612Cut(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P, T* func,T* diff) {
    if(post[LJ612CutDistanceSQ]>P[LJ612CutCutRSQ].value<T>()) {
      *func=0;
      *diff=0;
    } else {
      BothLJ612(post,P,func,diff);
      (*func)-=P[LJ612CutVc].value<T>();
      (*func)-=P[LJ612CutKc].value<T>()
              *(post[LJ612CutDistance]-P[LJ612CutCutR].value<T>());
      (*diff)-=P[LJ612CutKc].value<T>()*post[LJ612CutIvDistance];
    }
  }

}

#endif

