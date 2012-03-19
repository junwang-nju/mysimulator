
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/lj612cut/buffer/name.h"
#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/update4both.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ612CutUpdate4Both(const T& dsq, const Unique64Bit* P, T* buffer) {
    buffer[LJ612CutDistanceSQ]=dsq;
    if(dsq<P[LJ612CutCutRSQ].value<T>()) {
      LJ612Update4Both(dsq,P,buffer);
      buffer[LJ612CutDistance]=sqroot(dsq);
      buffer[LJ612CutIvDistance]=buffer[LJ612CutDistance]
                                *buffer[LJ612CutIvDistanceSQ];
    }
  }

}

#endif

