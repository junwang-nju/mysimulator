
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612cut/buffer/name.h"
#include "interaction/func/impl/pairwise/lj612/func.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612Cut(const T* buf,const Unique64Bit* P,T* func) {
    if(buf[LJ612CutDistanceSQ]>P[LJ612CutCutRSQ].value<T>())  *func=0;
    else {
      FuncLJ612(buf,P,func);
      (*func)-=P[LJ612CutVc].value<T>();
      (*func)-=P[LJ612CutKc].value<T>()
              *(buf[LJ612CutDistance]-P[LJ612CutCutR].value<T>());
    }
  }

}

#endif

