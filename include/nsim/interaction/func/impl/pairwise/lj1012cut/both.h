
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Both_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012/both.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012Cut(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func,T* diff) {
    if(post[LJ1012CutDistanceSQ]>Value<T>(P[LJ1012CutCutRSQ])) {
      *func=0;
      *diff=0;
    } else {
      BothLJ1012(post,P,func,diff);
      (*func)-=Value<T>(P[LJ1012CutVc]);
      (*func)-=Value<T>(P[LJ1012CutKc])
              *(post[LJ1012CutDistance]-Value<T>(P[LJ1012CutCutR]));
      (*diff)-=Value<T>(P[LJ1012CutKc])*post[LJ1012CutIvDistance];
    }
  }

}

#endif

