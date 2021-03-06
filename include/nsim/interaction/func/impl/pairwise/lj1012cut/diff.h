
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Diff_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012Cut(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* diff) {
    if(post[LJ1012CutDistanceSQ]>Value<T>(P[LJ1012CutCutRSQ])) *diff=0;
    else {
      DiffLJ1012(post,P,diff);
      (*diff)-=Value<T>(P[LJ1012CutKc])*post[LJ1012CutIvDistance];
    }
  }

}

#endif

