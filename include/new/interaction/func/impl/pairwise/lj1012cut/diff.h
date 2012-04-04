
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Diff_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/name.h"
#include "interaction/func/impl/pairwise/lj1012/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012Cut(const T* buf,const Unique64Bit* P,T* diff) {
    if(buf[LJ1012CutDistanceSQ]>P[LJ1012CutCutRSQ].value<T>()) *diff=0;
    else {
      DiffLJ1012(buf,P,diff);
      (*diff)-=P[LJ1012CutKc].value<T>()*buf[LJ1012CutIvDistance];
    }
  }

}

#endif

