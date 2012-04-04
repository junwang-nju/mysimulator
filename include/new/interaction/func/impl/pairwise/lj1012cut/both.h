
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Both_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/buffer/name.h"
#include "interaction/func/impl/pairwise/lj1012/both.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012Cut(const T* buf,const Unique64Bit* P,T* func,T* diff) {
    if(buf[LJ1012CutDistanceSQ]>P[LJ1012CutCutRSQ].value<T>()) {
      *func=0;
      *diff=0;
    } else {
      BothLJ1012(buf,P,func,diff);
      (*func)-=P[LJ1012CutVc].value<T>();
      (*func)-=P[LJ1012CutKc].value<T>()
              *(buf[LJ1012CutDistance]-P[LJ1012CutCutR].value<T>());
      (*diff)-=P[LJ1012CutKc].value<T>()*buf[LJ1012CutIvDistance];
    }
  }

}

#endif

