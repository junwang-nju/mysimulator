
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Both_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/name.h"
#include "interaction/func/impl/pairwise/lj612/both.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612Cut(const T* buf, const Unique64Bit* P, T* func,T* diff) {
    if(buf[LJ612CutDistanceSQ]>P[LJ612CutCutRSQ].value<T>()) {
      *func=0;
      *diff=0;
    } else {
      BothLJ612(buf,P,diff);
      (*func)-=P[LJ612CutVc].value<T>();
      (*func)-=P[LJ612CutKc].value<T>()
              *(buf[LJ612CutDistance]-P[LJ612CutCutR].value<T>());
      (*diff)-=P[LJ612CutKc].value<T>()*buf[LJ612CutIvDistance];
    }
  }

}

#endif

