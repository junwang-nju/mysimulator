
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/lj1012cut/buffer/name.h"
#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/update4both.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ1012CutUpdate4Both(const T& dsq,const Unique64Bit* P,T* buffer) {
    buffer[LJ1012CutDistanceSQ]=dsq;
    if(dsq<P[LJ1012CutCutRSQ].value<T>()) {
      LJ1012Update4Both(dsq,P,buffer);
      buffer[LJ1012CutDistance]=sqroot(dsq);
      buffer[LJ1012CutIvDistance]=buffer[LJ1012CutIvDistanceSQ]
                                 *buffer[LJ1012CutDistance];
    }
  }

}

#endif

