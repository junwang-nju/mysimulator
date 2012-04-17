
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Func_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012/func.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012Cut(const T* post,const Unique64Bit* P,T* func) {
    if(post[LJ1012CutDistanceSQ]>P[LJ1012CutCutRSQ].value<T>()) *func=0;
    else {
      FuncLJ1012(post,P,func);
      (*func)-=P[LJ1012CutVc].value<T>();
      (*func)-=P[LJ1012CutKc].value<T>()
              *(post[LJ1012CutDistance]-P[LJ1012CutCutR].value<T>());
    }
  }

}

#endif

