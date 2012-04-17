
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Diff_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612Cut(const T* post,const Unique64Bit* P,T* diff) {
    if(post[LJ612CutDistanceSQ]>P[LJ612CutCutRSQ].value<T>())  *diff=0;
    else {
      DiffLJ612(post,P,diff);
      (*diff)-=P[LJ612CutKc].value<T>()*post[LJ612CutIvDistance];
    }
  }

}

#endif

